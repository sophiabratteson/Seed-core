#ifndef E_INK_DISPLAY_H
#define E_INK_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

void eink_init(void);
void eink_clear(void);
void eink_draw_text(int x, int y, const char *text);
void eink_refresh(void);

#endif
