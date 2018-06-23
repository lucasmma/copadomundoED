/*  ----------------------------------------------
    Nome: Lucas Mendonça Macedo Amaral
    Materia: Estrutura de dados(Marcos F. Caetano)
    S.O.: Ubuntu 18.04 LTS
    versao(gcc): gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
    Editor: Atom
    2018/1
    ---------------------------------------------   */


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
team *team_create(char *nome, int ataque, int defesa, int resistencia, int velocidade);
void verificavalores(char *string, t_lista *lista);
t_lista *aloca_lista();
int esta_vazia(t_lista *lista);
void apaga_lista(t_lista *lista);
void remove_elemento(t_elemento *elemento);
int inserir_final(char *nome, int ataque, int defesa, int resistencia, int velocidade, t_lista *lista);
t_elemento *aloca_elemento(char *nome, int ataque, int defesa, int resistencia, int velocidade);
//endassinaturas
