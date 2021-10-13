#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EXIT 10


typedef struct {
    int validade;
    int rotulo;
    int celula[4];
} Conteudo;

typedef struct {
    int num;
    int FIFO;
    int miss;
    int hit;
} Culture;




// Função que inicializa os dados da Memória
void inicializaMemoria(Conteudo B[], int x){
    int num1 = 0, num2 = 0;
    for(int j=0; j<x; j++){
        B[j].validade = 0;
        B[j].rotulo = num1;
        num1++;
        for(int i=0; i<4; i++){
            B[j].celula[i] = num2;
            num2++;
        }
    }
}

// Função que imprime os dados da Memória Cache
void imprimeMemoriaCache(Conteudo *MemoriaCache){
    printf("\n");
    printf("Memória Cache:\n\n");
    printf("Validade    Rótulo    Célula 0    Célula 1    Célula 2    Célula 3\n");
    for(int j=0; j<8; j++){
        printf("    %d        0x%02x       0x%02x        0x%02x        0x%02x        0x%02x", MemoriaCache[j].validade, MemoriaCache[j].rotulo, MemoriaCache[j].celula[0], MemoriaCache[j].celula[1], MemoriaCache[j].celula[2], MemoriaCache[j].celula[3]);
        printf("\n");
    }
    printf("\n");
}

// Função que imprime os dados da Memória Principal
void imprimeMemoriaPrincipal(Conteudo *MemoriaPrincipal){
    printf("\n");
    printf("Memória Principal:\n\n");
    printf("Bloco    Validade    Rótulo    Célula 0    Célula 1    Célula 2    Célula 3\n");
    for(int j=0; j<32; j++){
        printf("0x%02x         %d        0x%02x       0x%02x        0x%02x        0x%02x        0x%02x", j, MemoriaPrincipal[j].validade, MemoriaPrincipal[j].rotulo, MemoriaPrincipal[j].celula[0], MemoriaPrincipal[j].celula[1], MemoriaPrincipal[j].celula[2], MemoriaPrincipal[j].celula[3]);
        printf("\n");
    }
    printf("\n");
}


int main(){

    int op=0, cont=0, endereco, valor;
    Culture l = {0}, e = {0};
    Conteudo BlocosMemoriaPrincipal[32] = {0};
    Conteudo LinhasMemoriaCache[8] = {0};

    // Inicialização da Memória Principal e da Memória Cache    
    inicializaMemoria(BlocosMemoriaPrincipal, 32);
    inicializaMemoria(LinhasMemoriaCache, 8);

    // Impressão da Memória Principal e da Memória Cache
    imprimeMemoriaPrincipal(BlocosMemoriaPrincipal);
    imprimeMemoriaCache(LinhasMemoriaCache);



    while(op!=EXIT){
          

        printf("\n __________________________________________________\n");
        printf("\n  Menu\n");
        printf("\n  1 Ler o conteúdo de um endereço da memória\n");
        printf("  2 Escrever em um determinado endereço da memória\n");
        printf("  3 Apresentar as estatísticas de acerto e faltas\n");
        printf("  4 Apresentar conteúdo da Memória Principal\n");
        printf("  5 Apresentar conteúdo da Memória Cache\n");
        printf("\n  %d Encerar o programa", EXIT);
        printf("\n __________________________________________________\n\n");
        scanf("%d", &op);

       

        switch (op) {
            case 1:
                printf("\nInsira o endereço da memória em binário de 7 bits: ");
                scanf("%d", &endereco);
              
                break;
            
            case 2:
                printf("\nInsira o endereço da memória em binário de 7 bits: ");
                scanf("%d", &endereco);
               
               break;
            
            case 3:
                
                break;
            
            case 4:
              
                break;

            case 5:
              
                break;
    
            default:
                break;
        }   
    }
        
    return 0;

}
