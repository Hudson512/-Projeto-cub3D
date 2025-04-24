# 🧱 Projeto cub3D - 42
## 📜 Descrição
cub3D é um projeto de design gráfico em C que consiste em criar uma representação 3D de um labirinto usando a técnica de raycasting. A visualização deve ser em primeira pessoa, similar aos jogos clássicos como Wolfenstein 3D.

Este projeto é uma excelente introdução prática à aplicação da matemática, algoritmos e à manipulação gráfica com MiniLibX, além de reforçar o uso da linguagem C e boas práticas de programação.

## 🎯 Objetivos
Criar uma visualização 3D de um labirinto a partir de um arquivo .cub

Aplicar conceitos de matemática para projetar uma engine de raycasting simples

Trabalhar com gráficos, eventos e renderização em tempo real

Desenvolver habilidades em parsing de arquivos, estruturas de dados e organização de código

## 🛠️ Requisitos Técnicos
### ✔️ Funcionalidades Obrigatórias
O programa deve se chamar cub3D

Deve aceitar como argumento um arquivo .cub

Renderizar a cena 3D baseada no conteúdo do arquivo

Implementar movimentação com teclado:

W, A, S, D: mover o jogador

←, →: rotacionar a câmera

ESC ou fechar a janela: sair do programa corretamente

Usar MiniLibX para exibição gráfica

Implementar texturas diferentes para paredes de acordo com a direção (Norte, Sul, Leste, Oeste)

Permitir configuração de cores do chão (F) e teto (C) usando valores RGB

A janela gráfica deve se comportar de forma fluida (minimizar, mudar de foco, etc.)

### 🧾 Formato do Arquivo .cub
Informações suportadas:
Textura do Norte: NO ./caminho_da_textura

Textura do Sul: SO ./caminho_da_textura

Textura do Oeste: WE ./caminho_da_textura

Textura do Leste: EA ./caminho_da_textura

Cor do Chão: F R,G,B

Cor do Teto: C R,G,B

Mapa: composto por:

1: parede

0: espaço vazio

N, S, E, W: posição e orientação inicial do jogador

Regras:
O mapa deve estar fechado por paredes (1)

Deve haver apenas um ponto inicial do jogador

Elementos podem ser separados por uma ou mais linhas vazias

Os dados (exceto o mapa) podem estar em qualquer ordem

O mapa deve ser a última parte do arquivo .cub

Espaços são válidos no mapa e devem ser tratados corretamente

⚠️ Tratamento de Erros
Em caso de erro (configuração inválida, mapa aberto, textura ausente, etc.):

O programa deve imprimir: Error\n seguido de uma mensagem explicativa

Sair corretamente sem leaks de memória

### 📂 Makefile
O projeto deve conter um Makefile com as seguintes regras:

all

clean

fclean

re

bonus

### ✅ Funções Permitidas
Funções padrão do C:

open, close, read, write, malloc, free, printf, perror, strerror, exit

Biblioteca matemática:

-lm e todas as funções listadas em man 3 math

MiniLibX

Libft (autorizada)

### 📌 Exemplo de mapa .cub
```txt
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```


