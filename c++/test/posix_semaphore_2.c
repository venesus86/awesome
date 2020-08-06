#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h> 
#include <stdio.h>
        
const char *countFile = "count.db";
int main(int argc, char **argv)
{       
  int count = 100;
  int fd; 
  sem_t *mysem;
  if((mysem = sem_open("mysem", 0, 0777, 0)) == SEM_FAILED)
  {
          perror("Sem Open Error");
          return 1;
  }
  if( (fd = open(countFile,O_RDWR)) == -1)
  {
          perror("Open Error\n");
          return 1;
  }
  printf("[%d] sem[2] sem_wait\n", getpid());
        sem_wait(mysem);

  while(1)
  {       
          #if 1
          printf("sem[2] sleep 100\n");
          sleep(100);
          #else
          sem_wait(mysem);
          lseek(fd, 0, SEEK_SET);
          read(fd, (void *)&count, sizeof(count));
          printf("Read Data %d\n",count);
          
          count++; 
          lseek(fd, 0, SEEK_SET);
          write(fd, (void *)&count, sizeof(count));
          sem_post(mysem);
          sleep(1); 
          #endif
  }       
  close(fd);
  return 0;
}              