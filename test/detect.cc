#define _FILE_OFFSET_BITS 64

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
    }
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("failed to open the file.");
        exit(EXIT_FAILURE);
    }
    off_t offset = 0, beg = 0, end = 0;
    struct stat status;
    fstat(fd, &status);
    const off_t size = status.st_size;
    do {
        beg = lseek(fd, offset, SEEK_DATA);
        if (beg == -1) {
            perror("SEEK_DATA failed");
            exit(EXIT_FAILURE);
        }
        end = lseek(fd, beg, SEEK_HOLE);
        if (end == -1) {
            perror("SEEK_HOLE failed\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "extent: %lld\t %lld\n",
                (unsigned long long) beg,
                (unsigned long long) end);
        offset = end;
    } while (offset < size);

    close(fd);
    return 0;
}
