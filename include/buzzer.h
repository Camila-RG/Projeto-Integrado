#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include "pico/stdlib.h"

#define BUZZER_PIN 21 // Pino do buzzer

extern float pwm_clkdiv;
extern uint32_t sys_clock_freq;

void pwm_init_buzzer(uint pin);
void play_victory(uint pin);
void play_defeat(uint pin);
void play_start_game(uint pin);
void play_coin(uint pin);

#endif // BUZZER_H