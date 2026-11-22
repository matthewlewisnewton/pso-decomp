# Recover camera playback, scene storage and render interfaces

The local review `great-merge/review/after-367/camera-scenes-and-rendering` is at `dd8bbb24297db27d06b85264d3d0ba40824ef0a8` above the shared-memory review `4fc1ed7afe9483df05b68f2dc6aec746edf05ec3`. Its five commits touch 102 paths. [Validation](2026-11-22-upstream-367-camera-scenes-validation.json)

## Proposed PR description

Recover the original camera, scene, and rendering records used by playback and drawing.

- Scripted and live cameras use typed playback state, motion channels, and sampler inputs. Matrix operations and view transforms accept their original matrix and vector pointers.
- Scene fog and light resources use typed storage, and player effects take the actual player object. Texture-strip allocation and traversal share the original model and strip records.
- Fade callbacks and deferred rendering use the original function, object, and queue types.

The 18 linker-label changes follow the recovered owners and signatures. The review reproduces retail with 27,572 exact functions, 2,417 linked units, and every byte from the starting data inventory accounted for. Runtime probes cover scripted playback, live shots, view transforms, fog and light loading, player effects, strip winding and release, fade completion, and queue capacity.
