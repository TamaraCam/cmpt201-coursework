#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *user_input = NULL;
  size_t size = 0;

  while (1) {
    printf("Please enter some text: ");
    ssize_t char_count = getline(&user_input, &size, stdin);

    if (char_count == -1) {
      perror("getline failed");
      exit(EXIT_FAILURE);
    }

    char *saveptr;
    char *ret = strtok_r(user_input, " ", &saveptr);

    printf("Tokens:\n");

    while (ret != NULL) {
      printf("  %s\n", ret);
      ret = strtok_r(NULL, " ", &saveptr); // pass in NULL to start from next word.
    }
  }

  free(user_input);
  return 0;
}
