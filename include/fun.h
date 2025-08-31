#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>


#define ARGS_CHECK(argc, num) do { if ((argc) != (num)) { fprintf(stderr, "args error!\n"); return -1; } } while (0)
#define ERROR_CHECK(ret,num,msg) do{if((ret)==(num)){perror(msg);return -1;}}while(0)