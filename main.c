/*  
*   Acadêmicos: Geovano Lago e Rafa Arruda 
*/

/*
* algumas observações
*  bits= numero de bits
*  num= binario
*  decimal= numero em decimal
*  inicial= valor que diz em qual bit esta
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linha
{
    int desloc_linha[4];
    int alterado; 
    int rotulo;
    int valido;
    int pol_substituicao;//marca a linha q sera substituida pela FIFO 
} linha;

typedef struct bloco
{
    int pos_no_bloco[4];
} bloco;


//Binario para decimal
int dec(int bits, char num[bits], int inicial){
    int cont = 0;
    for (int i = bits - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            cont += inicial;
        inicial *= 2;
    }
    return cont;
}


//Printar em binario
void bin(int num, int bits)
{
    int aux = bits - 1, bin[bits];
    for (; aux >= 0; aux--)
    {
        if (num % 2 == 0)
            bin[aux] = 0;
        else
            bin[aux] = 1;
        num /= 2;
    }
    for (aux = 0; aux < bits; aux++)
        printf("%d", bin[aux]);
}

//Printar a Memória
void print_memoria(struct bloco vetor_bloco[32], struct linha vetor_linha[8])
{
    printf("\n\t\t\t\t\t\t MEMORIA PRINCIPAL\n\n");
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("\t\tCelula[");
            bin(i * 4 + j, 7);
            printf("] - ");
            printf("Bloco[%d]: ", i);
            bin(vetor_bloco[i].pos_no_bloco[j], 8);
            if (j % 2 == 1)
                printf("\n");
        }
    }
    int maior_val = -10;
    int prox;
    for (int k = 0; k < 8; k++)//Acha o primeiro que entrou
    {
        if (vetor_linha[k].valido == 1)
        {
            if (vetor_linha[k].pol_substituicao > maior_val)
            {
                maior_val = vetor_linha[k].pol_substituicao;
            }
        }
        
        
    }
    
    puts("\n\n-------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t    MEMORIA CACHE\n");
    printf("\n\t\t|VALIDO| | SUB | | DIRTY | |  ROTULO | |   00   | |   01   | |   10   | |   11   | |LINHA|\n");
    for (int i = 0; i < 8; i++)
    {
        
            printf("\t\t|   %d  | | ", vetor_linha[i].valido);
            
            if (vetor_linha[i].valido == 0)
                printf("--- | | ");
            else{
               if(vetor_linha[i].pol_substituicao == maior_val){
                   printf(" 1  | | ");
                   prox = i;
               }
               else{
                   printf(" 0  | | ");
               }
            }

            printf("  %d   | | ", vetor_linha[i].alterado);
            
            if (vetor_linha[i].valido == 0)
                printf("-------");
            else{
                printf(" ");
                bin(vetor_linha[i].rotulo, 5);
                printf(" ");
            }
            printf(" | ");
            for (int k = 0; k < 4; k++)
            {
                printf("|");
                if (vetor_linha[i].valido == 0)
                    printf("--------");
                else
                    bin(vetor_linha[i].desloc_linha[k], 8);
                printf("| ");
            }
            printf("| ");
            bin(i, 3); //linha
            printf(" |\n");
        
    }
    puts("\n\n-------------------------------------------------------------------------------------------------------");
    
    printf("\n\t\t\tProxima linha para substituição: Linha [");
    bin(prox, 3);
    printf("]\n\n");
    
}

//Mostra as estatisticas
void estatisticas(double porc, double acertos_leitura[1], double acertos_escrita[1], double faltas_leitura[1], double faltas_escrita[1]){

    printf("\n\t\t\t\t\t\tESTATISTICAS:\n\n");


    porc = (acertos_leitura[0] / (acertos_leitura[0] + faltas_leitura[0])) * 100;
    printf("\t\t\tLeitura:\n");
    printf("\n\t\t\tAcertos: %.0lf  | %.2lf por cento\n", acertos_leitura[0], porc);

    porc = (faltas_leitura[0] / (acertos_leitura[0] + faltas_leitura[0])) * 100;
    printf("\t\t\tFaltas:  %.0lf  | %.2lf por cento\n\n\n", faltas_leitura[0], porc);


    porc = (acertos_escrita[0] / (acertos_escrita[0] + faltas_escrita[0])) * 100;
    printf("\t\t\tEscrita:\n");
    printf("\n\t\t\tAcertos: %.0lf  | %.2lf por cento\n", acertos_escrita[0], porc);

    porc = (faltas_escrita[0] / (acertos_escrita[0] + faltas_escrita[0])) * 100;
    printf("\t\t\tFaltas:  %.0lf  | %.2lf por cento\n\n\n", faltas_escrita[0], porc);


    porc = ((acertos_escrita[0] + acertos_leitura[0]) / (acertos_leitura[0] + acertos_escrita[0] + faltas_escrita[0] + faltas_leitura[0])) * 100;
    printf("\t\t\tGeral:\n");
    printf("\n\t\t\tAcertos: %.0lf  | %.2lf por cento\n", acertos_escrita[0] + acertos_leitura[0], porc);

    porc = ((faltas_escrita[0] + faltas_leitura[0]) / (acertos_leitura[0] + acertos_escrita[0] + faltas_escrita[0] + faltas_leitura[0])) * 100;
    printf("\t\t\tFaltas:  %.0lf  | %.2lf por cento\n\n\n", faltas_escrita[0] + faltas_leitura[0], porc);

}

//Memoria Cache (Leitura e Escrita)
void memoria_cache(struct bloco vetor_bloco[32], struct linha vetor_linha[8], double acertos_leitura[1], double acertos_escrita[1], double faltas_leitura[1], double faltas_escrita[1], int tipo)
{
    int aux = 0, cheio = 0, dado = 0, data = 0, end = 0, bloc = 0, int_linha, int_deslocamento, int_rotulo, int_bloco, int_dado, rotulo_cache = 0, menor_linha = 0;
    char bits_endereco[7], bits_dado[8], bits_rotulo[5], bits_deslocamento[2];

    printf("\nDigite o endereco desejado:\n");
    scanf("%d", &end);
    int ajuda = end;

    for (aux = 7; aux >= 1; aux--)
    {
        if (end % 2 == 0)
            bits_endereco[aux] = '0';
        else
            bits_endereco[aux] = '1';
        end /= 2;
    }


    bloc = ajuda / 4; //bloco do endereço = rotulo
    

    
    int_rotulo = bloc; //valor inteiro do rotulo

    printf("bloco: %d e rotulo: %d\n", bloc, int_rotulo);
    

    bits_deslocamento[0] = bits_endereco[6]; //aramzena o deslocamento
    bits_deslocamento[1] = bits_endereco[7]; //aramzena o deslocamento
    int_deslocamento = dec(2, bits_deslocamento, 1); //valor inteiro do deslocamento


    for(int_linha = 0; int_linha < 8; int_linha++){

        if (vetor_linha[int_linha].valido == 1) //verifica se a linha da cache é válida
        {
            if (vetor_linha[int_linha].rotulo == int_rotulo) //verifica na linha da cache o valor do rótulo
            {
                rotulo_cache = 1; //se o rótulo estiver na cache marca 1
                break;
                
            }
        }
        else{

            rotulo_cache = 0; //se o rótulo nao estiver na cache marca
            break;

        }

        if (int_linha == 7){

            cheio = 1;

        }
    }



    if (rotulo_cache == 0){

        printf("\n\nValor atualmente escrito: %d\n", vetor_bloco[bloc].pos_no_bloco[int_deslocamento]);
        printf("\nEndereço não encontrado na cache(miss)!\n\n");

        if (tipo == 0){

            faltas_leitura[0]++;

        }

        if (cheio == 0){ //se estiver linha livre

            for (int j = 0; j < 4; j++) //escreve o bloco na linha livre da cache
            {
                vetor_linha[int_linha].desloc_linha[j] = vetor_bloco[bloc].pos_no_bloco[j];
            }

            for (int k = 0; k < 8; k++)//Atualiza FIFO
            {
                if (vetor_linha[k].valido == 1)
                {
                    vetor_linha[k].pol_substituicao++;
                }
                
            }

            vetor_linha[int_linha].valido = 1;
            vetor_linha[int_linha].rotulo = int_rotulo;
            vetor_linha[int_linha].alterado = 0;
            vetor_linha[int_linha].pol_substituicao = 0;

            printf("Bloco: ");
            bin(bloc, 5);
            printf("\nLinha da Cache: ");
            bin(int_linha, 3);
            printf("\nDeslocamento: %c", bits_deslocamento[0]);
            printf("%c\n", bits_deslocamento[1]);

        }
        else{
            for(int i = 0; i < 8; i++){
                if (vetor_linha[i].pol_substituicao == 7){//FIFO
                        
                        
                    for (int j = 0; j < 4; j++)
                    {
                        if (vetor_linha[i].alterado == 1)//escrita no retorno
                            vetor_bloco[vetor_linha[i].rotulo].pos_no_bloco[j] = vetor_linha[i].desloc_linha[j];
                        

                        vetor_linha[i].desloc_linha[j] = vetor_bloco[bloc].pos_no_bloco[j];
                    }
                    for (int k = 0; k < 8; k++)//atualiza FIFO
                    {
                    if (vetor_linha[k].valido == 1)
                    {
                        vetor_linha[k].pol_substituicao++;
                    }
                    
                    }
                    
                    vetor_linha[i].alterado = 0;
                    vetor_linha[i].valido = 1;
                    vetor_linha[i].pol_substituicao = 0;
                    vetor_linha[i].rotulo = int_rotulo;
                    

                    printf("Bloco: ");
                    bin(bloc, 5);
                    printf("\nLinha da Cache: ");
                    bin(i, 3);
                    printf("\nDeslocamento: %c", bits_deslocamento[0]);
                    printf("%c\n", bits_deslocamento[1]);
                    break;
                }
            }
        }   

    }




    if (rotulo_cache == 1){

        printf("\nEndereço encontrado na cache(hit)!\n\n");
        printf("\n\nValor escrito: %d\n\n", vetor_linha[int_linha].desloc_linha[int_deslocamento]);

        if (tipo == 0){ //leitura

            acertos_leitura[0]++;

        }

        printf("Bloco: ");
        bin(bloc, 5);
        printf("\nLinha da Cache: ");
        bin(int_linha, 3);
        printf("\nDeslocamento: %c", bits_deslocamento[0]);
        printf("%c\n", bits_deslocamento[1]);

    }

    if (tipo == 1){ //escrita

        
        if (rotulo_cache == 1)
        {
            acertos_escrita[0]++;
        }
        else{
            faltas_escrita[0]++;
        }

        

        printf("\nDigite o conteudo a ser escrito:\n");
        scanf("%d", &dado);

        for (data = 7; data >= 0; data--){

            if (dado % 2 == 0)
                bits_dado[data] = '0';
            else
                bits_dado[data] = '1';
            dado /= 2;
        }

        int_dado = dec(8, bits_dado, 1);


        if (rotulo_cache == 1)
        {
            if(vetor_linha[int_linha].desloc_linha[int_deslocamento] != int_dado){
                vetor_linha[int_linha].desloc_linha[int_deslocamento] = int_dado;
                vetor_linha[int_linha].alterado = 1;
            }
        }
        else{
            if (cheio == 0)
            {
                vetor_linha[int_linha].desloc_linha[int_deslocamento] = int_dado;
                vetor_linha[int_linha].alterado = 1;
            }
            else{
                for(int i = 0; i < 8; i++){
                    if (vetor_linha[i].pol_substituicao == 7){//FIFO
                            
                            
                        for (int j = 0; j < 4; j++)
                        {
                            if (vetor_linha[i].alterado == 1)//escrita no retorno
                                vetor_bloco[vetor_linha[i].rotulo].pos_no_bloco[j] = vetor_linha[i].desloc_linha[j];
                            

                            vetor_linha[i].desloc_linha[j] = vetor_bloco[bloc].pos_no_bloco[j];
                        }
                        for (int k = 0; k < 8; k++)
                        {
                            if (vetor_linha[k].valido == 1)
                            {
                                vetor_linha[k].pol_substituicao++;
                            }
                        
                        }
                        
                        vetor_linha[i].valido = 1;
                        vetor_linha[i].pol_substituicao = 0;
                        vetor_linha[i].rotulo = int_rotulo;
                        vetor_linha[i].desloc_linha[int_deslocamento] = int_dado;
                        vetor_linha[i].alterado = 1;
                        
                        break;
                    }
                }
                
            }
        }


    }
    
}

int main(){
    struct linha vetor_linha[8];
    struct bloco vetor_bloco[32];
    double porc, acertos_leitura[1] = {0}, acertos_escrita[1] = {0}, faltas_leitura[1] = {0}, faltas_escrita[1] = {0};
    int op;
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vetor_bloco[i].pos_no_bloco[j] = rand() % 256;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        vetor_linha[i].alterado = 0;
        vetor_linha[i].valido = 0;
        
    }
    do
    {
        printf("\n\t\t\t\t\t\tMENU\n");
        printf("\t\t\t1 - Ler um endereço de memoria\n");
        printf("\t\t\t2 - Escrever na memoria\n");
        printf("\t\t\t3 - Estatísticas\n");
        printf("\t\t\t4 - Mostrar Memória Principal e Memória Cache\n");
        printf("\t\t\t0 - Encerrar\n\n");
        printf("\t\t\tEscolha uma opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            memoria_cache(vetor_bloco, vetor_linha, acertos_leitura, acertos_escrita, faltas_leitura, faltas_escrita, 0);

            break;
        case 2:
            memoria_cache(vetor_bloco, vetor_linha, acertos_leitura, acertos_escrita, faltas_leitura, faltas_escrita, 1);

            break;
        case 3:
            estatisticas(porc, acertos_leitura, acertos_escrita, faltas_leitura, faltas_escrita);
            break;
        case 4:
            print_memoria(vetor_bloco, vetor_linha);
            break;
        case 0:
            system("clear");
            printf("Encerrado\n");
            break;
        default:
            system("clear");
            printf("Opcao Inválida!\n");
        }
    } while (op != 0);
}
