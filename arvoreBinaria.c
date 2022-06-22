#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice{
   
    int id; //identificador unico de cada vertice
    
    //mecanismo p/ unir nos!
    struct Vertice * esq;
    struct Vertice * dir;
}VERTICE;

VERTICE *raiz = NULL;
int tam = 0;

VERTICE* buscar(int id, VERTICE *aux){
    
    if(aux != NULL){
        if(aux->id == id){
            return aux;
        }else if(id < aux->id){
            if(aux->esq != NULL){
                return buscar(id, aux->esq);
            }else{
                return aux;
            }
        }else if(id > aux->id){
            if(aux->dir != NULL){
                return buscar(id, aux->dir);
            }else{
                return aux;
            }
        }
    }else{
        return NULL;
    }
}


void adicionar(int num){

    VERTICE *aux =  buscar(num, raiz);

    if (aux != NULL && aux->id == num){
        printf("INSERÇÃO INVALIDA\n");
        
    }
    
    else{
        
        VERTICE *novo = malloc(sizeof(VERTICE));
        novo-> id = num;
        novo-> dir = NULL;
        novo-> esq = NULL;

        if (aux == NULL){
            raiz = novo; 
        }
        else{    
            if (num < aux->id){
                aux->esq = novo;
            }
            else{
                aux->dir = novo;
            }
        }
    }
}

VERTICE * remover(VERTICE * raiz, int numero){

    if (raiz == NULL){
        printf("Valor nao encontrado");
    }
    else{
        if (raiz->id == numero){
            if (raiz->dir == NULL && raiz->esq == NULL){
                free(raiz);
                return NULL;
            }
        
        }
        else{
            if (numero < raiz->id){
                raiz->esq == remover(raiz->esq, numero);
            }
            else{
                raiz->dir == remover(raiz->dir, numero);
            }
            return raiz;
        }


    }
    


}

void pre_ordem(VERTICE *aux){
    printf("%d", aux->id);
    if(aux->esq != NULL){
        pre_ordem(aux->esq);
    }
    if(aux->dir != NULL){
        pre_ordem(aux->dir);
    }
}

void in_ordem(VERTICE *aux){
    
    if(aux->esq != NULL){
        in_ordem(aux->esq);
    }
    printf("%d", aux->id);
    if(aux->dir != NULL){
        in_ordem(aux->dir);
    }
}

void pos_ordem(VERTICE *aux){
    
    if(aux->esq != NULL){
        pos_ordem(aux->esq);
    }
    if(aux->dir != NULL){
        pos_ordem(aux->dir);
    }
    printf("%d", aux->id);
}



int main(){
    adicionar(6);
    adicionar(2);
    adicionar(8);
    adicionar(3);
    adicionar(5);
    adicionar(9);
    adicionar(1);
    printf("\nIMPRIMINDO\n");
    in_ordem(raiz);
    printf("\nREMOVENDO\n");
    remover(raiz, 9);
    in_ordem(raiz); 


    return 0;
}
