# WIP: targeting receiver experiment — does not match

This branch preserves a failed experiment and must not be merged or used for an integration build. The player targeting helper accesses offset 0x2fc, asserted as TObjChara::body_center_position. Both enemy and ancient trap derive from TObjChara; the original trap call at 0x80179AB8 passes its receiver in r3, null output in r4 and range in f1. These facts support a TObjChara* receiver and Vec* output, but do not prove the exact original declarations.

Changing the implementation signature as shown here alters register allocation and instruction layout. A full build failed the original DOL SHA-1; objdiff reported the helper at 90.8% and its compiled text grew four bytes. Several alias-placement variants also failed to match. Restore the matching baseline implementation until a consistent signature can be reproduced without code or coverage loss. The PR100 prerequisite branch intentionally excludes this experiment.
