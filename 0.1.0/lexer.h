#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "common.h"

/*
 * TIPOS DE TOKENS - RUDIS
 * 
 * O lexer identifica diferentes tipos de elementos na expressão:
 * - TOKEN_NUMBER: números (inteiros, decimais, hex, bin)
 * - TOKEN_IDENTIFIER: variáveis (começa com letra, pode ter letras, dígitos e _)
 * - TOKEN_OPERATOR: operadores matemáticos (+, -, *, /, %, !, ^)
 * - TOKEN_FUNCTION: funções matemáticas, estatísticas e financeiras
 * - TOKEN_LPAREN: parêntese esquerdo (
 * - TOKEN_RPAREN: parêntese direito )
 * - TOKEN_COMMA: vírgula ,
 * - TOKEN_ASSIGN: operador de atribuição = (suporta encadeamento)
 * - TOKEN_SEMICOLON: ponto e vírgula ; (fim de instrução alternativo)
 * - TOKEN_COMMENT: comentários (ignorados durante análise)
 * - TOKEN_EOF: fim da entrada
 * - TOKEN_ERROR: erro de análise léxica
 * - TOKEN_STRING: strings
 */
typedef enum {
    TOKEN_UNKNOWN = 0,  // TOKEN DESCONHECIDO
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_FUNCTION,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,    // ; (fim de instrução. Permite encadear instruções em uma linha)
    TOKEN_NEWLINE,      // '\n'(fim de linha/fim de instrução)
    TOKEN_COMMENT,     
    TOKEN_EOF,
    TOKEN_ERROR,
    TOKEN_STRING,
} RTokenType; // Rudis TokenType para não ter conflito com TokenType definido no winnt.h do Windows.

typedef struct {
    RTokenType type;
    double value;          // Para números
    char text[STR_SIZE];// Para identificadores, funções, comentários e strings
    char operator;         // Para operadores
} Token;

void lexer_init_token(Token* token); 

/*
 * ESTRUTURA DO LEXER
 * 
 * Mantém o estado do analisador léxico:
 * - input: string de entrada
 * - position: posição atual na string
 * - current_char: caractere atual sendo analisado
 */
typedef struct {
    const char* input;
    int input_size;
    int position;
    char current_char;
} Lexer;

/*
 * FUNÇÕES DO LEXER - RUDIS
 */

// Inicializa o lexer com uma string de entrada
void lexer_init(Lexer* lexer, const char* input);

// Avança para o próximo caractere
void lexer_advance(Lexer* lexer);

// Pula espaços em branco
void lexer_skip_whitespace(Lexer* lexer);

// Retorna o próximo caractere sem avançar (lookahead)
char lexer_peek_next(Lexer* lexer);

// Verifica se o próximo caractere é o esperado
int lexer_peek_is(Lexer* lexer, char expected);

// Verifica se o próximo caractere é um dos esperados (múltiplas opções)
int lexer_peek_in(Lexer* lexer, const char* options);

// Lê e ignora comentário estilo Python (#)
void lexer_skip_python_comment(Lexer* lexer);

// Lê e ignora comentário estilo C++ (//)
void lexer_skip_cpp_comment(Lexer* lexer);

// Lê e ignora comentário estilo C (/* */)
void lexer_skip_c_comment(Lexer* lexer);

// Verifica se um caractere é válido para identificadores
int is_valid_identifier_char(char c);

// Converte uma string em formato de numero em seu valor double
double lexer_str_to_double(const char* str);

// Converte uma string em formato de numero hexadecimal em seu valor double
double lexer_hex_str_to_double(const char* str);

// Converte uma string em formato de numero binário em seu valor double
double lexer_binary_str_to_double(const char* str);

// Lê um número hexadecimal
Token lexer_read_hexadecimal(Lexer* lexer);

// Lê um número binário
Token lexer_read_binary(Lexer *lexer);

// Lê um número (inteiro ou decimal)
Token lexer_read_number(Lexer* lexer);

// Lê um identificador ou função
Token lexer_read_identifier(Lexer* lexer);

// Lê uma string
Token lexer_read_string(Lexer* lexer);

// Obtém o próximo token
Token lexer_get_next_token(Lexer* lexer);

// Verifica se uma string é uma função conhecida da linguagem Rudis
int is_function(const char* text);

// Verifica se uma string é uma palavra reservada da linguagem Rudis
int is_reserved_word(const char* text);

// Cria um token de erro com mensagem
Token create_error_token(const char* message);

// Imprime um token para debug (formato legível)
void lexer_print_token(Token token);

// Imprime todos os tokens de uma string (para testes)
void lexer_print_all_tokens(const char* input);

#endif // LEXER_H