/*  ----------------------------------------------
    Nome: Lucas Mendonça Macedo Amaral
    Materia: Estrutura de dados(Marcos F. Caetano)
    S.O.: Ubuntu 18.04 LTS
    versao(gcc): gcc (Ubuntu 7.2.0-8ubuntu3.2) 7.2.0
    Editor: Atom
    2018/1
    ---------------------------------------------   */

#include <stdio.h>
#include "lista.h"
#include "copadomundo.h"
#include <string.h>
#include <stdlib.h>

//funcoes
//iniciarjogo
void iniciarjogo(){
    FILE *arquivo;
    t_lista *lista;
    t_node *tree;
    t_node *ptr;
    int num,i,x,verificanum[16];
    memset(verificanum,100,sizeof(verificanum));
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
    comecarjogo(tree,timeescolhido);
    destroirtree(tree);
    return;
}
//endiniciarjogo
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
//printaarvore
void printaarvore(t_node *tree, int *vetordeatributos, int i){
    t_node *aux;
    printf("Jogos da Copa\n");
    for(int x=15;x>=i;x--){
        if(x==15)
            printf("\nOITAVAS DE FINAL:\n");
        else if(x==7)
            printf("\nQUARTAS DE FINAL:\n");
            else if(x==3)
                printf("\nSEMI-FINAL:\n");
                else if(x==1)
                    printf("\nFINAL:\n");
        aux=acharelemento(tree,x);
        if(vetordeatributos[x-1]==1){
            printf("%s (Ataque %d) x %s (Ataque %d)\n", aux->left->time->nome,aux->left->time->ataque,aux->right->time->nome,aux->right->time->ataque);
        }
            else if(vetordeatributos[x-1]==2){
                printf("%s (Defesa %d) x %s (Defesa %d)\n", aux->left->time->nome,aux->left->time->defesa,aux->right->time->nome,aux->right->time->defesa);
            }
                else if(vetordeatributos[x-1]==3){
                    printf("%s (Resistencia %d) x %s (Resistencia %d)\n", aux->left->time->nome,aux->left->time->resistencia,aux->right->time->nome,aux->right->time->resistencia);
                }
                    else if(vetordeatributos[x-1]==4){
                        printf("%s (Velocidade %d) x %s (Velocidade %d)\n", aux->left->time->nome,aux->left->time->velocidade,aux->right->time->nome,aux->right->time->velocidade);
                    }
    }
    return;
}
//endprintaarvore
//teamfree
void teamfree(team *ptr){
    if(ptr->nome[0]!='\0')
        free(ptr->nome);
    free(ptr);
    return;
}
//endteamfree
//destroirtree
void destroirtree(t_node *tree){
    t_node *aux;
    for(int i=31;i>=1;i--){
        aux=acharelemento(tree,i);
        if(i>15&&i<=32)
            teamfree(aux->time);
        free(aux);
    }
    return;
}
//enddestroirtree
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
    int atributo,i,flag=0;
    int vetordeatributos[15], atributoescolhido=0;
    for(i=15;i>0;i--){
        aux=acharelemento(ptr,i);
        if(strcmp(aux->left->time->nome,timeescolhido)==0||strcmp(aux->right->time->nome,timeescolhido)==0){
            if(i>=8)
                printf("OITAVAS DE FINAL\n\n");
            else if(i>=4)
                printf("QUARTAS DE FINAL\n\n");
                else if(i>=2)
                    printf("SEMI-FINAL\n\n");
                    else
                        printf("FINAL\n\n");
            if(strcmp(aux->left->time->nome,timeescolhido)==0){
                printf("Seu time %s\n",aux->left->time->nome);
                if(atributoescolhido==1)
                    printf("XX) XX           : XX\n");
                else
                    printf("1) Ataque        : %d\n",aux->left->time->ataque);
                if(atributoescolhido==2)
                    printf("XX) XX           : XX\n");
                else
                    printf("2) Defesa        : %d\n",aux->left->time->defesa);
                if(atributoescolhido==3)
                    printf("XX) XX           : XX\n");
                else
                    printf("3) Resistencia   : %d\n",aux->left->time->resistencia);
                if (atributoescolhido==4)
                    printf("XX) XX           : XX\n");
                else
                    printf("4) Velocidade    : %d\n\n",aux->left->time->velocidade);
                printf("Seu adversario: %s\n\n",aux->right->time->nome);
                printf("Selecione um atributo: ");
                scanf("%d", &atributo);
                while(atributo==atributoescolhido){
                    printf("O atributo escolhido esta indisponivel.\n");
                    printf("Selecione outro atributo: ");
                    scanf("%d", &atributo);
                }
            }
            else{
                printf("Seu time %s\n",aux->right->time->nome);
                if(atributoescolhido==1)
                    printf("XX) XX           : XX\n");
                else
                    printf("1) Ataque        : %d\n",aux->right->time->ataque);
                if(atributoescolhido==2)
                    printf("XX) XX           : XX\n");
                else
                    printf("2) Defesa        : %d\n",aux->right->time->defesa);
                if(atributoescolhido==3)
                    printf("XX) XX           : XX\n");
                else
                    printf("3) Resistencia   : %d\n",aux->right->time->resistencia);
                if (atributoescolhido==4)
                    printf("XX) XX           : XX\n");
                else
                    printf("4) Velocidade    : %d\n\n",aux->right->time->velocidade);
                printf("Seu adversario: %s\n\n",aux->left->time->nome);
                printf("Selecione um atributo: ");
                scanf("%d", &atributo);
                while(atributo==atributoescolhido){
                    printf("O atributo escolhido esta indisponivel.\n");
                    printf("Selecione outro atributo: ");
                    scanf("%d", &atributo);
                }
            }
            atributoescolhido=atributo;
            aux->time=match(aux->left->time,aux->right->time, atributo);
            if(strcmp(aux->time->nome,timeescolhido)==0){
                system("clear");
                printf("VITORIA\n%s ganhou a partida\n\nPressione qualquer tecla para prosseguir\n", timeescolhido);
                getchar();
                getchar();
                system("clear");
            }
            else{
                system("clear");
                printf("DERROTA\n%s ganhou a partida\n", aux->time->nome);
                vetordeatributos[i-1]=atributo;
                printaarvore(ptr ,vetordeatributos,i);
                while(flag!=1||flag!=2){
                    printf("\n\n[1]-Voltar ao menu principal\n");
                    printf("[2]-Sair do jogo\n");
                    scanf("%d", &flag);
                    if(flag==1){
                        menu();
                        return;
                    }
                    else if(flag==2)
                        return;
                    else
                        printf("Tecla invalida, digite novamente\n");
                }
            }
        }
        else{
            atributo=rand() % 4;
            if(atributo==0)
                atributo=4;
            aux->time=match(aux->left->time, aux->right->time, atributo);
        }
        vetordeatributos[i-1]=atributo;
    }
    printf("Campeao\n");
    i++;
    printaarvore(ptr, vetordeatributos, i);
    while(flag!=1||flag!=2){
        printf("\n\n");
        printf("[1]-Voltar ao menu principal\n");
        printf("[2]-Sair do jogo\n");
        scanf("%d", &flag);
        if(flag==1){
            menu();
            return;
        }
        else if(flag==2)
            return;
        else
            printf("Tecla invalida, digite novamente\n");
    }
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
//menu
void menu(){
    int flag;
    while(1){
        system("clear");
        printf("[1]- Iniciar jogo\n");
        printf("[2]- Sair\n");
        scanf("%d", &flag);
        if(flag==1){
            iniciarjogo();
            return;
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
//endfuncoes
