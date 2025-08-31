#include "fun.h"
typedef struct student_s
{
    int id;
    char name[100];
    float score;
} student_t;

int main(int argc, char *argv[])
{
    // ./0_homework filename
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");

    student_t stu[3] = {
        {1, "Alice", 80},
        {2, "Bob", 90},
        {3, "Charlie", 70}};

    write(fd, stu, sizeof(stu));

    student_t stu_read[3];
    lseek(fd, 0, SEEK_SET);
    read(fd, stu_read, sizeof(stu_read));
    for (int i = 0; i < 3; i++)
    {
        printf("id:%d, name:%s, score:%f\n", stu_read[i].id, stu_read[i].name, stu_read[i].score);
    }
    close(fd);
    return 0;
}
