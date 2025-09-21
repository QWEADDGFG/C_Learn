#include "func.h"

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    struct hostent *host = gethostbyname(argv[1]);
    if (host == NULL) {
        fprintf(stderr, "gethostbyname error: %s\n", hstrerror(h_errno));
        return -1;
    }
    printf("official name: %s\n", host->h_name);
    for (int i = 0; host->h_aliases[i] != NULL; i++) {
        printf("alias: %s\n", host->h_aliases[i]);
    }
    printf("address type: %d\n", host->h_addrtype);
    printf("length of address: %d\n", host->h_length);
    return 0;
}