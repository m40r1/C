#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static const unsigned int buffer_size = (16 * 1024);
static const unsigned int high_bit = 0x80 != 0;

int main(int argc, char *argv[]) {
  int in_fd; /*input file*/
  int lwbi_fd; /*low bytes*/
  int read_size; /*handle reads*/
  int write_size; /*handle writes*/
  unsigned char buffer[buffer_size]; /*stores data*/
   
  if (argc != 3) {
    fprintf(stderr, "wrong number of args\n");
    fprintf(stderr, "usage is : prog <asci file> <low bits>\n");
    exit(8);
  }

  in_fd = open(argv[1], O_RDONLY);
  if (in_fd < 0) {
    fprintf(stderr, "cant open %s\n", argv[1]);
    exit(8);
  }

  lwbi_fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  if (lwbi_fd < 0) {
    fprintf(stderr, "cant open %s\n", argv[2]);
    exit(8);
  }

  for (;;) {
    /*read routine*/
    read_size = read(in_fd, &buffer, sizeof(buffer));
    if (read_size == 0)
      break;
    if (read_size < 0) {
      fprintf(stderr, "cant read from %s\n", argv[1]);
      exit(8);
    }
    for (int x = 0; x < read_size; ++x) {
      if (buffer[x] & high_bit)
        buffer[x] = 0;
    }
    write_size = write(lwbi_fd, &buffer, (unsigned int)read_size);
    if (write_size < 0) {
      fprintf(stderr, "unable to write to %s\n", argv[2]);
      exit(8);
    }
    close(in_fd);
    close(lwbi_fd);
    return 0;
  }
}

