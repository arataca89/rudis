#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>

/*
 * FUNÇÕES MATEMÁTICAS BÁSICAS
 */

// Fatorial (operador !)
double factorial(double n);

// Potência (operador ^)
double power(double base, double exponent);

/*
 * FUNÇÕES MATEMÁTICAS AVANÇADAS
 */

// Raiz quadrada
double math_sqrt(double x);

// Logaritmo base 10
double math_log10(double x);

// Logaritmo natural
double math_ln(double x);

// Exponencial
double math_exp(double x);

// Valor absoluto
double math_abs(double x);

// Trigonométricas
double math_sin(double x);
double math_cos(double x);
double math_tan(double x);

/*
 * FUNÇÕES ESTATÍSTICAS
 */

// Média aritmética
double math_mean(double* values, int count);

// Mediana
double math_median(double* values, int count);

// Desvio padrão
double math_std(double* values, int count);

// Variância
double math_variance(double* values, int count);

// Moda
double math_mode(double* values, int count);

// Soma
double math_sum(double* values, int count);

// Mínimo
double math_min(double* values, int count);

// Máximo
double math_max(double* values, int count);

/*
 * FUNÇÕES FINANCEIRAS
 */

// Valor Presente
double math_pv(double rate, double nper, double pmt);

// Valor Futuro
double math_fv(double rate, double nper, double pmt);

// Pagamento Periódico
double math_pmt(double rate, double nper, double pv);

// Número de Períodos
double math_nper(double rate, double pmt, double pv);

// Taxa de Juros
double math_rate(double nper, double pmt, double pv, double fv);

// Valor Presente Líquido
double math_npv(double rate, double* cashflows, int count);

// Taxa Interna de Retorno
double math_irr(double* cashflows, int count, double guess);

// Juros Simples
double math_simple_interest(double principal, double rate, double time);

// Montante Juros Simples
double math_simple_amount(double principal, double rate, double time);

// Juros Compostos
double math_compound_interest(double principal, double rate, double time);

// Montante Juros Compostos
double math_compound_amount(double principal, double rate, double time);

#endif // FUNCTIONS_H