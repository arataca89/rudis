#include <stdio.h>
#include <string.h>
#include "lang.h"

Language current_lang = LANG_PT;

const char* get_text_banner() {
    return (current_lang == LANG_PT) 
        ? "Rudis versão 0.0.2 (%s %s) no %s"
        : "Rudis version 0.0.2 (%s %s) on %s";
}

const char* get_text_exit_instructions() {
    return (current_lang == LANG_PT)
        ? "Digite uma expressão. Para sair digite \"exit\" ou \"quit\". Para ajuda digite \"help."
        : "Type an expression. To exit type \"exit\" or \"quit\". For help, type \"help.\"";
}

const char* get_text_goodbye() {
    return (current_lang == LANG_PT)
        ? "Até logo. Obrigado por usar Rudis. :)"
        : "Goodbye. Thank you for using Rudis. :)"; 
}

const char* get_text_entered(const char* input) {
    static char buffer[256];
    if (current_lang == LANG_PT) {
        snprintf(buffer, sizeof(buffer), "Você digitou: '%s'", input);
    } else {
        snprintf(buffer, sizeof(buffer), "You entered: '%s'", input);
    }
    return buffer;
}

const char* get_text_help() {
    return (current_lang == LANG_PT)
        ? "Comandos disponíveis:\n"
          "  exit, quit      - Sair do Rudis\n"
          "  set lang pt     - Mudar para Português\n"
          "  set lang en     - Change to English\n"
          "  help            - Mostrar esta ajuda"
        : "Available commands:\n"
          "  exit, quit      - Exit Rudis\n"
          "  set lang pt     - Mudar para Português\n"
          "  set lang en     - Change to English\n"
          "  help            - Show this help";
}

void set_language(Language lang) {
    current_lang = lang;
}

//===================================================================
// MENSAGENS DE ERRO DO LEXER
//===================================================================
const char* get_error_invalid_number() {
    return (current_lang == LANG_PT) 
        ? "Erro: número inválido"
        : "Error: invalid number";
}

const char* get_error_hex_invalid() {
    return (current_lang == LANG_PT)
        ? "Número hexadecimal inválido: 0x%s (sem dígitos após 0x)"
        : "Invalid hexadecimal number: 0x%s (no digits after 0x)";
}

const char* get_error_hex_chars() {
    return (current_lang == LANG_PT)
        ? "Número hexadecimal inválido: 0x%s (caracteres inválidos)"
        : "Invalid hexadecimal number: 0x%s (invalid characters)";
}

const char* get_error_binary_invalid() {
    return (current_lang == LANG_PT)
        ? "Número binário inválido: 0b%s (sem dígitos após 0b)"
        : "Invalid binary number: 0b%s (no digits after 0b)";
}

const char* get_error_binary_chars() {
    return (current_lang == LANG_PT)
        ? "Número binário inválido: 0b%s (apenas 0 e 1 são permitidos)"
        : "Invalid binary number: 0b%s (only 0 and 1 are allowed)";
}

const char* get_error_identifier() {
    return (current_lang == LANG_PT)
        ? "Identificador inválido: %s (deve começar com letra ou _)"
        : "Invalid identifier: %s (must start with letter or _)";
}

const char* get_error_unknown_char() {
    return (current_lang == LANG_PT)
        ? "Caractere não reconhecido: %c"
        : "Unknown character: %c";
}

const char* get_error_unfinished_string() {
    return (current_lang == LANG_PT) 
        ? "String não terminada: %s"
        : "Unfinished string: %s";
}

const char* get_error_string_too_long() {
    return (current_lang == LANG_PT) 
        ? "String muito longa (máximo %d caracteres)"
        : "String too long (maximum %d characters)";
}

// =============================================================================
// FUNÇÕES DE TRADUÇÃO PARA main.c
// =============================================================================
const char* get_text_usage() {
    return (current_lang == LANG_PT) 
        ? "Uso: rudis [--lang pt|en]\n"
          "  --lang pt    Iniciar em Português (padrão)\n"
          "  --lang en    Start in English"
        : "Usage: rudis [--lang pt|en]\n"
          "  --lang pt    Start in Portuguese (default)\n"
          "  --lang en    Start in English";
}

const char* get_text_variables_header() {
    return (current_lang == LANG_PT) 
        ? "\n=== VARIÁVEIS DEFINIDAS ==="
        : "\n=== DEFINED VARIABLES ===";
}

const char* get_text_no_variables() {
    return (current_lang == LANG_PT) 
        ? "Nenhuma variável definida."
        : "No variables defined.";
}

const char* get_text_variables_count(int count) {
    static char buffer[50];
    if (current_lang == LANG_PT) {
        snprintf(buffer, sizeof(buffer), "Total: %d variáveis)", count);
    } else {
        snprintf(buffer, sizeof(buffer), "Total: %d variables)", count);
    }
    return buffer;
}

const char* get_text_language_changed_pt() {
    return (current_lang == LANG_PT) 
        ? "Idioma alterado para Português"
        : "Language changed to Portuguese";
}

const char* get_text_language_changed_en() {
    return (current_lang == LANG_PT) 
        ? "Idioma alterado para Inglês"
        : "Language changed to English";
}

const char* get_text_syntax_error() {
    return (current_lang == LANG_PT) 
        ? "Erro de sintaxe na expressão"
        : "Syntax error in expression";
}

const char* get_text_reset_success() {
    return (current_lang == LANG_PT) 
        ? "Estado resetado. Todas as variáveis removidas."
        : "State reset. All variables removed.";
}