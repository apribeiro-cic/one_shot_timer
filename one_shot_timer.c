#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

const uint led_pin_red = 13;
const uint led_pin_green = 11;
const uint led_pin_blue = 12;
const uint btn_A = 5;

static volatile bool current_state = 0; // Diz se a rotina de callback está em execução
static volatile uint8_t led_state = 0; // Diz qual etapa da rotina de callback está sendo executada

void setup_GPIOs() { // Função para configurar as GPIOs
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);

    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);

    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);

    gpio_init(btn_A);
    gpio_set_dir(btn_A, GPIO_IN);
    gpio_pull_up(btn_A);
}

void turn_on_LEDs() { // Liga todos os LEDs
    gpio_put(led_pin_red, 1);
    gpio_put(led_pin_green, 1);
    gpio_put(led_pin_blue, 1);
}

int64_t turn_off_callback(alarm_id_t id, void *user_data) { // Callback para desligar os LEDs
    switch (led_state) {
        case 0:  // Desliga o azul
            gpio_put(led_pin_blue, 0);
            led_state++;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case 1:  // Desliga o vermelho
            gpio_put(led_pin_red, 0);
            led_state++;
            add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            break;
        case 2:  // Desliga o verde e libera o botão
            gpio_put(led_pin_green, 0);
            current_state = 0;
            led_state = 0;
            break;
    }
    return 0;
}

int main()
{
    stdio_init_all();
    setup_GPIOs();

    while (true) {
        if (gpio_get(btn_A) == 0 && !current_state) { // Se o botão A for pressionado e a rotina de callback não estiver em execução
            sleep_ms(50); // Debounce de 50ms
            
            if (gpio_get(btn_A) == 0) { // Se o botão A ainda estiver pressionado após o debounce
                turn_on_LEDs(); 
                current_state = 1; 
                
                add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Adiciona um alarme para desligar os LEDs em 3 segundos (3000ms)
            }
        }
        sleep_ms(10); // Delay para evitar o uso excessivo da CPU
    }
}
