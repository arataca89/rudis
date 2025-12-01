#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tools.h"
#include "lang.h"
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "a89alloc.h"
#include "help.h"

// Configuração UTF-8 para Windows
#ifdef _WIN32
#include <windows.h>
void setup_utf8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}
#else
void setup_utf8() {
    // No Linux/macOS, UTF-8 já é o padrão
}
#endif

// Estado global do evaluator
EvaluatorState evaluator_state;

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

// =============================================================================
// FUNÇÕES PRINCIPAIS
// =============================================================================

void print_usage() {
    printf("%s\n", get_text_usage());
}

void parse_arguments(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--lang") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "en") == 0) {
                    set_language(LANG_EN);
                    i++; // Pula o próximo argumento
                } else if (strcmp(argv[i + 1], "pt") == 0) {
                    set_language(LANG_PT);
                    i++; // Pula o próximo argumento
                }
            }
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage();
            exit(0);
        }
    }
}

void print_banner() {
    printf(INFO_COLOR);
    printf(get_text_banner(), __DATE__, __TIME__, OS);
    printf(RESET "\n");   
    printf("%s\n", get_text_exit_instructions());
}

void handle_help_command(const char* argument) {
    if (argument == NULL || strlen(argument) == 0) {
        print_general_help();
        return;
    }
    
    // Verifica se é um número (página)
    if (argument[0] >= '0' && argument[0] <= '9') {
        int page = atoi(argument);
        print_help_page(page);
    } else {
        // É nome de função
        print_function_help(argument);
    }
}

void list_variables() {
    printf(CYAN "%s\n" RESET, get_text_variables_header());
    
    if (evaluator_state.variable_count == 0) {
        printf("%s\n", get_text_no_variables());
        return;
    }
    
    Variable* current = evaluator_state.variables;
    int count = 0;
    
    while (current != NULL) {
        printf("  %s = %g\n", current->name, current->value);
        current = current->next;
        count++;
    }
    
    printf("%s\n", get_text_variables_count(count));
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void process_single_instruction(const char* instruction) {
    // Processa uma única instrução
    Lexer lexer;
    lexer_init(&lexer, instruction);
    
    ASTNode* ast = parse(&lexer);
    
    if (ast != NULL) {
        EvaluatorResult result = evaluate(&evaluator_state, ast);
        
        if (result.success) {
            if (!result.is_assignment) {
                // Mostra resultado de expressões
                //printf(SUCCESS_COLOR "%g\n" RESET, result.value);
                printf(SUCCESS_COLOR "%.*f\n" RESET, 
               evaluator_state.decimal_places, result.value);
            }
            // Para atribuições, não mostra nada (comportamento atual)
        } else {
            if (current_lang == LANG_PT){
                printf(ERROR_COLOR "Erro: %s\n" RESET, result.error_message);
            } else {
                printf(ERROR_COLOR "Error: %s\n" RESET, result.error_message);
            }
        }
        
        free_ast(ast);
    } else {
        printf(ERROR_COLOR "%s\n" RESET, get_text_syntax_error());
    }
}

void process_input(const char* input) {
    // Ignora entradas vazias
    if (strlen(input) == 0) {
        return;
    }
    
    // Comandos especiais
    else if (strncmp(input, "help", 4) == 0) {
        // Extrai o argumento depois de "help"
        const char* argument = input + 4;
        while (*argument == ' ') argument++; // Pula espaços
        
        handle_help_command(argument);
        return;
    }
    else if (strcmp(input, "clear") == 0) {
        clear_screen();
        return;
    }
    else if (strcmp(input, "vars") == 0) {
        list_variables();
        return;
    }
    else if (strcmp(input, "set lang pt") == 0) {
        set_language(LANG_PT);
        printf(INFO_COLOR "%s\n" RESET, get_text_language_changed_pt());
        return;
    }
    else if (strcmp(input, "set lang en") == 0) {
        set_language(LANG_EN);
        printf(INFO_COLOR "%s\n" RESET, get_text_language_changed_en());
        return;
    }

    // Dividir input por ';' para múltiplas instruções
    char* input_copy = strdup(input);
    char* instruction = strtok(input_copy, ";");
    
    while (instruction != NULL) {
        // Pula instruções vazias, evita ";;"
        if (strlen(instruction) > 0) {
            process_single_instruction(instruction);
        }
        instruction = strtok(NULL, ";");
    }
        
    free(input_copy); 
}

int main(int argc, char *argv[]) {
    char input[512];
    
    // Configura UTF-8 para suporte a acentuação
    setup_utf8();
    
    // Parse dos argumentos de linha de comando
    parse_arguments(argc, argv);
    
    // Inicializa o evaluator
    evaluator_init(&evaluator_state);
    
    print_banner();
    
    // Loop principal do REPL
    while (1) {
        printf(PROMPT_COLOR "rudis> " RESET);
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Comandos de saída
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            printf(SUCCESS_COLOR "%s\n" RESET, get_text_goodbye());
            break;
        }
        
        // Processa o input
        process_input(input);
    }
    
    // Limpeza final
    evaluator_free(&evaluator_state);
    //a89check_leaks();
    
    return 0;
}