#include "fun.h"

int main(int argc, char *argv[])
{
    // ./9_myls_al dir1
    ARGS_CHECK(argc, 2);

    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir");

    struct dirent *pdirent;

    while ((pdirent = readdir(dirp)) != NULL)
    {
        // 文件名-->路径
        char path[1024] = {0};

        snprintf(path, sizeof(path), "%s/%s", argv[1], pdirent->d_name);
        struct stat statbuf;
        int ret = stat(path, &statbuf);
        ERROR_CHECK(ret, -1, "stat");

        // 打印文件信息，getpwuid
        printf("%o, %d, %d, %d, %s, %ld, %s\n", statbuf.st_mode,
               statbuf.st_nlink, statbuf.st_uid, statbuf.st_gid, 
            //    ctime(&statbuf.st_mtime),
               localtime(&statbuf.st_mtime),
               statbuf.st_size, pdirent->d_name);
    }

    closedir(dirp); 
    return 0;
}