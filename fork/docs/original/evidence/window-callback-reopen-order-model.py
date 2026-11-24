"""Conditional close/reopen ordering, not a full scheduler or game simulation."""

def cycle(descend_between=True, destruction_enabled=True):
    events = ['close-request', 'queue-old-transition', 'return-from-request']
    old_exists = True
    if descend_between and destruction_enabled:
        events.append('delete-old-transition')
        old_exists = False
    old_exists_at_publication = old_exists
    events.append('next-request-opens')
    events.append('publish-new-transition')
    # Missing descent permits a later old-generation clear. This is an
    # assumption-sensitivity scenario, not proof that the game reaches it.
    if not descend_between and destruction_enabled:
        events.append('delete-old-transition')
    return events, old_exists_at_publication

normal, remains = cycle()
assert normal.index('delete-old-transition') < normal.index('publish-new-transition')
assert not remains
skipped, remains = cycle(descend_between=False)
assert skipped.index('delete-old-transition') > skipped.index('publish-new-transition')
assert remains
blocked, remains = cycle(destruction_enabled=False)
assert 'delete-old-transition' not in blocked and remains
print('PASS: ordinary reopen order and two assumption-sensitivity cases')
