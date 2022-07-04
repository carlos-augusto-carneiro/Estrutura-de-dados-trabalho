#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cpf_global;

typedef struct secretario{
   
    int cpf; 
    int senha;
    int funcao;
    char* nome_secretario;

    struct secretario * prox;
}SECRETARIO;

SECRETARIO * inicio = NULL;
SECRETARIO * fim = NULL;


void addsecretario(int cpf, int senha, int funcao, char* nome_secretario){
    
    SECRETARIO * novo = ( SECRETARIO *) malloc(sizeof(SECRETARIO));
    novo->cpf = cpf;
    novo->senha = senha;
    novo ->funcao = funcao;
    novo->nome_secretario = nome_secretario;
    novo->prox = NULL;

    if(inicio == NULL){
        inicio = novo;
        fim = novo;
    }else{
        fim->prox = novo;
        fim = novo;
    }  
}


typedef struct Vertice{
   
    int id; 
    char * nome;
    int matricula;
    char * detalhe;

    struct Vertice * esq;
    struct Vertice * dir;
}VERTICE;

VERTICE * raiz = NULL;
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


void adicionar_arvore(int valor, char * nome, int matricula, char * detalhe){
    
    VERTICE *aux = buscar(valor, raiz);
    if (aux != NULL && aux -> id == valor){
        printf("Ja existe");
    }else{ 
        VERTICE *novo = malloc(sizeof(VERTICE));
        novo -> id = valor;
        novo -> nome = nome;
        novo -> matricula = matricula;
        novo -> detalhe = detalhe;
        novo -> esq = NULL;
        novo -> dir = NULL;

        if (aux == NULL){
            raiz = novo;
        }else{
            if (aux -> id > valor){
                aux -> esq = novo;
            }else{ 
                aux -> dir = novo;
            }
        }
    tam++;
    }
}


void in_ordem(VERTICE *aux){
    
    if(aux->esq != NULL){
        in_ordem(aux->esq);
    }
    printf("\n\nid: %d \nnome: %s \nmatricula: %d \ndetalhe: %s\n\n", aux -> id, aux -> nome, aux -> matricula, aux ->detalhe);
    if(aux->dir != NULL){
        in_ordem(aux->dir);
    }
}


typedef struct livro{
   
    int id; 
    char * nome;
    int matricula;
    char* detalhe;
    char* campus_origem;
    char* campus_aluno;
    char* secretario;
    int prioridade;
    
    struct livro * prox;
}LIVRO;

LIVRO * iniciofila = NULL;
LIVRO * fimfila = NULL;
int tamfila = 0;


void addfila(int id, char * nome, int matricula, char * detalhe, char* campus_origem, char* campus_aluno, char* secretario, int prioridade){
    
    LIVRO * novo = (LIVRO *) malloc(sizeof(LIVRO));
    novo->id = id;
    novo->nome = nome;
    novo->matricula = matricula;
    novo->detalhe = detalhe;
    novo->campus_origem = campus_origem;
    novo->campus_aluno = campus_aluno;
    novo->secretario = secretario;
    novo->prioridade = prioridade;
    novo->prox = NULL;
    if(iniciofila == NULL){
        iniciofila = novo;
        fimfila = novo;
    }else if(fimfila -> prioridade > novo ->prioridade){
        fimfila->prox = novo;
        fimfila = novo;
    }else if(iniciofila -> prioridade < novo ->prioridade){
        novo->prox = iniciofila;
        iniciofila = novo;
    }else{
        LIVRO* aux = iniciofila;
        while (aux -> prioridade > novo -> prioridade){
            aux = aux -> prox;
        }
        novo -> prox = aux -> prox;
        aux -> prox = novo; 
    }
    tamfila++;
}


void add_dados_secretario(int id, char * nome, int matricula, char * detalhe){
    int prioridade;
    printf("\n\nid: %d\n", id);
    printf("nome: %s\n", nome);
    printf("matricula: %d\n", matricula);
    printf("detalhe: %s\n", detalhe);
    printf("campus do livro: ");
    char *campus_origem = malloc(sizeof(char)*100);
    scanf(" %[^\n]s", campus_origem);
    printf("campus do aluno: ");
    char *campus_aluno = malloc(sizeof(char)*100);
    scanf(" %[^\n]s", campus_aluno);
    printf("prioridade: ");
    scanf("%d", &prioridade);
    SECRETARIO * aux = inicio;
    while (aux->cpf != cpf_global){
        aux = aux ->prox;
    }
    char* nome_secret = aux->nome_secretario;
    addfila(id, nome, matricula, detalhe, campus_origem, campus_aluno, nome_secret, prioridade);
}


VERTICE * remover(VERTICE * r, int numero){
    
    if (r == NULL){
        printf("Valor nao encontrado \n");
        return NULL;
    }
    else{
        if (numero < r->id){
            r->esq = remover(r->esq, numero);
        }
        else if(numero > r->id){
            r->dir = remover(r->dir, numero);
        }
        else{
            if (r->dir == NULL && r->esq == NULL){ 
                
                r= NULL;
            }
            else if (r->dir != NULL && r->esq != NULL){
                VERTICE *aux = r -> esq;
                while (aux->dir != NULL){
                    aux = aux -> dir;
                }
                r->id = aux -> id;
                r->nome = aux -> nome;
                r->matricula = aux -> matricula;
                r->detalhe= aux -> detalhe;
                aux->id = numero;
                r->esq = remover(r->esq, numero);
            }
            
            else{
                if(r->dir == NULL && r->esq != NULL){
                    r = r->esq;
                }
                else if(r-> dir != NULL && r->esq == NULL){
                    r = r->dir;
                }
            }
        }   
    }return r;
}


void removerfila(){
    LIVRO * aux = iniciofila;
    printf("\n\nid: %d\n", aux->id);
    printf("nome: %s\n", aux->nome);
    printf("matricula: %d\n", aux->matricula);
    printf("detalhe: %s\n", aux->detalhe);
    printf("campus de origem: %s\n", aux->campus_origem);
    printf("campus do aluno: %s\n", aux->campus_aluno);
    printf("secretario: %s\n", aux->secretario);
    printf("prioridade: %d\n", aux->prioridade);
    iniciofila = iniciofila -> prox;
    free(aux);
    tamfila--;
}

VERTICE* buscar_NO(int id, VERTICE *aux){
    while (aux){
        if (id < aux->id){
            aux = aux ->esq;
        }else if (id > aux->id){
            aux = aux->dir;
        }else{
            add_dados_secretario(aux->id, aux->nome, aux->matricula, aux->detalhe);
            return aux;
        }
    }
    return NULL;
}

int procurar(int cpf, int senha, int func){
    SECRETARIO * aux = inicio;
    while (aux -> cpf != cpf){
        aux = aux -> prox;
    }
    if ((aux -> cpf == cpf) && (aux -> funcao == func) && (func == 0)){
        if (aux -> senha == senha){
            printf("senha correta");
            in_ordem(raiz);
            printf("qual deseja editar: ");
            int val_editar;
            scanf("%d", &val_editar);
            buscar_NO(val_editar,raiz);
            raiz = remover(raiz, val_editar);                
        }else{
            printf("senha incorreta");
        }
    }else{
        if ((aux -> cpf == cpf) && (aux -> funcao == func) && (func == 1)){
            if (aux -> senha == senha){
                printf("senha correta");
                removerfila();      
            }else{
                printf("senha incorreta");
            } 
        }
    }
}

int ale1(){
    srand(time(NULL));
    int id = rand() % 998;
    id += 1;
    return id;
}

int ale2(){
    srand(time(NULL));
    int id = rand() % 999;
    id += 1001;
    return id;
}

int main(){
    addsecretario(1111, 151515, 0, "AAAA");
    addsecretario(2222, 252525, 0, "BBBB");
    addsecretario(3333, 353535, 0, "CCCC");
    addsecretario(4444, 454545, 0, "DDDD");
    addsecretario(5555, 555555, 1, "EEEE");
    addsecretario(6666, 656565, 1, "FFFF");
    addsecretario(7777, 757575, 1, "GGGG");
    addsecretario(8888, 858585, 1, "HHHH");
    int loop = 1;
    int escolha, matri, senha, cpft, senhat;
    int cont = 0;
    
    do{
        printf("1 - ENCOMENDAR LIVRO\n");
        printf("2 - EFETUAR PEDIDO DE LIVRO (SECRETARIO)\n");
        printf("3 - TRANSPORTADOR\n");
        scanf("%d", &escolha);

        switch (escolha){
        case 1:
            printf("Digite o nome do aluno: ");
            char *nome = malloc(sizeof(char)*100);
            scanf(" %[^\n]s", nome);
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matri);
            printf("Digite os detalhes do livro: ");
            char *detal = malloc(sizeof(char)*1000);
            scanf(" %[^\n]s", detal);
            int id;
            if(raiz == NULL){
                    id = 1000;
            }else if(cont % 2 == 0){
                id = ale1();
            }else{
                id = ale2();
            }
            cont++;
            adicionar_arvore(id, nome, matri, detal);
            break;
        case 2:
            printf("Digite o cpf: ");
            scanf("%d", &cpf_global);
            printf("Digite a senha: ");
            scanf("%d", &senha);
            procurar(cpf_global, senha, 0);
            break;
        case 3:
            printf("Digite o cpf: ");
            scanf("%d", &cpft);
            printf("Digite a senha: ");
            scanf("%d", &senhat);
            procurar(cpft, senhat, 1);    
            break;
        default:
            break;
        }
    }while (loop == 1);
    return 0;
}