#!/usr/bin/env python3
"""Reviewed config preparation: preflight and configure under the legacy EX lock.

Install this source and its checker outside all candidate roots only after
independent review. This launcher does not approve a graph or perform a build.
"""
import argparse
import fcntl
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import types

LEGACY_LOCK = Path('/tmp/pso-decomp-full-build.lock')
DOL_SHA1 = '0d85744b51d7379efb025a943d0cd5aaae2191a3'


def load_checker(path, expected, roots):
    p=Path(path)
    if not p.is_absolute() or p.is_symlink() or p.resolve()!=p or not p.is_file() or any(p.is_relative_to(Path(x).resolve()) for x in roots):
        raise ValueError('invalid checker path')
    raw=p.read_bytes()
    if hashlib.sha256(raw).hexdigest()!=expected: raise ValueError('stale checker')
    module=types.ModuleType('_reviewed_config_delta');module.__file__=str(p)
    exec(compile(raw,str(p),'exec'),module.__dict__)
    return module


def original_tree_sha256(root):
    base=root/'orig/GPOE8P/files'
    if base.is_symlink() or base.resolve()!=base or not base.is_dir(): raise ValueError('missing original tree')
    entries=[]
    for parent, dirs, files in os.walk(base,followlinks=False):
        for name in sorted(dirs+files):
            item=Path(parent)/name
            if item.is_symlink(): raise ValueError('original input symlink')
            if item.is_file(): entries.append([str(item.relative_to(base)),hashlib.sha256(item.read_bytes()).hexdigest(),item.stat().st_mode & 0o777])
            elif not item.is_dir(): raise ValueError('invalid original input')
    if not entries: raise ValueError('empty original tree')
    return hashlib.sha256(json.dumps(sorted(entries),separators=(',',':')).encode()).hexdigest()


def validate_tracked_python(checker, root):
    # Do not rely on Git's stat cache or assume-unchanged bits for import closure.
    records=checker.git_bytes(root,'ls-files','-s','-z','--','*.py','tools').split(b'\0')
    for record in records:
        if not record: continue
        metadata,raw_path=record.split(b'\t',1)
        mode,blob,stage=metadata.split(b' ')
        if stage != b'0' or mode not in (b'100644',b'100755'): raise ValueError('invalid import closure mode')
        path=root/os.fsdecode(raw_path)
        if path.is_symlink() or path.resolve()!=path or not path.is_file() or not path.resolve().is_relative_to(root): raise ValueError('invalid import closure path')
        raw=path.read_bytes()
        oid=hashlib.sha1(b'blob '+str(len(raw)).encode()+b'\0'+raw).hexdigest().encode()
        if oid != blob or bool(path.stat().st_mode & 0o111) != (mode==b'100755'): raise ValueError('import closure differs')


def validate_checkout(checker, root, expected_commit, expected_tree, original_sha256, original_tree_hash, *, fresh):
    if not root.is_absolute() or root.resolve()!=root or not root.is_dir(): raise ValueError('invalid root')
    if checker.git_bytes(root,'rev-parse','HEAD').strip().decode()!=expected_commit or checker.git_bytes(root,'rev-parse','HEAD^{tree}').strip().decode()!=expected_tree: raise ValueError('stale checkout')
    if checker.git_bytes(root,'status','--porcelain','--untracked-files=all'): raise ValueError('dirty checkout')
    validate_tracked_python(checker,root)
    if (root/'.venv').exists() or (root/'venv').exists(): raise ValueError('candidate interpreter')
    if fresh and any((root/name).exists() for name in ('build','build.ninja','objdiff.json','compile_commands.json','.ninja_log','.ninja_deps')): raise ValueError('reused generated state')
    # Ignored Python startup/module files can still influence configure imports.
    ignored=checker.git_bytes(root,'ls-files','--others','--ignored','--exclude-standard','-z').split(b'\0')
    for raw in ignored:
        if raw and (raw.endswith((b'.py',b'.pyc',b'.pth',b'.so')) or b'__pycache__/' in raw): raise ValueError('untracked Python import')
    _, blob=checker.blob(root,expected_commit)
    config=root/'configure.py'
    if config.is_symlink() or config.resolve()!=config or config.read_bytes()!=blob: raise ValueError('configuration worktree differs')
    dol=root/'orig/GPOE8P/files/PsoV3.dol'
    if dol.is_symlink() or dol.resolve()!=dol or not dol.is_file(): raise ValueError('missing original DOL')
    raw=dol.read_bytes()
    if original_tree_sha256(root) != original_tree_hash: raise ValueError('stale original tree')
    if hashlib.sha1(raw).hexdigest()!=DOL_SHA1 or hashlib.sha256(raw).hexdigest()!=original_sha256: raise ValueError('stale original DOL')


def prepare(request, checker_path, checker_sha256, *, lock_path=LEGACY_LOCK):
    if set(request) != {'packet','repo','role','target','candidate','tree','prs','commits','receipt','original_sha256','original_tree_sha256','plan_receipt'}: raise ValueError('invalid preparation request')
    root=Path(request['repo']); receipt=Path(request['receipt'])
    if not receipt.is_absolute() or receipt.resolve()!=receipt or receipt.is_relative_to(root.resolve()) or receipt.exists() or receipt.is_symlink(): raise ValueError('invalid receipt path')
    if request['role'] not in ('baseline','candidate'): raise ValueError('invalid root role')
    checker=load_checker(checker_path,checker_sha256,[root])
    for key in ('target','candidate','tree'):
        checker.full_sha(request[key],checker.SHA1)
    for key in ('original_sha256','original_tree_sha256'):
        checker.full_sha(request[key],checker.SHA256)
    expected=request['target'] if request['role']=='baseline' else request['candidate']
    expected_tree=checker.git_bytes(root,'rev-parse',expected+'^{tree}').strip().decode()
    if request['role']=='candidate' and expected_tree!=request['tree']: raise ValueError('candidate tree mismatch')
    def preflight(fresh):
        current=load_checker(checker_path,checker_sha256,[root])
        packet=current.read_packet(request['packet'],[root])
        if packet['pins']['checker'] != {'path':str(Path(checker_path)), 'sha256':checker_sha256}: raise ValueError('checker binding mismatch')
        if Path(packet['pins']['python']['path']) != Path(sys.executable).resolve(): raise ValueError('python identity mismatch')
        if Path(packet['pins']['preparer']['path']) != Path(__file__).resolve(): raise ValueError('preparer identity mismatch')
        if Path(packet['pins']['git']['path']) != Path('/usr/bin/git').resolve(): raise ValueError('git identity mismatch')
        plan_path=current.file_pin(request['plan_receipt'],[root])
        plan=current.strict_json(plan_path.read_bytes())
        expected_plan={'packet_sha256':request['packet']['sha256'],'target':request['target'],'candidate':request['candidate'],'tree':request['tree'],'effective_argv':packet['effective_argv']}
        if plan != expected_plan: raise ValueError('stale plan receipt')
        original=packet['originals'][request['role']]
        if original != {'dol_sha256':request['original_sha256'],'tree_sha256':request['original_tree_sha256']}: raise ValueError('original packet mismatch')
        current.verify_plan(root,packet,request['target'],request['candidate'],request['tree'],request['prs'],request['commits'])
        validate_checkout(current,root,expected,expected_tree,request['original_sha256'],request['original_tree_sha256'],fresh=fresh)
        return current,packet
    preflight(True)
    with open(lock_path,'a') as lock:
        fcntl.flock(lock,fcntl.LOCK_EX)
        checker,packet=preflight(True)  # revalidate after waiting, immediately before configure
        launcher=checker.file_pin(packet['pins']['launcher'],[root])
        paths={k:str(checker.path_pin(v,[root])) for k,v in packet['configure_paths'].items()}
        command=[str(launcher),'configure.py']
        for key in ('dtk','objdiff','wrapper','compilers','binutils'):command += ['--'+key,paths[key]]
        ninja=checker.file_pin(packet['pins']['ninja'],[root])
        env={'PATH':str(ninja.parent)+':/usr/bin:/bin','PSO_BUILD_NINJA':str(ninja),'PYTHONDONTWRITEBYTECODE':'1','PSO_QUEUE_PYTHON':str(launcher),'LC_ALL':'C'}
        subprocess.run(command,cwd=root,env=env,check=True,pass_fds=(lock.fileno(),))
        checker,after=preflight(False)
        if after != packet: raise ValueError('packet changed during configure')
        graph=root/'build.ninja'
        if graph.is_symlink() or not graph.is_file(): raise ValueError('missing configured graph')
        result={'version':1,'prepared_config':True,'packet_sha256':request['packet']['sha256'],
                'root':str(root),'role':request['role'],'target':request['target'],'candidate':request['candidate'],
                'tree':request['tree'],'root_commit':expected,'root_tree':expected_tree,
                'graph_sha256':hashlib.sha256(graph.read_bytes()).hexdigest(),
                'checker_sha256':checker_sha256,'preparer_sha256':packet['pins']['preparer']['sha256'],
                'original_tree_sha256':request['original_tree_sha256'],'plan_sha256':request['plan_receipt']['sha256'],
                'effective_argv_sha256':hashlib.sha256(json.dumps(packet['effective_argv'],separators=(',',':')).encode()).hexdigest()}
        with receipt.open('x') as out:
            json.dump(result,out,sort_keys=True);out.write('\n');out.flush();os.fsync(out.fileno())
    return result


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--request',required=True);ap.add_argument('--checker',required=True);ap.add_argument('--checker-sha256',required=True)
    args=ap.parse_args();p=Path(args.request)
    if not p.is_absolute() or p.is_symlink(): raise ValueError('invalid request')
    # Reject duplicate keys before handling any untrusted request.
    checker=load_checker(args.checker,args.checker_sha256,[])
    request=checker.strict_json(p.read_bytes())
    prepare(request,args.checker,args.checker_sha256)

if __name__=='__main__': main()
