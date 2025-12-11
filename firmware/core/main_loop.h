#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include <stdint.h>
#include <stdbool.h>

void seed_main_loop(void);
void seed_initialize_system(void);
void seed_process_events(void);
void seed_sleep_cycle(void);

#endif
