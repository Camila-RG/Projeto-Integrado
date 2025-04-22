#ifndef VISUAL_H
#define VISUAL_H

#include <stdint.h>
#include "pico/stdlib.h"

#define JOYSTICK_X_PIN 26  // GPIO para eixo X
#define JOYSTICK_Y_PIN 27  // GPIO para eixo Y
#define JOYSTICK_PB 22     // GPIO para botão do Joystick

// Valores de calibração do joystick
#define JOYSTICK_CENTER_X 2048  // Valor central aproximado do joystick X
#define JOYSTICK_CENTER_Y 2048  // Valor central aproximado do joystick Y
#define JOYSTICK_DEADZONE 300   // Zona morta para evitar vibrações quando o joystick está em repouso
#define DEAD_ZONE 150// visual.h

extern int pos_x;
extern int pos_y;
extern int adc_value_x;
extern int adc_value_y;
extern int alvo_x, alvo_y;
extern char str_x[5];
extern char str_y[5];
extern bool game_running;    // Para saber se o jogo está ativo
extern absolute_time_t start_time;
extern int score; // apenas declara, não cria uma nova variável
extern int contato_contador; // Novo contador de "toques"

void resetar_jogo();
void limpar_tela();
void mostrar_game_over();
void joystick_init();
void updatedisplay();
void gerar_novo_alvo();
void mensagem_inicial();
void ler_joystick(uint16_t *x, uint16_t *y);

#endif // VISUAL_H