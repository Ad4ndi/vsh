#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/prompt.h"
#include "../headers/color.h"

void parse() {
    char *temp_prompt = prompt, buffer[256];
    for (int i = 0; temp_prompt[i] != '\0'; i++) {
        if (temp_prompt[i] == '\\') {
            i++;
            switch (temp_prompt[i]) {
                case 'h': gethostname(buffer, sizeof(buffer)); printf("%s", buffer); break;
                case 'u': {
                    char *user = getenv("USER");
                    if (user) printf("%s", user);
                    break;
                }
                case 'w': if (getcwd(buffer, sizeof(buffer)) != NULL) printf("%s", buffer); break;
                case 'c': if (temp_prompt[++i] == '(') set_color(atoi(&temp_prompt[i+1])); while (temp_prompt[i] != ')' && temp_prompt[i] != '\0') i++; break;
                default: putchar('\\'); putchar(temp_prompt[i]);
            }
        } else {
            putchar(temp_prompt[i]);
        }
    }
    set_color(15);
}
