#include <stdio.h>
#include "../headers/color.h"

void set_color(int color) {
    const char* color_code;
    switch(color) {
        case 0: color_code = COLOR_BLACK; break;
        case 1: color_code = COLOR_BLUE; break;
        case 2: color_code = COLOR_GREEN; break;
        case 3: color_code = COLOR_CYAN; break;
        case 4: color_code = COLOR_RED; break;
        case 5: color_code = COLOR_MAGENTA; break;
        case 6: color_code = COLOR_YELLOW; break;
        case 7: color_code = COLOR_WHITE; break;
        case 8: color_code = COLOR_DARKGRAY; break;
        case 9: color_code = COLOR_LIGHTBLUE; break;
        case 10: color_code = COLOR_LIGHTGREEN; break;
        case 11: color_code = COLOR_LIGHTCYAN; break;
        case 12: color_code = COLOR_LIGHTRED; break;
        case 13: color_code = COLOR_LIGHTMAGENTA; break;
        case 14: color_code = COLOR_LIGHTYELLOW; break;
        case 15: color_code = COLOR_LIGHTWHITE; break;
        default: color_code = COLOR_WHITE; break;
    }
    printf("\033[%sm", color_code);
}
