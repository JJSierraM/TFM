#include <stdio.h>

#ifndef DEBUG
#define DEBUG

#define VERBOSE 1
#define DEBUG_PRINTLN(...) if(VERBOSE) printf(__VA_ARGS__); printf(" @ %s:%d\n", __FILE__, __LINE__); 

#endif
