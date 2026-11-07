#include "get_next_line.h"

int main()
{
    char *line;
    int fd = open("file.txt", O_RDWR);

    printf("%s", get_next_line(fd));
    // printf("%s", get_next_line(fd));
    // printf("%s", get_next_line(fd));

    // while ((line = get_next_line(fd)))
    // {
    //     printf("%s", line);
    //     free(line);
    // }

}