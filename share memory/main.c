#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
  key_t shm_key = 12345;

  
  int shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | 0666);
  if (shm_id < 0) {
    perror("shmget failed");
    exit(1);
  }

  
  void *shm_ptr = shmat(shm_id, NULL, 0);
  if (shm_ptr == (void *)-1) {
    perror("shmat failed");
    exit(1);
  }

  
  pid_t pid = fork();

  if (pid == 0) { 
    int *data = (int *)shm_ptr;

    while (1) {
      
      int num = *data;

      
      printf("عدد دریافت شده: %d\n", num);

      
      sleep(1);
    }
  } else if (pid > 0) { 
    int *data = (int *)shm_ptr;

    while (1) {
      
      int num = rand() % 100;

      
      *data = num;

      
      printf("عدد تولید شده: %d\n", num);

      
      sleep(1);
    }
  } else {
    perror("fork failed");
    exit(1);
  }

  
  shmdt(shm_ptr);

  
  shmctl(shm_id, IPC_RMID, NULL);

  return 0;
}
