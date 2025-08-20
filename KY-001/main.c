#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "ds18b20.h"

int main() {
    // Inicializa a E/S padrão (para printf via USB)
    stdio_init_all();
    
    // Uma pausa inicial para dar tempo de conectar o monitor serial
    sleep_ms(1000);
    printf("Iniciando leitor de temperatura DS18B20 (low-level)...\n");

    // Inicializa o pino GPIO
    gpio_init(ONEWIRE_PIN);
    
    while (1) {
        // Verifica se o sensor está conectado antes de cada leitura
        if (!onewire_reset()) {
            printf("Erro: Sensor DS18B20 nao encontrado.\n");
            sleep_ms(3000);
            continue; // Tenta novamente
        }

        // 1. Inicia a conversão de temperatura
        ds18b20_start_conversion();

        // 2. Espera a conversão terminar. O DS18B20 pode levar até 750ms em 12-bit.
        sleep_ms(800);

        // 3. Lê a temperatura
        float temperature = 0.0f;
        if (ds18b20_read_temperature(&temperature)) {
            // 4. Se a leitura foi bem-sucedida, imprime o resultado
            printf("Temperatura: %.2f C\n", temperature);
        } else {
            // 5. Se o CRC falhou, informa o erro
            printf("Erro: Falha na verificacao CRC. Dados corrompidos.\n");
        }

        // 6. Espera antes da próxima leitura
        sleep_ms(2000);
    }

    return 0;
}