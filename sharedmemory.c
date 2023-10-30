#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define SHMSZ 27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    key = 5678;

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Parent process writes to the shared memory
    strcpy(shm, "Hello World!");

    // Forking the process
    int pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process reads from the shared memory
        printf("%s\n", shm);
    } else {
        wait(NULL);
        // Parent process waits for the child to finish

        // Detach the shared memory segment
        if (shmdt(shm) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}
