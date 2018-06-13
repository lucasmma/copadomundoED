/*  ----------------------------------------------
    Nome: Lucas Mendonça Macedo Amaral
    Materia: Estrutura de dados(Marcos F. Caetano)
    S.O.: Ubuntu 18.04 LTS
    versao(gcc): gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
    Editor: Atom
    2018/1
    ---------------------------------------------   */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

typedef struct t_team{
    char *nome;
    int ataque; //0 a 100
    int defesa; //0 a 100
    int resistencia; // 0 a 100
    int velocidade; // 0 a 100
} team;

typedef struct elemento{
    struct elemento *anterior;
    team *time;
    struct elemento *proximo;
} t_elemento;

typedef struct{
    t_elemento *primeiro;
    t_elemento *ultimo;
    int quantidade;
} t_lista;

//assinaturas
void escolhenumeros(int *ptr, int posicao);
void verificavalores(char *string, t_lista *lista);
void iniciarjogo();
t_lista *aloca_lista();
int esta_vazia(t_lista *lista);
void apaga_lista(t_lista *lista);
void remove_elemento(t_elemento *elemento);
int inserir_final(char *nome, int ataque, int defesa, int resistencia, int velocidade, t_lista *lista);
t_elemento *aloca_elemento(char *nome, int ataque, int defesa, int resistencia, int velocidade);
//endassinaturas

//funcoes
//escolhenumeros
void escolhenumeros(int *ptr,int posicao){
    int random,flag=1,i;
    if(posicao<=16){
        while(flag<=3){
            random=rand()%32;
            flag=3;
            for(i=0;i<posicao&&flag!=2;i++){
                if(*(ptr+i)!=random)
                    flag=3;
                else
                    flag=2;
            }
            if(flag==3){
                ptr[i-1]=random;
                escolhenumeros(ptr, posicao+1);
                return;
            }
        }
    }
    else
        return;
}
//endescolhenumeros
//verificavalores
void verificavalores(char *string, t_lista *lista){
    int i=0,aux;
    char nome[20], atk[10], def[10], resist[10], vel[10];
    while(string[i]!=','){
        nome[i]=string[i];
        i++;
    }
    nome[i]='\0';
    i+=2;
    aux=i;
    while(string[i]!=','){
        atk[i-aux]=string[i];
        i++;
    }
    atk[i-aux]='\0';
    i+=2;
    aux=i;
    while(string[i]!=','){
        def[i-aux]=string[i];
        i++;
    }
    def[i-aux]='\0';
    i+=2;
    aux=i;
    while(string[i]!=','){
        resist[i-aux]=string[i];
        i++;
    }
    resist[i-aux]='\0';
    i+=2;
    aux=i;
    while(string[i]!='\0'){
        vel[i-aux]=string[i];
        i++;
    }
    vel[i-aux]='\0';
}

//endverificavalores
//iniciarjogo
void iniciarjogo(){
    FILE *arquivo;
    t_lista *lista;
    int num,i,x,verificanum[16];
    char string[50];
    lista=aloca_lista();
    arquivo=fopen("teams.txt","r");
    escolhenumeros(verificanum,1);
    for(i=0;i<16;i++){
        printf("%d ", verificanum[i]);
        for(x=-1;x<verificanum[i];x++){
            fgets(string,sizeof(string),arquivo);
            verificavalores(string, lista);
        }
        rewind(arquivo);
        printf("%s\n",string);
    }
    fclose(arquivo);
    return;
}
//endiniciarjogo
//menu
void menu(){
    int flag;
    while(1){
        printf("[1]- Iniciar jogo\n");
        printf("[2]- Sair\n");
        scanf("%d", &flag);
        if(flag==1){
            iniciarjogo();//implementar
        }
        else if(flag==2){
            return;
        }
        else{
            printf("Erro tecla invalida. Escolha outra opcao\n");
        }
    }
}
//endmenu
//aloca_lista
t_lista *aloca_lista(){
    t_lista *ptr=(t_lista*) malloc(sizeof(t_lista));

    if(ptr==NULL){
        return NULL;
    }

    ptr->primeiro=NULL;
    ptr->ultimo=NULL;
    ptr->quantidade=0;
    return ptr;
}
// end aloca_lista
//esta_vazia
int esta_vazia(t_lista *lista){
    return(lista->primeiro==NULL && lista->ultimo==NULL);
}
//endesta_vazia
//teamcreate
team *criatime(char *nome, int ataque, int defesa, int resistencia, int velocidade){
    team *ptr = (team*) malloc(sizeof(team));
    if(ptr==NULL){
        return NULL;
    }
    strcpy(ptr->nome, nome);
    ptr->ataque=ataque;
    ptr->defesa=defesa;
    ptr->resistencia=resistencia;
    ptr->velocidade=velocidade;
    return ptr;
}
//endteamcrate
//aloca_elemento
t_elemento *aloca_elemento(char *nome, int ataque, int defesa, int resistencia, int velocidade){
    t_elemento *ptr=(t_elemento*) malloc(sizeof(t_elemento));

    if(ptr==NULL)
        return NULL;

    ptr->time = criatime(nome, ataque, defesa, resistencia, velocidade);

    ptr->proximo=NULL;
    ptr->anterior=NULL;

    return ptr;
}
//end aloca_elemento
//inserir_final
int inserir_final(char *nome, int ataque, int defesa, int resistencia, int velocidade, t_lista *lista){
    if(lista==NULL)
        return FALSE;
    t_elemento *ptr= aloca_elemento(nome,ataque,defesa,resistencia,velocidade);
    if(ptr==NULL)
        return FALSE;
    ptr->anterior=lista->ultimo;
    if(lista->primeiro==NULL){
        lista->primeiro=ptr;
        lista->ultimo=ptr;
    }
    else{
        lista->ultimo->proximo=ptr;
        lista->ultimo=ptr;
    }
    lista->quantidade++;
    return TRUE;
}
//end inserir_final
//end esta_vazia
void remove_elemento(t_elemento *elemento){
    free(elemento->time);
    free(elemento);
}
//apaga_lista
void apaga_lista(t_lista *lista){
    t_elemento *ptr=lista->primeiro;
    if(esta_vazia(lista)==FALSE){
        while(ptr!=NULL){
            lista->primeiro=lista->primeiro->proximo;
            remove_elemento(ptr);
            ptr=lista->primeiro;
        }
    }
    free(lista);
}
//end apaga_lista



//endfuncoes




int main(){
    srand(time(NULL));
        menu();
        return 0;
}
