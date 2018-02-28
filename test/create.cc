/**
 * create.cc - programmaticaly create holes
 *
 * BUFLEN can be problematic if set less than 4KB
 * try 100 and then holes is not there.
 *
 * fwang2@ornl.gov
 *
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 8192

int main(int argc, char** argv) {

    int fd;

    char buf[BUFLEN];
    fd = open("/dev/urandom", O_RDONLY);
    read(fd, buf, BUFLEN);
    close(fd);


    fd = open("sparse.dat", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    if (fd < 0) {
        perror("file creation");
        exit(1);
    }
    // write BUFLEN at beginning
    write(fd, buf, BUFLEN);
    lseek(fd, 2*BUFLEN, SEEK_CUR); // seek to current offset + 2*BUFLEN
    write(fd, buf, BUFLEN);
    close(fd);

    return 0;
}
