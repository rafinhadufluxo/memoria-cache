# Memoria Cache 

A principio a memória cache funciona como uma biblioteca de acesso rápido que existe dentro de computadores e dispositivos móveis. Ela tem o objetivo de guardar dados, informações e processos temporários acessados com frequência e assim agilizar o processo de uso no momento em que são requisitados pelo usuário.

## Instruções para implementação
- Número de células na MP: 128;
- Tamanho do bloco: 4 células;
- Número de linhas na cache: 8;
- Tamanho da célula: 8 bits;
- Tamanho do conjunto: 2 ou 4 linhas 


A politica escolhi para desenvolver foi o mapeamento associativo com FIFO + escrita no retorno.

Na tela do programa  vai ser apresentado todo o conteúdo da memória
principal, da memória cache, da próxima localização que será substituída (de acordo
com a política definida), além de um menu que de acesso às seguintes operações:
- ler o conteúdo de um endereço da memória;
- escrever em um determinado endereço da memória;
- apresentar as estatísticas de acertos e faltas (absolutos e percentuais)
para as três situações: leitura, escrita e geral;
- encerrar o programa.

## Referências

* [Algoritmos de substituição - Memória cache - FIFO - LRU - LFU](https://www.youtube.com/watch?v=vVK6ffd9Aw4&t=3s) 
* [Barramentos (dados e endereços); Registradores; MP etc.](https://www.youtube.com/watch?v=iF_ni8d9MBc)
* [Memória Cache](https://www.youtube.com/watch?v=7j7A88izk8E)
* [Mapeamento Associativo e Mapeamento Associativo por Conjunto](https://www.youtube.com/watch?v=NG9yBJ1SMHQ&t=460s)