#ifndef _CHECK_FIRST_INCOMING_
#define _CHECK_FIRST_INCOMING_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#undef MYADDR
#define MYADDR "batman_vs_battamon@bamboo-copter.com"

#undef ADLEN
#define ADLEN 64

#undef MSIZE
#define MSIZE 1024

typedef int boolean;
#undef FALSE
#undef TRUE
const boolean FALSE = 0;
const boolean TRUE = 1;

#endif /* _CHECK_FIRST_INCOMING_ */
