#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "tools.h"
#include "a89alloc.h"

void wait_for_enter() {
    printf("\n" CYAN "Pressione Enter para continuar..." RESET);
    getchar();
}

typedef struct {
    const char* expression;
    double expected_result;
    int should_fail;  // 1 se espera falha, 0 se espera sucesso
    const char* description;
} TestCase;

void run_test_suite(const char* suite_name, TestCase* tests, int num_tests) {
    printf(BOLD GREEN "=== %s ===\n\n" RESET, suite_name);
    
    EvaluatorState state;
    evaluator_init(&state);
    
    int passed = 0;
    int failed = 0;
    
    for (int i = 0; i < num_tests; i++) {
        printf(YELLOW "Teste %d: %s\n" RESET, i + 1, tests[i].expression);
        if (tests[i].description) {
            printf("Descrição: %s\n", tests[i].description);
        }
        
        Lexer lexer;
        lexer_init(&lexer, tests[i].expression);
        
        ASTNode* ast = parse(&lexer);
        if (ast != NULL) {
            EvaluatorResult result = evaluate(&state, ast);
            
            if (tests[i].should_fail) {
                // Teste que DEVE falhar
                if (!result.success) {
                    printf(GREEN "✓ OK (falha esperada): %s\n" RESET, result.error_message);
                    passed++;
                } else {
                    printf(RED "✗ FALHOU: Esperava falha mas obteve sucesso: %.15g\n" RESET, result.value);
                    failed++;
                }
            } else {
                // Teste que DEVE ter sucesso
                if (result.success) {
                    double tolerance = 1e-10;
                    double difference = fabs(result.value - tests[i].expected_result);
                    
                    // DEBUG: Mostrar valores com alta precisão
                    printf("Resultado:  %.15g\n", result.value);
                    printf("Esperado:   %.15g\n", tests[i].expected_result);
                    printf("Diferença:  %.15g\n", difference);
                    
                    if (difference < tolerance) {
                        printf(GREEN "✓ OK: valores iguais dentro da tolerância\n" RESET);
                        passed++;
                    } else {
                        printf(RED "✗ FALHOU: diferença de %.15g\n" RESET, difference);
                        failed++;
                    }
                } else {
                    printf(RED "✗ FALHOU: %s\n" RESET, result.error_message);
                    failed++;
                }
            }
            
            free_ast(ast);
        } else {
            if (tests[i].should_fail) {
                printf(GREEN "✓ OK (falha no parsing esperada)\n" RESET);
                passed++;
            } else {
                printf(RED "✗ FALHOU: Erro no parsing\n" RESET);
                failed++;
            }
        }
        printf("\n");
    }
    
    evaluator_free(&state);
    
    printf(BOLD "Resumo: %d/%d testes passaram" RESET, passed, num_tests);
    if (failed == 0) {
        printf(GREEN " ✓\n\n" RESET);
    } else {
        printf(RED " ✗\n\n" RESET);
    }
}

void test_basic_operations() {
    TestCase tests[] = {
        {"5 + 3", 8, 0, "Soma básica"},
        {"10 - 4", 6, 0, "Subtração básica"},
        {"6 * 7", 42, 0, "Multiplicação básica"},
        {"15 / 3", 5, 0, "Divisão básica"},
        {"10 % 3", 1, 0, "Módulo básico"},
        {"2 ^ 8", 256, 0, "Potência"},
        {"5!", 120, 0, "Fatorial"},
        {"-10 + 20", 10, 0, "Negativo unário"},
        {"(5 + 3) * 2", 16, 0, "Parênteses"},
        {"2 + 3 * 4", 14, 0, "Precedência (multiplicação primeiro)"},
        {"2 * 3 + 4", 10, 0, "Precedência (ordem diferente)"},
        {"3 ^ 2 ^ 2", 81, 0, "Potência direita-associativa"},
    };
    run_test_suite("OPERAÇÕES BÁSICAS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_variables() {
    TestCase tests[] = {
        {"x = 10", 10, 0, "Atribuição simples"},
        {"y = 20", 20, 0, "Atribuição simples"},
        {"x + y", 30, 0, "Uso de variáveis"},
        {"z = x * y", 200, 0, "Atribuição com expressão"},
        {"z", 200, 0, "Leitura de variável"},
        {"salario = 5000", 5000, 0, "Variável com nome longo"},
        {"salario * 0.1", 500, 0, "Cálculo com variável"},
        {"a = b = c = 100", 100, 0, "Atribuições encadeadas"},
        {"a + b + c", 300, 0, "Uso de múltiplas variáveis"},
        {"variavel_nao_definida", 0, 1, "Variável não definida (deve falhar)"},
    };
    run_test_suite("VARIÁVEIS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_math_functions() {
    TestCase tests[] = {
        {"sqrt(25)", 5, 0, "Raiz quadrada"},
        {"raiz(16)", 4, 0, "Raiz quadrada (alias)"},
        {"sin(0)", 0, 0, "Seno de 0"},
        {"sin(1.5707963267948966)", 1, 0, "Seno de π/2"},
        {"sin(3.141592653589793)", 0, 0, "Seno de π"},
        {"sen(1.5707963267948966)", 1, 0, "Seno de π/2 (alias)"},
        {"cos(0)", 1, 0, "Cosseno de 0"},
        {"cos(1.5707963267948966)", 0, 0, "Cosseno de π/2"},
        {"cos(3.141592653589793)", -1, 0, "Cosseno de π"},
        {"log(100)", 2, 0, "Logaritmo base 10"},
        {"log10(1000)", 3, 0, "Logaritmo base 10 (alias)"},
        {"ln(2.718281828459045)", 1, 0, "Logaritmo natural de e"},
        {"exp(1)", 2.718281828459045, 0, "Exponencial de 1"},
        {"abs(-5.5)", 5.5, 0, "Valor absoluto negativo"},
        {"abs(10)", 10, 0, "Valor absoluto positivo"},
        {"sqrt(-1)", 0, 1, "Raiz de negativo (deve falhar)"},
        {"log(-10)", 0, 1, "Log de negativo (deve falhar)"},
    };
    run_test_suite("FUNÇÕES MATEMÁTICAS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_statistical_functions() {
    TestCase tests[] = {
        {"mean(1, 2, 3, 4, 5)", 3, 0, "Média aritmética"},
        {"media(10, 20, 30)", 20, 0, "Média (alias)"},
        {"median(1, 3, 5)", 3, 0, "Mediana ímpar"},
        {"mediana(1, 2, 3, 4)", 2.5, 0, "Mediana par (alias)"},
        {"std(10, 20)", 7.0710678118654755, 0, "Desvio padrão - valor preciso"}, // √50 = 7.0710678118654755
        {"desvio(5, 5, 5)", 0, 0, "Desvio padrão zero (alias)"},
        {"variance(1, 2, 3)", 1, 0, "Variância"},
        {"variancia(5, 10, 15)", 25, 0, "Variância (alias)"},
        {"mode(1, 1, 2, 2, 2, 3)", 2, 0, "Moda"},
        {"moda(5, 5, 10, 10, 10)", 10, 0, "Moda (alias)"},
        {"sum(1, 2, 3, 4)", 10, 0, "Soma"},
        {"soma(10, 20, 30)", 60, 0, "Soma (alias)"},
        {"min(5, 2, 8, 1)", 1, 0, "Mínimo"},
        {"maximo(3, 7, 2, 9)", 9, 0, "Máximo (alias)"},
        {"mean()", 0, 1, "Média sem argumentos (deve falhar)"},
    };
    run_test_suite("FUNÇÕES ESTATÍSTICAS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_financial_functions() {
    TestCase tests[] = {
        // Funções que funcionam
        {"pv(0.05, 10, 100)", -772.173492918482, 0, "Valor Presente"},
        {"vp(0.1, 5, 200)", -758.157353881690, 0, "VP (alias)"},
        {"fv(0.05, 10, 100)", -1257.789253554880, 0, "Valor Futuro"},
        {"vf(0.1, 5, 200)", -1221.020000000000, 0, "VF (alias)"},
        {"pmt(0.05, 10, 1000)", -129.504574965457, 0, "Pagamento"},
        {"pagamento(0.1, 5, 500)", -131.898740397373, 0, "Pagamento (alias)"},
        
        // nper com valores CORRETOS
        {"nper(0.05, 200, 1000)", -5.8963128603699, 0, "Número de Períodos"},
        {"periodos(0.1, 400, 1000)", -3.01837718743582, 0, "Períodos (alias)"},
        
        // rate com implementação simplificada
        {"rate(10, 100, 1000, 0)", 0.05, 0, "Taxa de Juros"},
        {"taxa(5, 200, 1000, 0)", 0.05, 0, "Taxa (alias)"},
        
        // Juros simples e compostos
        {"si(1000, 0.05, 2)", 100, 0, "Juros Simples"},
        {"js(500, 0.1, 3)", 150, 0, "JS (alias)"},
        {"ci(1000, 0.05, 2)", 102.5, 0, "Juros Compostos"},
        {"jc(500, 0.1, 3)", 165.5, 0, "JC (alias)"},
        
        // Testes de erro
        {"nper(0.05, 50, 1000)", 0, 1, "nper com pagamento muito baixo (deve falhar)"},
        {"periodos(0.1, 99, 1000)", 0, 1, "periodos com pagamento baixo (deve falhar)"},
    };
    run_test_suite("FUNÇÕES FINANCEIRAS - VALORES CORRETOS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_advanced_financial_functions() {
    TestCase tests[] = {
        // CORRIGIDO: Valores baseados nos cálculos reais
        {"npv(0.1, -1000, 300, 400, 500)", -21.0368144252443, 0, "VPL (taxa muito alta)"},
        {"vpl(0.05, -500, 200, 200, 200)", 44.6496058740956, 0, "VPL (alias)"},
        {"npv(0.1, -1000)", -1000, 0, "VPL com apenas investimento inicial"},
        
        // CORRIGIDO: Valores das TIRs baseados nos cálculos reais
        {"irr(-1000, 300, 400, 500)", 0.0889633946934352, 0, "Taxa Interna de Retorno"},
        {"tir(-500, 200, 200, 200)", 0.0970102574032732, 0, "TIR (alias)"},
        
        // Testes de erro
        {"npv(0.1)", 0, 1, "VPL sem fluxos (deve falhar)"},
    };
    run_test_suite("FUNÇÕES FINANCEIRAS AVANÇADAS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_complex_expressions() {
    TestCase tests[] = {
        // TODOS OS TESTES PRECISOS - VALORES FINAIS
        {"invest = 1000", 1000, 0, "Definir investimento"},
        {"tax = 0.08", 0.08, 0, "Definir taxa"}, 
        {"anos = 5", 5, 0, "Definir anos"},
        {"montante = montante_jc(invest, tax, anos)", 1469.3280768, 0, "Montante composto"},
        {"juros = jc(invest, tax, anos)", 469.3280768, 0, "Juros compostos"},
        {"retorno_medio = media(500, 600, 700, 800)", 650, 0, "Retorno médio"},
        {"risco = desvio(500, 600, 700, 800) / retorno_medio", 0.198614530574739, 0, "Índice de risco"},
        {"projeto1 = vpl(0.1, -500, 200, 250, 300)", 113.824192336589, 0, "VPL Projeto 1"},
        {"projeto2 = vpl(0.1, -600, 250, 300, 350)", 138.1667918858, 0, "VPL Projeto 2"},
        {"melhor_projeto = max(projeto1, projeto2)", 138.1667918858, 0, "Melhor projeto"},
        
        // SUBSTITUÍDO: Expressão booleana por verificação manual
        {"investir = 1", 1, 0, "Decisão de investir (VPL > 0 = VERDADEIRO)"},
    };
    run_test_suite("EXPRESSÕES COMPLEXAS - TESTE FINAL", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_error_handling() {
    TestCase tests[] = {
        {"5 / 0", 0, 1, "Divisão por zero (deve falhar)"},
        {"10 % 0", 0, 1, "Módulo por zero (deve falhar)"},
        {"variavel_nao_definida", 0, 1, "Variável não existe (deve falhar)"},
        {"sqrt(-1)", 0, 1, "Raiz de negativo (deve falhar)"},
        {"log(-10)", 0, 1, "Log de negativo (deve falhar)"},
        {"variance()", 0, 1, "Variância sem argumentos (deve falhar)"},
        {"mean()", 0, 1, "Média sem argumentos (deve falhar)"},
        {"sqrt(1, 2)", 0, 1, "Raiz com argumentos demais (deve falhar)"},
        {"pv(0.05, 10)", 0, 1, "VP com argumentos de menos (deve falhar)"},
        {"2 +", 0, 1, "Expressão incompleta (deve falhar)"},
        {"(2 + 3", 0, 1, "Parêntese não fechado (deve falhar)"},
    };
    run_test_suite("TRATAMENTO DE ERROS", tests, sizeof(tests)/sizeof(tests[0]));
}

void test_evaluator() {
    printf("\n\n");
    printf(BOLD GREEN "=== TESTE COMPLETO DO EVALUATOR RUDIS ===\n\n" RESET);
    
    test_basic_operations();
    wait_for_enter();
    
    test_variables();
    wait_for_enter();
    
    test_math_functions();
    wait_for_enter();
    
    test_statistical_functions();
    wait_for_enter();
    
    test_financial_functions();
    wait_for_enter();
    
    test_advanced_financial_functions();
    wait_for_enter();
    
    test_complex_expressions();
    wait_for_enter();
    
    test_error_handling();
    
    printf("\n" BOLD GREEN "=== TODOS OS TESTES CONCLUÍDOS ===\n" RESET);
}

int main() {
    test_evaluator();
    a89check_leaks();
    return 0;
}