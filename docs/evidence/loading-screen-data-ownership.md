# Loading-screen data ownership

The fallback unit `auto_06_804349C0_rodata` covers
`0x804349C0–0x80434A08`. Its two class-name strings are referenced by the
class-name pointers at `0x805D2630` and `0x805D2638`. Keep the strings
externally visible so the pointers retain their relocation targets.

`TLoadCtrl::run_task` passes the vector at `0x804349CC` to the loading
indicator constructor. The constructor reads it through `VecCopy`. The
same task passes the vectors at `0x804349D8` and `0x804349E4` to
`set_active_camera_pose` as the eye position and direction.
`TLoadingCur::update_camera_facing_offset` reads three zero words at
`0x804349FC`, then passes the first two to `direction_to_rotation_xy`.
The third word is part of the initializer's extent. The split-object and
compiled-object scan found no other owners referencing the four initializers.

Independent C and C++ definitions reproduced the 72-byte pool with the
standard GC/2.0 flags. [Upstream #289](https://github.com/zeroz41/pso-decomp/pull/289)
divides the same range between the two consumers at `0x804349F0`. This
change uses that boundary. The following signed conversion constant at
`0x80434A08` stays in the cursor unit, with its new section offset at `0x18`.

| Compiler trial | Result |
|---|---|
| Define the vectors before their consumers and assign the cursor aggregate | Data matched. The controller used a shared data base and an extra saved register. The cursor called a generated assignment operator. |
| [Define constants after their consumers](bridge-item-light-constant-pool.md) and copy the cursor members explicitly | The separate address loads returned. GC/2.0 placed the late aggregate definitions in writable `.data`. |
| Use a local aggregate initializer for the cursor's three words | The full cursor object matched, including the original loads and exact data layout. |
| Use local camera vectors and scope `pool_data off` to `TLoadCtrl::run_task` | The full controller object matched. The original function forms each vector address separately, as in the [ballistic particle renderer](ballistic-particle-recovery.md). |
