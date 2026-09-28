#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *user_input = NULL;
  size_t size = 0;

  while (1) {
    printf("Enter programs to run.\n> ");
    ssize_t char_count = getline(&user_input, &size, stdin);

    if (char_count == -1) {
      perror("getline failure");
      exit(EXIT_FAILURE);
    }

    char *saveptr;
    char *command = strtok_r(user_input, " \n", &saveptr);

    pid_t pid = fork();
    if (pid == 0) {
      execlp(command, command, (char *)NULL);
      printf("Exec failure\n");
      exit(EXIT_FAILURE);
    } else {
      waitpid(pid, NULL, 0);
    }
  }

  free(user_input);
  return 0;
}
