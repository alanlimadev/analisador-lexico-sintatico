#include "TokenList.h"
#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void statement();
void error(char* errorMsg);
void variable_declaration();
void variable_assingment();

int listIndex=0;
Token* addrCurrentToken;
Token* addrLastToken=NULL;
int currTokenType=99;

void error(char* errorMsg){
    printf("ERRO! %s na linha %d", errorMsg, addrCurrentToken->line);
    exit(1);
}

void getNextToken(){ //avanca para o proximo token de Tokens
    addrLastToken=addrCurrentToken;
    addrCurrentToken = addrCurrentToken->prox;
    currTokenType=addrCurrentToken->tokenType;
}

int peekNextToken(){ //ESPIA e retorna o proximo token de Tokens (nao altera nenhua outra variavel global)
    return addrCurrentToken->prox->tokenType;
}

void ungetNextToken(){ //volta (APENAS 1 NO MAXIMO) para o token antecessor do token atual
    if(addrLastToken==NULL)
        exit(404);
    addrCurrentToken=addrLastToken;
    addrLastToken=NULL;
    currTokenType=addrCurrentToken->tokenType;
}

void parserFunction(Token* tokenList){ //unica funcao presente em Parser.h, apenas ela eh chamada na main de AnalisadorLexico.c
    addrCurrentToken = tokenList;
    currTokenType=addrCurrentToken->tokenType;
    statement();
}

void statement(){ //aqui a brincadeira comeca
    printf("Enter <statement>\n");
    if(currTokenType==VAR_TYPE){
        variable_declaration();
    } else if(currTokenType==IDENT){
        variable_assingment();
    } else {
        error("Declaracao de variavel invalida");
    }

    //printf("NOME: %s || TIPO: %d\n", addrCurrentToken->name, addrCurrentToken->tokenType);
    getNextToken();
    if(currTokenType!=SEMICOLON)
        error("Insira ';' ao final da linha");
    
    getNextToken();
    if(currTokenType!=EOF)
        statement();

    printf("Leaving <statement>\n");
}

void variable_declaration(){
    printf("Enter <variable_declaration>\n");
    if(currTokenType==VAR_TYPE){
        variable_list();
    } else error("erro no <variable_declaration>");
    printf("Leaving <variable_declaration>\n");
}
//int a, b, c;
//int a=5, b=7, c=9;
void variable_list(){
    getNextToken();
    if(currTokenType==IDENT){

        if(peekNextToken()==COMMA){
            while (peekNextToken()==COMMA) {
                getNextToken();
                if(peekNextToken()==IDENT){
                    getNextToken();
                } else {
                    error("Siga o formato correto para declarar multiplas variaveis na mesma linha");
                }
            }

        } else if(peekNextToken()==ASSIGN_OP){
            variable_assingment();
            while(peekNextToken()==COMMA){
                getNextToken(); //passa o token para o da virgula
                getNextToken(); //passa o token para o do identificador (se estiver tudo escrito corretamente)
                variable_assingment();
            }
            
        } else error("Siga o formato correto para declarar e inicializar multiplas variaveis na mesma linha");

    } else error("Declaracao de variavel incorreta (forma correta: {tipo} {nomeVar})");


}

void variable_assingment(){
    printf("Enter <variable_assingment>\n");
    if(currTokenType==IDENT){
        getNextToken();
        if(currTokenType==ASSIGN_OP){
            getNextToken();
            if(!(currTokenType==IDENT || currTokenType==INT_LIT)){
                error("expressao do lado direito da atribuicao invalida");
            }
        } else {
            error("sinal de recebe '=' faltando");
        }
    } else error("Era esperado um Nome de Variavel (identificador faltando)");

    printf("Leaving <variable_assingment>\n");
}