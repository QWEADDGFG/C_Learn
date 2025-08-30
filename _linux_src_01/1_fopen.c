#include "fun.h"
int main(int argc, char *argv[])
{
    // ./1_fopen.c file1
    // if(argc!=2){
    //     fprintf(stderr,"args error!\n");
    //     return -1;
    // }
    ARGS_CHECK(argc, 2);
    FILE *fp = fopen(argv[1], "r+");
    // if (fp == NULL){
    //     perror("fopen 1");
    //     return -1;
    // }
    ERROR_CHECK(fp, NULL, "1_fopen");
    return 0;
}