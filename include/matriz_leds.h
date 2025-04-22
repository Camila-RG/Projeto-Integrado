#ifndef MATRIZ_LEDS_H
#define MATRIZ_LEDS_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "include/setup.h"
#include "hardware/clocks.h"  // Para clock_get_hz()
#include "hardware/pio.h"     // Para funções PIO

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7

extern PIO pio;
extern uint sm;
extern uint led_r;
extern uint led_g;
extern uint led_b;

void setup();
void coracao();
void acender_led(int index);
void imprimirbinario();
uint32_t matrix_rgb(double b, double r, double g);
void abertura_jogo();
void acender_todos_leds_vermelho();
void piscar_leds_vermelhos();
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b);

#endif // MATRIZ_LEDS_H