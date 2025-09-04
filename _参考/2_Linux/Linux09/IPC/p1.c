#include <func.h>

#define MAXLINE 256

int main(int argc, char* argv[])
{
    int fd1 = open("pipe1", O_WRONLY);
    if (fd1 == -1) {
        error(1, errno, "open pipe1");
    }

    int fd2 = open("pipe2", O_RDONLY);
    if (fd2 == -1) {
        error(1, errno, "open pipe2");
    }

    printf("Established\n");

    char recvline[MAXLINE];
    char sendline[MAXLINE];

    while (fgets(sendline, MAXLINE, stdin) != NULL) {
        write(fd1, sendline, strlen(sendline));
        read(fd2, recvline, MAXLINE);
        printf("from p2: %s\n", recvline);
    }

    close(fd1);
    close(fd2);
    
    return 0;
}

