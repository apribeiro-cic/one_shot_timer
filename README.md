# Atividade EmbarcaTech - Temporizador de um disparo (One Shot).
# README - Sistema de Temporização para Acionamento de LEDs

## Visão Geral da Atividade
Esta atividade tem como objetivo desenvolver um sistema de temporização para o acionamento de LEDs utilizando a placa **BitDogLab** e o microcontrolador **RP2040 (Raspberry Pi Pico W)**, além de uma simulação do projeto no Wokwi. O sistema opera da seguinte forma:

1. **Ao pressionar o botão (Pushbutton - GPIO 05), os três LEDs RGB (GPIOs 11, 12 e 13) são ligados imediatamente.**
2. **A cada 3 segundos (3.000ms), um LED será desligado** na seguinte ordem:
   - Primeiro, o LED **azul** apaga.
   - Depois, o LED **vermelho** apaga.
   - Por fim, o LED **verde** apaga.
3. **Durante a sequência de desligamento, o botão não pode ser pressionado novamente.**
4. **A gestão da temporização é feita com a função `add_alarm_in_ms()`** do **Pico SDK**.
5. **Foi implementado um debounce via software de 50ms** para evitar leituras falsas do botão.

## Observação Importante
Como as GPIOs da placa BitDogLab estão distribuídas de forma diferente da distribuição recomendada na Tarefa para a simulação no Wokwi, foi criada uma outra branch com o nome 'BitDogLab' com o código adaptado para a placa. (Ambos códigos funcionam na BitDogLab, apenas com LEDs acendendo de forma diferente)

## Requisitos de Software
Para compilar e executar o programa, serão necessários:
- **Pico SDK** instalado
- **Compilador ARM (arm-none-eabi-gcc)**
- **Ambiente de desenvolvimento** (Ex: VS Code)
- **Extensão do Wokwi**
- **Extensão do Raspberry Pi**

## Instruções de Compilação e Execução
1. **Clonar o projeto para sua máquina:**
   ```sh
   git clone https://github.com/apribeiro-cic/one_shot_timer
   ```
   
2. **Importar o projeto pela extensão Raspberry Pi:**
   
   Esse passo pode não ser necessário, pois ao estar com a extensão instalada o VSCode cria a pasta build automaticamente ao ser executado. Porém, se esse não for o caso será necessário importar o projeto pela extensão Raspberry Pi:

   Clique na barra lateral em **Raspberry Pi Pico Project** e em **Import Project**
   
   ![image](https://github.com/user-attachments/assets/8f9351c3-8030-4e3c-a6a5-49b07a4b3265)

   Selecione o diretório e clique em **Import**
   
   ![image](https://github.com/user-attachments/assets/f4ed807c-1d56-427f-a787-fa82fa97228d)

  
4. **Compile o projeto e abra o arquivo 'diagram.json':**
   Compile o projeto e abra o arquivo 'diagram.json' para que a simulação do projeto apareça (Extensão do Wokwi deve estar instalada)
   
   ![image](https://github.com/user-attachments/assets/df5065fd-3d22-4cc7-9c9a-d1b490441a59)

5. **Inicie a simulação do projeto:**
   
   ![image](https://github.com/user-attachments/assets/ffd057d6-7ed0-4d67-94a4-d9e8d186746c)


## Uso do Programa
1. **Pressione o botão** (GPIO 05) para iniciar a sequência.
2. Os **três LEDs acenderão imediatamente**.
3. **A cada 3 segundos, um LED será desligado** na seguinte ordem: azul → vermelho → verde.
4. **O sistema só permite nova interação após todos os LEDs estarem apagados**.

## Considerações Finais
Este projeto demonstra o uso de **interrupções, debounce por software e temporização utilizando a função `add_alarm_in_ms()`** do Pico SDK, junto com o controle de LEDs no RP2040. A implementação foi testada na BitDogLab e simulada no Wokwi.
