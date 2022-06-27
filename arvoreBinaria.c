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

VERTICE * remover(VERTICE * r, int numero){
    
    if (r == NULL){
        printf("Valor nao encontrado \n");
        return NULL;
    }
    else if (numero < r->id){
        r->esq == remover(r->esq, numero);
    }
    else if(numero > r->id){
        r->dir == remover(r->dir, numero);
    }
    else{
        if (r->dir == NULL && r->esq == NULL){ //folha
            free(r); 
            return NULL;
        }
        else if (r->dir != NULL && r->esq != NULL){ //2 filho
            VERTICE *aux = r -> esq;
            while (aux->dir != NULL){
                aux = aux -> dir;
            }
            r->id = aux ->id;
            aux->id = numero;

            printf("Elemento foi trocado: %d", numero);
            r->esq = remover(r->esq, numero);
            return NULL;
            
        }
        else{ // 1 filho
            VERTICE *aux;
            if(r->dir == NULL && r->esq != NULL){
                aux = r->esq;
            }
            else if(r-> dir != NULL && r->esq == NULL){
                aux = r->dir;
            }
            return aux;
        }
    }  
}  

void in_ordem(VERTICE *aux){
   
    if(aux->esq != NULL){
        in_ordem(aux->esq);
    }
    printf("%d\n", aux->id);
    if(aux->dir != NULL){
        in_ordem(aux->dir);
    }
}


int main(){
    int valor;
    int remoer;
    int loop = 1;
    int escolha;

    do{
        printf("1 - ADICIONAR\n");
        printf("2 - REMOVER\n");
        printf("3 - IMPRIMIR\n");
        scanf("%d", &escolha);

        switch (escolha){
        case 1:
            printf("Valor adicionar:");
            scanf("%d", &valor);
            adicionar(valor);
            break;
        case 2:
            printf("Digite o numero a ser removido: ");
            scanf("%d", &remoer);
            raiz = remover(raiz, remoer);
            break;
        case 3:
            in_ordem(raiz);
            break;
        case 0:
            break;
        }
    }while (loop == 1);


    return 0;
}