#include "include/buzzer.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

float pwm_clkdiv = 4.0f;            // valor frequência
uint32_t sys_clock_freq = 125000000; // 125 MHz típico do RP2040

// Música vitória
const uint victory_notes[] = {
    523, 659, 784, 1046, 784, 1046, 1318
};

const uint victory_duration[] = {
    300, 300, 300, 600, 300, 600, 900
};

// Música derrota
const uint defeat_notes[] = {
    659, 622, 587, 554, 523
};

const uint defeat_duration[] = {
    200, 200, 200, 200, 400
};

// Música de início de jogo
const uint start_game_notes[] = {
    659, 784, 880, 784, 1046, 1318, 1760, 1568
};

const uint start_game_duration[] = {
    125, 125, 125, 125, 125, 125, 125, 125
};

// Inicializa o PWM
void pwm_init_buzzer(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, pwm_clkdiv);
    
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(pin, 0);
}

// Toca uma nota com a frequência e duração especificadas
void play_tone(uint pin, uint frequency, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);
    
    uint32_t top = (sys_clock_freq / pwm_clkdiv) / frequency - 1;

    pwm_set_wrap(slice_num, top);
    pwm_set_gpio_level(pin, top / 2); // 50% duty cycle

    sleep_ms(duration_ms);

    pwm_set_gpio_level(pin, 0);
    sleep_ms(50);
}

// Função para tocar a música de vitória
void play_victory(uint pin) {
    for (int i = 0; i < sizeof(victory_notes) / sizeof(victory_notes[0]); i++) {
        play_tone(pin, victory_notes[i], victory_duration[i]);
    }
}

// Função para tocar a música de derrota
void play_defeat(uint pin) {
    for (int i = 0; i < sizeof(defeat_notes) / sizeof(defeat_notes[0]); i++) {
        play_tone(pin, defeat_notes[i], defeat_duration[i]);
    }
}

// Função para tocar a música de início de jogo
void play_start_game(uint pin) {
    for (int i = 0; i < sizeof(start_game_notes) / sizeof(start_game_notes[0]); i++) {
        play_tone(pin, start_game_notes[i], start_game_duration[i]);
    }
}

// Função para tocar uma música de início de jogo (som de moeda + poder do Mario)
void play_coin(uint pin) {
    const uint mario_powerup_notes[] = {
        1318, 1568, 1760, 2093, 2637
    };

    const uint mario_powerup_duration[] = {
        100, 100, 100, 150, 200
    };

    for (int i = 0; i < sizeof(mario_powerup_notes) / sizeof(mario_powerup_notes[0]); i++) {
        play_tone(pin, mario_powerup_notes[i], mario_powerup_duration[i]);
    }
}
