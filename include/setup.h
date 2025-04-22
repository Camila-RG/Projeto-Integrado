#ifndef SETUP_H
#define SETUP_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definição dos pinos
#define JOY_X 26
#define JOY_Y 27
#define BUTTON_JS 22
#define BUTTON_A 5 
#define BUTTON_B 6
#define LED_G_PIN 11
#define LED_B_PIN 12
#define LED_R_PIN 13 

void setup();

#endif // SETUP_H