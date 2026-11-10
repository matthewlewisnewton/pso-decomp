// Genuine secondary-base conversion diagnostic; these are not PSO classes.
struct Prefix { unsigned prefix; };
struct Root { unsigned state; };
struct Multiple : Prefix, Root { unsigned tail; };
struct Single : Root { unsigned tail; };
extern "C" Root *convert_primary(Single *p) { return p; }
extern "C" Root *convert_secondary(Multiple *p) { return p; }

#ifdef KENKYUW_WITNESS_HOST_CHECK
#include <cassert>
#include <cstdio>
int main() {
    Single single; Multiple multiple;
    assert(convert_primary(0) == 0 && convert_secondary(0) == 0);
    Root *primary = convert_primary(&single);
    Root *secondary = convert_secondary(&multiple);
    assert((void *)primary == (void *)&single);
    assert((char *)secondary - (char *)&multiple == sizeof(Prefix));
    primary->state = 17; secondary->state = 23;
    assert(single.state == 17 && multiple.state == 23);
    std::puts("PASS: null and nonnull primary/secondary base conversions; 4 cases");
}
#endif
