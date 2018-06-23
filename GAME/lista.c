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
#include <string.h>
#include <stdlib.h>

//funcoes

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
//endfuncoes
