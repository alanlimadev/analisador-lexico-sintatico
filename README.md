
# Analisador Léxico e Sintático

Um analisador léxico converte código em tokens, enquanto o analisador sintático verifica se a estrutura dos tokens segue a gramática definida.

## Autores

- [@alanlimadev](https://www.github.com/alanlimadev)
- [@CizeLucas](https://www.github.com/CizeLucas)
- [@jvictorcostaa](https://www.github.com/jvictorcostaa)
- [@MicaiasMartins120](https://www.github.com/MicaiasMartins120)
- [@pauloherbt](https://www.github.com/pauloherbt)
- [@pedromsh](https://www.github.com/pedromsh)
## Instalação

```bash
  git clone https://github.com/alanlimadev/analisador-lexico-sintatico.git

  cd analisador-lexico-sintatico

  gcc *.c -o myprogram 

  ./myprogram.exe
```
    
## Gramática EBNF

```http

<program> ::= <main_function>

<main_function> ::= ACESS_MOD? STATIC_KW ( INT_TYPE | VOID_KW ) MAIN_KW “(“ (( VAR_TYPE  |  INT_TYPE )(“[““]”)?  IDENT )? ”)” “{“  <statement>*  “}”

<return_stmt> ::= RETURN_KW <expression>

<statement> ::= <control_structures> | ( ( <variable_declaration> | <variable_attribution> | <return_stmt> )  “;”)

<float_number> ::= INT_LIT “.” INT_LIT

<integer_number> ::= INT_LIT

<control_structures> = ( <if_condition> | <while_loop> | <for_loop> )

<variable_declaration> ::= ( VAR_TYPE | INT_TYPE ) <variable_list>

<variable_list> ::= ( <identifier> (“,” <identifier>)* ) | ( <variable_attribution> (“,” <variable_attribution>)* )

<variable_atribution> ::= <identifier> <assignment>

<assignment> ::= ( “=” <right_value> )

<right_value> ::= ( <bool_expr> | <expression> | <string> | <char_> )

<string> ::= "\"" <char>* "\""

<char_> ::= "\'" <char> "\'"

<expression>  ::= <term> ( ("+" | "-") <term> )*
<term>        ::= <factor> ( ("*" | "/") <factor> )*
<factor>   ::= <identifier> | <integer_number> | <float_number> | "(" <expression> ")"

<bool_expr>     ::= <bool_term> ( ("&&") <bool_term> )*
<bool_term>     ::= <bool_factor> ( ("||") <bool_factor> )*
<bool_factor>   ::= <identifier> | ("!" <bool_factor>) | "(" <bool_expr> ")" | TRUE_OP | FALSE_OP

<if_condition> ::= IF_COMMAND “(“ <bool_expr> ”)”  <embedded_stmt> (“else” <embedded_statement>)?

<while_loop> ::= WHILE_COMMAND “(“ <bool_expr> ”)” <embedded_statement>

<for_loop> ::= 
FOR_COMMAND ((<variable_declaration> | <variable_attribution>)”;” <bool_expr>”;” <variable_attribuition>) <embedded_statement>

<embedded_statement> ::= ( <statement> | "{" <statement>* "}" )

```

```
