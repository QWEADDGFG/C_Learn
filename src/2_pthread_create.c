#include "func.h"
void* routine(void* arg){
    printf("in thread-child\n");
    return NULL;
}
int main(int argc, char* argv[]){
    pthread_t tid;
    pthread_create(&tid, NULL, routine, NULL);
    printf("in thread-parent\n");
    // sleep(1);
    return 0;
}