# LedHunter - Jogo com Joystick e Matriz de LEDs

Repositório destinado ao desenvolvimento do projeto prático individual, com o objetivo de revisar e consolidar os conhecimentos adquiridos sobre o microcontrolador RP2040 e os principais recursos disponíveis na placa de desenvolvimento BitDogLab.

O projeto consiste na criação de um jogo interativo utilizando joystick analógico, matriz de LEDs, buzzer musical e display OLED, integrando diversas funcionalidades práticas de hardware e software.

---

## Descrição

O objetivo do jogo é movimentar o cursor (controlado pelo joystick) até o alvo mostrado no display OLED.  
Cada acerto:
- Marca 1 ponto,
- Acende o LED verde RGB,
- Toca um som de acerto!

O jogo tem duração de **40 segundos**.  
**Ganha** quem atingir **10 pontos** antes do tempo acabar! 🏆

---

##  Funcionalidades
- Joystick analógico para controle do cursor 🕹️
- Sistema de pontuação e contagem regressiva ⏱️
- Matriz de LEDs mostrando ao final vitória ou derrota 💡
- Música de vitória 🎵 ou derrota 😢 via buzzer
- Display OLED mostrando **score** e **tempo** 📟
- Botão físico para reiniciar o jogo 🔄

---

## 🛠Instalação

1. Clone o repositório:
   ```bash
   git clone [https://github.com/Camila-RG/Projeto-de-Revisao.git](https://github.com/Camila-RG/Projeto-Integrado.git)
   ```

2. Construa o projeto:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Importe o projeto usando a extensão da Raspberry Pi.

---

## Componentes utilizados
- Raspberry Pi Pico (RP2040)
- BitDogLab
- Matriz de LEDs (5x5)
- Display OLED SSD1306 (I2C)
- Joystick analógico
- Buzzer
- Botões físicos

---

## 🎯 Como jogar

- Use o joystick para mover o cursor até o alvo piscando.
- Cada acerto = +1 ponto e acende um LED verde!
- Marque 10 pontos antes do tempo acabar para vencer. 🎉
- Aperte o botão "A" para reiniciar a qualquer momento antes de finalizar o jogo.

---

##  Linguagem Utilizada

- **C**

---

##  Desenvolvedor

- **Camila Ramos Gomes**

---

## Vídeo Explicativo
