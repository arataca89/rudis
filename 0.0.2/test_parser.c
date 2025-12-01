#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "tools.h"
#include "a89alloc.h"

void wait_for_enter() {
    printf("\n" CYAN "Pressione Enter para continuar..." RESET);
    getchar();
}

void test_parser() {
    printf("\n\n");
    printf(BOLD GREEN "=== TESTE COMPLETO DO PARSER RUDIS ===\n\n" RESET);
    
    // Array de testes - cada um testa um aspecto específico
    const char* test_cases[] = {
        // 1. EXPRESSÕES ARITMÉTICAS BÁSICAS
        "5 + 3",
        "10 - 4 * 2",
        "(5 + 3) * 2",
        "10 / 2 + 1",
        
        // 2. PRECEDÊNCIA DE OPERADORES
        "2 + 3 * 4",
        "2 * 3 + 4",
        "2 + 3 * 4 ^ 2",
        "2 ^ 3 * 4 + 1",
        
        // 3. OPERADOR POTÊNCIA
        "2 ^ 8",
        "3 ^ 2 ^ 2",        // Direita-associativo: 3^(2^2) = 81
        "(2 ^ 3) ^ 2",      // Esquerda-associativo: 8^2 = 64
        
        // 4. OPERADOR FATORIAL
        "5!",
        "3! + 2",
        "(3 + 2)!",
        
        // 5. NEGATIVO UNÁRIO
        "-5",
        "-x + 3",
        "-(2 + 3)",
        
        // 6. IDENTIFICADORES COMPLETOS
        "variavel",
        "salario_bruto",
        "_temp",
        "resultado1",
        
        // 7. ATRIBUIÇÕES
        "x = 5",
        "salario = 5000",
        "a = b = c = 10",   // Atribuições encadeadas
        
        // 8. FUNÇÕES MATEMÁTICAS
        "sqrt(25)",
        "sin(0)",
        "log(100)",
        "exp(1)",
        
        // 9. FUNÇÕES ESTATÍSTICAS ORIGINAIS
        "mean(1, 2, 3, 4, 5)",
        "min(5, 2, 8, 1)",
        "max(5, 2, 8, 1)",
        "std(10, 20, 30)",
        
        // 10. NOVAS FUNÇÕES ESTATÍSTICAS
        "variance(1, 2, 3, 4, 5)",      // Nova função
        "mode(1, 1, 2, 2, 2, 3)",       // Nova função
        "media(10, 20, 30)",            // Alias em português
        "variancia(5, 10, 15)",         // Alias em português
        
        // 11. FUNÇÕES FINANCEIRAS ORIGINAIS
        "si(1000, 0.05, 2)",
        "fv_si(1000, 0.05, 2)",
        "ci(1000, 0.05, 2)",
        "fv_ci(1000, 0.05, 2)",
        
        // 12. NOVAS FUNÇÕES FINANCEIRAS
        "npv(0.1, -1000, 300, 400, 500)",  // Nova função
        "irr(-1000, 300, 400, 500)",       // Nova função
        "vpl(0.05, -500, 200, 200)",       // Alias em português
        "tir(-800, 250, 300, 350)",        // Alias em português
        
        // 13. FUNÇÕES COM ALIAS EM PORTUGUÊS
        "raiz(16)",                     // sqrt
        "sen(3.14)",                    // sin
        "desvio(5, 10, 15)",            // std
        "mediana(1, 3, 5, 7, 9)",       // median
        
        // 14. EXPRESSÕES COMPLEXAS ORIGINAIS
        "resultado = (x + y) * sqrt(z) / 2.5",
        "total = sum(1,2,3) + max(5,8,2) * ci(1000,0.1,3)",
        "valor = pv(0.05, 10, 100) + fv_si(500, 0.02, 5)",
        
        // 15. EXPRESSÕES COMPLEXAS COM NOVAS FUNÇÕES
        "analise = variance(dados) / mean(dados)",           // Coeficiente de variação
        "retorno = npv(taxa, -investimento, fluxo1, fluxo2)",
        "decisao = irr(-500, 150, 200, 250) > 0.1",         // Análise de investimento
        "risco = std(retornos) / media(retornos)",           // Índice de risco
        
        // 16. COMBINAÇÕES AVANÇADAS
        "portfolio = vpl(0.1, -1000, 400, 500) + fv_ci(500, 0.05, 3)",
        "estatisticas_completas = [media(dados), mediana(dados), variancia(dados), moda(dados)]",
        "projecao = montante_jc(1000, tir(fluxos), periodos)",
        "comparacao = js(1000, 0.05, 5) < jc(1000, 0.05, 5)",
        
        // 17. CASOS ESPECIAIS (ERROS SINTÁTICOS)
        "2 +",                          // Expressão incompleta
        "(2 + 3",                       // Parêntese não fechado
        "sqrt 25",                      // Parêntese faltando
        "2 + * 3",                      // Operador inválido
        "1var = 5",                     // Identificador inválido
        "variance()",                   // Sem argumentos (deveria falhar)
        "npv(0.1)",                     // Poucos argumentos (deveria falhar)
    };
    
    const char* category_names[] = {
        "EXPRESSÕES ARITMÉTICAS BÁSICAS",
        "PRECEDÊNCIA DE OPERADORES", 
        "OPERADOR POTÊNCIA",
        "OPERADOR FATORIAL",
        "NEGATIVO UNÁRIO",
        "IDENTIFICADORES COMPLETOS",
        "ATRIBUIÇÕES",
        "FUNÇÕES MATEMÁTICAS",
        "FUNÇÕES ESTATÍSTICAS ORIGINAIS",
        "NOVAS FUNÇÕES ESTATÍSTICAS",
        "FUNÇÕES FINANCEIRAS ORIGINAIS",
        "NOVAS FUNÇÕES FINANCEIRAS",
        "FUNÇÕES COM ALIAS EM PORTUGUÊS",
        "EXPRESSÕES COMPLEXAS ORIGINAIS",
        "EXPRESSÕES COMPLEXAS COM NOVAS FUNÇÕES",
        "COMBINAÇÕES AVANÇADAS",
        "CASOS ESPECIAIS (ERROS)",
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int current_category = -1;
    
    for (int i = 0; i < num_tests; i++) {
        // Detecta mudança de categoria (cada 4 testes é uma categoria)
        int category = i / 4;
        if (category != current_category) {
            if (current_category != -1) {
                wait_for_enter();
            }
            current_category = category;
            printf("\n" BOLD "--- CATEGORIA: %s ---\n" RESET, category_names[category]);
        }
        
        printf(GREEN "\n--- TESTE %d: '%s' ---\n" RESET, i + 1, test_cases[i]);
        
        // Cria lexer e parser
        Lexer lexer;
        lexer_init(&lexer, test_cases[i]);
        
        printf(YELLOW "=== PARSER DEBUG ===\n" RESET);
        
        // Executa o parsing
        ASTNode* ast = parse(&lexer);
        
        if (ast != NULL) {
            printf("Parsing bem-sucedido!\n");
            printf("Árvore Sintática (AST):\n");
            print_ast(ast, 1);
            
            // Libera a AST
            free_ast(ast);
        } else {
            printf(RED "Erro no parsing\n" RESET);
        }
        
        printf(YELLOW "=== FIM DA ANÁLISE ===\n" RESET);
    }
    
    printf("\n" BOLD GREEN "=== TODOS OS TESTES CONCLUÍDOS ===\n" RESET);
}

int main() {
    test_parser();
    a89check_leaks();
    return 0;
}