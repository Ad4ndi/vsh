#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <dlfcn.h>

#include "../headers/color.h"
#include "../headers/prompt.h"

extern char prompt[];
extern char path[];

#define MAX_INPUT_LENGTH 256
#define MAX_ARGV_LENGTH 64

int main() {
    char input[MAX_INPUT_LENGTH], *argv[MAX_ARGV_LENGTH], libpath[MAX_INPUT_LENGTH];
    void *handle;
    int i;

    if (setenv("PATH", path, 1) == -1) {
        perror("vsh");
        return 1;
    }

    while (1) {
        parse();
        if (!fgets(input, sizeof(input), stdin)) { perror("vsh"); break; }
        input[strcspn(input, "\n")] = '\0';
        if (*input == '\0') continue;
        if (!strcmp(input, "exit")) break;

        i = 0;
        for (char *token = strtok(input, " "); token && i < MAX_ARGV_LENGTH - 1; token = strtok(NULL, " "))
            argv[i++] = token;
        argv[i] = NULL;

        if (i > 1 && !strcmp(argv[0], "call")) {
            snprintf(libpath, sizeof(libpath), "./lib/lib%s.so", argv[1]);
            if (!(handle = dlopen(libpath, RTLD_LAZY))) {
                fprintf(stderr, "vsh: %s: %s\n", libpath, dlerror());
                continue;
            }
            void (*func)(const char *) = (void (*)(const char *)) dlsym(handle, argv[1]);
            if (!func) {
                fprintf(stderr, "vsh: %s: %s\n", argv[1], dlerror());
                dlclose(handle);
                continue;
            }
            func(argv[2] ? argv[2] : "");
            dlclose(handle);
        } else {
            pid_t pid = fork();
            if (pid == -1) { perror("vsh"); continue; }
            if (!pid) {
                if (execvp(argv[0], argv) == -1) {
                    perror("vsh");
                    exit(1);
                }
            } else if (waitpid(pid, NULL, 0) == -1) {
                perror("vsh");
            }
        }
    }
    return 0;
}
