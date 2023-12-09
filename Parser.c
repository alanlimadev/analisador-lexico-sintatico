#include "TokenList.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void error(char *errorMsg);

// Funcoes da Gramatica:
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
void char_();
void bool_expression();
void bool_term();
void bool_factor();
void if_else_statement();
void embedded_statement();
void control_structures();
void while_loop();
void for_loop();
int isBoolExpression();
int isControlStructure();

Token *addrCurrentToken;
int currentTokenType = UNKNOWN;

void error(char *errorMsg)
{
    printf("ERROR! %s at line %d", errorMsg, addrCurrentToken->line);
    exit(1);
}

void getNextToken()
{ // avanca para o proximo token de Tokens
    addrCurrentToken = addrCurrentToken->prox;
    currentTokenType = addrCurrentToken->tokenType;
}

int peekNextToken()
{ // ESPIA e retorna o proximo token de Tokens (nao altera nenhua outra variavel global)
    return addrCurrentToken->prox->tokenType;
}


void parserFunction(Token *tokenList)
{ // unica funcao presente em Parser.h, apenas ela eh chamada na main de AnalisadorLexico.c
    addrCurrentToken = tokenList;
    currentTokenType = addrCurrentToken->tokenType;
    program();
}

void program()
{
    printf("Enter <program>\n");
    while (currentTokenType != EOF)
    {
        //*if (currentTokenType == IF_STMT | currentTokenType == WHILE_STMT | currentTokenType == FOR_STMT)
            //control_structures();
        //else
            statement();
        
    }
    printf("Leaving <program>\n");
}

void control_structures()
{
    if (currentTokenType == IF_STMT)
        if_else_statement();
    else if (currentTokenType == WHILE_STMT)
        while_loop();
    else if (currentTokenType == FOR_STMT)
        for_loop();
}

void statement()
{
    printf("Enter <statement>\n");

    if(isControlStructure()){
        control_structures();

    } else {

        if (addrCurrentToken->tokenType == VAR_TYPE)
        {
            variable_declaration();
        }
        else if (addrCurrentToken->tokenType == IDENT)
        {
            variable_attribuition();
            while (addrCurrentToken->tokenType == COMMA)
            {
                getNextToken(); // consome ,
                variable_attribuition();
            }
        }
        else
        {
            error("Declaracao de variavel invalida");
        }

        // printf("NOME: %s || TIPO: %d\n", CurrentToken->name, CurrentToken->tokenType);

        if (addrCurrentToken->tokenType != SEMICOLON)
            error("Expected ';' in the end of line");
        getNextToken(); //consome o ;

    }

    

    printf("Leaving <statement>\n");
}

void variable_declaration()
{
    printf("Enter <variable_declaration>\n");
    type();
    variable_list();
    printf("Leaving <variable_declaration>\n");
}
void variable_attribuition()
{
    printf("enter <variable_attribuition>\n");
    identifier();
    assingment();
    printf("leaving <variable_attribuition>\n");
}
void type()
{
    printf("Enter <type>\n");
    if (addrCurrentToken->tokenType != VAR_TYPE)
        error("expected a vartype");
    getNextToken();
    printf("leaving <type>\n");
}
void identifier()
{
    printf("Enter <identifier>\n");
    if (addrCurrentToken->tokenType != IDENT)
        error("expected a identifier");
    getNextToken();
    printf("leaving <identifier>\n");
}

// int a, b, c;
// int a=5, b=7, c=9;
void variable_list() { //<identifier>
    printf("enter <variable_list>\n");

    if (peekNextToken() != ASSIGN_OP)
    {
        identifier();
        while (currentTokenType == COMMA)
        {
            getNextToken(); // consome a virgula
            identifier();
            if (currentTokenType != COMMA && currentTokenType != SEMICOLON)
                error("There should only be identifier names separated by commas");
            // Os nomes do indentificadores devem ser separados por virgulas
        }
    }
    else
    {
        while (1)
        {
            variable_attribuition();
            if (currentTokenType == COMMA)
            {
                getNextToken(); // consome a virgula novamente
            }
            else
            {
                if (currentTokenType == SEMICOLON || currentTokenType == EOF)
                    break; // finaliza a função se um ; for encontrado

                error("The identifier names and their inicializations should be separated by commas");
                // Os nomes do indentificadores e suas inicializacoes devem ser separados por virgulas
            }
        }
    }
    printf("leaving <variable_list>\n");
}

void assingment() {
    printf("Enter <assingment>\n");
    if (addrCurrentToken->tokenType == ASSIGN_OP)
    {
        getNextToken(); // consome =
        right_value();  // expression();
    }
    else
    {
        error("expected a '='");
    }

    printf("Leaving <assingment>\n");
}

void expression()
{
    printf("enter <expression>\n");

    if(isBoolExpression())
        error("Invalid arithmetic expression (Expected only identifiers, integer literals and arithmetic operators)");
    

    term();
    while (addrCurrentToken->tokenType == SUM_OP || addrCurrentToken->tokenType == SUB_OP)
    {
        getNextToken();
        term();
    }
    printf("leaving <expression>\n");
}
void term()
{
    printf("enter <term>\n");
    factor();
    while (addrCurrentToken->tokenType == MULTIPLY_OP || addrCurrentToken->tokenType == DIVIDE_OP)
    {
        getNextToken();
        factor();
    }
    printf("leaving <term>\n");
}
void factor()
{
    printf("enter <factor>\n");
    if (addrCurrentToken->tokenType == IDENT)
        identifier();
    else if (addrCurrentToken->tokenType == INT_LIT)
        getNextToken();
    else if (addrCurrentToken->tokenType == LEFT_PAREN)
    {
        //printf("%d", currentTokenType);
        getNextToken();
        expression();
        if (addrCurrentToken->tokenType == RIGHT_PAREN)
        {
            getNextToken();
        }
        else
            error("expected a ')'");
    }
    else
        error("right value not recognized");

    printf("leaving <factor>\n");
}

int isBoolExpression()
{
    Token *tokenAux = addrCurrentToken;
    int type;
    while (tokenAux->prox != NULL)
    {
        type = tokenAux->tokenType;
        if (type == OR_OP || type == NOT_OP || type == AND_OP)
            return 1;

        if (type == INT_LIT || type == SUM_OP || type == SUB_OP || type == DIVIDE_OP || type == MULTIPLY_OP )
            return 0;
        tokenAux = tokenAux->prox;
    }

    return 0;
}

void right_value()
{
    printf("Enter <right_value>\n");

    int isBool = isBoolExpression();

    if (currentTokenType == DQUOT_MARK)
        string(); // "(...)"
    else if (currentTokenType == SQUOT_MARK)
        char_(); // '(...)'
    else if (isBool)
        bool_expression(); //expressao booleana
    else if (!isBool)
        expression(); //int_lit ou expressao aritimetica
    else 
        error("Invalid right side of the variable attribution");
    
    printf("Leaving <right_value>\n");
}

void string()
{
    printf("Enter <string>\n");
    if (currentTokenType == DQUOT_MARK)
    {
        getNextToken(); // consome a primeira "
        while (currentTokenType != DQUOT_MARK)
        {
            getNextToken(); // consome todos os caracteres ate a proxima aspas duplas
            if (currentTokenType == EOF)
                error("The quotation mark for string value never closed");
        }
        getNextToken(); // consome a ultima "
    }
    printf("Leaving <string>\n");
}

void char_()
{ //<char> grammar rule
    printf("Enter <char_>\n");
    if (currentTokenType == SQUOT_MARK)
    {
        getNextToken(); // consome a primeira '
        getNextToken(); // consome o char (supostamente, a explicacao do erro ta na TODO list)
        if (currentTokenType == SQUOT_MARK)
        {
            getNextToken(); // consome a ultima '
        }
        else
            error("Single Quotations marks should only be used for assigning char type (only one character)");
    }

    printf("Leaving <char_>\n");
}

void bool_expression()
{
    printf("enter <bool_expression>\n");

    if(!isBoolExpression())
        error("Invalid boolean expression (Expected only identifiers and boolean operators)");

    bool_term(); 
    while (addrCurrentToken->tokenType == OR_OP)
    {
        getNextToken();
        bool_term();
    }
    printf("leaving <bool_expression>\n");
}

void bool_term()
{
    printf("enter <bool_term>\n");
    bool_factor();
    while (addrCurrentToken->tokenType == AND_OP)
    {
        getNextToken();
        bool_factor();
    }
    printf("leaving <bool_term>\n");
}

void bool_factor()
{
    printf("enter <bool_factor>\n");
    if (currentTokenType == IDENT)
        identifier();
    else if (currentTokenType == NOT_OP) {
        getNextToken(); // consome o !
        identifier();
    }
    else if (currentTokenType == LEFT_PAREN) {
        getNextToken();
        bool_expression();
        if (currentTokenType == RIGHT_PAREN)
        {
            getNextToken();
        }
        else
            error("expected a ')'");
    }
    else
        error("expected a logic expression");

    printf("leaving <bool_factor>\n");
}

void if_else_statement()
{
    printf("Enter <if_else_statement>\n");

    if (addrCurrentToken->tokenType == IF_STMT)
    {
        getNextToken(); // Consome "if"

        if (addrCurrentToken->tokenType == LEFT_PAREN)
        {
            getNextToken();    // Consome "("
            bool_expression(); // Avalia a expressão booleana

            if (addrCurrentToken->tokenType == RIGHT_PAREN)
            {
                getNextToken();       // Consome ")"
                embedded_statement(); // Avalia o bloco de código dentro do "if"

                if (addrCurrentToken->tokenType == ELSE_STMT)
                {
                    getNextToken();       // Consome "else"
                    embedded_statement(); // Avalia o bloco de código dentro do "else"
                }
            }
            else
            {
                error("Expected closing parenthesis ')'");
            }
        }
        else
        {
            error("Expected opening parenthesis '('");
        }
    }
    else
    {
        error("Invalid if statement");
    }

    printf("Leaving <if_else_statement>\n");
}

void while_loop()
{
    printf("Enter <while_loop>\n");

    if (addrCurrentToken->tokenType == WHILE_STMT)
    {
        getNextToken(); // Consome "while"

        if (addrCurrentToken->tokenType == LEFT_PAREN)
        {
            getNextToken();    // Consome "("
            bool_expression(); // Avalia a expressão booleana

            if (addrCurrentToken->tokenType == RIGHT_PAREN)
            {
                getNextToken();       // Consome ")"
                embedded_statement(); // Avalia o bloco de código dentro do "while"
            }
            else
            {
                error("Expected closing parenthesis ')'");
            }
        }
        else
        {
            error("Expected opening parenthesis '('");
        }
    }
    else
    {
        error("Invalid while statement");
    }

    printf("Leaving <while_loop>\n");
}

void for_loop() {
    while (currentTokenType != BRACE_RIGHT) {
        // Verifica se o lexema é um loop "for"
        if (currentTokenType == FOR_STMT) {
            getNextToken();

            if (currentTokenType != LEFT_PAREN) {
                error("Erro: Esperava-se um tipo de variável na inicialização do loop 'for'");
            }
            getNextToken();

            if(currentTokenType == IDENT){
                statement();
            } else{
                if(currentTokenType){
                    error("Erro: expected ;");
                }
                getNextToken();
            }
            

            bool_expression();
            //getNextToken();

            if (currentTokenType == SEMICOLON){
                getNextToken();
                variable_attribuition();
            }
            else
                error("Erro: esperava-se ; no final da statement"); 

            if(currentTokenType != RIGHT_PAREN){
                error("Erro: for loop statements nao foi fechado");
            }

            getNextToken();
            if(currentTokenType != BRACE_LEFT){
                error("Erro: for loop nao foi iniciado corretamente");
            }
            getNextToken();

            while (currentTokenType != BRACE_RIGHT && currentTokenType != EOF){
                statement();
                //getNextToken();
                if(currentTokenType == EOF){
                    error("Erro: for loop nao foi fechado");
                }
            }
            getNextToken();
            
        } else{
            break;
        }
    }
}
int isControlStructure(){
    return (currentTokenType==IF_STMT || currentTokenType==WHILE_STMT || currentTokenType == FOR_STMT);
}
void embedded_statement()
{
    printf("Enter <embedded_statement>\n");

    if (addrCurrentToken->tokenType == BRACE_LEFT)
    {
        // Se o bloco de código inicia com uma chave "{"
        getNextToken();// Consome "{"

        //isControlStructure() ? control_structures(): statement(); // Avalia o código dentro do bloco

        // Aqui você lidaria com o código dentro do bloco
        // Você provavelmente teria um loop ou uma lógica para processar o código dentro do bloco

        while (addrCurrentToken->tokenType != BRACE_RIGHT)
        {
            statement();
        }

        if (addrCurrentToken->tokenType == BRACE_RIGHT)
        {
            // Finaliza o bloco quando encontra a chave de fechamento "}"
            getNextToken(); // Consome "}"
        }
        else
        {
            error("Expected closing brace '}'");
        }
    }
    else
    {
        // Se for apenas uma única instrução sem chaves
        // Implemente a lógica para processar uma única instrução (se aplicável)
        // Isso pode ser uma declaração, atribuição, etc.
        // Não vou implementar a lógica específica aqui, pois pode variar conforme a necessidade do seu analisador
        // Certifique-se de lidar com as regras gramaticais da linguagem para uma única instrução

        // Exemplo simples:
        // processSingleStatement();
        // getNextToken(); // Avança para o próximo token após processar a instrução
    }

    printf("Leaving <embedded_statement>\n");
}
