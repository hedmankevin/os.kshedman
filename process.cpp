#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 9; ++i) {
        pid_t child_pid = fork();

        if (child_pid == 0) {
            // This is the child process.
            std::cout << "Child process ID: " << getpid() << std::endl;
            std::cout << "Parent process ID: " << getppid() << std::endl;
            return 0;
        }
    }

    return 0;
}
