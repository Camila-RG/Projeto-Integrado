#include "include/setup.h"

// Função para configurar os pinos e iniciar o display
void setup() {
    stdio_init_all();

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_init(BUTTON_JS);
    gpio_set_dir(BUTTON_JS, GPIO_IN);
    gpio_pull_up(BUTTON_JS);

    gpio_init(LED_G_PIN);  // Inicializa o LED verde
    gpio_set_dir(LED_G_PIN, GPIO_OUT);  // Configura como saída

    gpio_init(LED_B_PIN);  // Inicializa o LED azul
    gpio_set_dir(LED_B_PIN, GPIO_OUT);  // Configura como saída

    gpio_init(LED_R_PIN);  // Inicializa o LED vermelho
    gpio_set_dir(LED_R_PIN, GPIO_OUT);  // Configura como saída
}