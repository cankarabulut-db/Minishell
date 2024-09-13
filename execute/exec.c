#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
 char *user = getenv("PATH");
 printf("%s\n", user);
}
