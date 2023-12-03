typedef struct token Token;
struct token{int tokenType;char name[30];Token* prox;int line;};
Token* create();
Token* insert(Token* list, int tokenType,char* name, int line;);
void printList(Token* list);
