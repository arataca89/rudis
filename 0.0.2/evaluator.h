#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "parser.h"
#include "a89alloc.h"
#include <math.h>

/*
 * ESTRUTURA DE VARIÁVEL - RUDIS
 * 
 * Armazena uma variável com nome completo e valor
 */
typedef struct Variable {
    char name[64];          // Nome completo da variável
    double value;           // Valor numérico
    int initialized;        // Se foi inicializada
    struct Variable* next;  // Próxima variável (para lista encadeada)
} Variable;

/*
 * ESTADO DO AVALIADOR - RUDIS
 * 
 * Mantém o estado global do avaliador:
 * - variables: lista encadeada de variáveis (identificadores completos)
 * - variable_count: número de variáveis armazenadas
 */
typedef struct {
    Variable* variables;    // Lista de variáveis
    int variable_count;     // Contador de variáveis
    int decimal_places;     // Número de casas decimais
} EvaluatorState;

/*
 * RESULTADO DA AVALIAÇÃO - RUDIS
 * 
 * Contém o resultado de uma operação:
 * - success: indica se a operação foi bem-sucedida
 * - value: valor numérico do resultado
 * - error_message: mensagem de erro (se success = 0)
 * - is_assignment: indica se foi uma atribuição
 *   (não deve imprimir resultado)
 */
typedef struct {
    int success;
    double value;
    char error_message[256];
    int is_assignment;
} EvaluatorResult;

/*
 * FUNÇÕES DO AVALIADOR - RUDIS
 */

// Inicializa o estado do avaliador
void evaluator_init(EvaluatorState* state);

// Libera a memória do avaliador
void evaluator_free(EvaluatorState* state);

// Obtém valor de uma variável
double get_variable(EvaluatorState* state, const char* variable_name);

// Define valor de uma variável
void set_variable(EvaluatorState* state, const char* variable_name, double value);

// Verifica se uma variável existe
int variable_exists(EvaluatorState* state, const char* variable_name);

// Avalia uma AST e retorna o resultado
EvaluatorResult evaluate(EvaluatorState* state, ASTNode* node);

// Execução de funções
EvaluatorResult execute_function(EvaluatorState* state, const char* function_name, 
                                 double* arg_values, int arg_count);

// Cria resultado de sucesso
EvaluatorResult create_success_result(double value, int is_assignment);

// Cria resultado de erro
EvaluatorResult create_error_result(const char* message);

#endif // EVALUATOR_H