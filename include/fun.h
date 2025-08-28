#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ARGS_CHECK(argc,num){if(argc!=num){fprintf(stderr,"args error!\n");return -1;}}