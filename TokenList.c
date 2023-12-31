#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TokenList.h"

Token* create(){
    return NULL;
}
Token* insert(Token* list, int tokenType,char* name,int line, char* value){
    Token* newToken = (Token*)malloc(sizeof(Token));
    strcpy(newToken->name,name);
    newToken->tokenType=tokenType;
    newToken->line = line;
    newToken->prox=NULL;
    strcpy(newToken->value,value);
    if(list==NULL){
        return newToken;
    }
    
    Token* aux = list;
    while (aux->prox!=NULL){
        aux=aux->prox;
    }
    aux->prox=newToken;
    return list;
}
void printList(Token* list){
    Token* aux=list;
    while(aux!=NULL){
        //printf("Linha %d) token: %s\n",aux->line, aux->name);
        printf("%d) ""%s"" (lexema: %s)\n", aux->line, aux->name, aux->value);
        aux=aux->prox;
    }
}
