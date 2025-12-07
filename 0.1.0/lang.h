#ifndef LANG_H
#define LANG_H

//===================================================================
// SISTEMA DE IDIOMAS
//===================================================================
typedef enum {
    LANG_EN,  // Inglês
    LANG_PT   // Português
} Language;

//===================================================================
// VARIÁVEL GLOBAL PARA IDIOMA ATUAL
//===================================================================
extern Language current_lang;

//===================================================================
// FUNÇÕES PARA TEXTOS
//===================================================================
const char* get_text_banner(void);
const char* get_text_exit_instructions(void);
const char* get_text_goodbye(void);
const char* get_text_entered(const char* input);
const char* get_text_help(void);

//===================================================================
// FUNÇÃO PARA MUDAR IDIOMA
//===================================================================
void set_language(Language lang);

//===================================================================
// MENSAGENS DE ERRO DO LEXER
//===================================================================
const char* get_error_invalid_number(void);
const char* get_error_hex_invalid(void);
const char* get_error_hex_chars(void);
const char* get_error_binary_invalid(void);
const char* get_error_binary_chars(void);
const char* get_error_identifier(void);
const char* get_error_unknown_char(void);
const char* get_error_unfinished_string(void);
const char* get_error_string_too_long(void);

//===================================================================
// MENSAGENS DE ERRO DO PARSER
//===================================================================
const char* get_error_unexpected_token(void);
const char* get_error_expected_rparen(void);
const char* get_error_expected_lparen_after_func(void);
const char* get_error_expected_rparen_after_args(void) ;
const char* get_error_max_args_exceeded(void);
const char* get_error_invalid_expression(void);
const char* get_error_incomplete_expression(void);
const char* get_error_syntax(void);

// ==================================================================
// FUNÇÕES AUXILIARES PARA MENSAGENS DE ERRO DO EVALUATOR
// ==================================================================
void build_arg_error_msg(char* buffer, int size, const char* func_name, int required_args, int is_minimum);
void build_unknown_function_msg(char* buffer, int size, const char* func_name);
void build_math_error_msg(char* buffer, int size, const char* func_name);

//===================================================================
// FUNÇÕES DE TRADUÇÃO PARA main.c
//===================================================================
const char* get_text_usage(void);
const char* get_text_variables_header(void);
const char* get_text_no_variables(void);
const char* get_text_variables_count(int count);
const char* get_text_language_changed_pt(void);
const char* get_text_language_changed_en(void);
const char* get_text_syntax_error(void);
const char* get_text_reset_success(void);
#endif