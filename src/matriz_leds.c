#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pio_matrix.pio.h"
#include "include/matriz_leds.h"
#include "include/buzzer.h"
#include "include/visual.h"

//imprimir valor binário
void imprimir_binario(int num) {
 int i;
 for (i = 31; i >= 0; i--) {
  (num & (1 << i)) ? printf("1") : printf("0");
 }
}

// Definição da intensidade dos leds
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//rotina para acionar a matrix de leds - ws2812
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        if (i%2==0)
        {
            valor_led = matrix_rgb(b = 0.0, desenho[24-i], desenho[24-i]);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led = matrix_rgb(b = 0.0, desenho[24-i], desenho[24-i]);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

void desenho_pio2(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        if (i%2==0)
        {
            valor_led = matrix_rgb(desenho[24-i], g = 0.0, r = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led = matrix_rgb(desenho[24-i], g = 0.0, r = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

void desenho_pio3(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        if (i%2==0)
        {
            valor_led = matrix_rgb(r = 0.0, g = 0.0, desenho[24-i]);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led = matrix_rgb(r = 0.0, g = 0.0, desenho[24-i]);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

double desenho0[25] =   
    {0.0, 0.0, 0.3, 0.3, 0.0,
    0.3, 0.3, 0.3, 0.3, 0.0, 
    0.0, 0.3, 0.3, 0.3, 0.3,
    0.3, 0.3, 0.3, 0.3, 0.0,
    0.0, 0.0, 0.3, 0.3, 0.0};

double desenho1[25] =   
    {0.0, 0.0, 0.3, 0.0, 0.0,
    0.0, 0.3, 0.3, 0.0, 0.0, 
    0.0, 0.0, 0.3, 0.3, 0.0,
    0.0, 0.3, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.0, 0.0};
    
double desenho2[25] =   
    {0.0, 0.0, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.0, 0.0, 
    0.0, 0.0, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.0, 0.0};

double desenho3[25] =   
    {0.0, 0.0, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.3, 0.0, 
    0.0, 0.3, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.3, 0.0,
    0.0, 0.0, 0.3, 0.0, 0.0};

double desenho4[25] =   
    {0.0, 0.0, 0.3, 0.0, 0.0,
    0.0, 0.3, 0.3, 0.0, 0.0, 
    0.0, 0.0, 0.3, 0.3, 0.3,
    0.0, 0.3, 0.3, 0.0, 0.0,
    0.0, 0.0, 0.3, 0.0, 0.0};

double desenho5[25] =   
    {0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0};

double desenho7[25] =   
    {0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0};

double desenho6[25] = 
{
        0.0, 0.3, 0.0, 0.3, 0.0, 
        0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3, 0.3, 0.3, 
        0.0, 0.3, 0.3, 0.3, 0.0, 
        0.0, 0.0, 0.3, 0.0, 0.0,
};

void abertura_jogo(){
    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, WS2812_PIN);
    double r = 0.0, b = 1.0 , g = 0.0;
    desenho_pio(desenho5, valor_led, pio, sm, r, g, b);

    mensagem_inicial();
    for (int i=0; i < 2; i++){
        play_start_game(BUZZER_PIN);
        desenho_pio2(desenho4, valor_led, pio, sm, r, g, b);
        sleep_ms(500);
        desenho_pio(desenho5, valor_led, pio, sm, r, g, b);
    }

    for(int a=0; a < 3; a++)
    {
        play_coin(BUZZER_PIN);
        desenho_pio(desenho0, valor_led, pio, sm, r, g, b);
        sleep_ms(200);
        desenho_pio(desenho1, valor_led, pio, sm, r, g, b);
        sleep_ms(200);
        desenho_pio(desenho2, valor_led, pio, sm, r, g, b);
        sleep_ms(200);
        desenho_pio(desenho3, valor_led, pio, sm, r, g, b);
        sleep_ms(200);
        desenho_pio(desenho0, valor_led, pio, sm, r, g, b);
        sleep_ms(200);
        desenho_pio(desenho5, valor_led, pio, sm, r, g, b);
    }

    desenho_pio(desenho5, valor_led, pio, sm, r, g, b);
}

// vetor para guardar quais LEDs estão acesos
static double desenho_atual[25] = {0}; // Tudo apagado no começo

// função que acende um LED pelo índice
void acender_led(int index) {
    if (index < 0 || index >= 25) return; // Proteção básica

    desenho_atual[24 - index] = 0.3; // acende o LED no índice (ajuste para seu desenho ser invertido)
    
    // Atualiza a matriz de LEDs
    PIO pio = pio0;
    uint32_t valor_led = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, WS2812_PIN);

    double r = 0.0, g = 1.0, b = 0.0; // Verde
    desenho_pio(desenho_atual, valor_led, pio, sm, r, g, b);
}

void acender_todos_leds_vermelho() {
    double desenho_vermelho[25];

    for (int i = 0; i < 25; i++) {
        desenho_vermelho[i] = 0.3; // Brilho de 30%
    }

    PIO pio = pio0;
    uint32_t valor_led = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, WS2812_PIN);

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(0.0, desenho_vermelho[24-i], 0.0); // Vermelho agora no lugar certo
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

void piscar_leds_vermelhos() {
    PIO pio = pio0;
    uint32_t valor_led = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, WS2812_PIN);

    for (int k = 0; k < 3; k++) { // Piscando 3 vezes
        // Liga vermelho
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.0, 0.3, 0.0); // Vermelho 30%
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        sleep_ms(300);

        // Apaga
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.0, 0.0, 0.0); // Tudo apagado
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        sleep_ms(300);
    }
}

void coracao(){
    PIO pio = pio0;
    uint32_t valor_led = 0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, WS2812_PIN);
    double r = 1.0, b = 0.0 , g = 0.0;

    for(int a=0; a < 3; a++)
        {
        play_coin(BUZZER_PIN);
        desenho_pio3(desenho6, valor_led, pio, sm, r, g, b);
        sleep_ms(200);
        desenho_pio(desenho7, valor_led, pio, sm, r, g, b);
        }
}