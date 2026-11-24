# Controller flag receivers: suppression is not task suspension

Bounded evidence pass at `b661647b8db29232632be0eb87e9fd1c967520bc`.
No production changes or native build. This follows the conditional reopen proof
and tests a concrete candidate for its missing descendant-traversal interval.

## Resolved suppression route

The original PMF data at 804CEA04 (suppress_slot) is words
0, -1, set_radar_dirty_flag; 804CE9F8 (unsuppress_slot) is
0, -1, clear_flag_bit0. call_window_method obtains its receiver through get_window,
which indexes the active controller's +0x48 controller-slot array. It does not
return that child controller's +0x28 menu pointer. For the constructor-established player-controller slots, the receiver here
is the player controller, not its 1P menu or transition task. The accessor accepts
indices through 11, so this type claim is tied to those verified slot producers.

Original set_radar_dirty_flag at 8024C76C loads/stores a halfword at +0x1C,
ORing mask 0x1 (store 8024C780). clear_flag_bit0 at 8024C798 clears the same mask
(store 8024C7AC). They also hide/show the separate radar singleton. Those helpers
reset its +0x184 counter and change its rendering flag, not the menu's flags.
The controller scheduling/destruction field is instead TObject's halfword +0x04.
The names suppress_slot and set_radar_dirty_flag must not be interpreted as
TObject suspension without following this receiver and offset evidence.

The observed controller suppression is read by is_visible and therefore selects
the close branch in update_main_menu_request; that branch returns as already
recorded. The inspected PMF target does not itself stop the normal menu descent.
This removes that specific proposed explanation for a missing retirement visit,
not every possible way traversal could be suppressed.

## Concrete scheduling writes in the inspected constructor corridor

- TWindowCtrl constructor's split-screen path creates four CtrlPlayer objects
  in the +0x48 slot array and calls suspend_update at 8024C478. The 1P path does
  not make that call; its CtrlPlayer constructor creates the 1P menu rather than
  the split-screen 4P menu. This real ancestor suspension cannot simply be applied
  to the non-split reopen proof.
- The non-split setup suspends separate party-status windows from the +0x78 array
  at 8024C4F4. These are not the +0x48 player-controller slots.
- CtrlPlayer construction suspends the separately stored status (+0x30) and
  action-palette (+0x34) objects at 8024E388 and 8024E3B0, not its +0x28 menu.
- suspend_update itself ORs mask 0x4 into TObject +0x04. The staged opening
  sequence clears that mask on split-player slots or party-status slots. It does
  not clear the separate pause mask 0x8 or destruction-disable mask 0x20.
- The inspected controller/menu/transition constructors use normal TObject
  attachment. No explicit set_parent call was found in this named corridor;
  this is a scoped source observation, not absence of raw aliases or outside
  reparenting.

These are actual receiver-qualified writes, not a whole-program alias census.
The inspected close/destructor corridor queues owned children; no supported
caller that sets the 1P menu or transition's destruction-disable mask was
established in this pass. TObject's own destructor sets that mask for its cleanup
protocol, which is not evidence of an ordinary live-object disable caller.

## Limits and next useful step

A source search restricted to TWindowCtrl*, TWindowMainMenu* and the transition
unit cannot rule out writes through returned slots, raw offsets, aliases, generic
object helpers or external subsystems. No general lifetime hold is lifted.
Do not replace that missing alias proof with a guard or forced match.

The cheaper positive next target is following callers of get_window and the
PMF-dispatch entries that can forward operations into the menu, especially the
open_submenu forwarding path. Those may expose a second entry order not covered
by the ordinary request-method return. Merely repeating the word “suppress”
search is no longer discriminating.

## Validation

Retained original/compiled complete .text equality passes for Ctrl_8024C160
(976 bytes), Ctrl_8024C024 (256), Ctrl_8024C6CC (340), Ctrl_8024AEAC (412) and
TObjLuker_8001A438 (16). Original data/assembly provide the PMF target and offset
anchors above. These are artifact/source checks, not a fresh compile, integrated
current-main result, universal relocation check or simulated game run. Prior
AreaMap and reopen ordering models retain their explicit sensitivity assumptions.

Independent read-only review passed with the receiver-type claim restricted to
constructor-established player-controller slots. No lifetime hold was lifted.
