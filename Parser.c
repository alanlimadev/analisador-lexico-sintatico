#include "TokenList.h"
#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LETTER 0 
#define DIGIT 1
#define NEW_LINE 98
#define UNKNOWN 99

//Definição dos Tokens
#define INT_LIT 10 
#define REAL_NUM 11
#define IDENT 12
#define VAR_TYPE 13
#define SEMICOLON 14
#define DOT 15

//operadores
#define ASSIGN_OP 17
#define SUM_OP 18
#define SUB_OP 19
#define MULTIPLY_OP 20
#define DIVIDE_OP 21
#define COMMA 22
#define LOGIC_OP 23
#define COMPARE_OP 24

#define FOR_STMT 27
#define ELSE_STMT 28
#define IF_STMT 29

#define ACESS_MOD 32
#define LEFT_PAREN 33
#define RIGHT_PAREN 34
#define STATIC_KW 35
#define WHILE_STMT 36
#define QUOT_MARK 37
#define BRACE_LEFT 38
#define BRACE_RIGHT 39
#define UNKNOWN_TOKEN 404

void statement();
void error(char* errorMsg);
void variable_declaration();
void variable_assingment();
void variable_list();
void expression();
void term();
void factor();

int listIndex=0;
Token* CurrentToken;
Token* addrLastToken=NULL;
//int CurrentToken->tokenType=99;

void error(char* errorMsg){
    printf("ERRO! %s na linha %d", errorMsg, CurrentToken->line);
    exit(1);
}

void getNextToken(){ //avanca para o proximo token de Tokens
    addrLastToken=CurrentToken;
    CurrentToken = CurrentToken->prox;
    CurrentToken->tokenType=CurrentToken->tokenType;
}

int peekNextToken(){ //ESPIA e retorna o proximo token de Tokens (nao altera nenhua outra variavel global)
    return CurrentToken->prox->tokenType;
}

void ungetNextToken(){ //volta (APENAS 1 NO MAXIMO) para o token antecessor do token atual
    if(addrLastToken==NULL)
        exit(404);
    CurrentToken=addrLastToken;
    addrLastToken=NULL;
    CurrentToken->tokenType=CurrentToken->tokenType;
}

void parserFunction(Token* tokenList){ //unica funcao presente em Parser.h, apenas ela eh chamada na main de AnalisadorLexico.c
    CurrentToken = tokenList;
    //CurrentToken->tokenType=CurrentToken->tokenType;
    statement();
}

void statement(){ //aqui a brincadeira comeca
    printf("Enter <statement>\n");
    if(CurrentToken->tokenType==VAR_TYPE){
        variable_declaration();
    } else if(CurrentToken->tokenType==IDENT){
        variable_assingment();
    } else {
        error("Declaracao de variavel invalida");
    }

    printf("NOME: %s || TIPO: %d\n", CurrentToken->name, CurrentToken->tokenType);
    
    if(CurrentToken->tokenType==SEMICOLON)
        printf("Leaving <statement>\n");
    else error("Expected ';' in the end of line");
    
    getNextToken();
    if(CurrentToken->tokenType!=EOF)
        statement();
}

void variable_declaration(){
    printf("Enter <variable_declaration>\n");
    if(CurrentToken->tokenType==VAR_TYPE){
        variable_list();
    } else error("erro no <variable_declaration>");
    printf("Leaving <variable_declaration>\n");
}
//int a, b, c;
//int a=5, b=7, c=9;
void variable_list(){
    printf("enter <variable_list>\n");
    int isList= 0; //assume que nao teremos uma var_list
    getNextToken();
    if(CurrentToken->tokenType==IDENT){
        getNextToken();
        if(CurrentToken->tokenType==SEMICOLON); //int x;
        
        else if(CurrentToken->tokenType == COMMA){ //int x,a,b,c;
            while(CurrentToken->tokenType == COMMA){
                getNextToken();
                isList=1;
                if(CurrentToken->tokenType!=IDENT) 
                    error("expected a identifier after ','");
                else
                    getNextToken();
            }         
        }
        else if(isList==0){ // int x = 1
            variable_assingment();
            while(CurrentToken->tokenType==COMMA){ //int x=1,a=2;
                getNextToken();
                if(CurrentToken->tokenType==IDENT){
                    getNextToken();
                    variable_assingment();
                }
                else if(CurrentToken->tokenType==SEMICOLON){
                    break;
                }
                else error("expected a identifier after ','");
            }
        }
        if(CurrentToken->tokenType==ASSIGN_OP && isList==1){ //tentativa de a,b,c=2;
            error("expected a '='");
        }
    printf("leaving <variable_list>\n");
    }
    else error("expected a identifier");
} 
        
void variable_assingment(){
    printf("Enter <variable_assingment>\n");
        if(CurrentToken->tokenType==ASSIGN_OP){
            getNextToken();
            
            expression();
        } else {
            error("expected a '=' ");
        }
        //getNextToken();
    printf("Leaving <variable_assingment>\n");
}
void expression(){
    printf("enter <expression>\n");
    term();
    while(CurrentToken->tokenType==SUM_OP||CurrentToken->tokenType==SUB_OP){
        getNextToken();
        term();
    }
    printf("leaving <expression>\n");
}
void term(){
    printf("enter <term>\n");
    factor();
    while(CurrentToken->tokenType==MULTIPLY_OP||CurrentToken->tokenType==DIVIDE_OP){
        getNextToken();
        factor();
    }
    printf("leaving <term>\n");
}
void factor(){
    printf("enter <factor\n");
    if(CurrentToken->tokenType==IDENT || CurrentToken->tokenType==INT_LIT)
        getNextToken();
    else if(CurrentToken->tokenType==LEFT_PAREN){
        getNextToken();
        expression();
        if(CurrentToken->tokenType==RIGHT_PAREN){
            getNextToken();
        }
        else
            error("expected a ')'");
    }
    else error("right value not recognized");    
          
    printf("leaving <factor>\n");
}