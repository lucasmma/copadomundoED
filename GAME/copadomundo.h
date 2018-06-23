/*  ----------------------------------------------
    Nome: Lucas Mendonça Macedo Amaral
    Materia: Estrutura de dados(Marcos F. Caetano)
    S.O.: Ubuntu 18.04 LTS
    versao(gcc): gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
    Editor: Atom
    2018/1
    ---------------------------------------------   */

//assinaturas
void iniciarjogo();
void printaarvore(t_node *tree, int *vetordeatributos, int i);
void teamfree(team *ptr);
void destroirtree(t_node *tree);
team *match(team *time1, team *time2, int atributo);
void comecarjogo(t_node *ptr, char *timeescolhido);
void inserirtimes(t_lista *lista, t_node *tree);
t_node *node_create();
t_node *tree_create();
t_node *acharelemento(t_node *ptr, int posicao);
void escolhenumeros(int *ptr, int posicao);
char *escolhertime(t_lista *lista);
void menu();
//endassinaturas
