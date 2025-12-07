#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "value.h"
#include "lexer.h"
#include "a89alloc.h"

// ==================================================================
// ÁRVORE SINTÁTICA (AST)
// ==================================================================
typedef enum {
    NODE_NUMBER,
    NODE_STRING,
    NODE_VARIABLE,
    NODE_BINARY_OP, //operacao binaria (+, -, *, /, %, ^)
    NODE_UNARY_OP,  //operacao unaria (!, -)
    NODE_FUNCTION,
    NODE_ASSIGNMENT,
    NODE_SEQUENCE 
} NodeType;

typedef struct ASTNode {
    NodeType type;
    
    // Dados especificos do no
    Value value;            // Para NODE_NUMBER e NODE_STRING
    char text[STR_SIZE];    // Para NODE_VARIABLE (nome) 
    char operator;          // Para NODE_BINARY_OP e NODE_UNARY_OP
    char function[STR_SIZE];// Para NODE_FUNCTION
    
    // Filhos do no
    struct ASTNode* left;   // Filho esquerdo (operacoes binarias)
    struct ASTNode* right;  // Filho direito (operacoes binarias)
    struct ASTNode* operand;// Operando (operacoes unarias)
    
    // Para funcoes com multiplos argumentos
    struct ASTNode** args;  // Array de argumentos
    int arg_count;          // Numero de argumentos

    // Para NODE_SEQUENCE
    struct ASTNode** statements;  // Array de statements
    int stmt_count;  
} ASTNode;

ASTNode* create_number_node(double value);
ASTNode* create_variable_node(const char* variable);
ASTNode* create_binary_op_node(char operator, ASTNode* left, ASTNode* right);
ASTNode* create_unary_op_node(char operator, ASTNode* operand);
ASTNode* create_function_node(const char* function, ASTNode** args, int arg_count);
ASTNode* create_assignment_node(const char* variable, ASTNode* value);
ASTNode* create_string_node(const char* str_value);
ASTNode* create_sequence_node(ASTNode** statements, int stmt_count);

void free_ast(ASTNode* node);

// ==================================================================
// PARSER
// ==================================================================
typedef struct {
    Lexer* lexer;
    Token current_token;
    int has_error;
    char error_message[STR_SIZE];
} Parser;

// Inicializa o parser
void parser_init(Parser* parser, Lexer* lexer);

// Avanca para o proximo token
void parser_advance(Parser* parser);

// Verifica se o token atual e do tipo esperado
int parser_expect(Parser* parser, RTokenType expected_type);

// Define mensagem de erro no parser
void parser_set_error(Parser* parser, const char* message);

// Valida numero de argumentos das funcoes RUDIS
int validate_function_args(Parser* parser, const char* function_name, int arg_count);


/********************************************************************
FUNCOES DE PARSING 

GRAMATICA v0.0.2
program          := statement_list
statement_list   := statement ((';' | NEWLINE) statement)*
statement        := expression
expression       := assignment | arithmetic_expr
assignment       := IDENTIFIER '=' expression
arithmetic_expr  := term (('+' | '-') term)*
term             := factor (('*' | '/' | '%') factor)*
factor           := power ('!')?
power            := atom ('^' power)?
atom             := NUMBER | STRING | IDENTIFIER | function_call | '(' expression ')' | '-' atom
function_call    := FUNCTION '(' argument_list ')'
argument_list    := expression (',' expression)*
********************************************************************/
ASTNode* parse_program(Parser* parser); // a ser implementada quando necessário
ASTNode* parse_statement_list(Parser* parser);
ASTNode* parse_statement(Parser* parser);
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_assignment(Parser* parser);
ASTNode* parse_arithmetic_expr(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_factor(Parser* parser);
ASTNode* parse_power(Parser* parser);
ASTNode* parse_atom(Parser* parser);
ASTNode* parse_function_call(Parser* parser, const char* function_name);

// Funcao principal de parsing
ASTNode* parse(Lexer* lexer);

// Funcao para imprimir a AST (para debug)
void print_ast(ASTNode* node, int indent, int decimal_places);

#endif // PARSER_H