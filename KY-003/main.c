#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


// Define o pino GPIO onde o sensor Hall está conectado
#define HALL_SENSOR_PIN 15
#define LED_PIN 0

int main() {

    // Inicializa o pino do sensor
    gpio_init(HALL_SENSOR_PIN);
    gpio_set_dir(HALL_SENSOR_PIN, GPIO_IN);
    // Habilita o resistor de pull-up interno. O pino ficará em HIGH por padrão.
    gpio_pull_up(HALL_SENSOR_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("KY-003 - Sensor de Efeito Hall (Polling)\n");
    printf("Aproxime um imã do sensor.\n");

    // Loop principal
    while (true) {
        // O sensor puxa o pino para LOW quando um campo magnético é detectado.
        // Portanto, lemos 'true' quando o pino está em LOW (!gpio_get).
        bool magnet_detected = !gpio_get(HALL_SENSOR_PIN);

        if (magnet_detected) {
            // Acende o LED se o ímã for detectado
            gpio_put(LED_PIN, 1);
            printf("Campo magnético detectado!\r");
        } else {
            // Apaga o LED se nenhum ímã for detectado
            gpio_put(LED_PIN, 0);
        }

        // Uma pequena pausa para não sobrecarregar o microcontrolador
        sleep_ms(100);
    }

    return 0;
}