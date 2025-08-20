#include "ds18b20.h"
#include <pico/stdlib.h>


/**
 * @brief Envia um pulso de reset no barramento 1-Wire e verifica a presença de dispositivos.
 * 
 * @return true Se um dispositivo respondeu com um pulso de presença.
 * @return false Se nenhum dispositivo foi detectado.
 */
bool onewire_reset() {
    // Puxa a linha para baixo por 480µs (Reset Pulse)
    gpio_set_dir(ONEWIRE_PIN, GPIO_OUT);
    gpio_put(ONEWIRE_PIN, 0);
    busy_wait_us(480);

    // Libera a linha e espera o dispositivo responder (Presence Pulse)
    gpio_set_dir(ONEWIRE_PIN, GPIO_IN);
    busy_wait_us(70);

    // Lê o estado da linha. Se estiver baixa, um dispositivo está presente.
    bool presence = !gpio_get(ONEWIRE_PIN);

    // Espera o restante do tempo (total de 480µs)
    busy_wait_us(410);

    return presence;
}

/**
 * @brief Escreve um único bit no barramento 1-Wire.
 * 
 * @param bit O bit a ser escrito (0 ou 1).
 */
void onewire_write_bit(int bit) {
    // Para escrever '1': puxa a linha para baixo por ~6µs e libera.
    // Para escrever '0': puxa a linha para baixo por ~60µs e libera.
    gpio_set_dir(ONEWIRE_PIN, GPIO_OUT);
    gpio_put(ONEWIRE_PIN, 0);
    busy_wait_us(bit ? 6 : 60);
    
    gpio_put(ONEWIRE_PIN, 1); // Libera a linha
    busy_wait_us(bit ? 64 : 10);
}

/**
 * @brief Lê um único bit do barramento 1-Wire.
 * 
 * @return int O valor do bit lido (0 ou 1).
 */
int onewire_read_bit() {
    // Para ler, puxamos a linha para baixo brevemente (~6µs) para iniciar o "read time slot".
    gpio_set_dir(ONEWIRE_PIN, GPIO_OUT);
    gpio_put(ONEWIRE_PIN, 0);
    busy_wait_us(6);

    // Liberamos a linha e a configuramos como entrada para ler a resposta do sensor.
    gpio_set_dir(ONEWIRE_PIN, GPIO_IN);
    busy_wait_us(9);

    int bit = gpio_get(ONEWIRE_PIN);

    // Esperamos o restante do "time slot" para garantir a temporização correta.
    busy_wait_us(55);

    return bit;
}

/**
 * @brief Escreve um byte (8 bits) no barramento.
 */
void onewire_write_byte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        onewire_write_bit(byte & 1);
        byte >>= 1; // Próximo bit (LSB primeiro)
    }
}

/**
 * @brief Lê um byte (8 bits) do barramento.
 */
uint8_t onewire_read_byte() {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        byte >>= 1; // Abre espaço para o próximo bit
        if (onewire_read_bit()) {
            byte |= 0x80; // Coloca o bit lido na posição mais significativa
        }
    }
    return byte;
}

// --- Funções Específicas para o Sensor DS18B20 ---

// Comandos do DS18B20
const uint8_t CMD_CONVERT_T = 0x44;
const uint8_t CMD_READ_SCRATCHPAD = 0xBE;
const uint8_t CMD_SKIP_ROM = 0xCC;

/**
 * @brief Inicia a conversão de temperatura no sensor.
 */
void ds18b20_start_conversion() {
    onewire_reset();
    onewire_write_byte(CMD_SKIP_ROM); // Comando para todos os dispositivos na linha
    onewire_write_byte(CMD_CONVERT_T); // Comando para converter a temperatura
}

/**
 * @brief Calcula o CRC8 dos dados para verificar a integridade.
 */
uint8_t crc8(const uint8_t *data, int len) {
    uint8_t crc = 0;
    for (int i = 0; i < len; i++) {
        uint8_t byte = data[i];
        for (int j = 0; j < 8; j++) {
            uint8_t mix = (crc ^ byte) & 0x01;
            crc >>= 1;
            if (mix) {
                crc ^= 0x8C; // Polinômio x^8 + x^5 + x^4 + 1
            }
            byte >>= 1;
        }
    }
    return crc;
}

/**
 * @brief Lê a temperatura do sensor após uma conversão.
 * 
 * @param temperature_out Ponteiro para a variável float onde a temperatura será armazenada.
 * @return true Se a leitura e a verificação CRC forem bem-sucedidas.
 * @return false Se ocorrer um erro (CRC inválido).
 */
bool ds18b20_read_temperature(float *temperature_out) {
    uint8_t scratchpad[9];
    
    onewire_reset();
    onewire_write_byte(CMD_SKIP_ROM);
    onewire_write_byte(CMD_READ_SCRATCHPAD);
    
    // Lê os 9 bytes do "scratchpad" (memória de rascunho do sensor)
    for (int i = 0; i < 9; i++) {
        scratchpad[i] = onewire_read_byte();
    }

    // O 9º byte é o CRC. Verificamos se os 8 primeiros bytes estão corretos.
    if (crc8(scratchpad, 8) == scratchpad[8]) {
        // A temperatura está nos dois primeiros bytes (LSB, MSB)
        int16_t raw_temp = (scratchpad[1] << 8) | scratchpad[0];
        
        // Converte o valor raw para Celsius (para resolução de 12 bits)
        *temperature_out = (float)raw_temp / 16.0f;
        return true;
    }

    // Se o CRC falhou, retorna erro
    return false;
}
