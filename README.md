# Biblioteca para proteção de leitura da memória FLASH

**Descrição da biblioteca:**<br>
Biblioteca que permite realizar o bloqueio de leitura da memória FLASH por dispositivos externos, deste modo é possível proteger o microcontrolador de clonagens.
A seguir, temos dois exemplos de tentativas de leitura, sem e com o bloqueio de leitura ativados:
&nbsp;<br>

![clone_stm32_protection](https://user-images.githubusercontent.com/58537514/160456998-6ea08455-0a68-4321-8bf3-6390b969817a.jpg)

**Status do desenvolvimento:**<br>
✅ Concluído
&nbsp;<br> &nbsp;<br>

**Modo de utilização da biblioteca (passo-a-passo):**

1 - Após criar o projeto, insira os arquivos .h e .c deste repositório nas seguintes pastas do projeto a seguir **(1)** e realize a inserção da seguinte linha de código no local mostrado a seguir **(2)**:
```ruby
#include "ProtecaoFlash.h"
```

![screen](https://user-images.githubusercontent.com/58537514/160458344-5945c9f4-e709-4593-8439-da87e0f97ab2.jpg)

2  - Usando a biblioteca:&nbsp;<br>
A biblioteca possui as funções a seguir. O exemplo de utilização está sendo mostrado [neste link](https://github.com/delpitec/C_STM32_Exemplo_LibProtecaoFlash), onde é realizado o bloqueio e desbloqueio de leitura da memória FLASH do STM32 através de estado lógico de teclas com exibição do estado de bloqueio através de LEDs, com explicação e demonstração [em vídeo aqui](https://www.youtube.com/watch?v=wHxHnztGx1g).

&nbsp;<br>

```ruby
// Bloqueia leitura da memória FLASH
void BloquearLeituraDaFlash(void);

// Desbloqueia leitura da memória FLASH
void DesbloquearLeituraDaFlash(void);

// Retorna status de bloqueio da leitura da memória FLASH
uint8_t LerBitsRDP(void);
```
&nbsp;<br><br>

## Contact me:
💼[LinkedIn](https://br.linkedin.com/in/rafaeldelpino)&nbsp;&nbsp;&nbsp;
📹[Youtube](https://www.youtube.com/delpitec)&nbsp;&nbsp;&nbsp;
📸[Instagram](https://www.instagram.com/delpitec_/)&nbsp;&nbsp;&nbsp;
📧[E-mail](delpitec@gmail.com)&nbsp;&nbsp;&nbsp;