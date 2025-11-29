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

void print_usage() {
    printf("Uso: rudis [--lang pt|en]\n");
    printf("  --lang pt    Iniciar em Português (padrão)\n");
    printf("  --lang en    Start in English\n");
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
    
    // printf(CYAN "=== RUDIS 0.0.1 - Calculadora Avançada ===\n" RESET);
    // printf("Funções disponíveis:\n");
    // printf("  • Matemáticas: sqrt, sin, cos, log, exp, abs, ^, !\n");
    // printf("  • Estatísticas: mean, median, std, variance, mode, min, max\n");
    // printf("  • Financeiras: pv, fv, pmt, nper, npv, irr, si, ci\n");
    // printf("  • Aliases em português: raiz, sen, media, mediana, vpl, tir, etc.\n");
    // printf("  • Variáveis: x = 5, resultado = expressao\n\n");
    
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
    printf(CYAN "\n=== VARIÁVEIS DEFINIDAS ===\n" RESET);
    
    if (evaluator_state.variable_count == 0) {
        printf("Nenhuma variável definida.\n");
        return;
    }
    
    Variable* current = evaluator_state.variables;
    int count = 0;
    
    while (current != NULL) {
        printf("  %s = %g\n", current->name, current->value);
        current = current->next;
        count++;
    }
    
    printf("Total: %d variáveis)\n", count);
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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
        printf(INFO_COLOR "Idioma alterado para Português\n" RESET);
        return;
    }
    else if (strcmp(input, "set lang en") == 0) {
        set_language(LANG_EN);
        printf(INFO_COLOR "Language changed to English\n" RESET);
        return;
    }
    
    // Processa como expressão matemática
    Lexer lexer;
    lexer_init(&lexer, input);
    
    ASTNode* ast = parse(&lexer);
    
    if (ast != NULL) {
        EvaluatorResult result = evaluate(&evaluator_state, ast);
        
        if (result.success) {
            if (!result.is_assignment) {
                // Mostra resultado de expressões
                printf(SUCCESS_COLOR "%g\n" RESET, result.value);
            } else {
                // Para atribuições, mostra confirmação
                //printf(INFO_COLOR "Variável definida\n" RESET, );
            }
        } else {
            printf(ERROR_COLOR "Erro: %s\n" RESET, result.error_message);
        }
        
        free_ast(ast);
    } else {
        printf(ERROR_COLOR "Erro de sintaxe na expressão\n" RESET);
    }
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