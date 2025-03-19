#include <stdio.h>
#include "../headers/color.h"

void set_color
(int color) {
    const char* color_codes[] = {
        COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
        COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE,
        COLOR_DARKGRAY, COLOR_LIGHTBLUE, COLOR_LIGHTGREEN, COLOR_LIGHTCYAN,
        COLOR_LIGHTRED, COLOR_LIGHTMAGENTA, COLOR_LIGHTYELLOW, COLOR_LIGHTWHITE
    };
    
    if (color < 0 || color > 15) color = 7; 
    printf("\033[%sm", color_codes[color]);
}
