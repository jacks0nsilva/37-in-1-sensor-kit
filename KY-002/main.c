#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 0
#define SENSOR_PIN 18

int main()
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(SENSOR_PIN);
    gpio_set_dir(SENSOR_PIN, GPIO_IN);

    printf("KY-002 sensor de vibração\n");

    while (true) {
        if(gpio_get(SENSOR_PIN)) {
            gpio_put(LED_PIN, 1);
            printf("Vibração detectada!\n");
        } else {
            gpio_put(LED_PIN, 0);
        }
    }
}
