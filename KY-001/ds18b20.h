#ifndef DS18B20_H
#define DS18B20_H

#include <stdbool.h>
#include <stdint.h>

#define ONEWIRE_PIN 16 // Pino do Pico conectado ao  módulo GY-001 (DS18B20)

// Declarações de funções para o protocolo 1-Wire

bool onewire_reset();
void onewire_write_bit(int bit);
int onewire_read_bit();
void onewire_write_byte(uint8_t byte);
uint8_t onewire_read_byte();
void ds18b20_start_conversion();
uint8_t crc8(const uint8_t *data, int len);
bool ds18b20_read_temperature(float *temperature_out);




#endif // DS18B20_H