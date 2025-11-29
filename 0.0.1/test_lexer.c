#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "tools.h"

void wait_for_enter() {
    printf("\n" CYAN "Pressione Enter para continuar..." RESET);
    getchar(); // Espera o usuário pressionar Enter
}

void test_lexer() {
    printf("\n\n"); // Espaço antes do título#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "tools.h"

void wait_for_enter() {
    printf("\n" CYAN "Pressione Enter para continuar..." RESET);
    getchar(); // Espera o usuário pressionar Enter
}

void test_lexer() {
    printf("\n\n"); // Espaço antes do título
    printf(BOLD GREEN "=== TESTE COMPLETO DO LEXER RUDIS ===\n\n" RESET);
    
    // Array de testes - cada um testa um aspecto específico
    const char* test_cases[] = {
        // 1. NÚMEROS
        "123",                          // Inteiro decimal
        "45.67",                        // Decimal com ponto
        "0xFF",                         // Hexadecimal
        "0b1101",                       // Binário
        
        // 2. IDENTIFICADORES
        "x",                            // Identificador simples
        "variavel",                     // Identificador múltiplo
        "_temp",                        // Identificador com underscore
        "resultado1",                   // Identificador com números
        
        // 3. OPERADORES
        "+ - * / % ! ^",                // Todos os operadores
        
        // 4. ATRIBUIÇÕES
        "x = 5",                        // Atribuição simples
        "a = b = c = 10",               // Atribuições encadeadas
        
        // 5. FUNÇÕES (ORIGINAIS)
        "sqrt(25)",                     // Função matemática
        "mean(1,2,3)",                  // Função estatística
        "si(1000,0.05,2)",              // Função financeira
        
        // 6. NOVAS FUNÇÕES ESTATÍSTICAS
        "variance(1,2,3,4,5)",          // Nova função variância
        "mode(1,1,2,2,2,3)",            // Nova função moda
        "media(10,20,30)",              // Alias em português
        "variancia(5,5,10,10)",         // Alias em português
        
        // 7. NOVAS FUNÇÕES FINANCEIRAS
        "npv(0.1, -1000, 300, 400)",    // Valor Presente Líquido
        "irr(-1000, 300, 400, 500)",    // Taxa Interna de Retorno
        "vpl(0.05, -500, 200, 200)",    // Alias em português (VPL)
        "tir(-800, 250, 300, 350)",     // Alias em português (TIR)
        
        // 8. FUNÇÕES COM ALIAS EM PORTUGUÊS
        "raiz(16)",                     // Alias para sqrt
        "sen(3.14)",                    // Alias para sin
        "desvio(5,10,15)",              // Alias para std
        "mediana(1,3,5,7,9)",           // Alias para median
        
        // 9. COMENTÁRIOS
        "x = 5 # comentário python",    // Comentário Python
        "y = 10 // comentário c++",     // Comentário C++
        "z = 15 /* comentário c */",    // Comentário C multi-linha
        
        // 10. PONTO E VÍRGULA
        "a = 1; b = 2; c = a + b",     // Múltiplas instruções
        
        // 11. EXPRESSÕES COMPLEXAS COM NOVAS FUNÇÕES
        "resultado = variance(x,y,z) + npv(taxa, fluxos)",
        "analise = media(vendas) * (1 + tir(investimento))",
        "risco = desvio(retornos) / media(retornos)",
        
        // 12. MISTURA COMPLETA DE TODAS AS FUNÇÕES
        "portfolio = sum(vpl(0.1, -1000, 400, 500), fv_ci(500, 0.05, 3))",
        "estatisticas = [media(dados), mediana(dados), variancia(dados), moda(dados)]",
        "financas = vp(taxa, periodos, pagamento) + vf(taxa, periodos, pagamento)",
        
        // 13. JUROS EM PORTUGUÊS
        "juros_simples = js(1000, 0.05, 2)",           // Juros simples
        "montante_composto = montante_jc(1000, 0.08, 5)", // Montante juros compostos
        
        // 14. CASOS ESPECIAIS
        "0xG",                          // Hexadecimal inválido
        "0b102",                        // Binário inválido
        "1var",                         // Identificador inválido
        "var@vel",                      // Caractere inválido
    };
    
    const char* category_names[] = {
        "NÚMEROS",
        "IDENTIFICADORES", 
        "OPERADORES",
        "ATRIBUIÇÕES",
        "FUNÇÕES (ORIGINAIS)",
        "NOVAS FUNÇÕES ESTATÍSTICAS",
        "NOVAS FUNÇÕES FINANCEIRAS", 
        "FUNÇÕES COM ALIAS EM PORTUGUÊS",
        "COMENTÁRIOS",
        "PONTO E VÍRGULA",
        "EXPRESSÕES COMPLEXAS COM NOVAS FUNÇÕES",
        "MISTURA COMPLETA DE TODAS AS FUNÇÕES",
        "JUROS EM PORTUGUÊS",
        "CASOS ESPECIAIS (ERROS)",
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int current_category = -1;
    
    for (int i = 0; i < num_tests; i++) {
        // Detecta mudança de categoria
        int category = i / 3; // Agora 3 testes por categoria
        if (category != current_category) {
            if (current_category != -1) {
                wait_for_enter(); // Pausa entre categorias
            }
            current_category = category;
            printf("\n" BOLD "--- CATEGORIA: %s ---\n" RESET, category_names[category]);
        }
        
        printf(GREEN "\n--- TESTE %d: '%s' ---\n" RESET, i + 1, test_cases[i]);
        
        // Chama a função de debug do lexer (sem cores internas)
        Lexer lexer;
        Token token;
        
        printf(YELLOW "=== LEXER DEBUG ===\n" RESET);
        printf("Entrada: '%s'\n", test_cases[i]);
        printf("Tokens:\n");
        
        lexer_init(&lexer, test_cases[i]);
        
        int token_count = 0;
        do {
            token = lexer_get_next_token(&lexer);
            printf("  %2d: ", ++token_count);
            
            // Versão simples do print_token sem cores
            const char* type_names[] = {
                "NÚMERO", "IDENTIFICADOR", "OPERADOR", "FUNÇÃO", 
                "ABRE_PAR", "FECHA_PAR", "VÍRGULA", "ATRIBUIÇÃO", 
                "PONTO_VÍRGULA", "COMENTÁRIO", "FIM", "ERRO"
            };
            
            printf("[%s] ", type_names[token.type]);
            
            switch (token.type) {
                case TOKEN_NUMBER:
                    printf("valor: %g", token.value);
                    if (strlen(token.text) > 0) printf(" (texto: %s)", token.text);
                    break;
                case TOKEN_IDENTIFIER:
                    printf("texto: '%s'", token.text);
                    break;
                case TOKEN_FUNCTION:
                    printf("função: '%s'", token.text);
                    break;
                case TOKEN_OPERATOR:
                    printf("operador: '%c'", token.operator);
                    break;
                case TOKEN_ERROR:
                    printf(RED "erro: '%s'" RESET, token.text);
                    break;
                case TOKEN_LPAREN: printf("("); break;
                case TOKEN_RPAREN: printf(")"); break;
                case TOKEN_COMMA: printf(","); break;
                case TOKEN_ASSIGN: printf("="); break;
                case TOKEN_SEMICOLON: printf(";"); break;
                case TOKEN_COMMENT: printf("comentário: '%s'", token.text); break;
                case TOKEN_EOF: printf("FIM DO ARQUIVO"); break;
            }
            printf("\n");
            
            if (token.type == TOKEN_ERROR) {
                printf(RED "ERRO ENCONTRADO - parando análise\n" RESET);
                break;
            }
            
        } while (token.type != TOKEN_EOF);
        
        printf(YELLOW "=== FIM DA ANÁLISE ===\n" RESET);
    }
    
    printf("\n" BOLD GREEN "=== TODOS OS TESTES CONCLUÍDOS ===\n" RESET);
}

int main() {
    test_lexer();
    return 0;
}    printf(BOLD GREEN "=== TESTE COMPLETO DO LEXER RUDIS ===\n\n" RESET);
    
    // Array de testes - cada um testa um aspecto específico
    const char* test_cases[] = {
        // 1. NÚMEROS
        "123",                          // Inteiro decimal
        "45.67",                        // Decimal com ponto
        "0xFF",                         // Hexadecimal
        "0b1101",                       // Binário
        
        // 2. IDENTIFICADORES
        "x",                            // Identificador simples
        "variavel",                     // Identificador múltiplo
        "_temp",                        // Identificador com underscore
        "resultado1",                   // Identificador com números
        
        // 3. OPERADORES
        "+ - * / % ! ^",                // Todos os operadores
        
        // 4. ATRIBUIÇÕES
        "x = 5",                        // Atribuição simples
        "a = b = c = 10",               // Atribuições encadeadas
        
        // 5. FUNÇÕES
        "sqrt(25)",                     // Função matemática
        "mean(1,2,3)",                  // Função estatística
        "si(1000,0.05,2)",              // Função financeira
        
        // 6. COMENTÁRIOS
        "x = 5 # comentário python",    // Comentário Python
        "y = 10 // comentário c++",     // Comentário C++
        "z = 15 /* comentário c */",    // Comentário C multi-linha
        
        // 7. PONTO E VÍRGULA
        "a = 1; b = 2; c = a + b",     // Múltiplas instruções
        
        // 8. EXPRESSÕES COMPLEXAS
        "resultado = (x + y) * sqrt(z) / 2.5",
        "valor = pv(0.05, 10, 100) + fv_si(500, 0.02, 5)",
        
        // 9. MISTURA COMPLETA
        "total = sum(1,2,3) + max(5,8,2) * ci(1000,0.1,3)",
        
        // 10. CASOS ESPECIAIS
        "0xG",                          // Hexadecimal inválido
        "0b102",                        // Binário inválido
        "1var",                         // Identificador inválido
        "var@vel",                      // Caractere inválido
    };
    
    const char* category_names[] = {
        "NÚMEROS",
        "IDENTIFICADORES", 
        "OPERADORES",
        "ATRIBUIÇÕES",
        "FUNÇÕES",
        "COMENTÁRIOS", 
        "PONTO E VÍRGULA",
        "EXPRESSÕES COMPLEXAS",
        "MISTURA COMPLETA",
        "CASOS ESPECIAIS (ERROS)",
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int current_category = -1;
    
    for (int i = 0; i < num_tests; i++) {
        // Detecta mudança de categoria (cada 4 testes é uma categoria)
        int category = i / 4;
        if (category != current_category) {
            if (current_category != -1) {
                wait_for_enter(); // Pausa entre categorias
            }
            current_category = category;
            printf("\n" BOLD "--- CATEGORIA: %s ---\n" RESET, category_names[category]);
        }
        
        printf(GREEN "\n--- TESTE %d: '%s' ---\n" RESET, i + 1, test_cases[i]);
        
        // Chama a função de debug do lexer (sem cores internas)
        Lexer lexer;
        Token token;
        
        printf(YELLOW "=== LEXER DEBUG ===\n" RESET);
        printf("Entrada: '%s'\n", test_cases[i]);
        printf("Tokens:\n");
        
        lexer_init(&lexer, test_cases[i]);
        
        int token_count = 0;
        do {
            token = lexer_get_next_token(&lexer);
            printf("  %2d: ", ++token_count);
            
            // Versão simples do print_token sem cores
            const char* type_names[] = {
                "NÚMERO", "IDENTIFICADOR", "OPERADOR", "FUNÇÃO", 
                "ABRE_PAR", "FECHA_PAR", "VÍRGULA", "ATRIBUIÇÃO", 
                "PONTO_VÍRGULA", "COMENTÁRIO", "FIM", "ERRO"
            };
            
            printf("[%s] ", type_names[token.type]);
            
            switch (token.type) {
                case TOKEN_NUMBER:
                    printf("valor: %g", token.value);
                    if (strlen(token.text) > 0) printf(" (texto: %s)", token.text);
                    break;
                case TOKEN_IDENTIFIER:
                    printf("texto: '%s'", token.text);
                    break;
                case TOKEN_FUNCTION:
                    printf("função: '%s'", token.text);
                    break;
                case TOKEN_OPERATOR:
                    printf("operador: '%c'", token.operator);
                    break;
                case TOKEN_ERROR:
                    printf(RED "erro: '%s'" RESET, token.text);
                    break;
                case TOKEN_LPAREN: printf("("); break;
                case TOKEN_RPAREN: printf(")"); break;
                case TOKEN_COMMA: printf(","); break;
                case TOKEN_ASSIGN: printf("="); break;
                case TOKEN_SEMICOLON: printf(";"); break;
                case TOKEN_COMMENT: printf("comentário: '%s'", token.text); break;
                case TOKEN_EOF: printf("FIM DO ARQUIVO"); break;
            }
            printf("\n");
            
            if (token.type == TOKEN_ERROR) {
                printf(RED "ERRO ENCONTRADO - parando análise\n" RESET);
                break;
            }
            
        } while (token.type != TOKEN_EOF);
        
        printf(YELLOW "=== FIM DA ANÁLISE ===\n" RESET);
    }
    
    printf("\n" BOLD GREEN "=== TODOS OS TESTES CONCLUÍDOS ===\n" RESET);
}

int main() {
    test_lexer();
    return 0;
}