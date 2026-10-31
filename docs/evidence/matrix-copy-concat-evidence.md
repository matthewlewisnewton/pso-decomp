# Matrix copy and concatenation

The functions at `0x803D9324` and `0x803D9730` take two matrix
pointers; they do not use a player receiver. A null destination or source
selects the current matrix. Copy writes the source into the destination;
concatenation writes destination × source into the destination.

The parameter types use the SDK's pointer-to-four-float-row matrix layout.
Some callers still obtain matrices through legacy integer or byte-buffer
fields; their casts do not establish the ownership or lifetime of those
fields. The current-matrix global also retains its existing integer
representation. The copy implementation retains address-valued integer
intermediates from the matching source while exposing pointer arguments.
