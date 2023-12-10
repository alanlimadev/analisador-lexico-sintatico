#pragma once

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
#define OR_OP 23
#define AND_OP 24
#define NOT_OP 25
#define COMPARE_OP 26

#define FOR_COMMAND 29
#define IF_COMMAND 30
#define ELSE_COMMAND 31

#define ACESS_MOD 32
#define LEFT_PAREN 33
#define RIGHT_PAREN 34
#define STATIC_KW 35
#define WHILE_COMMAND 36
#define BRACE_LEFT 37
#define BRACE_RIGHT 38
#define DQUOT_MARK 40
#define SQUOT_MARK 41
#define RETURN_KW 42
#define TRUE_OP 43
#define FALSE_OP 44
#define MAIN_KW 45
#define VOID_KW 46
#define INT_TYPE 47
#define STRING_ARG 48
#define ARGS_KW 49
#define LEFT_SQUARE_BRKT 51
#define RIGHT_SQUARE_BRKT 52
#define UNKNOWN_TOKEN 404



typedef struct token Token;
struct token{int tokenType;char name[30];Token* prox;int line;char value[100];};
Token* create();
Token* insert(Token* list, int tokenType,char* name, int line,char* value);
void printList(Token* list);
