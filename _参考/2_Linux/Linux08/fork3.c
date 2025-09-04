#include <func.h>

int main(int argc, char* argv[])
{
    int fd = open("text", O_RDWR | O_CREAT | O_TRUNC, 0666);
    printf("pos: %ld\n", lseek(fd, 0, SEEK_CUR));

    pid_t pid = fork();
    int newfd;
    switch (pid) {
    case -1:
        error(1, errno, "fork");
    case 0: 
        // 子进程
        write(fd, "Hello world", 11);
        
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        newfd = dup(fd);    // newfd=1
        printf("newfd = %d\n", newfd);
        exit(0);
    default:
        // 父进程
        sleep(2);
        printf("pos: %ld\n", lseek(fd, 0, SEEK_CUR));
        
        newfd = dup(fd);
        printf("newfd = %d\n", newfd);  // newfd = 4
        exit(0);
    }
    return 0;
}

