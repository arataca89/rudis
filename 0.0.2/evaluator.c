#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "evaluator.h"
#include "functions.h"
#include "tools.h"
#include "lang.h"
#include "a89alloc.h"


// ===========================================
// FUNÇÕES AUXILIARES PARA MENSAGENS DE ERRO 
// ===========================================

void build_arg_error_msg(char* buffer, size_t size, const char* func_name, int required_args, int is_minimum) {
    if (current_lang == LANG_PT) {
        if (is_minimum) {
            snprintf(buffer, size, "%s requer pelo menos %d argumento%s", 
                    func_name, required_args, required_args > 1 ? "s" : "");
        } else {
            snprintf(buffer, size, "%s requer %d argumento%s", 
                    func_name, required_args, required_args > 1 ? "s" : "");
        }
    } else {
        if (is_minimum) {
            snprintf(buffer, size, "%s requires at least %d argument%s", 
                    func_name, required_args, required_args > 1 ? "s" : "");
        } else {
            snprintf(buffer, size, "%s requires %d argument%s", 
                    func_name, required_args, required_args > 1 ? "s" : "");
        }
    }
}

void build_unknown_function_msg(char* buffer, size_t size, const char* func_name) {
    if (current_lang == LANG_PT) {
        snprintf(buffer, size, "Função desconhecida: %s", func_name);
    } else {
        snprintf(buffer, size, "Unknown function: %s", func_name);
    }
}

void build_math_error_msg(char* buffer, size_t size, const char* func_name) {
    if (current_lang == LANG_PT) {
        snprintf(buffer, size, "Erro matemático na função %s", func_name);
    } else {
        snprintf(buffer, size, "Math error in function %s", func_name);
    }
}

/*
 * INICIALIZAÇÃO DO AVALIADOR
 */
void evaluator_init(EvaluatorState* state) {
    state->variables = NULL;
    state->variable_count = 0;
    state->decimal_places = 6;
}

/*
 * LIBERAÇÃO DE MEMÓRIA
 */
void evaluator_free(EvaluatorState* state) {
    Variable* current = state->variables;
    while (current != NULL) {
        Variable* next = current->next;
        a89free(current);
        current = next;
    }
    state->variables = NULL;
    state->variable_count = 0;
}

/*
 * OBTÉM VALOR DE UMA VARIÁVEL
 */
double get_variable(EvaluatorState* state, const char* variable_name) {
    Variable* current = state->variables;
    while (current != NULL) {
        if (strcmp(current->name, variable_name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return 0.0; // Retorna 0 se variável não existir
}

/*
 * DEFINE VALOR DE UMA VARIÁVEL
 */
void set_variable(EvaluatorState* state, const char* variable_name, double value) {
    // Procura variável existente
    Variable* current = state->variables;
    while (current != NULL) {
        if (strcmp(current->name, variable_name) == 0) {
            current->value = value;
            current->initialized = 1;
            return;
        }
        current = current->next;
    }
    
    // Cria nova variável
    Variable* new_var = (Variable*)A89ALLOC(sizeof(Variable));
    strncpy(new_var->name, variable_name, sizeof(new_var->name) - 1);
    new_var->name[sizeof(new_var->name) - 1] = '\0';
    new_var->value = value;
    new_var->initialized = 1;
    new_var->next = state->variables;
    state->variables = new_var;
    state->variable_count++;
}

/*
 * VERIFICA SE VARIÁVEL EXISTE
 */
int variable_exists(EvaluatorState* state, const char* variable_name) {
    Variable* current = state->variables;
    while (current != NULL) {
        if (strcmp(current->name, variable_name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/*
 * CRIA RESULTADO DE SUCESSO
 */
EvaluatorResult create_success_result(double value, int is_assignment) {
    EvaluatorResult result;
    result.success = 1;
    result.value = value;
    result.error_message[0] = '\0';
    result.is_assignment = is_assignment;
    return result;
}

/*
 * CRIA RESULTADO DE ERRO
 */
EvaluatorResult create_error_result(const char* message) {
    EvaluatorResult result;
    result.success = 0;
    result.value = 0.0;
    strncpy(result.error_message, message, sizeof(result.error_message) - 1);
    result.error_message[sizeof(result.error_message) - 1] = '\0';
    result.is_assignment = 0;
    return result;
}

/*
 * AVALIA UMA AST
 */
EvaluatorResult evaluate(EvaluatorState* state, ASTNode* node) {
    if (node == NULL) {
        if(current_lang == LANG_PT)
            return create_error_result("Nó AST nulo");
        else 
            return create_error_result("Null AST node");
    }
    
    switch (node->type) {
        case NODE_NUMBER:
            return create_success_result(node->value, 0);
            
        case NODE_VARIABLE:  
            if (variable_exists(state, node->variable)) {  
                return create_success_result(get_variable(state, node->variable), 0);  
            } else {
                if (current_lang == LANG_PT)
                    return create_error_result("Variável não definida");
                else 
                    return create_error_result("Variable not defined");
            }
            
        case NODE_ASSIGNMENT:
            {
                EvaluatorResult right_result = evaluate(state, node->right);
                if (!right_result.success) {
                    return right_result;
                }
                set_variable(state, node->variable, right_result.value);  // CORREÇÃO: node->variable
                return create_success_result(right_result.value, 1);
            }
            
        case NODE_BINARY_OP:
            {
                EvaluatorResult left_result = evaluate(state, node->left);
                if (!left_result.success) {
                    return left_result;
                }
                
                EvaluatorResult right_result = evaluate(state, node->right);
                if (!right_result.success) {
                    return right_result;
                }
                
                double result;
                switch (node->operator) {
                    case '+': result = left_result.value + right_result.value; break;
                    case '-': result = left_result.value - right_result.value; break;
                    case '*': result = left_result.value * right_result.value; break;
                    case '/': 
                        if (right_result.value == 0) {
                            if (current_lang == LANG_PT)
                                return create_error_result("Divisão por zero");
                            else 
                                return create_error_result("Division by zero");
                        }
                        result = left_result.value / right_result.value; 
                        break;
                    case '%': 
                        if ((int)right_result.value == 0) {
                            if (current_lang == LANG_PT)
                                return create_error_result("Módulo por zero");
                            else 
                                return create_error_result("Modulo by zero");
                        }
                        result = (int)left_result.value % (int)right_result.value; 
                        break;
                    case '^': result = power(left_result.value, right_result.value); break;
                    default: 
                        if (current_lang == LANG_PT)
                            return create_error_result("Operador binário inválido");
                        else 
                            return create_error_result("Invalid binary operator");
                }
                return create_success_result(result, 0);
            }
            
        case NODE_UNARY_OP:
            {
                EvaluatorResult operand_result = evaluate(state, node->operand);  
                if (!operand_result.success) {
                    return operand_result;
                }
                
                double result;
                switch (node->operator) {
                    case '-': result = -operand_result.value; break;
                    case '!': result = factorial(operand_result.value); break;
                    default: 
                        if (current_lang == LANG_PT)
                            return create_error_result("Operador unário inválido");
                        else 
                            return create_error_result("Invalid unary operator");
                }
                return create_success_result(result, 0);
            }
            
        case NODE_FUNCTION:  
            {
                if (node->args == NULL || node->arg_count == 0) {
                    if (current_lang == LANG_PT)
                        return create_error_result("Função sem argumentos");
                    else 
                        return create_error_result("Function without arguments");
                }
                
                // Avalia todos os argumentos
                double* arg_values = (double*)A89ALLOC(node->arg_count * sizeof(double));
                
                for (int i = 0; i < node->arg_count; i++) {
                    EvaluatorResult arg_result = evaluate(state, node->args[i]);
                    if (!arg_result.success) {
                        a89free(arg_values);
                        return arg_result;
                    }
                    arg_values[i] = arg_result.value;
                }
                
                // Executa a função
                EvaluatorResult func_result = execute_function(state, node->function, arg_values, node->arg_count);  // CORREÇÃO: node->function
                
                // Libera memória
                a89free(arg_values);
                
                return func_result;
            }
            
        default:
            if (current_lang == LANG_PT)
                return create_error_result("Tipo de nó AST desconhecido");
            else 
                return create_error_result("Unknown AST node type");
    }
}

/*
 * EXECUÇÃO DE FUNÇÕES
 */
EvaluatorResult execute_function(EvaluatorState* state, const char* function_name, 
                                 double* arg_values, int arg_count) {
    double result;
    char error_msg[256];


    // ============ FUNÇÕES MATEMÁTICAS ============
    if (strcmp(function_name, "sqrt") == 0 || strcmp(function_name, "raiz") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "sqrt", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_sqrt(arg_values[0]);
    }
    else if (strcmp(function_name, "sin") == 0 || strcmp(function_name, "sen") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "sin", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_sin(arg_values[0]);
    }
    else if (strcmp(function_name, "cos") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "cos", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_cos(arg_values[0]);
    }
    else if (strcmp(function_name, "tan") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "tan", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_tan(arg_values[0]);
    }
    else if (strcmp(function_name, "log") == 0 || strcmp(function_name, "log10") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "log", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_log10(arg_values[0]);
    }
    else if (strcmp(function_name, "ln") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "ln", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_ln(arg_values[0]);
    }
    else if (strcmp(function_name, "exp") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "exp", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_exp(arg_values[0]);
    }
    else if (strcmp(function_name, "abs") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "abs", 1, 0);
            return create_error_result(error_msg);
        }
        result = math_abs(arg_values[0]);
    }
    
    // ============ FUNÇÕES ESTATÍSTICAS ============
    else if (strcmp(function_name, "mean") == 0 || strcmp(function_name, "media") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "mean", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_mean(arg_values, arg_count);
    }
    else if (strcmp(function_name, "median") == 0 || strcmp(function_name, "mediana") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "median", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_median(arg_values, arg_count);
    }
    else if (strcmp(function_name, "std") == 0 || strcmp(function_name, "desvio") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "std", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_std(arg_values, arg_count);
    }
    else if (strcmp(function_name, "variance") == 0 || strcmp(function_name, "variancia") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "variance", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_variance(arg_values, arg_count);
    }
    else if (strcmp(function_name, "mode") == 0 || strcmp(function_name, "moda") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "mode", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_mode(arg_values, arg_count);
    }
    else if (strcmp(function_name, "sum") == 0 || strcmp(function_name, "soma") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "sum", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_sum(arg_values, arg_count);
    }
    else if (strcmp(function_name, "min") == 0 || strcmp(function_name, "minimo") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "min", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_min(arg_values, arg_count);
    }
    else if (strcmp(function_name, "max") == 0 || strcmp(function_name, "maximo") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "max", 1, 1);
            return create_error_result(error_msg);
        }
        result = math_max(arg_values, arg_count);
    }
    
    // ============ FUNÇÕES FINANCEIRAS ============
    else if (strcmp(function_name, "pv") == 0 || strcmp(function_name, "vp") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "pv", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_pv(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "fv") == 0 || strcmp(function_name, "vf") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "fv", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_fv(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "pmt") == 0 || strcmp(function_name, "pagamento") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "pmt", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_pmt(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "nper") == 0 || strcmp(function_name, "periodos") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "nper", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_nper(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "rate") == 0 || strcmp(function_name, "taxa") == 0) {
        if (arg_count != 4) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "rate", 4, 0);
            return create_error_result(error_msg);
        }
        result = math_rate(arg_values[0], arg_values[1], arg_values[2], arg_values[3]);
    }
    else if (strcmp(function_name, "si") == 0 || strcmp(function_name, "js") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "si", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_simple_interest(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "fv_si") == 0 || strcmp(function_name, "montante_js") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "fv_si", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_simple_amount(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "ci") == 0 || strcmp(function_name, "jc") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "ci", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_compound_interest(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "fv_ci") == 0 || strcmp(function_name, "montante_jc") == 0) {
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "fv_ci", 3, 0);
            return create_error_result(error_msg);
        }
        result = math_compound_amount(arg_values[0], arg_values[1], arg_values[2]);
    }
    else if (strcmp(function_name, "npv") == 0 || strcmp(function_name, "vpl") == 0) {
        if (arg_count < 2) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "npv", 2, 1);
            return create_error_result(error_msg);
        }
        // Primeiro argumento é a taxa, os demais são fluxos de caixa
        double rate = arg_values[0];
        double* cashflows = &arg_values[1];
        int cf_count = arg_count - 1;
        result = math_npv(rate, cashflows, cf_count);
    }
    else if (strcmp(function_name, "irr") == 0 || strcmp(function_name, "tir") == 0) {
        if (arg_count < 2) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "irr", 2, 1);
            return create_error_result(error_msg);
        }
        // Todos os argumentos são fluxos de caixa
        double guess = 0.1; // Chute inicial padrão
        result = math_irr(arg_values, arg_count, guess);
    }
    // ============ FUNÇÕES DE CONFIGURAÇÃO ============ ⭐️ NOVA!
    else if (strcmp(function_name, "setdec") == 0) {
        // Implementação do setdec
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "setdec", 1, 0);
            return create_error_result(error_msg);
        }
        
        int places = (int)arg_values[0];
        if (places < 0 || places > 15) {
            if (current_lang == LANG_PT)
                snprintf(error_msg, sizeof(error_msg), "setdec: número de casas deve estar entre 0 e 15");
            else 
                snprintf(error_msg, sizeof(error_msg), "setdec: number of places must be between 0 and 15");
            return create_error_result(error_msg);
        }
        
        state->decimal_places = places;
        return create_success_result(0.0, 1); // Sucesso silencioso
    }

    //================ FUNÇÕES DE ENTRADA/SAIDA ================================
    else if (strcmp(function_name, "print") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "median", 1, 1);
            return create_error_result(error_msg);
        }
        // Processa cada argumento do print
        for (int i = 0; i < arg_count; i++) {
            // TODO: Implementar parsing especial para:
            // 1. CORES: RED:, GREEN:, BLUE:, etc.
            // 2. ALINHAMENTO: left:, center:, right:
            // 3. LARGURA: 20:, 30:, etc.
            // 4. SEPARADORES: , (tabulado) vs ; (concatenação)
            
            // Por enquanto, só mostra o valor
            printf("%.*f ", state->decimal_places, arg_values[i]);
        }
        printf("\n");
        
        return create_success_result(0.0, 1); // Sucesso silencioso
    }

    else {
        build_unknown_function_msg(error_msg, sizeof(error_msg), function_name);
        return create_error_result(error_msg);
    }
    
    // Verifica se resultado é NAN
    if (isnan(result)) {
        build_math_error_msg(error_msg, sizeof(error_msg), function_name);
        return create_error_result(error_msg);
    }
    
    return create_success_result(result, 0);
}
