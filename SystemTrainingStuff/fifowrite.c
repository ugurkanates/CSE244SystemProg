
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <unistd.h>

void err_sys(const char *msg);
void err_usr(const char *msg);

int main(int argc, char *argv[])
{
    int fd;
    int i;

    if (argc != 2) 
        err_usr("yanlis sayida arguman girildi!\n");

    if ((fd = open(argv[1], O_WRONLY)) < 0)
        err_sys("open");

    for (i = 0; i < 100; ++i)
        if (write(fd, &i, sizeof(int)) < 0)
            err_sys("write");

    close(fd);

    return 0;
}

void err_sys(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void err_usr(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}