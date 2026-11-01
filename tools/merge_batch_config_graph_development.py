#!/usr/bin/python3 -I
"""Development-only pinned frozen-graph launcher: never regenerate configure."""
import hashlib
import json
import os
import subprocess
from pathlib import Path
import sys
import types


def fail(message):
    raise SystemExit(message)


def pin(entry):
    if set(entry) != {'path', 'sha256'}: fail('invalid pin')
    path=Path(entry['path'])
    if not path.is_absolute() or path.is_symlink() or path.resolve()!=path or not path.is_file(): fail('invalid pin path')
    if hashlib.sha256(path.read_bytes()).hexdigest()!=entry['sha256']: fail('stale pin')
    return path


def unique(pairs):
    out={}
    for key,value in pairs:
        if key in out: fail('duplicate packet key')
        out[key]=value
    return out


LEGACY_LOCK = Path('/tmp/pso-decomp-full-build.lock')
CAPACITY = Path('/tmp/pso-build-capacity-v2')


def inherited_lock(path, mode):
    if path.is_symlink() or not path.is_file() or path.resolve() != path:
        return False
    expected=path.stat()
    for fd in Path('/proc/self/fd').iterdir():
        try:
            actual=os.fstat(int(fd.name))
            if (actual.st_dev,actual.st_ino)!=(expected.st_dev,expected.st_ino): continue
            info=Path('/proc/self/fdinfo',fd.name).read_text()
            if any(line.startswith('lock:') and 'FLOCK' in line and mode in line for line in info.splitlines()): return True
        except (OSError,ValueError): continue
    return False


def require_inherited_lock():
    if not inherited_lock(LEGACY_LOCK, 'READ'): fail('missing inherited shared queue lock')
    if not any(inherited_lock(CAPACITY / ('development-' + str(i) + '.lock'), 'WRITE') for i in (0, 1)):
        fail('missing inherited development slot')


def main():
    packet_path=Path(os.environ['PSO_CONFIG_PACKET_PATH'])
    packet=pin({'path':str(packet_path),'sha256':os.environ['PSO_CONFIG_PACKET_SHA256']})
    data=json.loads(packet.read_bytes(),object_pairs_hook=unique)
    launcher=pin(data['pins']['launcher'])
    if launcher != Path(__file__).resolve(): fail('wrong launcher')
    python=pin(data['pins']['python'])
    if python != Path(sys.executable).resolve(): fail('wrong interpreter')
    root=Path.cwd()
    if not root.is_absolute() or root.resolve()!=root: fail('invalid execution root')
    require_inherited_lock()
    request_path=pin({'path':os.environ['PSO_CONFIG_REQUEST_PATH'],'sha256':os.environ['PSO_CONFIG_REQUEST_SHA256']})
    if request_path.is_relative_to(root): fail('request inside build root')
    request=json.loads(request_path.read_bytes(),object_pairs_hook=unique)
    if request.get('config_admission',{}).get('packet') != {'path':str(packet_path),'sha256':os.environ['PSO_CONFIG_PACKET_SHA256']}: fail('request packet mismatch')
    if request.get('cli')!=data['pins']['cli'] or request.get('validator')!=data['pins']['guard']: fail('request runtime mismatch')
    environment_path=Path(request['environment'])
    if not environment_path.is_absolute() or environment_path.is_symlink() or environment_path.resolve()!=environment_path or environment_path.is_relative_to(root): fail('invalid environment')
    if hashlib.sha256(environment_path.read_bytes()).hexdigest()!=request.get('environment_sha256'): fail('stale environment')
    environment=json.loads(environment_path.read_bytes(),object_pairs_hook=unique)
    if environment.get('config_admission')!=request['config_admission']: fail('environment packet mismatch')
    review_path=pin(environment['development_capacity']['review'])
    review=json.loads(review_path.read_bytes(),object_pairs_hook=unique)
    entries=review.get('roots',{})
    if set(entries)!={'baseline','candidate'}: fail('invalid reviewed roots')
    matches=[role for role,entry in entries.items() if entry.get('path')==str(root)]
    if len(matches)!=1: fail('unreviewed execution root')
    role=matches[0];entry=entries[role]
    expected_commit=request['target'] if role=='baseline' else request['candidate']
    if entry.get('commit')!=expected_commit or (role=='candidate' and entry.get('tree')!=request['tree']): fail('wrong reviewed root')
    adapter=pin(data['pins']['adapter'])
    subprocess.run([str(python),'-I','-B',str(adapter),'--check-config',str(request_path)],check=True,env=os.environ)
    base_path=pin(data['pins']['base_validator'])
    base=types.ModuleType('_pinned_graph_driver');base.__file__=str(base_path)
    exec(compile(base_path.read_bytes(),str(base_path),'exec'),base.__dict__)
    args=sys.argv[1:]
    if not args or args[0].startswith('-'): fail('script entry required')
    script=Path(args[0]).resolve()
    if script == root/'configure.py':
        expected=['configure.py']
        for key in ('dtk','objdiff','wrapper','compilers','binutils'):
            expected += ['--'+key,data['configure_paths'][key]['path']]
        expected += ['progress']
        if args != expected: fail('frozen graph cannot regenerate configuration')
    elif not script.is_relative_to(root/'tools') or script.suffix!='.py':
        fail('unreviewed graph Python entry point')
    env=os.environ.copy();env['PSO_QUEUE_PYTHON']=str(launcher)
    code='import sys; sys.dont_write_bytecode=True\n'+base.PYTHON_DRIVER
    os.execve(str(python),[str(python),'-I','-B','-c',code,str(root),*args],env)

if __name__=='__main__': main()
