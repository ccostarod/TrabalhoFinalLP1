# Matriz de Conflitos - README

Este código em C tem o objetivo de montar uma matriz de conflitos com base em um arquivo de entrada e realizar análises a partir de disciplinas sorteadas.

## Funcionalidades

1. *montarMatrizConflitos*: Lê um arquivo de entrada contendo o número de disciplinas e conflitos entre elas. Em seguida, cria uma matriz de conflitos e a armazena em um arquivo chamado "matriz.txt".

2. *verificarConflitos*: Verifica se uma nova disciplina escolhida entra em conflito com as disciplinas já escolhidas anteriormente, com base na matriz de conflitos.

3. *montarGrade*: A partir de uma posição de início de análise (decidida por sorteio) e da matriz de conflitos, seleciona as disciplinas que não têm conflitos com as disciplinas escolhidas anteriormente.

4. *main*: A função principal do programa. Chama a função "montarMatrizConflitos" para gerar a matriz de conflitos. Em seguida, lê a matriz do arquivo "matriz.txt" e realiza 3 análises a partir de disciplinas sorteadas, utilizando a função "montarGrade".

## Exemplo de Entrada: 
## Exemplo de Saída: 
![Exemplo de saída]("imgs/saida.png")

## Tópicos utilizados em C

- Leitura e escrita de arquivos (`FILE`, `fopen`, `fclose`, `fscanf`, `fprintf`).
- Uso de bibliotecas.
- Utilização de matrizes.
- Uso de estruturas de decisão.
- Uso de estruturas de repetição.
- Uso de funções e passagem de parâmetros.
- Geração de números aleatórios (`srand`, `rand`).
- Structs (estruturas).
- Alocação Dinâmica.
- Recursividade.

## Como executar o código

1. Certifique-se de ter um compilador C instalado em sua máquina (por exemplo, GCC no Linux ou MinGW no Windows).
2. Recomendo fortemente que baixe o .zip da pasta e abra depois a main.c em alguma idle.
3. Execute o código e seja feliz!

