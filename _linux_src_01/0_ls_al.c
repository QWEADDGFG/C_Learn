#include "fun.h"

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir");
    struct dirent *pdirent;

    while ((pdirent = readdir(dirp)) != NULL)
    {
        // 文件名-->路径
        char path[1024] = {0};

        snprintf(path, sizeof(path), "%s/%s", argv[1], pdirent->d_name);
        struct stat buf;
        int ret = stat(path, &buf);   
        ERROR_CHECK(ret, -1, "stat");

        char timestr[20];
        struct tm *tm = localtime(&buf.st_mtime);
        strftime(timestr, sizeof(timestr), "%b %d %H:%M", tm);

        printf("%x %u %s %s %ld %s %s\n",
               (unsigned)buf.st_mode,
               (unsigned)buf.st_nlink,
               getpwuid(buf.st_uid)->pw_name,
               getgrgid(buf.st_gid)->gr_name,
               (long)buf.st_size,
               timestr,
               pdirent->d_name);
    }

    closedir(dirp);

    return 0;
}
