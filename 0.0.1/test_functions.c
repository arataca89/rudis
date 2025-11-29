#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
#include "tools.h"
#include "a89alloc.h"

void wait_for_enter() {
    printf("\n" CYAN "Pressione Enter para continuar..." RESET);
    getchar();
}

void test_math_functions() {
    printf(BOLD GREEN "=== TESTE DAS FUNÇÕES MATEMÁTICAS ===\n\n" RESET);
    
    printf(YELLOW "--- Funções Básicas ---\n" RESET);
    
    // Teste Fatorial
    printf("factorial(5) = %.2f (esperado: 120.00)\n", factorial(5));
    printf("factorial(0) = %.2f (esperado: 1.00)\n", factorial(0));
    printf("factorial(-5) = %.2f (esperado: NAN)\n", factorial(-5));
    printf("factorial(2.5) = %.2f (esperado: NAN)\n", factorial(2.5));
    
    // Teste Potência
    printf("power(2, 3) = %.2f (esperado: 8.00)\n", power(2, 3));
    printf("power(4, 0.5) = %.2f (esperado: 2.00)\n", power(4, 0.5));
    printf("power(10, -1) = %.2f (esperado: 0.10)\n", power(10, -1));
}

void test_advanced_math() {
    printf(YELLOW "\n--- Funções Avançadas ---\n" RESET);
    
    // Teste Raiz Quadrada
    printf("math_sqrt(25) = %.2f (esperado: 5.00)\n", math_sqrt(25));
    printf("math_sqrt(-4) = %.2f (esperado: NAN)\n", math_sqrt(-4));
    
    // Teste Logaritmos
    printf("math_log10(100) = %.2f (esperado: 2.00)\n", math_log10(100));
    printf("math_log10(-10) = %.2f (esperado: NAN)\n", math_log10(-10));
    printf("math_ln(2.71828) ≈ %.2f (esperado: ~1.00)\n", math_ln(2.71828));
    
    // Teste Exponencial
    printf("math_exp(1) ≈ %.2f (esperado: ~2.72)\n", math_exp(1));
    printf("math_exp(0) = %.2f (esperado: 1.00)\n", math_exp(0));
    
    // Teste Valor Absoluto
    printf("math_abs(-5.5) = %.2f (esperado: 5.50)\n", math_abs(-5.5));
    printf("math_abs(3.14) = %.2f (esperado: 3.14)\n", math_abs(3.14));
    
    // Teste Trigonométricas
    printf("math_sin(0) = %.2f (esperado: 0.00)\n", math_sin(0));
    printf("math_cos(0) = %.2f (esperado: 1.00)\n", math_cos(0));
    printf("math_tan(0) = %.2f (esperado: 0.00)\n", math_tan(0));
}

void test_statistical_functions() {
    printf(BOLD GREEN "\n=== TESTE DAS FUNÇÕES ESTATÍSTICAS ===\n\n" RESET);
    
    double dataset1[] = {1, 2, 3, 4, 5};
    double dataset2[] = {10, 20, 30, 40, 50};
    double dataset3[] = {5, 2, 8, 1, 9, 3};
    double dataset4[] = {1, 1, 2, 2, 2, 3, 4}; // Para moda
    double empty_dataset[] = {};
    
    printf(YELLOW "--- Dataset 1: {1, 2, 3, 4, 5} ---\n" RESET);
    printf("math_mean = %.2f (esperado: 3.00)\n", math_mean(dataset1, 5));
    printf("math_median = %.2f (esperado: 3.00)\n", math_median(dataset1, 5));
    printf("math_std = %.2f (esperado: ~1.58)\n", math_std(dataset1, 5));
    printf("math_variance = %.2f (esperado: ~2.50)\n", math_variance(dataset1, 5));
    printf("math_sum = %.2f (esperado: 15.00)\n", math_sum(dataset1, 5));
    printf("math_min = %.2f (esperado: 1.00)\n", math_min(dataset1, 5));
    printf("math_max = %.2f (esperado: 5.00)\n", math_max(dataset1, 5));
    
    printf(YELLOW "\n--- Dataset 2: {10, 20, 30, 40, 50} ---\n" RESET);
    printf("math_mean = %.2f (esperado: 30.00)\n", math_mean(dataset2, 5));
    printf("math_median = %.2f (esperado: 30.00)\n", math_median(dataset2, 5));
    
    printf(YELLOW "\n--- Dataset 3: {5, 2, 8, 1, 9, 3} (para mediana par) ---\n" RESET);
    printf("math_median = %.2f (esperado: 4.00)\n", math_median(dataset3, 6));
    printf("math_min = %.2f (esperado: 1.00)\n", math_min(dataset3, 6));
    printf("math_max = %.2f (esperado: 9.00)\n", math_max(dataset3, 6));
    
    printf(YELLOW "\n--- Dataset 4: {1, 1, 2, 2, 2, 3, 4} (para moda) ---\n" RESET);
    printf("math_mode = %.2f (esperado: 2.00)\n", math_mode(dataset4, 7));
    
    printf(YELLOW "\n--- Dataset Vazio ---\n" RESET);
    printf("math_mean(vazio) = %.2f (esperado: 0.00)\n", math_mean(empty_dataset, 0));
    printf("math_median(vazio) = %.2f (esperado: 0.00)\n", math_median(empty_dataset, 0));
    printf("math_mode(vazio) = %.2f (esperado: NAN)\n", math_mode(empty_dataset, 0));
}

void test_financial_functions() {
    printf(BOLD GREEN "\n=== TESTE DAS FUNÇÕES FINANCEIRAS ===\n\n" RESET);
    
    printf(YELLOW "--- Valor Presente e Futuro ---\n" RESET);
    printf("math_pv(0.05, 10, 100) = %.2f\n", math_pv(0.05, 10, 100));
    printf("math_fv(0.05, 10, 100) = %.2f\n", math_fv(0.05, 10, 100));
    printf("math_pmt(0.05, 10, 1000) = %.2f\n", math_pmt(0.05, 10, 1000));
    
    printf(YELLOW "\n--- Número de Períodos ---\n" RESET);
    printf("math_nper(0.05, 100, 1000) = %.2f\n", math_nper(0.05, 100, 1000));
    
    printf(YELLOW "\n--- Juros Simples ---\n" RESET);
    printf("math_simple_interest(1000, 0.05, 2) = %.2f (esperado: 100.00)\n", 
           math_simple_interest(1000, 0.05, 2));
    printf("math_simple_amount(1000, 0.05, 2) = %.2f (esperado: 1100.00)\n", 
           math_simple_amount(1000, 0.05, 2));
    
    printf(YELLOW "\n--- Juros Compostos ---\n" RESET);
    printf("math_compound_interest(1000, 0.05, 2) = %.2f (esperado: 102.50)\n", 
           math_compound_interest(1000, 0.05, 2));
    printf("math_compound_amount(1000, 0.05, 2) = %.2f (esperado: 1102.50)\n", 
           math_compound_amount(1000, 0.05, 2));
    
    printf(YELLOW "\n--- Valor Presente Líquido ---\n" RESET);
    double cashflows1[] = {-1000, 300, 400, 500};
    double cashflows2[] = {-500, 200, 200, 200};
    
    printf("math_npv(0.1, [-1000,300,400,500], 4) = %.2f\n", 
           math_npv(0.1, cashflows1, 4));
    printf("math_npv(0.1, [-500,200,200,200], 4) = %.2f\n", 
           math_npv(0.1, cashflows2, 4));
    
    printf(YELLOW "\n--- Taxa Interna de Retorno ---\n" RESET);
    printf("math_irr([-1000,300,400,500], 4, 0.1) = %.2f\n", 
           math_irr(cashflows1, 4, 0.1));
}

void test_error_handling() {
    printf(BOLD GREEN "\n=== TESTE DE TRATAMENTO DE ERROS ===\n\n" RESET);
    
    printf(YELLOW "--- Operações Inválidas ---\n" RESET);
    printf("math_sqrt(-25) = %.2f (esperado: NAN)\n", math_sqrt(-25));
    printf("math_log10(-10) = %.2f (esperado: NAN)\n", math_log10(-10));
    printf("math_ln(0) = %.2f (esperado: NAN)\n", math_ln(0));
    printf("factorial(-5) = %.2f (esperado: NAN)\n", factorial(-5));
    
    printf(YELLOW "\n--- Valores Extremos ---\n" RESET);
    printf("factorial(100) = %.2f (pode retornar INFINITY)\n", factorial(100));
    printf("math_exp(1000) = %.2f (pode retornar INFINITY)\n", math_exp(1000));
    
    double single_value[] = {42};
    double empty_array[] = {};
    
    printf(YELLOW "\n--- Arrays com Poucos Elementos ---\n" RESET);
    printf("math_std([42], 1) = %.2f (esperado: 0.00)\n", math_std(single_value, 1));
    printf("math_variance([42], 1) = %.2f (esperado: 0.00)\n", math_variance(single_value, 1));
    printf("math_std(vazio, 0) = %.2f (esperado: 0.00)\n", math_std(empty_array, 0));
}

void test_comprehensive_scenarios() {
    printf(BOLD GREEN "\n=== CENÁRIOS COMPREENSIVOS ===\n\n" RESET);
    
    printf(YELLOW "--- Análise de Investimento ---\n" RESET);
    double investment_returns[] = {1500, 1600, 1400, 1800, 1700};
    int n_returns = 5;
    
    printf("Retornos: {1500, 1600, 1400, 1800, 1700}\n");
    printf("Retorno médio: %.2f\n", math_mean(investment_returns, n_returns));
    printf("Volatilidade (desvio padrão): %.2f\n", math_std(investment_returns, n_returns));
    printf("Melhor retorno: %.2f\n", math_max(investment_returns, n_returns));
    printf("Pior retorno: %.2f\n", math_min(investment_returns, n_returns));
    
    printf(YELLOW "\n--- Planejamento de Aposentadoria ---\n" RESET);
    double monthly_savings = 500;
    double annual_rate = 0.08;
    double years = 30;
    double monthly_rate = annual_rate / 12;
    double months = years * 12;
    
    printf("Poupança mensal: R$ %.2f\n", monthly_savings);
    printf("Taxa anual: %.1f%%\n", annual_rate * 100);
    printf("Período: %.0f anos\n", years);
    printf("Montante final estimado: R$ %.2f\n", 
           math_fv(monthly_rate, months, -monthly_savings));
    
    printf(YELLOW "\n--- Análise de Dados de Vendas ---\n" RESET);
    double sales[] = {10500, 9800, 11200, 8900, 12500, 9800, 9800, 13200};
    int n_sales = 8;
    
    printf("Vendas mensais: ");
    for (int i = 0; i < n_sales; i++) {
        printf("%.0f ", sales[i]);
    }
    printf("\n");
    printf("Venda média: R$ %.2f\n", math_mean(sales, n_sales));
    printf("Mediana das vendas: R$ %.2f\n", math_median(sales, n_sales));
    printf("Moda das vendas: R$ %.2f\n", math_mode(sales, n_sales));
    printf("Total de vendas: R$ %.2f\n", math_sum(sales, n_sales));
}

void test_functions() {
    printf("\n\n");
    printf(BOLD GREEN "=== TESTE COMPLETO DO MÓDULO DE FUNÇÕES RUDIS ===\n\n" RESET);
    
    test_math_functions();
    wait_for_enter();
    
    test_advanced_math();
    wait_for_enter();
    
    test_statistical_functions();
    wait_for_enter();
    
    test_financial_functions();
    wait_for_enter();
    
    test_error_handling();
    wait_for_enter();
    
    test_comprehensive_scenarios();
    
    printf("\n" BOLD GREEN "=== TODOS OS TESTES CONCLUÍDOS ===\n" RESET);
}

int main() {
    test_functions();
    a89check_leaks();
    return 0;
}