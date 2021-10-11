#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linha{
    int desloc_linha[4];
    int dirty; 
    int rotulo;
    int valido;
    int pol_sub;
} linha;

typedef struct conjunto{
    struct linha vetor_linha[4];
} conjunto;

typedef struct bloco{
    int pos_no_bloco[4];
} bloco;



int main(){
    
    struct conjunto vetor_conjunto[2];
    struct bloco vetor_bloco[32];
    double porc, acertos_leitura[1] = {0}, acertos_escrita[1] = {0}, faltas_leitura[1] = {0}, faltas_escrita[1] = {0};
    int op;
    
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 4; j++)
        
            vetor_bloco[i].pos_no_bloco[j] = rand() % 256;
        
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++)
            vetor_conjunto[i].vetor_linha[j].pol_sub = 0;
            vetor_conjunto[i].vetor_linha[j].valido = 0;
            vetor_conjunto[i].vetor_linha[j].dirty = 0;
    }


    do
    {
        printf("\n\t\t\t\t\t\tMENU\n");
        printf("\t\t\t1 - Ler um endereço de memoria\n");
        printf("\t\t\t2 - Escrever na memoria\n");
        printf("\t\t\t3 - Estatísticas\n");
        printf("\t\t\t4 - Mostrar Memória Principal e Memória Cache\n");
        printf("\t\t\t0 - Encerrar\n");
        printf("\t\t\tEscolha uma opcao: ");
        scanf("%d", &op);
        
        switch (op){
            case 1:
                printf("\n entrou no ler um endereço\n");
                printf(" \33[0;32m TESTE \33[0m");
                break;
           
            case 2:
                printf("\n entrou no escrever na memoria");
                break;
          
            case 3:
                printf("\n entrou na parte Estatísticas\n");
                break;
          
            case 4:
                printf("\n entrou no memoria Principal e na cache\n");
                break;
            
            case 0:
                printf("\n entrou no Encerrar programa\n");
                break;
           
            default:
                printf("\nentrou no default\n");
                break;
           
        }
    } while (op != 0);
}
