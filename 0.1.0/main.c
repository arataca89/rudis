#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "color.h"
#include "lang.h"
#include "help.h"
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "a89alloc.h"
#include "functions.h"

//

void process_input(const char* input);

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

// ==================== ESTRUTURA DE ARGUMENTOS ====================

typedef struct {
    int show_help;
    int show_version;
    int interactive_mode;      // Modo REPL
    int execute_string;        // Executar string (-e)
    char* filename;           // Arquivo para executar
    char* code_string;        // Código para executar (-e)
    int has_error;
    char error_message[256];
} CommandLineArgs;

// ==================== FUNÇÕES AUXILIARES ====================

void print_usage() {
    printf("%s\n", get_text_usage());
}

void print_version() {
    printf("%sRudis v0.1.0%s\n", CYAN, RESET);
    printf("%sCompilado em: %s %s%s\n", CYAN, __DATE__, __TIME__, RESET);
    printf("%sSistema: %s%s\n", CYAN, OS, RESET);
}

void print_command_line_help() {
    printf("Rudis v0.1.0\n\n");
    
    if (current_lang == LANG_PT) {
        printf("USO:\n");
        printf("  rudis                    Inicia o ambiente interativo (REPL)\n");
        printf("  rudis <arquivo>          Executa o arquivo especificado\n");
        printf("  rudis -e \"código\"        Executa código inline\n");
        printf("  rudis -h, --help         Mostra esta ajuda\n");
        printf("  rudis -v, --version      Mostra a versão\n");
        printf("  rudis --lang pt|en       Define o idioma\n");
        printf("\nEXEMPLOS:\n");
        printf("  rudis                         # Inicia REPL\n");
        printf("  rudis calculos.rudis          # Executa arquivo\n");
        printf("  rudis -e \"print(2+2)\"        # Imprime 4\n");
        printf("  rudis -e \"x=5; print(x^2)\"   # Imprime 25\n");
        printf("  rudis --lang pt               # Português\n");
        printf("  rudis --lang en               # Inglês\n");
    } else {
        printf("USAGE:\n");
        printf("  rudis                    Starts interactive environment (REPL)\n");
        printf("  rudis <file>             Executes the specified file\n");
        printf("  rudis -e \"code\"          Executes inline code\n");
        printf("  rudis -h, --help         Shows this help\n");
        printf("  rudis -v, --version      Shows version\n");
        printf("  rudis --lang pt|en       Sets language\n");
        printf("\nEXAMPLES:\n");
        printf("  rudis                         # Starts REPL\n");
        printf("  rudis calculations.rudis      # Executes file\n");
        printf("  rudis -e \"print(2+2)\"        # Prints 4\n");
        printf("  rudis -e \"x=5; print(x^2)\"   # Prints 25\n");
        printf("  rudis --lang pt               # Portuguese\n");
        printf("  rudis --lang en               # English\n");
    }
}

CommandLineArgs parse_arguments(int argc, char *argv[]) {
    CommandLineArgs args = {0};
    args.interactive_mode = 1; // Default: REPL
    
    if (argc == 1) {
        return args; // Modo REPL
    }
    
    for (int i = 1; i < argc; i++) {
        // --help ou -h
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            args.show_help = 1;
            args.interactive_mode = 0;
        }
        // --version ou -v
        else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            args.show_version = 1;
            args.interactive_mode = 0;
        }
        // -e (execute string)
        else if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc) {
                args.code_string = argv[++i];
                args.execute_string = 1;
                args.interactive_mode = 0;
            } else {
                args.has_error = 1;
                if (current_lang == LANG_PT) {
                    snprintf(args.error_message, sizeof(args.error_message),
                             "Erro: -e requer código para executar");
                } else {
                    snprintf(args.error_message, sizeof(args.error_message),
                             "Error: -e requires code to execute");
                }
            }
        }
        // --lang (mantém compatibilidade com seu código)
        else if (strcmp(argv[i], "--lang") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "en") == 0) {
                    set_language(LANG_EN);
                    i++; // Pula o próximo argumento
                } else if (strcmp(argv[i + 1], "pt") == 0) {
                    set_language(LANG_PT);
                    i++; // Pula o próximo argumento
                }
            }
        }
        // Opção desconhecida começando com -
        else if (argv[i][0] == '-') {
            args.has_error = 1;
            if (current_lang == LANG_PT) {
                snprintf(args.error_message, sizeof(args.error_message),
                         "Erro: opção desconhecida '%s'", argv[i]);
            } else {
                snprintf(args.error_message, sizeof(args.error_message),
                         "Error: unknown option '%s'", argv[i]);
            }
        }
        else {
            // Assume que é nome de arquivo (CASO MAIS COMUM!)
            args.filename = argv[i];
            args.interactive_mode = 0;
        }
    }
    
    return args;
}

// ==================== EXECUÇÃO DE ARQUIVO ====================

int execute_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        if (current_lang == LANG_PT) {
            fprintf(stderr, ERROR_COLOR "Erro: Não foi possível abrir arquivo '%s'\n" RESET, filename);
        } else {
            fprintf(stderr, ERROR_COLOR "Error: Could not open file '%s'\n" RESET, filename);
        }
        return 1;
    }
    
    char line[STR_SIZE];
    int line_number = 0;
    int has_errors = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        
        // Remove newline no final
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        
        // Ignora linhas vazias
        if (strlen(line) == 0) {
            continue;
        }
        
        // Ignora comentários
        if (line[0] == '#' || (line[0] == '/' && line[1] == '/')) {
            continue;
        }
        
        // Processa a linha (usa a mesma função do REPL)
        process_input(line);
        
        // Verifica se houve erro no evaluator_state
        // (você precisaria adicionar uma flag de erro no EvaluatorState)
    }
    
    fclose(file);
    return has_errors ? 1 : 0;
}

// ==================== EXECUÇÃO DE STRING (-e) ====================

void execute_string(const char* code) {
    // Simplesmente passa para o process_input
    process_input(code);
}

// ==================== FUNÇÕES EXISTENTES (mantidas) ====================

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
        printf("  %s = ", current->name);
        print_value(current->value, evaluator_state.decimal_places);
        printf("\n");
        current = current->next;
        count++;
    }
    
    printf("Total: %d variáveis\n", count);
}

void process_input(const char* input) {
    // Ignora entradas vazias
    if (strlen(input) == 0) {
        return;
    }
    
    // Comandos especiais
    if (strncmp(input, "help", 4) == 0) {
        const char* argument = input + 4;
        while (*argument == ' ') argument++;
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
    else if (strcmp(input, "reset") == 0) {
        evaluator_free(&evaluator_state);
        evaluator_init(&evaluator_state);
        printf(INFO_COLOR "%s\n" RESET, get_text_reset_success());
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
    else if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
        printf(INFO_COLOR "%s\n" RESET, get_text_goodbye());
        exit(0);
    }

    // Processa entrada normal
    Lexer lexer;
    lexer_init(&lexer, input);
    
    ASTNode* ast = parse(&lexer);
    
    if (ast != NULL) {
        EvaluatorResult result = evaluate(&evaluator_state, ast);
        
        if (result.success) {
            if (!result.is_assignment && result.value.type != VAL_NULL) {
                print_value(result.value, evaluator_state.decimal_places); 
                printf("\n");
            }
        } else {
            printf(ERROR_COLOR "%s: %s\n" RESET, 
                   (current_lang == LANG_PT ? "Erro" : "Error"), 
                   result.error_message);
        }
        
        free_ast(ast);
    }
}

// ==================== FUNÇÃO REPL ====================

void run_repl() {
    char input[STR_SIZE];
    
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
        
        // Processa o input
        process_input(input);
    }
}

// ==================== MAIN ATUALIZADA ====================

int main(int argc, char *argv[]) {
    // Configura UTF-8 para suporte a acentuação
    setup_utf8();
    
    // Parse dos argumentos
    CommandLineArgs args = parse_arguments(argc, argv);
    
    // Trata erros de parsing
    if (args.has_error) {
        fprintf(stderr, ERROR_COLOR "%s\n" RESET, args.error_message);
        fprintf(stderr, INFO_COLOR "Use 'rudis -h' para ajuda\n" RESET);
        return 1;
    }
    
    // Mostra ajuda
    if (args.show_help) {
        print_command_line_help();
        return 0;
    }
    
    // Mostra versão
    if (args.show_version) {
        print_version();
        return 0;
    }
    
    // Inicializa o evaluator
    evaluator_init(&evaluator_state);
    
    // Executa string (-e)
    if (args.execute_string) {
        execute_string(args.code_string);
        evaluator_free(&evaluator_state);
        //a89check_leaks();
        return 0;
    }
    
    // Executa arquivo
    if (args.filename) {
        int result = execute_file(args.filename);
        evaluator_free(&evaluator_state);
        //a89check_leaks();
        return result;
    }
    
    // Modo REPL (default)
    run_repl();
    
    // Limpeza final
    evaluator_free(&evaluator_state);
    //a89check_leaks();   
    return 0;
}