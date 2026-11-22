# Recover camera playback, scene storage and render interfaces

The local review `great-merge/review/after-366/camera-scenes-and-rendering` is at `a3cd2e2647cfa0885abc15cf9d7be86a6929e9ea` above the memory review `848e38d3679eb90d80c35f80e25f83bf3da4ad0c`. Its five commits touch 60 paths. [Validation](2026-11-22-upstream-366-camera-scene-review-validation.json)

## Proposed PR description

Use the original camera, scene and render records in the playback and drawing code that shares them.

- Scripted and live cameras use their native playback state, motion channels and sampler inputs. Matrix and view calls take their real matrix and vector pointers.
- Scene fog and light resources use typed storage. Texture-strip allocation and traversal use the shared model and strip records.
- Fade callbacks and deferred render inputs use their original function, object and queue types.

The eleven linker label changes follow the restored owners and signatures. The review matches retail with 27,572 exact functions, 2,447 source-linked units and all 1,147 original data bytes accounted for. Runtime probes cover camera selection and playback, view transforms, fog and light loads, strip winding and release, and fade completion and queue capacity.
