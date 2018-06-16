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

typedef struct node{
    team* time;
    struct node* left;
    struct node* right;
} t_node;

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
void comecarjogo(t_node *ptr, char *timeescolhido);
void inserirtimes(t_lista *lista, t_node *tree);
t_node *node_create();
t_node *tree_create();
t_node *acharelemento(t_node *ptr, int posicao);
void escolhenumeros(int *ptr, int posicao);
void verificavalores(char *string, t_lista *lista);
char *escolhertime(t_lista *lista);
void iniciarjogo();
t_lista *aloca_lista();
int esta_vazia(t_lista *lista);
team *team_create(char *nome, int ataque, int defesa, int resistencia, int velocidade);
void apaga_lista(t_lista *lista);
void remove_elemento(t_elemento *elemento);
int inserir_final(char *nome, int ataque, int defesa, int resistencia, int velocidade, t_lista *lista);
t_elemento *aloca_elemento(char *nome, int ataque, int defesa, int resistencia, int velocidade);
//endassinaturas

//funcoes
//match
team *match(team *time1, team *time2, int atributo){
    if(atributo==1){
        if(time1->ataque<time2->ataque)
            return time2;
        else
            return time1;
    }
    else if(atributo==2){
        if(time1->defesa<time2->defesa)
            return time2;
        else
            return time1;
    }
        else if(atributo==3){
            if(time1->resistencia<time2->resistencia)
                return time2;
            else
                return time1;
        }
            else if(atributo==4){
                if(time1->velocidade<time2->velocidade)
                    return time2;
                else
                    return time1;
            }
}
//endmatch
//comecarjogo
void comecarjogo(t_node *ptr, char *timeescolhido){
    t_node *aux;
    int atributo;
    for(int i=15;i>0;i--){
        aux=acharelemento(ptr,i);
        if(strcmp(aux->left->time->nome,timeescolhido)==0||strcmp(aux->right->time->nome,timeescolhido)==0){
            if(i>=8)
                printf("OITAVAS DE FINAL\n\n");
            else if(i>=4)
                printf("QUARTAS DE FINAL\n\n");
                else if(i>=2)
                    printf("SEMI-FINAL\n\n");
                    else
                        printf("FINAL");
            if(strcmp(aux->left->time->nome,timeescolhido)==0){
                printf("Seu time %s\n",aux->left->time->nome);
                printf("1) Ataque        : %d\n",aux->left->time->ataque);
                printf("2) Defesa        : %d\n",aux->left->time->defesa);
                printf("3) Resistencia   : %d\n",aux->left->time->resistencia);
                printf("4) Velocidade   : %d\n\n",aux->left->time->velocidade);
                printf("Seu adversario: %s\n\n",aux->right->time->nome);
                printf("Selecione um atributo: ");
                scanf("%d", &atributo);
            }
            else{
                printf("Seu time %s\n",aux->right->time->nome);
                printf("1) Ataque        : %d\n",aux->right->time->ataque);
                printf("2) Defesa        : %d\n",aux->right->time->defesa);
                printf("3) Resistencia   : %d\n",aux->right->time->resistencia);
                printf("4) Velocidade   : %d\n\n",aux->right->time->velocidade);
                printf("Seu adversario: %s\n\n",aux->left->time->nome);
                printf("Selecione um atributo: ");
                scanf("%d", &atributo);
            }
            aux->time=match(aux->left->time,aux->right->time, atributo);
            if(strcmp(aux->time->nome,timeescolhido)==0){
                printf("Voce venceu a partida prepare para a proxima partida\n");
            }
            else{
                printf("voce perdeu.\n");
                return;
            }
        }
        else{
            atributo=rand() % 4;
            if(atributo==0)
                atributo=4;
            aux->time=match(aux->left->time, aux->right->time, atributo);
        }
    }
    printf("Venceu o jogo\n");
    return;
}
//endcomecarjogo
//inserirtimes
void inserirtimes(t_lista *lista, t_node *tree){
    t_elemento *ptrlista;
    t_node *ptrtree;
    int i;
    ptrlista=lista->primeiro;
    for(i=16;i<=31;i++){
        ptrtree=acharelemento(tree, i);
        ptrtree->time=ptrlista->time;
        ptrlista=ptrlista->proximo;
    }
    ptrlista=lista->primeiro;
    for(i=1; i<16; i++){
        ptrlista->anterior=NULL;
        ptrlista=ptrlista->proximo;
        ptrlista->anterior->proximo=NULL;
        free(ptrlista->anterior);
    }
    free(ptrlista);
    lista->primeiro=NULL;
    lista->ultimo=NULL;
    free(lista);
    return;
}
//endinserirtimes
//node_create
t_node *node_create(){
    t_node *ptr= (t_node*) malloc(sizeof(t_node));
    ptr->time = NULL;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}
//endnode_create
//tree_create
t_node *tree_create(){
    t_node *ptr=node_create();
    t_node *aux;
    for(int i=2;i<=31;i++){
        aux=acharelemento(ptr, i/2);
        if(i%2==0){
            aux->left=node_create();
        }
        else{
            aux->right=node_create();
        }
    }
    return ptr;
}
//endtree_create
//percorretree
t_node *acharelemento(t_node *ptr, int posicao){
    t_node *aux=ptr;
    if(posicao==1)
        return aux;
    int resto=posicao%2;
    posicao=(posicao-resto)/2;
    if(resto==0){
        aux=acharelemento(aux,posicao);
        aux=aux->left;
        return aux;
    }
    aux=acharelemento(aux,posicao);
    aux=aux->right;
    return aux;
}
//endpercorretree
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
    int i=0,aux,ataque,defesa,resistencia,velocidade;
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
    ataque=atoi(atk);
    i+=2;
    aux=i;
    while(string[i]!=','){
        def[i-aux]=string[i];
        i++;
    }
    def[i-aux]='\0';
    defesa=atoi(def);
    i+=2;
    aux=i;
    while(string[i]!=','){
        resist[i-aux]=string[i];
        i++;
    }
    resist[i-aux]='\0';
    resistencia=atoi(resist);
    i+=2;
    aux=i;
    while(string[i]!='\0'){
        vel[i-aux]=string[i];
        i++;
    }
    vel[i-aux]='\0';
    velocidade=atoi(vel);
    inserir_final(nome,ataque,defesa,resistencia,velocidade,lista);
}

//endverificavalores
//escolhertime
char *escolhertime(t_lista *lista){
    t_elemento *aux=lista->primeiro;
    int i=1,random,numerodotime;
    printf("\nEscolha seu time\n\n");

    while(i<=lista->quantidade){
        random=rand()%4;
        printf("Time %d:\n", i);
        printf("Ataque: ");
        if(random==0)
            printf("%d ",aux->time->ataque);
        else
            printf("?? ");
        printf("Defesa: ");
        if(random==1)
            printf("%d ", aux->time->defesa);
        else
            printf("?? ");
        printf("Resistencia: ");
        if(random==2)
            printf("%d ", aux->time->resistencia);
        else
            printf("?? ");
        printf("Velocidade: ");
        if(random==3)
            printf("%d\n\n", aux->time->velocidade);
        else
            printf("??\n\n");
        i++;
        aux=aux->proximo;
    }
    scanf("%d", &numerodotime);
    aux=lista->primeiro;
    if(numerodotime==1)
        return aux->time->nome;
    else{
        for(i=1;i<numerodotime;i++){
            aux=aux->proximo;
        }
        return aux->time->nome;
    }
}
//endescolhertime
//iniciarjogo
void iniciarjogo(){
    FILE *arquivo;
    t_lista *lista;
    t_node *tree;
    t_node *ptr;
    int num,i,x,verificanum[16];
    char string[50];
    char *timeescolhido;
    lista=aloca_lista();
    arquivo=fopen("teams.txt","r");
    escolhenumeros(verificanum,1);
    for(i=0;i<16;i++){
        printf("%d ", verificanum[i]);
        for(x=-1;x<verificanum[i];x++){
            fgets(string,sizeof(string),arquivo);
        }
        verificavalores(string, lista);
        rewind(arquivo);
    }
    fclose(arquivo);
    timeescolhido=escolhertime(lista);
    tree=tree_create();
    inserirtimes(lista,tree);
    printf("%s\n\n", timeescolhido);
    /*for(i=16;i<=31;i++){
        ptr=acharelemento(tree, i);
        printf("%s\n", ptr->time->nome);
    }*/
    comecarjogo(tree,timeescolhido);
    return;
}
//endiniciarjogo
//menu
void menu(){
    int flag;
    while(1){
        system("clear");
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
team *team_create(char *nome, int ataque, int defesa, int resistencia, int velocidade){
    team *ptr = (team*) malloc(sizeof(team));
    if(ptr==NULL){
        return NULL;
    }
    ptr->nome=(char*)malloc(sizeof(char)*30);
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

    ptr->time = team_create(nome, ataque, defesa, resistencia, velocidade);

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
    ptr->anterior=lista->ultimo;
    ptr->proximo=lista->primeiro;
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
