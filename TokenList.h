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
#define ASSIGN_OP 16
#define SUM_OP 17
#define SUB_OP 18
#define MULTIPLY_OP 19
#define DIVIDE_OP 20
#define COMMA 21
#define LOGIC_OP 22
#define OR_OP 23
#define AND_OP 24
#define NOT_OP 25
#define COMPARE_OP 26

#define FOR_STMT 28
#define ELSE_STMT 29
#define IF_STMT 30

#define ACESS_MOD 32
#define LEFT_PAREN 33
#define RIGHT_PAREN 34
#define STATIC_KW 35
#define WHILE_STMT 36
#define QUOT_MARK 37 //Double quotation
#define BRACE_LEFT 38
#define BRACE_RIGHT 39
//#define DQUOT_MARK 40
//#define SQUOT_MARK 41
#define UNKNOWN_TOKEN 404



typedef struct token Token;
struct token{int tokenType;char name[30];Token* prox;int line;};
Token* create();
Token* insert(Token* list, int tokenType,char* name, int line);
void printList(Token* list);
