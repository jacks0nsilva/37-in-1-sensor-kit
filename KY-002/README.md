# KY-002: Módulo Interruptor de Vibração

Este diretório contém um projeto de exemplo para o **Raspberry Pi Pico W** que demonstra como detectar vibrações ou impactos utilizando o módulo KY-002.

A abordagem utilizada aqui é baseada em **polling**, onde o estado do pino do sensor é verificado continuamente dentro de um loop. Quando uma vibração é detectada, um LED conectado ao Pico W acende como indicador visual e uma mensagem é impressa no console serial.

Este projeto faz parte de uma coleção maior para explorar 37 periféricos com o Raspberry Pi Pico W. Para mais informações, consulte o [README principal do repositório](../README.md).

## ✨ Funcionalidades

- **Leitura de Entrada Digital:** Demonstra a forma básica de ler o estado de um pino (ALTO ou BAIXO).
- **Método de Polling:** Utiliza um loop `while` para verificar constantemente o estado do sensor.
- **Feedback Visual:** Acende um LED para indicar visualmente que uma vibração foi detectada.
- **Sem dependências externas:** Utiliza apenas as bibliotecas padrão do Pico C/C++ SDK.

## 🛠️ Componentes Necessários

- 1x Raspberry Pi Pico W
- 1x Módulo Interruptor de Vibração KY-002
- 1x LED (qualquer cor)
- 1x Resistor de ~330Ω (para limitar a corrente do LED)
- Protoboard e Jumpers

## 🔌 Esquema de Ligação

O módulo envia um sinal BAIXO (GND) quando uma vibração é detectada. É recomendado usar o resistor de pull-up interno do Pico W para manter o pino em nível ALTO em estado de repouso.

| Componente               | Conexão                 | Pino do Raspberry Pi Pico W |
| :----------------------- | :---------------------- | :-------------------------- |
| **Módulo KY-002: GND**   | Terra                   | **GND** (ex: Pino 3)        |
| **Módulo KY-002: VCC**   | Alimentação 3.3V        | **3V3 (OUT)** (Pino 36)     |
| **Módulo KY-002: Sinal** | Pino de Dados do Sensor | **GPIO 18** (Pino 24)       |
| **LED: Cátodo (-)**      | Terra                   | **GND** (ex: Pino 38)       |
| **LED: Anodo (+)**       | Via Resistor de 330Ω    | **GPIO 0** (Pino 1)         |

## 💻 Estrutura do Código

Dada a simplicidade da abordagem de polling, todo o código necessário está contido em um único arquivo:

- **`main.c`**: Contém toda a lógica: configuração dos pinos de GPIO (um como entrada para o sensor, outro como saída para o LED) e o loop principal infinito que lê o sensor e controla o LED.

## ⚙️ Como Funciona

O módulo KY-002 contém um interruptor mecânico que reage a vibrações. A detecção via polling funciona da seguinte forma:

1.  **Configuração Inicial**: O `GPIO 18` é configurado como uma entrada digital (e deve-se usar um pull-up, seja interno ou externo) e o `GPIO 0` é configurado como uma saída para o LED.
2.  **Estado de Repouso**: O interruptor interno do sensor está aberto. O resistor de pull-up mantém o `GPIO 18` em nível lógico **ALTO** (3.3V).
3.  **Loop de Verificação (Polling)**: O loop `while(true)` no código executa milhares de vezes por segundo. A cada iteração, a função `gpio_get(SENSOR_PIN)` lê o estado do `GPIO 18`.
4.  **Vibração Detectada**: Uma vibração faz o interruptor interno se fechar, conectando o pino de sinal ao GND. Isso puxa o `GPIO 18` para o nível lógico **BAIXO** (0V).
5.  **Ação no Código**: Dentro do loop, a condição `if` detecta essa mudança para o estado BAIXO. Quando isso ocorre, o código executa `gpio_put(LED_PIN, 1)` para acender o LED e imprime "Vibração detectada!" no monitor serial.
6.  **Fim da Vibração**: Assim que a vibração cessa, o interruptor se abre novamente, o pino volta ao estado ALTO e, na próxima iteração do loop, a condição `else` é atendida, apagando o LED com `gpio_put(LED_PIN, 0)`.

---
