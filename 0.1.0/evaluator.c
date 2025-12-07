#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lang.h"
#include "evaluator.h"
#include "functions.h"
#include "a89alloc.h"

void evaluator_init(EvaluatorState* state) {
    state->variables = NULL;
    state->variable_count = 0;
    state->decimal_places = 6;
}

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

Value get_variable(EvaluatorState* state, const char* variable_name) {
    Variable* current = state->variables;
    while (current != NULL) {
        if (strcmp(current->name, variable_name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return create_null_value(); // Retorna null
}

void set_variable(EvaluatorState* state, const char* variable_name, Value value) {
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

void print_variables(EvaluatorState* state) {
    printf("=== Variáveis no estado ===\n");
    
    Variable* current = state->variables;
    int count = 0;
    
    while (current != NULL) {
        printf("%d. %s: ", ++count, current->name);
        print_value(current->value, state->decimal_places); 
        printf("\n");
        current = current->next;
    }
    
    if (count == 0) {
        printf("Nenhuma variável definida\n");
    }
    printf("===========================\n");
}

EvaluatorResult create_success_result(Value value, int is_assignment) {
    EvaluatorResult result;
    result.success = 1;
    result.value = value;
    result.error_message[0] = '\0';
    result.is_assignment = is_assignment;
    return result;
}

EvaluatorResult create_error_result(const char* message) {
    EvaluatorResult result;
    result.success = 0;
    result.value = create_null_value();
    strncpy(result.error_message, message, sizeof(result.error_message) - 1);
    result.error_message[sizeof(result.error_message) - 1] = '\0';
    result.is_assignment = 0;
    return result;
}

//===================================================================
// AVALIA A AST
//===================================================================
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
            
        case NODE_STRING:
            return create_success_result(node->value, 0);
            
        case NODE_VARIABLE:  
            if (variable_exists(state, node->text)) {  
                return create_success_result(get_variable(state, node->text), 0);  
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
                set_variable(state, node->text, right_result.value);  
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
                
                if (left_result.value.type == VAL_NUMBER && right_result.value.type == VAL_NUMBER) {  
                    double result;
                    switch (node->operator) {
                        case '+': result = left_result.value.number + right_result.value.number; break;
                        case '-': result = left_result.value.number - right_result.value.number; break;
                        case '*': result = left_result.value.number * right_result.value.number; break;
                        case '/': 
                            if (right_result.value.number == 0) {
                                if (current_lang == LANG_PT)
                                    return create_error_result("Divisão por zero");
                                else 
                                    return create_error_result("Division by zero");
                            }
                            result = left_result.value.number / right_result.value.number; 
                            break;
                        case '%': 
                            if ((int)right_result.value.number == 0) {
                                if (current_lang == LANG_PT)
                                    return create_error_result("Módulo por zero");
                                else 
                                    return create_error_result("Modulo by zero");
                            }
                            result = (int)left_result.value.number % (int)right_result.value.number; 
                            break;
                        case '^': result = power(left_result.value.number, right_result.value.number); break;
                        default: 
                            if (current_lang == LANG_PT)
                                return create_error_result("Operador binário inválido");
                            else 
                                return create_error_result("Invalid binary operator");
                    }
                    return create_success_result(create_number_value(result), 0);
                } else {
                    if(node->operator == '+'){
                        return string_concatenate(&left_result, &right_result, -1);
                    } else {
                        // Outros operadores com strings → ERRO
                        if (current_lang == LANG_PT)
                            return create_error_result("Operações aritméticas requerem números");
                        else 
                            return create_error_result("Arithmetic operations require numbers");
                    }
                
                }
            }
            
        case NODE_UNARY_OP:
            {
                EvaluatorResult operand_result = evaluate(state, node->operand);  
                if (!operand_result.success) {
                    return operand_result;
                }
                
                // Verificar se é número
                if (operand_result.value.type != VAL_NUMBER) {
                    if (current_lang == LANG_PT)
                        return create_error_result("Operações unárias requerem números");
                    else 
                        return create_error_result("Unary operations require numbers");
                }
                
                double result;
                switch (node->operator) {
                    case '-': result = -operand_result.value.number; break;
                    case '!': result = factorial(operand_result.value.number); break;
                    default: 
                        if (current_lang == LANG_PT)
                            return create_error_result("Operador unário inválido");
                        else 
                            return create_error_result("Invalid unary operator");
                }
                return create_success_result(create_number_value(result), 0);
            }
            
        case NODE_FUNCTION:  
            {
                if(!strcmp(node->function, "print") && (node->args == NULL || node->arg_count == 0 )){
                    return execute_function(state, node->function, NULL,0);
                }

                if(!strcmp(node->function, "clear") && (node->args == NULL || node->arg_count == 0 )){
                    return execute_function(state, node->function, NULL,0);
                }


                if (node->args == NULL || node->arg_count == 0 ) {
                    if (current_lang == LANG_PT)
                        return create_error_result("Função sem argumentos");
                    else 
                        return create_error_result("Function without arguments");
                }
                
                // Avalia todos os argumentos
                Value* arg_values = (Value*)A89ALLOC(node->arg_count * sizeof(Value));
                if (!arg_values) {
                    if (current_lang == LANG_PT)
                        return create_error_result("Falha de alocação de memória");
                    else 
                        return create_error_result("Memory allocation failed");
                }
                
                for (int i = 0; i < node->arg_count; i++) {
                    EvaluatorResult arg_result = evaluate(state, node->args[i]);
                    if (!arg_result.success) {
                        a89free(arg_values);
                        return arg_result;
                    }
                    arg_values[i] = arg_result.value;
                }
                
                // Executa a função
                EvaluatorResult func_result = execute_function(state, node->function, arg_values, node->arg_count);
                
                // Libera memória
                a89free(arg_values);
                
                return func_result;
            }

        case NODE_SEQUENCE:
            {
                Value last_value = create_null_value();
                int has_value = 0;  // Flag para saber se algum statement retornou valor
                
                // Executar todos os statements em sequência
                for (int i = 0; i < node->stmt_count; i++) {
                    EvaluatorResult stmt_result = evaluate(state, node->statements[i]);
                    
                    if (!stmt_result.success) {
                        return stmt_result;  // Propagação de erro
                    }
                    
                    // Armazenar o último valor não-nulo (que não seja de atribuição)
                    if (!stmt_result.is_assignment) {
                        last_value = stmt_result.value;
                        has_value = 1;
                    }
                }
                
                if (has_value) {
                    return create_success_result(last_value, 0);
                } else {
                    // Se todos foram assignments, retorna sucesso sem valor
                    return create_success_result(create_null_value(), 1);
                }
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
                                 Value* arg_values, int arg_count) {
    double result;
    char error_msg[STR_SIZE];

    // ============ FUNÇÃO PRINT ============
    if (strcmp(function_name, "print") == 0) {
        if (arg_count < 1) {
            printf("\n");
            return create_success_result(create_null_value(), 1); // Sucesso silencioso           
        }
        
        // Processa cada argumento do print
        for (int i = 0; i < arg_count; i++) {
            print_value(arg_values[i], state->decimal_places); 
            if (i < arg_count - 1) printf(" ");
        }
        printf("\n");
        
        return create_success_result(create_null_value(), 1); // Sucesso silencioso
    }

    // ============ FUNÇÃO CLEAR ============
    if (strcmp(function_name, "clear") == 0) {
        if (arg_count != 0) {
            if (current_lang == LANG_PT)
                return create_error_result("Função clear não requer argumentos");
            else 
                return create_error_result("Function clear does not require arguments");   
        }        
        clear_screen();
        return create_success_result(create_null_value(), 1); // Sucesso silencioso
    }

    // ============ FUNÇÕES DE ALINHAMENTO ============
    if (strcmp(function_name, "left") == 0) {
        return create_success_result(left(arg_values, arg_count),0);
    }

    if (strcmp(function_name, "center") == 0) {
        return create_success_result(center(arg_values, arg_count),0);
    }

    if (strcmp(function_name, "right") == 0) {
        return create_success_result(right(arg_values, arg_count),0);
    }

    // ============ FUNÇÃO REPEAT ============
    if (strcmp(function_name, "repeat") == 0) {
        if (arg_count != 2) {
            Value error;
            error.type = VAL_STRING;
            if (current_lang == LANG_PT) {
                // snprintf(error.string, STR_SIZE,
                //          "Erro: repeat requer exatamente 2 argumentos");
                return create_error_result("Função repeat requer exatamente 2 argumentos");;
            } else {
                // snprintf(error.string, STR_SIZE,
                //          "Error: repeat requires exactly 2 arguments");
                return create_error_result("Function repeat requires exactly 2 arguments");;
            }
        }
        Value v = repeat(create_string_value(arg_values[0].string),
                         create_number_value(arg_values[1].number));
        return create_success_result(v,0);
    }

    // ============ FUNÇÕES DE CORES ============
    if (strcmp(function_name, "black") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função black requer exatamente 1 argumento");
            else 
                return create_error_result("Function black requires exactly 1 argument");
        }
        return create_success_result(black(arg_values[0]), 0);
    }

    if (strcmp(function_name, "red") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função red requer exatamente 1 argumento");
            else 
                return create_error_result("Function red requires exactly 1 argument");
        }
        return create_success_result(red(arg_values[0]), 0);
    }

    if (strcmp(function_name, "green") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função green requer exatamente 1 argumento");
            else 
                return create_error_result("Function green requires exactly 1 argument");
        }
        return create_success_result(green(arg_values[0]), 0);
    }

    if (strcmp(function_name, "yellow") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função yellow requer exatamente 1 argumento");
            else 
                return create_error_result("Function yellow requires exactly 1 argument");
        }
        return create_success_result(yellow(arg_values[0]), 0);
    }

    if (strcmp(function_name, "blue") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função blue requer exatamente 1 argumento");
            else 
                return create_error_result("Function blue requires exactly 1 argument");
        }
        return create_success_result(blue(arg_values[0]), 0);
    }

    if (strcmp(function_name, "magenta") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função magenta requer exatamente 1 argumento");
            else 
                return create_error_result("Function magenta requires exactly 1 argument");
        }
        return create_success_result(magenta(arg_values[0]), 0);
    }

    if (strcmp(function_name, "cyan") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função cyan requer exatamente 1 argumento");
            else 
                return create_error_result("Function cyan requires exactly 1 argument");
        }
        return create_success_result(cyan(arg_values[0]), 0);
    }

    if (strcmp(function_name, "white") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função white requer exatamente 1 argumento");
            else 
                return create_error_result("Function white requires exactly 1 argument");
        }
        return create_success_result(white(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_black") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_black requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_black requires exactly 1 argument");
        }
        return create_success_result(bright_black(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_red") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_red requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_red requires exactly 1 argument");
        }
        return create_success_result(bright_red(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_green") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_green requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_green requires exactly 1 argument");
        }
        return create_success_result(bright_green(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_yellow") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_yellow requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_yellow requires exactly 1 argument");
        }
        return create_success_result(bright_yellow(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_blue") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_blue requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_blue requires exactly 1 argument");
        }
        return create_success_result(bright_blue(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_magenta") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_magenta requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_magenta requires exactly 1 argument");
        }
        return create_success_result(bright_magenta(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_cyan") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_cyan requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_cyan requires exactly 1 argument");
        }
        return create_success_result(bright_cyan(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bright_white") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bright_white requer exatamente 1 argumento");
            else 
                return create_error_result("Function bright_white requires exactly 1 argument");
        }
        return create_success_result(bright_white(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_black") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_black requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_black requires exactly 1 argument");
        }
        return create_success_result(bg_black(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_red") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_red requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_red requires exactly 1 argument");
        }
        return create_success_result(bg_red(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_green") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_green requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_green requires exactly 1 argument");
        }
        return create_success_result(bg_green(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_yellow") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_yellow requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_yellow requires exactly 1 argument");
        }
        return create_success_result(bg_yellow(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_blue") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_blue requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_blue requires exactly 1 argument");
        }
        return create_success_result(bg_blue(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_magenta") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_magenta requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_magenta requires exactly 1 argument");
        }
        return create_success_result(bg_magenta(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_cyan") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_cyan requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_cyan requires exactly 1 argument");
        }
        return create_success_result(bg_cyan(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_white") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_white requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_white requires exactly 1 argument");
        }
        return create_success_result(bg_white(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_black") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_black requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_black requires exactly 1 argument");
        }
        return create_success_result(bg_bright_black(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_red") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_red requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_red requires exactly 1 argument");
        }
        return create_success_result(bg_bright_red(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_green") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_green requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_green requires exactly 1 argument");
        }
        return create_success_result(bg_bright_green(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_yellow") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_yellow requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_yellow requires exactly 1 argument");
        }
        return create_success_result(bg_bright_yellow(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_blue") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_blue requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_blue requires exactly 1 argument");
        }
        return create_success_result(bg_bright_blue(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_magenta") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_magenta requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_magenta requires exactly 1 argument");
        }
        return create_success_result(bg_bright_magenta(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_cyan") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_cyan requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_cyan requires exactly 1 argument");
        }
        return create_success_result(bg_bright_cyan(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bg_bright_white") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bg_bright_white requer exatamente 1 argumento");
            else 
                return create_error_result("Function bg_bright_white requires exactly 1 argument");
        }
        return create_success_result(bg_bright_white(arg_values[0]), 0);
    }

    if (strcmp(function_name, "bold") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função bold requer exatamente 1 argumento");
            else 
                return create_error_result("Function bold requires exactly 1 argument");
        }
        return create_success_result(bold(arg_values[0]), 0);
    }

    if (strcmp(function_name, "dim") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função dim requer exatamente 1 argumento");
            else 
                return create_error_result("Function dim requires exactly 1 argument");
        }
        return create_success_result(dim(arg_values[0]), 0);
    }

    if (strcmp(function_name, "italic") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função italic requer exatamente 1 argumento");
            else 
                return create_error_result("Function italic requires exactly 1 argument");
        }
        return create_success_result(italic(arg_values[0]), 0);
    }

    if (strcmp(function_name, "underline") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função underline requer exatamente 1 argumento");
            else 
                return create_error_result("Function underline requires exactly 1 argument");
        }
        return create_success_result(underline(arg_values[0]), 0);
    }

    if (strcmp(function_name, "blink") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função blink requer exatamente 1 argumento");
            else 
                return create_error_result("Function blink requires exactly 1 argument");
        }
        return create_success_result(blink(arg_values[0]), 0);
    }

    if (strcmp(function_name, "inverse") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função inverse requer exatamente 1 argumento");
            else 
                return create_error_result("Function inverse requires exactly 1 argument");
        }
        return create_success_result(inverse(arg_values[0]), 0);
    }

    if (strcmp(function_name, "hidden") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função hidden requer exatamente 1 argumento");
            else 
                return create_error_result("Function hidden requires exactly 1 argument");
        }
        return create_success_result(hidden(arg_values[0]), 0);
    }

    if (strcmp(function_name, "strikethrough") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT)
                return create_error_result("Função strikethrough requer exatamente 1 argumento");
            else 
                return create_error_result("Function strikethrough requires exactly 1 argument");
        }
        return create_success_result(strikethrough(arg_values[0]), 0);
    }

    // ============ VERIFICAR ARGUMENTOS PARA FUNÇÕES MATEMÁTICAS ============
    for (int i = 0; i < arg_count; i++) {
        if (arg_values[i].type != VAL_NUMBER) {
            if (current_lang == LANG_PT) {
                snprintf(error_msg, sizeof(error_msg), 
                         "Função %s requer argumentos numéricos", function_name);
            } else {
                snprintf(error_msg, sizeof(error_msg), 
                         "Function %s requires numeric arguments", function_name);
            }
            return create_error_result(error_msg);
        }
    }
    
    // Converter Value[] para double[]
    double* double_args = A89ALLOC(arg_count * sizeof(double));
    if (!double_args) {
        if (current_lang == LANG_PT)
            return create_error_result("Falha de alocação de memória para double_args");
        else 
            return create_error_result("Memory allocation failed for double_args");
    }
    
    for (int i = 0; i < arg_count; i++) {
        double_args[i] = arg_values[i].number;
    }

    // ============ FUNÇÕES MATEMÁTICAS ============
    if (strcmp(function_name, "sqrt") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "sqrt", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_sqrt(double_args[0]);
    }
    else if (strcmp(function_name, "sin") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "sin", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_sin(double_args[0]);
    }
    else if (strcmp(function_name, "cos") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "cos", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_cos(double_args[0]);
    }
    else if (strcmp(function_name, "tan") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "tan", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_tan(double_args[0]);
    }
    else if (strcmp(function_name, "log") == 0){
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "log", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_log10(double_args[0]);
    }
    else if (strcmp(function_name, "ln") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "ln", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_ln(double_args[0]);
    }
    else if (strcmp(function_name, "exp") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "exp", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_exp(double_args[0]);
    }
    else if (strcmp(function_name, "abs") == 0) {
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "abs", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_abs(double_args[0]);
    }
    
    // ============ FUNÇÕES ESTATÍSTICAS ============
    else if (strcmp(function_name, "mean") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "mean", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_mean(double_args, arg_count);
    }
    else if (strcmp(function_name, "median") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "median", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_median(double_args, arg_count);
    }
    else if (strcmp(function_name, "std") == 0) {
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "std", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_std(double_args, arg_count);
    }
    else if (strcmp(function_name, "variance") == 0){
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "variance", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_variance(double_args, arg_count);
    }
    else if (strcmp(function_name, "mode") == 0){
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "mode", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_mode(double_args, arg_count);
    }
    else if (strcmp(function_name, "sum") == 0){
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "sum", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_sum(double_args, arg_count);
    }
    else if (strcmp(function_name, "min") == 0){
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "min", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_min(double_args, arg_count);
    }
    else if (strcmp(function_name, "max") == 0){
        if (arg_count < 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "max", 1, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_max(double_args, arg_count);
    }
    
    // ============ FUNÇÕES FINANCEIRAS ============
    else if (strcmp(function_name, "pv") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "pv", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_pv(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "fv") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "fv", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_fv(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "pmt") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "pmt", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_pmt(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "nper") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "nper", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_nper(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "rate") == 0){
        if (arg_count != 4) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "rate", 4, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_rate(double_args[0], double_args[1], double_args[2], double_args[3]);
    }
    else if (strcmp(function_name, "si") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "si", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_simple_interest(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "fv_si") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "fv_si", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_simple_amount(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "ci") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "ci", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_compound_interest(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "fv_ci") == 0){
        if (arg_count != 3) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "fv_ci", 3, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        result = math_compound_amount(double_args[0], double_args[1], double_args[2]);
    }
    else if (strcmp(function_name, "npv") == 0){
        if (arg_count < 2) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "npv", 2, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        // Primeiro argumento é a taxa, os demais são fluxos de caixa
        double rate = double_args[0];
        double* cashflows = &double_args[1];
        int cf_count = arg_count - 1;
        result = math_npv(rate, cashflows, cf_count);
    }
    else if (strcmp(function_name, "irr") == 0){
        if (arg_count < 2) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "irr", 2, 1);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        // Todos os argumentos são fluxos de caixa
        double guess = 0.1; // Chute inicial padrão
        result = math_irr(double_args, arg_count, guess);
    }
    // ============ FUNÇÕES DE CONFIGURAÇÃO ============ 
    else if (strcmp(function_name, "setdec") == 0) {
        // Implementação do setdec
        if (arg_count != 1) {
            build_arg_error_msg(error_msg, sizeof(error_msg), "setdec", 1, 0);
            a89free(double_args);
            return create_error_result(error_msg);
        }
        
        int places = (int)double_args[0];
        if (places < 0 || places > 15) {
            if (current_lang == LANG_PT)
                snprintf(error_msg, sizeof(error_msg), "setdec: número de casas deve estar entre 0 e 15");
            else 
                snprintf(error_msg, sizeof(error_msg), "setdec: number of places must be between 0 and 15");
            a89free(double_args);
            return create_error_result(error_msg);
        }
        
        state->decimal_places = places;
        a89free(double_args);
        return create_success_result(create_number_value(0.0), 1); // Sucesso silencioso
    }
    else {
        build_unknown_function_msg(error_msg, sizeof(error_msg), function_name);
        a89free(double_args);
        return create_error_result(error_msg);
    }
    
    // Liberar memória
    a89free(double_args);
    
    // Verifica se resultado é NAN
    if (isnan(result)) {
        build_math_error_msg(error_msg, sizeof(error_msg), function_name);
        return create_error_result(error_msg);
    }
    
    return create_success_result(create_number_value(result), 0);
}

//===================================================================
// FUNÇÃO QUE CONCATENA STRINGS
//===================================================================
EvaluatorResult string_concatenate(EvaluatorResult* left, 
                                   EvaluatorResult* right,
                                   int decimal_places) {
    EvaluatorResult result;

    // Converter left para string
    Value left_str_val = value_to_string_value(left->value, decimal_places);
    
    // Converter right para string  
    Value right_str_val = value_to_string_value(right->value, decimal_places);
    
    // Calcular tamanho total
    size_t left_len = strlen(left_str_val.string);
    size_t right_len = strlen(right_str_val.string);
    size_t total_len = left_len + right_len;
    
    // Buffer para resultado
    char result_str[STR_SIZE];
    
    if (total_len >= STR_SIZE) {
        // Resultado muito grande - truncar
        // Primeiro copiar left (até onde couber)
        strncpy(result_str, left_str_val.string, STR_SIZE - 1);
        result_str[STR_SIZE - 1] = '\0';
        
        // Se ainda houver espaço, adicionar parte do right
        size_t used = strlen(result_str);
        if (used < STR_SIZE - 1) {
            strncat(result_str, right_str_val.string, STR_SIZE - used - 1);
        }
        
    } else {
        // Cabe normalmente
        snprintf(result_str, total_len + 1, "%s%s", 
                 left_str_val.string, right_str_val.string);
    }
    
    // Configurar resultado
    result.success = 1;
    result.value = create_string_value(result_str);
    result.is_assignment = 0;
    return result;
}

