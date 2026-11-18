"""Static ancestry model only; not a game render/interleaving simulation."""
parents = {'tl03': 'main', 'tl04': 'main', 'screen': 'tlwindow',
           'subcontroller': 'tl01', 'tlwindow': 'main', 'tl01': 'main',
           'window-root': None, 'viewport0': 'window-root',
           'viewport4': 'window-root', 'callback': 'viewport0'}

def descendant(node, root):
    seen = set()
    while node is not None and node not in seen:
        seen.add(node)
        if node == root:
            return True
        node = parents.get(node)
    return False

assert not any(descendant('callback', r) for r in ('tl03', 'tl04'))
# Split-screen client 4 selects another root in the same detached window tree.
parents['callback'] = 'viewport4'
assert not any(descendant('callback', r) for r in ('tl03', 'tl04'))
# Reparenting defeats the conclusion; the original graph must not be assumed
# immutable based only on its constructors.
parents['window-root'] = 'tl03'
assert descendant('callback', 'tl03')
print('PASS: two static root paths and reparenting sensitivity')
