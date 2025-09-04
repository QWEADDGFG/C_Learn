#include <func.h>

#define MMAP_SIZE (4096 * 10)

int main(int argc, char* argv[])
{
    // ./mmap_cp src dst
    if (argc != 3) {
        error(1, 0, "Usage: %s src dst", argv[0]);
    }

    int srcfd = open(argv[1], O_RDONLY);
    if (srcfd == -1) {
        error(1, errno, "open %s", argv[1]);
    }

    int dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (dstfd == -1) {
        close(srcfd);
        error(1, errno, "open %s", argv[2]);
    }

    // 1. 文件大小需要事先固定!
    // 获取src的大小
    struct stat sb;
    fstat(srcfd, &sb); // sb.st_size 
    off_t fsize = sb.st_size;
    // 将 dst 文件的大小设置为 sb.st_size 
    ftruncate(dstfd, fsize);
    
    off_t offset = 0;   // 已复制的数据
    while (offset < fsize) {
        // 计算映射区的长度
        off_t length;   
        if (fsize - offset >= MMAP_SIZE) {
            length = MMAP_SIZE;
        } else {
            length = fsize - offset;
        }
        
        // 映射
        void* addr1 = mmap(NULL, length, PROT_READ, MAP_SHARED, srcfd, offset);
        if (addr1 == MAP_FAILED) {
            error(1, errno, "mmap %s", argv[1]);
        }

        void* addr2 = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, dstfd, offset);
        if (addr2 == MAP_FAILED) {
            error(1, errno, "mmap %s", argv[2]);
        }

        // addr2 = addr1
        // 复制   
        memcpy(addr2, addr1, length);
        offset += length;

        // 解除映射
        int err = munmap(addr1, length);
        if (err) {
            error(1, errno, "munmap %s", argv[1]);
        }

        err = munmap(addr2, length);
        if (err) {
            error(1, errno, "munmap %s", argv[2]);
        }
    }   // offset == fsize
    
    // 关闭文件描述符
    close(srcfd);
    close(dstfd);

    return 0;
}

