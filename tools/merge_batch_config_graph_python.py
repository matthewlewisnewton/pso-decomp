#!/usr/bin/python3 -I
"""Pinned frozen-graph launcher: never permit Ninja to run configure."""
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


def require_inherited_lock():
    if LEGACY_LOCK.is_symlink() or not LEGACY_LOCK.is_file(): fail('missing inherited queue lock')
    expected=LEGACY_LOCK.stat()
    for path in Path('/proc/self/fd').iterdir():
        try:
            actual=os.fstat(int(path.name))
            if (actual.st_dev,actual.st_ino)!=(expected.st_dev,expected.st_ino): continue
            info=Path('/proc/self/fdinfo',path.name).read_text()
            if any(line.startswith('lock:') and 'FLOCK' in line and ('READ' in line or 'WRITE' in line) for line in info.splitlines()): return
        except (OSError,ValueError): continue
    fail('missing inherited queue lock')


def main():
    packet_path=Path(os.environ['PSO_CONFIG_PACKET_PATH'])
    packet=pin({'path':str(packet_path),'sha256':os.environ['PSO_CONFIG_PACKET_SHA256']})
    data=json.loads(packet.read_bytes(),object_pairs_hook=unique)
    launcher=pin(data['pins']['launcher'])
    if launcher != Path(__file__).resolve(): fail('wrong launcher')
    python=pin(data['pins']['python'])
    if python != Path(sys.executable).resolve(): fail('wrong interpreter')
    base_path=pin(data['pins']['base_validator'])
    base=types.ModuleType('_pinned_graph_driver');base.__file__=str(base_path)
    exec(compile(base_path.read_bytes(),str(base_path),'exec'),base.__dict__)
    root=Path.cwd().resolve()
    args=sys.argv[1:]
    if not args or args[0].startswith('-'): fail('script entry required')
    script=Path(args[0]).resolve()
    if script == root/'configure.py':
        expected=['configure.py']
        for key in ('dtk','objdiff','wrapper','compilers','binutils'):
            expected += ['--'+key,data['configure_paths'][key]['path']]
        expected += ['progress']
        if args != expected: fail('frozen graph cannot regenerate configuration')
        require_inherited_lock()
        request=pin({'path':os.environ['PSO_CONFIG_REQUEST_PATH'],'sha256':os.environ['PSO_CONFIG_REQUEST_SHA256']})
        if request.is_relative_to(root): fail('request inside build root')
        adapter=pin(data['pins']['adapter'])
        subprocess.run([str(python),'-I','-B',str(adapter),'--check-config',str(request)],check=True,env=os.environ)
    elif not script.is_relative_to(root/'tools') or script.suffix!='.py':
        fail('unreviewed graph Python entry point')
    env=os.environ.copy();env['PSO_QUEUE_PYTHON']=str(launcher)
    code='import sys; sys.dont_write_bytecode=True\n'+base.PYTHON_DRIVER
    os.execve(str(python),[str(python),'-I','-B','-c',code,str(root),*args],env)

if __name__=='__main__': main()
