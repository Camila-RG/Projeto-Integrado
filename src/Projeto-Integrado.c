#include <stdio.h>
#include "pico/stdlib.h"
#include "include/setup.h"
#include "include/buzzer.h"
#include "include/matriz_leds.h"
#include "hardware/adc.h"
#include "include/ssd1306.h"
#include <pio_matrix.pio.h>
#include "include/visual.h"
#include "pico/bootrom.h"

#define UART_ID uart0 // Seleciona a UART0
#define BAUD_RATE 115200 // Define a taxa de transmissão
#define UART_TX_PIN 0 // Pino GPIO usado para TX
#define UART_RX_PIN 1 // Pino GPIO usado para RX

// Posição inicial do quadrado (centro da tela)
int pos_x = 60;  // Centro aproximado no eixo X
int pos_y = 28;  // Centro aproximado no eixo Y
extern int contato_contador;
extern int score;
bool game_over_enviado = false; // Para garantir que manda o GAME OVER só uma vez

absolute_time_t start_time;  // Para controlar o tempo do jogo

void gpio_irq_handler(uint gpio, uint32_t events);

// Variáveis globais
static volatile uint a = 1;
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento 

void gpio_irq_handler(uint gpio, uint32_t events)
{
    static uint32_t last_time = 0; // Move para dentro da função pra ser mais seguro
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (current_time - last_time < 200000) {
        // Menos de 200ms, ignorar (estamos "rebatendo" ruído)
        return;
    }
    last_time = current_time; // Atualiza tempo da última ação válida

    if (gpio == BUTTON_A && gpio_get(BUTTON_A) == 0) {
            gerar_novo_alvo();
            score = 0;
            start_time = get_absolute_time();
    }
    else if (gpio == BUTTON_B && gpio_get(BUTTON_B) == 0) {
        // Botão B pressionado
        gpio_set_irq_enabled(BUTTON_A, GPIO_IRQ_EDGE_FALL, false);
        gpio_set_irq_enabled(BUTTON_B, GPIO_IRQ_EDGE_FALL, false);
        uart_puts(UART_ID, "HABILITANDO O MODO GRAVACAO\n");
        printf("HABILITANDO O MODO GRAVAÇÃO");
        sleep_ms(100);
        reset_usb_boot(0,0);
        while (1);
    }
}

int main(){
    setup();
    pwm_init_buzzer(BUZZER_PIN);
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa a UART
     uart_init(UART_ID, BAUD_RATE);

    // Configura os pinos GPIO para a UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); // Configura o pino 0 para TX
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); // Configura o pino 1 para RX
    
    joystick_init(); // inicializa o joystick + display
    abertura_jogo(); // abertura do jogo com matriz de leds e ssd1306
    mensagem_inicial();
    uart_puts(UART_ID, "Jogo iniciado! Boa sorte!");
    start_time = get_absolute_time();

     // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        if (game_running) {
            updatedisplay();  // Atualiza o jogo
            // Aqui calcula o tempo
            int tempo_passado = absolute_time_diff_us(start_time, get_absolute_time()) / 1000000;
            int tempo_restante = 40 - tempo_passado;    
            if (tempo_restante < 0) tempo_restante = 0; // Evita valores negativos
    
            // Mostra no display
            char buffer[20];
            sprintf(buffer, "Tempo: %d", tempo_restante);
    
            // Verifica se acabou o tempo
            if (tempo_passado >= 40) {
                game_running = false;  // Marca fim de jogo
                gpio_put(LED_R_PIN, 1); // Acende LED vermelho
            }
        } else {
            if (!game_over_enviado) {
                mostrar_game_over();
                char buffer[50];
                sprintf(buffer, "GAME OVER! Pontos: %d", score);
                uart_puts(UART_ID, "Jogo finalizado!");
                uart_puts(UART_ID, buffer);
                acender_todos_leds_vermelho();
                game_over_enviado = false;
                sleep_ms(2000);
            }
        }
        
        sleep_ms(20); // Delay para estabilidade
    }
    
}