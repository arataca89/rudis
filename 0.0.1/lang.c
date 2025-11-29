#include "lang.h"
#include <stdio.h>
#include <string.h>

Language current_lang = LANG_PT;

const char* get_text_banner() {
    return (current_lang == LANG_PT) 
        ? "Rudis versão 0.0.1 (%s %s) no %s"
        : "Rudis version 0.0.1 (%s %s) on %s";
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