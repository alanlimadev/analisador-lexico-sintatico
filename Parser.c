#include "TokenList.h"
#include <stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void error(char* errorMsg);
void parserFunction();

//Funcoes da Gramatica:
void program();
void statement();
void variable_declaration();
void variable_attribuition();
void assingment();
void type();
void variable_list();
void expression();
void term();
void factor();
void identifier();
void string();
void right_value();

Token* addrCurrentToken;
Token* addrLastToken=NULL;
int currentTokenType=UNKNOWN;

void error(char* errorMsg){
    printf("ERROR! %s at line %d", errorMsg, addrCurrentToken->line);
    exit(1);
}

void getNextToken(){ //avanca para o proximo token de Tokens
    addrLastToken=addrCurrentToken;
    addrCurrentToken = addrCurrentToken->prox;
    currentTokenType=addrCurrentToken->tokenType;
}

int peekNextToken(){ //ESPIA e retorna o proximo token de Tokens (nao altera nenhua outra variavel global)
    return addrCurrentToken->prox->tokenType;
}

void ungetNextToken(){ //volta (APENAS 1 NO MAXIMO) para o token antecessor do token atual
    if(addrLastToken==NULL)
        exit(404);
    addrCurrentToken=addrLastToken;
    addrLastToken=NULL;
    currentTokenType=addrCurrentToken->tokenType;
}

void parserFunction(Token* tokenList){ //unica funcao presente em Parser.h, apenas ela eh chamada na main de AnalisadorLexico.c
    addrCurrentToken = tokenList;
    currentTokenType=addrCurrentToken->tokenType;
    program();
}

void program(){
    printf("Enter <program>\n");
    while (currentTokenType!=EOF){
        statement();
    }
    printf("Leaving <program>\n");
}

void statement(){ //aqui a brincadeira comeca
    printf("Enter <statement>\n");
    if(addrCurrentToken->tokenType==VAR_TYPE){
        variable_declaration();
    } else if(addrCurrentToken->tokenType==IDENT){
        variable_attribuition();
        while(addrCurrentToken->tokenType==COMMA){
            getNextToken(); //consome ,
            variable_attribuition();
        }
            
    } else {
        error("Declaracao de variavel invalida");
    }

    //printf("NOME: %s || TIPO: %d\n", CurrentToken->name, CurrentToken->tokenType);
    
    if(addrCurrentToken->tokenType==SEMICOLON)
        printf("Leaving <statement>\n");
    else error("Expected ';' in the end of line");
    
    getNextToken();
    if(addrCurrentToken->tokenType!=EOF)
        statement();
}

void variable_declaration(){
    printf("Enter <variable_declaration>\n");
        type();
        variable_list();
    printf("Leaving <variable_declaration>\n");
}
void variable_attribuition(){
    printf("enter <variable_attribuition>\n");
    identifier();
    assingment();
    printf("leaving <variable_attribuition>\n");
}
void type(){
    printf("Enter <type>\n");
    if(addrCurrentToken->tokenType!=VAR_TYPE)
        error("expected a vartype");
    getNextToken();        
    printf("leaving <type>\n");    
}
void identifier(){
    printf("Enter <identifier>\n");
    if(addrCurrentToken->tokenType!=IDENT)
        error("expected a identifier");
    getNextToken();
    printf("leaving <identifier>\n");
}

//int a, b, c;
//int a=5, b=7, c=9;
void variable_list(){  //<identifier> 
    printf("enter <variable_list>\n");

    if(peekNextToken() != ASSIGN_OP){
        identifier();
        while(currentTokenType==COMMA){
            getNextToken(); //consome a virgula
            identifier();
            if(currentTokenType!=COMMA && currentTokenType!=SEMICOLON)
                error("There should only be identifier names separated by commas");
                //Os nomes do indentificadores devem ser separados por virgulas
        }
    } else {
        while(1){
            variable_attribuition();
            if(currentTokenType==COMMA){
                getNextToken(); //consome a virgula novamente
            } else {
                if(currentTokenType==SEMICOLON)
                    break; //finaliza a função se um ; for encontrado
                    
                error("The identifier names and their inicializations should be separated by commas");
                //Os nomes do indentificadores e suas inicializacoes devem ser separados por virgulas
            }
        }
    }

/*
    if(peekNextToken()==ASSIGN_OP){
        while(1){
            variable_attribuition();
            if(currentTokenType==COMMA){
                getNextToken(); //consome a virgula novamente
            } else {
                if(currentTokenType==SEMICOLON)
                    break; //finaliza a função se um ; for encontrado

                error("The identifier names and their inicializations should be separated by commas");
                //Os nomes do indentificadores e suas inicializacoes devem ser separados por virgulas
            }
        }
    } else if(peekNextToken()==COMMA || peekNextToken()==SEMICOLON){
        identifier();
        while(currentTokenType==COMMA){
            getNextToken(); //consome a virgula
            identifier();
            if(currentTokenType!=COMMA && currentTokenType!=SEMICOLON)
                error("There should only be identifier names separated by commas");
                //Os nomes do indentificadores devem ser separados por virgulas
        }
    } else {
        error("Invalid expression for variable declaration");
    } */

    printf("leaving <variable_list>\n");
}

void assingment(){
    printf("Enter <assingment>\n");
        if(addrCurrentToken->tokenType==ASSIGN_OP){
            getNextToken(); //consome =
            right_value(); //expression();
        }
        else {
            error("expected a '='");
        }
    printf("Leaving <assingment>\n");
}

void expression(){
    printf("enter <expression>\n");
    term();
    while(addrCurrentToken->tokenType==SUM_OP || addrCurrentToken->tokenType==SUB_OP){
        getNextToken();
        term();
    }
    printf("leaving <expression>\n");
}
void term(){
    printf("enter <term>\n");
    factor();
    while(addrCurrentToken->tokenType==MULTIPLY_OP||addrCurrentToken->tokenType==DIVIDE_OP){
        getNextToken();
        factor();
    }
    printf("leaving <term>\n");
}
void factor(){
    printf("enter <factor>\n");
    if(addrCurrentToken->tokenType==IDENT)
        identifier();
    else if(addrCurrentToken->tokenType==INT_LIT)
        getNextToken();
    else if(addrCurrentToken->tokenType==LEFT_PAREN){
        getNextToken();
        expression();
        if(addrCurrentToken->tokenType==RIGHT_PAREN){
            getNextToken();
        }
        else
            error("expected a ')'");
    }
    else error("right value not recognized");    
          
    printf("leaving <factor>\n");
}

void right_value() {
    printf("Enter <right_value>\n");

    if(currentTokenType==INT_LIT || currentTokenType==IDENT)
        expression();
    else if(currentTokenType==DQUOT_MARK)
        string();
    else
        error("Invalid right side of the variable attribution");

    printf("Leaving <right_value>\n");
}

void string(){
    printf("Enter <string>\n");
    if(currentTokenType==DQUOT_MARK){
        getNextToken(); //consome a primeira "
        while(currentTokenType!=DQUOT_MARK){
            getNextToken(); //consome todos os caracteres ate a proxima aspas duplas
            if(currentTokenType==EOF)
                error("The quotation mark for string value never closed");
        }
        getNextToken(); //consome a ultima "
    }
    printf("Leaving <string>\n");
}



/*
void char_(){ //<char> grammar rule
    printf("Enter <char_>");
    if(currentTokenType==SQUOT_MARK){
        getNextToken(); //consome a primeira '
        getNextToken(); //consome o char
        if(currentTokenType==SQUOT_MARK)
            getNextToken();
        else
            error("Single Quotations marks should only be used for assigning char type (only one character)")
    }

    printf("Leaving <char_>");
}
*/

/*
//functions below refer to the boolean expression grammar rule
void bool_expression(){
    printf("enter <expression>\n");
    bool_term();
    while(addrCurrentToken->tokenType==OR_OP){
        getNextToken();
        bool_term();
    }
    printf("leaving <expression>\n");
}
void bool_term(){
    printf("enter <term>\n");
    bool_factor();
    while(addrCurrentToken->tokenType==AND_OP){
        getNextToken();
        bool_factor();
    }
    printf("leaving <term>\n");
}
void bool_factor(){
    printf("enter <factor>\n");
    if(currentTokenType==IDENT)
        identifier();
    else if(currentTokenType==NOT_OP)
        getNextToken();
    else if(currentTokenType==LEFT_PAREN){
        getNextToken();
        bool_expression();
        if(currentTokenType==RIGHT_PAREN){
            getNextToken();
        }
        else
            error("expected a ')'");
    }
    else error("right value not recognized");    
          
    printf("leaving <factor>\n");
}
*/