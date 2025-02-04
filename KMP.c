#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vetor_LPS(const char* padrao,int* lps,int tam_padrao){
    int tam = 0; // tamanho do maior prefixo sufixo
    lps[0] = 0;

    int i = 1; // i é o index do padrao
    while (i<tam_padrao) {
        
        if (padrao[i] == padrao[tam]) { // Se o caractere do padrao for igual ao caractere do prefixo sufixo
            tam++; // O tamanho do prefixo sufixo aumenta
            lps[i] = tam; // O vetor lps recebe o tamanho do prefixo sufixo
            i++;
        } 
        
        else { // Se o caractere do padrao for diferente do caractere do prefixo sufixo
            
            if (tam != 0) { // Se o tamanho do prefixo sufixo for diferente de 0
                tam = lps[tam - 1]; // O tamanho do prefixo sufixo recebe o valor do prefixo sufixo anterior
            } 
            
            else {// Se o tamanho do prefixo sufixo for igual a 0
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Retorna um vetor com os indices das ocorrencias do padrao no texto
// Para saber quantas ocorrencias foram encontradas, acesse a variavel ocorrencias
int* kmp_search(char* texto,char* padrao,int* ocorrencias){
    int tam_padrao = strlen(padrao);
    long int tam_texto = strlen(texto);

    int* lps = (int*)malloc(tam_padrao*sizeof(int)); // Vetor que armazena o tamanho do maior prefixo sufixo
    vetor_LPS(padrao,lps,tam_padrao);
    
    int* result_index = (int*)malloc(tam_texto*sizeof(int)); // Vetor que armazena os indices das ocorrencias
    *ocorrencias = 0;
    
    int index_texto = 0;
    int index_padrao = 0;

    while((tam_texto - index_texto) >= (tam_padrao - index_padrao)){ // Enquanto o tamanho do padrao for maior ou igual ao tamanho do texto
        if (padrao[index_padrao] == texto[index_texto]) { // Se o caractere do padrao for igual ao caractere do texto
            index_padrao++;
            index_texto++;
        }

        if (index_padrao == tam_padrao) { // Se o index do padrao for igual ao tamanho do padrao
            result_index[*ocorrencias] = index_texto - index_padrao + 1; // O vetor de indices recebe o index do texto menos o index do padrao
            (*ocorrencias) ++;
            index_padrao = lps[index_padrao - 1]; // O index do padrao recebe o valor do prefixo sufixo anterior
        } 
        
        else if (index_texto < tam_texto && padrao[index_padrao] != texto[index_texto]) { 
            if (index_padrao != 0) {
                index_padrao = lps[index_padrao - 1]; // O index do padrao recebe o valor do prefixo sufixo anterior
            } else {
                index_texto ++;
            }
        }
    }
    free(lps);
    return result_index;
}

int main(){ // main de teste
    char texto[] = "OLA TESOLA OLT OLA";
    char padrao[] = "OLA";
    
    int ocorrencias = 0;
    int* indices = kmp_search(texto,padrao,&ocorrencias);
    printf("O padrao foi encontrado %d vezes\n",ocorrencias);
    for(int i = 0; i<ocorrencias;i++){
        printf("O padrao foi encontrado no indice %d\n",indices[i]);
    }
    free(indices);
    return 0;
}