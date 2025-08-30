#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int dir_count = 0;
int file_count = 0;

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char full_path[1024];
        char *slash = strrchr(path, '/');
        if (slash && *(slash + 1) == '\0') {
            snprintf(full_path, sizeof(full_path), "%s%s", path, entry->d_name);
        } else {
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        }

        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        struct stat statbuf;
        if (stat(full_path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            printf("%s/\n", full_path);
            dir_count++;
            list_directory(full_path);
        } else {
            printf("%s\n", full_path);
            file_count++;
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    list_directory(argv[1]);

    printf("\n%d directory, %d files\n", dir_count, file_count);
    return EXIT_SUCCESS;
}