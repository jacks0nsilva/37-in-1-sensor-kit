# KY-003: Sensor Magnético de Efeito Hall

Este diretório contém um projeto de exemplo para o **Raspberry Pi Pico W** que demonstra como detectar um campo magnético utilizando o módulo KY-003.

O sensor de Efeito Hall neste módulo fornece uma saída **digital**, funcionando como um interruptor que é ativado pela presença de um ímã. A abordagem utilizada neste código é baseada em **polling**, onde o estado do sensor é verificado continuamente. Um LED externo é usado como indicador visual.

Este projeto faz parte de uma coleção maior para explorar 37 periféricos com o Raspberry Pi Pico W. Para mais informações, consulte o [README principal do repositório](../README.md).

![Esquema de Ligação](diagrama.jpg)

## ✨ Funcionalidades

- **Detecção de Campo Magnético:** Demonstra o uso de um sensor de Efeito Hall digital.
- **Método de Polling:** Utiliza um loop `while` para verificar constantemente o estado do sensor.
- **Feedback Visual:** Acende um LED externo para indicar a detecção de um campo magnético.
- **Pull-up Interno:** Utiliza o resistor de pull-up interno do Pico W para garantir níveis de tensão seguros e simplificar o circuito.
- **Sem dependências externas:** Utiliza apenas as bibliotecas padrão do Pico C/C++ SDK.

## 🛠️ Componentes Necessários

- 1x Raspberry Pi Pico W
- 1x Módulo Sensor de Efeito Hall KY-003
- 1x LED (qualquer cor)
- 1x Resistor de ~330Ω (para o LED)
- Protoboard e Jumpers

## 🔌 Esquema de Ligação

O módulo KY-003 deve ser alimentado com 5V para operar corretamente. No entanto, sua saída de sinal é do tipo "coletor aberto", o que nos permite conectá-lo diretamente e com segurança a um pino do Pico W, desde que habilitemos o resistor de pull-up interno do microcontrolador.

| Componente               | Conexão              | Pino do Raspberry Pi Pico W |
| :----------------------- | :------------------- | :-------------------------- |
| **Módulo KY-003: GND**   | Terra                | **GND** (ex: Pino 38)       |
| **Módulo KY-003: VCC**   | Alimentação 5V       | **Alimentação externa**     |
| **Módulo KY-003: Sinal** | Pino de Sinal        | **GPIO 15** (Pino 20)       |
| **LED: Cátodo (-)**      | Terra                | **GND** (ex: Pino 3)        |
| **LED: Anodo (+)**       | Via Resistor de 330Ω | **GPIO 0** (Pino 1)         |

## 💻 Estrutura do Código

Para este projeto, todo o código está contido em um único arquivo para simplificar:

- **`main.c`**: Contém a lógica de configuração dos GPIOs (sensor com pull-up interno e LED) e o loop principal que continuamente verifica o sensor e atualiza o estado do LED.

## ⚙️ Como Funciona

1.  **Alimentação**: O sensor é alimentado com 5V externos, mas sua saída de sinal é compatível com os níveis de 3.3V do Pico W devido ao seu design de coletor aberto.
2.  **Estado de Repouso**: O código ativa o resistor de pull-up interno do `GPIO 15`. Como o sensor (sem ímã) não está fazendo nada na linha de sinal, este resistor a puxa para **3.3V**, e o Pico W lê um nível lógico **ALTO**.
3.  **Loop de Polling**: O loop `while(true)` no código lê o estado do `GPIO 15` centenas de vezes por segundo usando `gpio_get()`.
4.  **Detecção de Campo Magnético**: Ao aproximar um ímã, o sensor é ativado e internamente conecta o pino de sinal ao **GND**. Isso anula o efeito do resistor de pull-up e puxa a tensão do `GPIO 15` para **0V** (nível lógico **BAIXO**).
5.  **Ação no Código**: A condição `if (magnet_detected)` se torna verdadeira, pois a lógica `!gpio_get(HALL_SENSOR_PIN)` detecta o nível BAIXO. O código então acende o LED com `gpio_put(LED_PIN, 1)`.
6.  **Remoção do Campo**: Quando o ímã é afastado, o sensor "solta" a linha novamente, o pull-up interno a eleva para 3.3V (ALTO), e a condição `else` é executada, apagando o LED.

---
