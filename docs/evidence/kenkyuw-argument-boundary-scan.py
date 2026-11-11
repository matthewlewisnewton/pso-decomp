#!/usr/bin/env python3
"""Read-only candidate survey for the KenkyuW argument-order investigation.

Filters build.ninja units by the dispatcher's compiler version and exact command
flags, then scans .text for independent move/load/direct-call triples.
The original provider uses the corresponding original split objects; configured
flags select the cohort but do not establish the original compiler's provenance.
Source pragmas and actual scheduling causes still require separate validation.
Block boundaries use direct targets and branch/call fallthroughs; destinations
of indirect jumps are not recovered from jump tables.
This does not compile, alter, link or activate any object.
"""
from pathlib import Path
import argparse,struct,json,re,bisect,hashlib

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--repo',type=Path,default=Path(__file__).resolve().parents[2])
parser.add_argument('--output',type=Path,help='Write JSON here instead of stdout')
parser.add_argument('--include-narrow-loads',action='store_true',
                    help='Also consider lbz, lhz and lha argument loads')
parser.add_argument('--provider',choices=('source','original'),default='source',
                    help='Scan compiled source objects or corresponding original split objects')
args=parser.parse_args()
repo=args.repo.resolve()

def elf(path):
    data = path.read_bytes()
    h = struct.unpack_from('>16sHHIIIIIHHHHHH', data)
    assert h[0][:6] == b'\x7fELF\x01\x02'
    sections = [struct.unpack_from('>IIIIIIIIII', data, h[6]+i*h[11]) for i in range(h[12])]
    strs = sections[h[13]]
    names = data[strs[4]:strs[4]+strs[5]]
    def name(offset, blob=names): return blob[offset:].split(b'\0', 1)[0].decode()
    snames = [name(s[0]) for s in sections]
    bodies = {n:data[s[4]:s[4]+s[5]] for n,s in zip(snames,sections)}
    symbols_by_table = {}
    symbols = {}
    for index, s in enumerate(sections):
        if s[1] != 2: continue
        linked = sections[s[6]]
        st = data[linked[4]:linked[4]+linked[5]]
        table = []
        for o in range(s[4], s[4]+s[5], 16):
            symbol = struct.unpack_from('>IIIBBH', data, o)
            n = name(symbol[0], st)
            table.append((n, symbol))
            if n and symbol[5] < len(snames) and snames[symbol[5]] == '.text': symbols[n] = symbol
        symbols_by_table[index] = table
    relocs = []
    for s in sections:
        if s[1] not in (4,9): continue
        size = 12 if s[1]==4 else 8
        for o in range(s[4], s[4]+s[5], size):
            offset,info = struct.unpack_from('>II', data, o)
            addend = struct.unpack_from('>i',data,o+8)[0] if size==12 else 0
            n,sym = symbols_by_table[s[6]][info>>8]
            if not n and sym[5] < len(snames): n = '@section:'+snames[sym[5]]
            relocs.append((snames[s[7]],offset,info&255,n,addend))
    alloc = {n:bodies[n] for n,s in zip(snames,sections) if s[2]&2 and s[1]!=8}
    return bodies, symbols, sorted(relocs), alloc

def is_store(word):
    primary=word>>26
    if primary in (36,37,38,39,44,45,47,52,53,54,55,60,61):
        return True
    if primary==31:
        return (word>>1&1023) in (150,151,183,215,247,407,439,661,662,663,695,725,727,759,918,983)
    return primary==4 and (word>>1&63) in (7,39)


raw=(repo/'build.ninja').read_text().splitlines()
logical=[]
i=0
while i<len(raw):
    line=raw[i]
    while line.endswith('$'):
        i+=1;line=line[:-1]+raw[i].strip()
    logical.append(line);i+=1
rules={};current=None
for line in logical:
    if line.startswith('build '):
        output=line[6:].split(':',1)[0]
        current={'build':line,'output':output}
        rules[output]=current
    elif line and not line[0].isspace(): current=None
    elif current is not None and '=' in line:
        key,val=line.strip().split('=',1);current[key.strip()]=val.strip()
control=rules['build/GPOE8P/src/pso/npc/TObjNpcKenkyuW.o']
reference_flags=' '.join(control['cflags'].split())
allowed_loads=(32,34,40,42) if args.include_narrow_loads else (32,)
rows=[];units=functions=0
corpus=hashlib.sha256()
for name,rule in rules.items():
    if not name.startswith('build/GPOE8P/src/') or not name.endswith('.o'): continue
    if rule.get('mw_version')!='GC/2.6' or ' '.join(rule.get('cflags','').split())!=reference_flags: continue
    object_name=name.replace('/src/','/obj/',1) if args.provider=='original' else name
    path=repo/object_name
    if not path.exists():continue
    corpus.update(object_name.encode()+b'\0'+hashlib.sha256(path.read_bytes()).digest())
    units+=1
    sections,symbols,relocs,allocated=elf(path)
    if '.text' not in sections:continue
    data=sections['.text'];words=[v[0] for v in struct.iter_unpack('>I',data)]
    reloc={r[1]:r for r in relocs if r[0]=='.text'}
    for fn,s in symbols.items():
        start,size=s[1:3]
        if s[3]&15!=2 or not size or start+size>len(data):continue
        functions+=1
        starts={start};targets=set()
        for offset in range(start,start+size,4):
            w=words[offset//4];op=w>>26
            branch=op in (16,18) or op==19 and (w>>1&1023) in (16,528)
            if branch and offset+4<start+size:starts.add(offset+4)
            if offset in reloc:continue
            if op==18:
                delta=w&0x03fffffc
                if delta&0x02000000:delta-=0x04000000
            elif op==16:
                delta=w&0xfffc
                if delta&0x8000:delta-=0x10000
            else:continue
            target=delta if w&2 else offset+delta
            if start<=target<start+size:targets.add(target);starts.add(target)
        ordered=sorted(starts)
        for offset in range(start,start+size-8,4):
            a,b,c=words[offset//4:offset//4+3]
            src=a>>21&31;dst=a>>16&31;rb=a>>11&31
            if a>>26!=31 or (a>>1&1023)!=444 or a&1 or src!=rb or not 3<=dst<=10:continue
            ld=b>>21&31;base=b>>16&31
            if b>>26 not in allowed_loads or not 3<=ld<=10 or ld==dst or src==ld or base==dst:continue
            if c&0xfc000003!=0x48000001:continue
            block=ordered[bisect.bisect_right(ordered,offset)-1]
            before=words[block//4:offset//4]
            source=rule['build'].split(': mwcc ',1)[1].split(' | ',1)[0].strip()
            row={'unit':object_name,'source':source,'symbol':fn,'offset':hex(offset),
                 'function_offset':hex(offset-start),
                 'move_destination':dst,'move_source':src,'load_destination':ld,'load_base':base,'load_opcode':b>>26,
                 'branch_target':offset in targets,'block_start':hex(block),
                 'preceding_in_block':len(before),'preceding_store':any(is_store(w)for w in before),
                 'call_target':reloc.get(offset+8,('unknown',))[3] if offset+8 in reloc else 'local call'}
            rows.append(row)
summary={'compiler':'GC/2.6','flags':reference_flags,'object_provider':args.provider,
         'object_corpus_sha256':corpus.hexdigest(),'units':units,'functions':functions,'sites':len(rows),
         'no_preceding_store':sum(not r['preceding_store'] for r in rows),'rows':rows}
summary['build_ninja_sha256']=hashlib.sha256((repo/'build.ninja').read_bytes()).hexdigest()
report=repo/'build/GPOE8P/report.json'
summary['report_sha256']=hashlib.sha256(report.read_bytes()).hexdigest() if report.exists() else None
payload=json.dumps(summary,indent=2)+'\n'
if args.output:
    args.output.write_text(payload)
else:
    print(payload,end='')
