#include <func.h>

int main(int argc, char* argv[])
{
    // ./dirent dir
    if (argc != 2) {
        error(1, 0, "Usage: %s dir", argv[0]);
    }

    DIR* stream = opendir(argv[1]);
    if (!stream) {
        error(1, errno, "opendir %s", argv[1]);
    }

    errno = 0;
    struct dirent* pdirent;
    while ((pdirent = readdir(stream)) != NULL) {
        printf("d_ino = %ld, d_off = %ld, d_reclen = %hu, d_typ = %d, d_name = %s\n",
               pdirent->d_ino,
               pdirent->d_off, 
               pdirent->d_reclen,
               pdirent->d_type,
               pdirent->d_name);
    }
    
    if (errno) {
        error(1, errno, "readdir");
    }

    closedir(stream);
    return 0;
}

