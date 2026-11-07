#include "get_next_line.h"

int main()
{
    char *line;
    int fd = open("file.txt", O_RDWR);

    line = get_next_line(fd);

    while (line)
    {
        printf("%s",line);
        free(line);
        line = get_next_line(fd);
    }
}