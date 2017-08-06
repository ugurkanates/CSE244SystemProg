/* pipeop.c */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void err_sys(const char *msg);
void err_usr(const char *msg);

int main(int argc, char *argv[])
{
    int ch, cflag, rflag;

    opterr = 0;
    cflag = 0, rflag = 0;

    while ((ch = getopt(argc, argv, "cr")) != -1) {
        switch (ch) {
            case 'c':
                cflag = 1;
                break;
            case 'r':
                rflag = 1;
                break;
            case '?':
                err_usr("gecersiz secenek!\n");
        }
    }

    if (!cflag && !rflag)
        err_usr("-c ya da -r seçeneklerinden biri girilmeli!\n");

    if (cflag && rflag) 
        err_usr("-c ve -r seçenekleri birlikte girilemez!\n");

    if (argc - optind != 1)
        err_usr("yanlis sayıda argüman girildi!\n");

    if (cflag) {
        if (mkfifo(argv[optind], S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH) < 0) 
            err_sys("mkfifo");
    }
    else 
        if (unlink(argv[optind]) < 0)
            err_sys("unlink");

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