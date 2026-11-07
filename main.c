// #include "get_next_line.h"
#include "get_next_line_bonus.h"

int main()
{
    char *line;
    int fd1 = open("file01.txt", O_RDWR);
    int fd2 = open("file02.txt",O_RDWR);


    printf("%s",get_next_line_bonus(fd1));
    printf("%s",get_next_line_bonus(fd2));
    printf(":%s:",get_next_line_bonus(fd1));
    printf(":%s:",get_next_line_bonus(fd2));
}