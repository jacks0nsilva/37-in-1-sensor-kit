---

# Raspberry Pi Pico W - Explorando Periféricos com C SDK

Bem-vindo a este repositório dedicado a explorar a vasta gama de periféricos disponíveis para o Raspberry Pi Pico W, utilizando o C/C++ SDK oficial. O objetivo deste projeto é fornecer exemplos de código claros, bem documentados e fáceis de usar para 37 periféricos diferentes, abrangendo desde sensores e atuadores básicos até módulos de comunicação mais complexos.

## 🚀 Sobre o Projeto

O Raspberry Pi Pico W, com seu microcontrolador RP2040 de núcleo duplo ARM Cortex M0+, oferece uma plataforma poderosa e de baixo custo para o desenvolvimento de sistemas embarcados. Este repositório serve como um guia prático e uma coleção de projetos para ajudar desenvolvedores, estudantes e entusiastas a aproveitarem ao máximo os recursos do Pico no ambiente de programação C.

Cada projeto neste repositório é autocontido e focado em um único periférico, demonstrando como inicializá-lo e interagir com ele.

## 🛠️ Como Começar

Para compilar e executar os projetos deste repositório, você precisará ter o ambiente de desenvolvimento do Raspberry Pi Pico W C/C++ SDK configurado em sua máquina.

### Pré-requisitos

Certifique-se de ter as seguintes ferramentas instaladas:

*   **ARM GCC Compiler**
*   **Git**
*   **SDK do Raspberry Pi Pico**

## 📂 Estrutura do Repositório

O repositório está organizado da seguinte forma:

```
├── peripheral_01/       # Projeto para o periférico 1
│   ├── main.c
|   ├── CMakeLists.txt
│   └── README.md
├── peripheral_02/       # Projeto para o periférico 2
│   ├── main.c
|   ├── CMakeLists.txt
│   └── README.md
...
├── peripheral_37/       # Projeto para o periférico 37
│   ├── main.c
|   ├── CMakeLists.txt
│   └── README.md
├── .gitignore
└── README.md
```

### Como Compilar e Executar um Projeto

1.  **Navegue até o diretório do projeto desejado:**
    ```bash
    cd peripheral_xx
    ```

2.  **Crie um diretório de compilação:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Execute o CMake para gerar os arquivos de compilação:**
    ```bash
    cmake ..
    ```

4.  **Compile o projeto:**
    ```bash
    make
    ```

5.  **Carregue o firmware no Pico:**
    *   Pressione e segure o botão `BOOTSEL` no seu Pico e conecte-o ao seu computador via USB.
    *   Ele será montado como um dispositivo de armazenamento em massa chamado `RPI-RP2`.
    *   Arraste e solte o arquivo `.uf2` gerado no diretório `build` para o dispositivo `RPI-RP2`.
    *   O Pico será reiniciado automaticamente e começará a executar o programa.

## 🔌 Periféricos Explorados

Abaixo está a lista dos 37 periféricos que serão abordados neste repositório. Conforme os projetos forem concluídos, a lista será atualizada com links para os respectivos diretórios.

1.  [KY-001 - Sensor de Temperatura]()


## 🤝 Como Contribuir

Contribuições são o que tornam a comunidade de código aberto um lugar incrível para aprender, inspirar e criar. Quaisquer contribuições que você fizer serão **muito apreciadas**.

Se você tiver uma sugestão para melhorar este projeto, por favor, faça um fork do repositório e crie uma pull request. Você também pode simplesmente abrir uma issue com a tag "melhoria".

1.  Faça um Fork do Projeto
2.  Crie sua Feature Branch (`git checkout -b feature/Atualizacao`)
3.  Faça o Commit de suas mudanças (`git commit -m 'Sua mensagem de commit'`)
4.  Faça o Push para a Branch (`git push origin feature/Atualizacao`)
5.  Abra uma Pull Request

## 📜 Licença

Distribuído sob a Licença MIT. Veja `LICENSE` para mais informações.

## 📧 Contato

Jackson Silva dos Santos - [Instagram](https://www.instagram.com/jacks0n_ss/) - jacksonsilva_fsa@outlook.com

Link do Projeto: [https://github.com/jacks0nsilva/37-in-1-sensor-kit](https://github.com/jacks0nsilva/37-in-1-sensor-kit)

---
