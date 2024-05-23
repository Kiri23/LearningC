#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

struct database_header_t
{
  unsigned short version;
  unsigned short employee;
  unsigned int filesize;
};

int main(int argc, char *argv[])
{

  unsigned int x = 2;
  int y = (int)x;
  printf("Size of int: %d\n", y);
  struct database_header_t head = {0};
  struct stat dbStat = {0};

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 0;
  }
  int fd = open(argv[1], O_RDWR | O_CREAT, 0600);
  if (fd == -1)
  {
    perror("open");
    return -1;
  }

  if (read(fd, &head, sizeof(head)) != sizeof(head))
  {
    perror("read");
    close(fd);
    return -1;
  }
  printf("Version: %d\n", head.version);
  printf("Employee: %d\n", head.employee);
  printf("Filesize: %d\n", head.filesize);

  if (fstat(fd, &dbStat) < 0)
  {
    perror("stat");
    close(fd);
    return -1;
  }
  printf("Db File Length, reported by stat: %lld\n", dbStat.st_size);
  printf("Db File Length, reported by header: %u\n", head.filesize);
  if (dbStat.st_size != head.filesize)
  {
    printf("File size mismatch\n");
    close(fd);
    return -2;
  }

  close(fd);
  return 0;
}