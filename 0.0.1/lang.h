#ifndef LANG_H
#define LANG_H

// Sistema de idiomas
typedef enum {
    LANG_EN,  // Inglês
    LANG_PT   // Português
} Language;

// Variável global para idioma atual
extern Language current_lang;

// Funções para textos
const char* get_text_banner();
const char* get_text_exit_instructions();
const char* get_text_goodbye();
const char* get_text_entered(const char* input);
const char* get_text_help();

// Função para mudar idioma
void set_language(Language lang);

#endif