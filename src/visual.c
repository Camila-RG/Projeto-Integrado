#include "include/visual.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "include/setup.h"
#include "include/buzzer.h"
#include "include/matriz_leds.h"
#include "hardware/adc.h"
#include "include/ssd1306.h"
#include <pio_matrix.pio.h>

bool game_running = true;    // Para saber se o jogo está ativo

ssd1306_t ssd;
int alvo_x = 30;
int alvo_y = 0;
int score=0;
int contato_contador=0;

extern int pos_x;
extern int pos_y;

const int frames_para_acertar = 3; // Quantos frames encostando pra contar ponto

void gerar_novo_alvo() {
    alvo_x = rand() % (WIDTH - 5);
    alvo_y = rand() % ((HEIGHT/2) - 5); // Só na metade de cima
}

void joystick_init() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);

    start_time = get_absolute_time();

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    
    bool cor = true;
    ssd1306_fill(&ssd, !cor);
    ssd1306_rect(&ssd, pos_x, pos_y, 8, 8, cor, !cor);
    ssd1306_send_data(&ssd);

    gerar_novo_alvo();
}

void ler_joystick(uint16_t *x, uint16_t *y) {
    adc_select_input(0);
    *x = adc_read();
    adc_select_input(1);
    *y = adc_read();
}

void updatedisplay() {
    uint16_t adc_x, adc_y;
    ler_joystick(&adc_x, &adc_y);

    pos_y = (adc_y * 120) / 4095; 
    pos_x = 56 - (adc_x * 56) / 4095;

    if (abs(adc_y - 2048) < DEAD_ZONE) pos_y = 60;
    if (abs(adc_x - 2048) < DEAD_ZONE) pos_x = 28;

    if (gpio_get(BUTTON_JS) == 0) { // 0 = botão pressionado
        gerar_novo_alvo();
        sleep_ms(200); // debounce manual pra não criar 1000 alvos de uma vez
    }

    // Verificar se está perto do alvo
    if (abs(pos_x - alvo_x) < 8 && abs(pos_y - alvo_y) < 8) {
        contato_contador++;
        if (contato_contador >= frames_para_acertar) {
            score++;
            gpio_put(LED_G_PIN, 1); 
            sleep_ms(100);          
            gpio_put(LED_G_PIN, 0); 
            gerar_novo_alvo();
            contato_contador = 0;
            play_coin(BUZZER_PIN);
        }
    } else {
        contato_contador = 0;
    }

    // Atualiza tela
    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, pos_x, pos_y, 8, 8, true, true);
    ssd1306_rect(&ssd, alvo_x, alvo_y, 5, 5, true, true);

    char buffer[30];
    sprintf(buffer, "Score: %d", score);
    ssd1306_draw_string(&ssd, buffer, 0, 0);

    absolute_time_t agora = get_absolute_time();
    int tempo_passado_ms = absolute_time_diff_us(start_time, agora) / 1000;
    int tempo_restante = 40000 - tempo_passado_ms;

    if (tempo_restante < 0) tempo_restante = 0;

    char tempo_buffer[20];
    sprintf(tempo_buffer, "Tempo: %ds", tempo_restante / 1000);
    ssd1306_draw_string(&ssd, tempo_buffer, 0, 10);
    
    if (score >= 10) {
        game_running = false;
        ssd1306_fill(&ssd, false);
        ssd1306_draw_string(&ssd, "PARABENS!", 20, 20);
        ssd1306_draw_string(&ssd, "VOCE VENCEU!", 10, 40);
        ssd1306_send_data(&ssd);
        play_victory(BUZZER_PIN);
        gerar_novo_alvo();
        coracao();
        score = 0;
        start_time = get_absolute_time();
        return;
    }

    if (tempo_restante == 0) {
        game_running = false;
        mostrar_game_over();
        acender_todos_leds_vermelho();
        void resetar_jogo();
        return; // Sai para não redesenhar
    }

    ssd1306_send_data(&ssd);
}


void mostrar_game_over() {
    ssd1306_fill(&ssd, false); // Limpa a tela
    ssd1306_draw_string(&ssd, "GAME OVER", 30, 20); // Escreve no meio da tela
    play_defeat(BUZZER_PIN);
    ssd1306_send_data(&ssd);

    ssd1306_fill(&ssd, false); // Limpa a tela
}

void mensagem_inicial() {
    // Código para mostrar "Bem-vindo" no display, por exemplo
    ssd1306_fill(&ssd, false);
    ssd1306_draw_string(&ssd, "Bem-vindo!", 20, 30);
    ssd1306_send_data(&ssd);
}

void limpar_tela(){
        // Atualiza tela
        ssd1306_fill(&ssd, false);
        ssd1306_rect(&ssd, pos_x, pos_y, 8, 8, true, true); // quadrado jogador
        ssd1306_rect(&ssd, alvo_x, alvo_y, 5, 5, true, true); // alvo
}

void resetar_jogo() {
    score = 0;
    contato_contador = 0;
    start_time = get_absolute_time();
    game_running = true;
    gerar_novo_alvo();
    limpar_tela();
    mensagem_inicial();
    sleep_ms(1000); // Pequena pausa para o jogador ver a mensagem
}