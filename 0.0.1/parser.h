#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "a89alloc.h"

/*
 * TIPOS DE NOS DA ARVORE SINTATICA ABSTRATA (AST) - RUDIS
 * 
 * Cada no da arvore representa um elemento da expressao:
 * - NODE_NUMBER: um numero literal
 * - NODE_VARIABLE: uma variavel (identificador completo)
 * - NODE_BINARY_OP: operacao binaria (+, -, *, /, %, ^)
 * - NODE_UNARY_OP: operacao unaria (!, -)
 * - NODE_FUNCTION: chamada de funcao
 * - NODE_ASSIGNMENT: atribuicao de valor a variavel
 */
typedef enum {
    NODE_NUMBER,
    NODE_VARIABLE,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_FUNCTION,
    NODE_ASSIGNMENT
} NodeType;

/*
 * ESTRUTURA DO NO DA AST - RUDIS
 * 
 * Cada no contem:
 * - type: tipo do no
 * - value: valor numerico (para NODE_NUMBER)
 * - variable: nome da variavel (para NODE_VARIABLE)
 * - operator: operador (para NODE_BINARY_OP e NODE_UNARY_OP)
 * - function: nome da funcao (para NODE_FUNCTION)
 * - left, right: filhos esquerdo e direito (operacoes binarias)
 * - operand: operando (para operacoes unarias)
 * - args: argumentos da funcao (para NODE_FUNCTION)
 * - arg_count: numero de argumentos
 */
typedef struct ASTNode {
    NodeType type;
    
    // Dados especificos do no
    double value;           // Para NODE_NUMBER
    char variable[64];      // Para NODE_VARIABLE (identificadores completos)
    char operator;          // Para NODE_BINARY_OP e NODE_UNARY_OP
    char function[32];      // Para NODE_FUNCTION
    
    // Filhos do no
    struct ASTNode* left;   // Filho esquerdo (operacoes binarias)
    struct ASTNode* right;  // Filho direito (operacoes binarias)
    struct ASTNode* operand;// Operando (operacoes unarias)
    
    // Para funcoes com multiplos argumentos
    struct ASTNode** args;  // Array de argumentos
    int arg_count;          // Numero de argumentos
} ASTNode;

/*
 * ESTRUTURA DO PARSER - RUDIS
 * 
 * Mantem o estado do analisador sintatico:
 * - lexer: referencia ao lexer
 * - current_token: token atual sendo analisado
 * - has_error: indica se ocorreu erro no parsing
 * - error_message: mensagem de erro descritiva
 */
typedef struct {
    Lexer* lexer;
    Token current_token;
    int has_error;
    char error_message[100];
} Parser;

/*
 * FUNCOES DO PARSER - RUDIS
 */

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

// Cria nos da AST
ASTNode* create_number_node(double value);
ASTNode* create_variable_node(const char* variable);
ASTNode* create_binary_op_node(char operator, ASTNode* left, ASTNode* right);
ASTNode* create_unary_op_node(char operator, ASTNode* operand);
ASTNode* create_function_node(const char* function, ASTNode** args, int arg_count);
ASTNode* create_assignment_node(const char* variable, ASTNode* value);

// Libera memoria da AST
void free_ast(ASTNode* node);

// Funcoes de parsing (seguindo a gramatica RUDIS)
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
void print_ast(ASTNode* node, int indent);

#endif // PARSER_H