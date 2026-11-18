"""Bounded ordering model, NOT game execution or a complete TObject model.

Encode only the normal update branch, tail attachment and destruction-enabled
queued-node branch inspected in original TObject code. Counterexamples remove
one assumption; they do not establish reachable game bugs.
"""

def trace(*, tail_attachment=True, retire_old=True):
    children = ['old-transition']
    queued = {'old-transition'}
    global_owner = 'old-transition'
    events = []
    if tail_attachment:
        children.append('area-map')
    else:
        children.insert(0, 'area-map')
    cursor = children[0]
    while cursor is not None:
        index = children.index(cursor)
        next_node = children[index + 1] if index + 1 < len(children) else None
        if cursor in queued:
            if retire_old:
                events.append('delete-old-transition')
                global_owner = None
                children.remove(cursor)
            # The actual disabled-destruction branch consumes the queue bit;
            # it is intentionally not represented as a guaranteed later delete.
            queued.discard(cursor)
        elif cursor == 'area-map':
            events.append('area-map-return')
            queued.add(cursor)  # current node is not rechecked after its task
            children.append('new-transition')
            events.append('publish-new-transition')
            global_owner = 'new-transition'
        cursor = next_node
    return events, global_owner, children

normal = trace()
assert normal[0] == ['delete-old-transition', 'area-map-return', 'publish-new-transition']
assert normal[1] == 'new-transition'
assert normal[2] == ['area-map', 'new-transition']
# A head-insertion hypothesis is observably different, so list order is material.
reordered = trace(tail_attachment=False)
assert reordered[0] == ['area-map-return', 'publish-new-transition', 'delete-old-transition']
assert reordered[1] is None
# Disabled destruction defeats the retirement claim, not necessarily publication.
disabled = trace(retire_old=False)
assert 'delete-old-transition' not in disabled[0]
assert 'old-transition' in disabled[2]
print('PASS: supported ordering and two assumption-sensitivity cases')
