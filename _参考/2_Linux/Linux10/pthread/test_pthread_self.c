#include <func.h>

int main(int argc, char* argv[])
{
    pthread_t tid = pthread_self();
    
    printf("tid = %lu\n", tid);
    return 0;
}

