#include "parser.h"
#include "lang.h"
#include "a89alloc.h"

/*
 * FUNÇÃO AUXILIAR PARA LIBERAR ARGUMENTOS DE FUNÇÃO
 */
void free_function_args(ASTNode** args, int arg_count) {
    if (args == NULL) return;
    
    for (int i = 0; i < arg_count; i++) {
        free_ast(args[i]);
    }
    a89free(args);
}

/*
 * MENSAGENS DE ERRO INTERNACIONALIZADAS
 */

const char* get_error_unexpected_token() {
    return (current_lang == LANG_PT) 
        ? "Token inesperado" 
        : "Unexpected token";
}

const char* get_error_expected_rparen() {
    return (current_lang == LANG_PT)
        ? "Esperado ')'"
        : "Expected ')'";
}

const char* get_error_expected_lparen_after_func() {
    return (current_lang == LANG_PT)
        ? "Esperado '(' apos nome da função"
        : "Expected '(' after function name";
}

const char* get_error_expected_rparen_after_args() {
    return (current_lang == LANG_PT)
        ? "Esperado ')' apos argumentos da função"
        : "Expected ')' after function arguments";
}

const char* get_error_max_args_exceeded() {
    return (current_lang == LANG_PT)
        ? "Numero máximo de argumentos excedido"
        : "Maximum number of arguments exceeded";
}

const char* get_error_invalid_expression() {
    return (current_lang == LANG_PT)
        ? "Expressao inválida"
        : "Invalid expression";
}

const char* get_error_incomplete_expression() {
    return (current_lang == LANG_PT)
        ? "Expressao incompleta ou inválida"
        : "Incomplete or invalid expression";
}

const char* get_error_syntax() {
    return (current_lang == LANG_PT)
        ? "Erro de sintaxe"
        : "Syntax error";
}

/*
 * FUNÇÃO PARA SALVAR ESTADO DO PARSER
 */
void parser_save_state(Parser* parser, Parser* saved_state) {
    // Salva o lexer completo
    saved_state->lexer->input = parser->lexer->input;
    saved_state->lexer->input_size = parser->lexer->input_size;
    saved_state->lexer->position = parser->lexer->position;
    saved_state->lexer->current_char = parser->lexer->current_char;
    
    // Salva o token atual
    saved_state->current_token = parser->current_token;
    
    // Salva estado de erro
    saved_state->has_error = parser->has_error;
    strcpy(saved_state->error_message, parser->error_message);
}

/*
 * FUNÇÃO PARA RESTAURAR ESTADO DO PARSER
 */
void parser_restore_state(Parser* parser, Parser* saved_state) {
    // Restaura o lexer
    parser->lexer->input = saved_state->lexer->input;
    parser->lexer->input_size = saved_state->lexer->input_size;
    parser->lexer->position = saved_state->lexer->position;
    parser->lexer->current_char = saved_state->lexer->current_char;
    
    // Restaura o token atual
    parser->current_token = saved_state->current_token;
    
    // Restaura estado de erro
    parser->has_error = saved_state->has_error;
    strcpy(parser->error_message, saved_state->error_message);
}

/*
 * INICIALIZACAO DO PARSER
 */
void parser_init(Parser* parser, Lexer* lexer) {
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->has_error = 0;
    strcpy(parser->error_message, "");
}

/*
 * AVANCO DO PARSER
 */
void parser_advance(Parser* parser) {
    parser->current_token = lexer_get_next_token(parser->lexer);
}

/*
 * VERIFICACAO DE TIPO DE TOKEN
 */
int parser_expect(Parser* parser, RTokenType expected_type) {
    return parser->current_token.type == expected_type;
}

/*
 * DEFINICAO DE ERRO DO PARSER
 */
void parser_set_error(Parser* parser, const char* message) {
    parser->has_error = 1;
    strncpy(parser->error_message, message, sizeof(parser->error_message) - 1);
    parser->error_message[sizeof(parser->error_message) - 1] = '\0';
}

/*
 * VALIDACAO DE ARGUMENTOS DE FUNÇÃO
 */
int validate_function_args(Parser* parser, const char* function_name, int arg_count) {
    char error_msg[100];
    
    // Funcoes com 1 argumento
    if (strcmp(function_name, "sqrt") == 0 || 
        strcmp(function_name, "sin") == 0 ||
        strcmp(function_name, "cos") == 0 ||
        strcmp(function_name, "tan") == 0 ||
        strcmp(function_name, "log") == 0 ||
        strcmp(function_name, "ln") == 0 ||
        strcmp(function_name, "exp") == 0 ||
        strcmp(function_name, "abs") == 0 ||
        // Aliases em português
        strcmp(function_name, "raiz") == 0 ||
        strcmp(function_name, "sen") == 0 ||
        strcmp(function_name, "log10") == 0 ||
        strcmp(function_name, "setdec") == 0) {
        if (arg_count != 1) {
            if (current_lang == LANG_PT) {
                snprintf(error_msg, sizeof(error_msg), "Função %s requer exatamente 1 argumento", function_name);
            } else {
                snprintf(error_msg, sizeof(error_msg), "Function %s requires exactly 1 argument", function_name);
            }
            parser_set_error(parser, error_msg);
            return 0;
        }
    }
    // Funcoes com 3 argumentos
    else if (strcmp(function_name, "pv") == 0 ||
             strcmp(function_name, "fv") == 0 ||
             strcmp(function_name, "pmt") == 0 ||
             strcmp(function_name, "nper") == 0 ||
             strcmp(function_name, "si") == 0 ||
             strcmp(function_name, "fv_si") == 0 ||
             strcmp(function_name, "ci") == 0 ||
             strcmp(function_name, "fv_ci") == 0 ||
             // Aliases em português
             strcmp(function_name, "vp") == 0 ||
             strcmp(function_name, "vf") == 0 ||
             strcmp(function_name, "pagamento") == 0 ||
             strcmp(function_name, "periodos") == 0 ||
             strcmp(function_name, "js") == 0 ||
             strcmp(function_name, "montante_js") == 0 ||
             strcmp(function_name, "jc") == 0 ||
             strcmp(function_name, "montante_jc") == 0) {
        if (arg_count != 3) {
            if (current_lang == LANG_PT) {
                snprintf(error_msg, sizeof(error_msg), "Função %s requer exatamente 3 argumentos", function_name);
            } else {
                snprintf(error_msg, sizeof(error_msg), "Function %s requires exactly 3 arguments", function_name);
            }
            parser_set_error(parser, error_msg);
            return 0;
        }
    }
    // Funcoes com 4 argumentos
    else if (strcmp(function_name, "rate") == 0 ||
             // Alias em português
             strcmp(function_name, "taxa") == 0) {
        if (arg_count != 4) {
            if (current_lang == LANG_PT) {
                snprintf(error_msg, sizeof(error_msg), "Função %s requer exatamente 4 argumentos", function_name);
            } else {
                snprintf(error_msg, sizeof(error_msg), "Function %s requires exactly 4 arguments", function_name);
            }
            parser_set_error(parser, error_msg);
            return 0;
        }
    }
    // Funcoes com multiplos argumentos (estatísticas)
    else if (strcmp(function_name, "mean") == 0 || 
             strcmp(function_name, "median") == 0 ||
             strcmp(function_name, "std") == 0 ||
             strcmp(function_name, "sum") == 0 ||
             strcmp(function_name, "min") == 0 ||
             strcmp(function_name, "max") == 0 ||
             // NOVAS FUNÇÕES ESTATÍSTICAS
             strcmp(function_name, "variance") == 0 ||
             strcmp(function_name, "mode") == 0 ||
             // Aliases em português
             strcmp(function_name, "media") == 0 ||
             strcmp(function_name, "mediana") == 0 ||
             strcmp(function_name, "desvio") == 0 ||
             strcmp(function_name, "soma") == 0 ||
             strcmp(function_name, "minimo") == 0 ||
             strcmp(function_name, "maximo") == 0 ||
             strcmp(function_name, "variancia") == 0 ||
             strcmp(function_name, "moda") == 0 ||
             // FUNÇÕES DE ENTRADA/SAIDA
             strcmp(function_name, "print") == 0){
        if (arg_count < 1) {
            if (current_lang == LANG_PT) {
                snprintf(error_msg, sizeof(error_msg), "Função %s requer pelo menos 1 argumento", function_name);
            } else {
                snprintf(error_msg, sizeof(error_msg), "Function %s requires at least 1 argument", function_name);
            }
            parser_set_error(parser, error_msg);
            return 0;
        }
    }
    // NOVAS FUNÇÕES FINANCEIRAS
    else if (strcmp(function_name, "npv") == 0 ||
             strcmp(function_name, "irr") == 0 ||
             // Aliases em português
             strcmp(function_name, "vpl") == 0 ||
             strcmp(function_name, "tir") == 0) {
        if (arg_count < 2) {
            if (current_lang == LANG_PT) {
                snprintf(error_msg, sizeof(error_msg), "Função %s requer pelo menos 2 argumentos", function_name);
            } else {
                snprintf(error_msg, sizeof(error_msg), "Function %s requires at least 2 arguments", function_name);
            }
            parser_set_error(parser, error_msg);
            return 0;
        }
    }
    
    return 1;
}


/*
 * CRIACAO DE NOS DA AST
 */
ASTNode* create_number_node(double value) {
    ASTNode* node = A89ALLOC(sizeof(ASTNode));
    if (!node) {
        printf("Erro ao alocar memória para number_node: %.2f\n", value);
        exit(EXIT_FAILURE);
    }
    node->type = NODE_NUMBER;
    node->value = value;
    node->left = node->right = node->operand = NULL;
    node->args = NULL;
    node->arg_count = 0;
    return node;
}

ASTNode* create_variable_node(const char* variable) {
    ASTNode* node = A89ALLOC(sizeof(ASTNode));
    if (!node) {
        printf("Erro ao alocar memória para variable_node: %s\n", variable);
        exit(EXIT_FAILURE);
    }
    node->type = NODE_VARIABLE;
    strncpy(node->variable, variable, sizeof(node->variable) - 1);
    node->variable[sizeof(node->variable) - 1] = '\0';
    node->left = node->right = node->operand = NULL;
    node->args = NULL;
    node->arg_count = 0;
    return node;
}

ASTNode* create_binary_op_node(char operator, ASTNode* left, ASTNode* right) {
    ASTNode* node = A89ALLOC(sizeof(ASTNode));
    if (!node) {
        printf("Erro ao alocar memória para binary_op_node: %c\n", operator);
        exit(EXIT_FAILURE);
    }
    node->type = NODE_BINARY_OP;
    node->operator = operator;
    node->left = left;
    node->right = right;
    node->operand = NULL;
    node->args = NULL;
    node->arg_count = 0;
    return node;
}

ASTNode* create_unary_op_node(char operator, ASTNode* operand) {
    ASTNode* node = A89ALLOC(sizeof(ASTNode));
    if (!node) {
        printf("Erro ao alocar memória para unary_op_node: %c\n", operator);
        exit(EXIT_FAILURE);
    }
    node->type = NODE_UNARY_OP;
    node->operator = operator;
    node->operand = operand;
    node->left = node->right = NULL;
    node->args = NULL;
    node->arg_count = 0;
    return node;
}

ASTNode* create_function_node(const char* function, ASTNode** args, int arg_count) {
    ASTNode* node = A89ALLOC(sizeof(ASTNode));
    if (!node) {
        printf("Erro ao alocar memória para function_node: %s\n", function);
        exit(EXIT_FAILURE);
    }
    node->type = NODE_FUNCTION;
    strncpy(node->function, function, sizeof(node->function) - 1);
    node->function[sizeof(node->function) - 1] = '\0';
    node->args = args;
    node->arg_count = arg_count;
    node->left = node->right = node->operand = NULL;
    return node;
}

ASTNode* create_assignment_node(const char* variable, ASTNode* value) {
    ASTNode* node = A89ALLOC(sizeof(ASTNode));
    if (!node) {
        printf("Erro ao alocar memória para assignment_node: %s\n", variable);
        exit(EXIT_FAILURE);
    }
    node->type = NODE_ASSIGNMENT;
    strncpy(node->variable, variable, sizeof(node->variable) - 1);
    node->variable[sizeof(node->variable) - 1] = '\0';
    node->right = value;
    node->left = node->operand = NULL;
    node->args = NULL;
    node->arg_count = 0;
    return node;
}

/*
 * LIBERACAO DE memória DA AST
 */
void free_ast(ASTNode* node) {
    if (node == NULL) return;
    
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->operand);
    
    if (node->args != NULL) {
        for (int i = 0; i < node->arg_count; i++) {
            free_ast(node->args[i]);
        }
        a89free(node->args);
    }
    
    a89free(node);
}

/*
 * expression := assignment | arithmetic_expr
 */
ASTNode* parse_expression(Parser* parser) {
    // Salva estado atual para possivel rollback
    Parser saved_state;
    Lexer saved_lexer;
    saved_state.lexer = &saved_lexer;
    parser_save_state(parser, &saved_state);
    
    // Tenta parsear como atribuicao
    if (parser->current_token.type == TOKEN_IDENTIFIER) {
        char variable[64];
        strncpy(variable, parser->current_token.text, sizeof(variable) - 1);
        variable[sizeof(variable) - 1] = '\0';
        
        parser_advance(parser);
        
        if (parser->current_token.type == TOKEN_ASSIGN) {
            // É uma atribuicao valida
            parser_advance(parser);
            ASTNode* value = parse_expression(parser);
            if (parser->has_error) return NULL;
            return create_assignment_node(variable, value);
        }
    }
    
    // Se não é atribuição, restaura estado e parse como expressão aritmética
    parser_restore_state(parser, &saved_state);
    return parse_arithmetic_expr(parser);
}

/*
 * arithmetic_expr := term (('+' | '-') term)*
 */
ASTNode* parse_arithmetic_expr(Parser* parser) {
    ASTNode* node = parse_term(parser);
    if (parser->has_error) return NULL;
    
    while (parser->current_token.type == TOKEN_OPERATOR &&
           (parser->current_token.operator == '+' ||
            parser->current_token.operator == '-')) {
        char op = parser->current_token.operator;
        parser_advance(parser);
        ASTNode* right = parse_term(parser);
        if (parser->has_error) {
            free_ast(node);
            return NULL;
        }
        node = create_binary_op_node(op, node, right);
    }
    
    return node;
}

/*
 * term := factor (('*' | '/' | '%') factor)*
 */
ASTNode* parse_term(Parser* parser) {
    ASTNode* node = parse_factor(parser);
    if (parser->has_error) return NULL;
    
    while (parser->current_token.type == TOKEN_OPERATOR &&
           (parser->current_token.operator == '*' || 
            parser->current_token.operator == '/' || 
            parser->current_token.operator == '%')) {
        char op = parser->current_token.operator;
        parser_advance(parser);
        ASTNode* right = parse_factor(parser);
        if (parser->has_error) {
            free_ast(node);
            return NULL;
        }
        node = create_binary_op_node(op, node, right);
    }
    
    return node;
}

/*
 * factor := power ('!')?
 */
ASTNode* parse_factor(Parser* parser) {
    ASTNode* node = parse_power(parser);
    if (parser->has_error) return NULL;
    
    if (parser->current_token.type == TOKEN_OPERATOR &&
        parser->current_token.operator == '!') {
        char op = parser->current_token.operator;
        parser_advance(parser);
        node = create_unary_op_node(op, node);
    }
    
    return node;
}

/*
 * power := atom ('^' power)?
 */
ASTNode* parse_power(Parser* parser) {
    ASTNode* node = parse_atom(parser);
    if (parser->has_error) return NULL;
    
    if (parser->current_token.type == TOKEN_OPERATOR &&
        parser->current_token.operator == '^') {
        char op = parser->current_token.operator;
        parser_advance(parser);
        ASTNode* right = parse_power(parser);
        if (parser->has_error) {
            free_ast(node);
            return NULL;
        }
        node = create_binary_op_node(op, node, right);
    }
    
    return node;
}

/*
 * atom := NUMBER | IDENTIFIER | function_call | '(' expression ')' | '-' atom
 */
ASTNode* parse_atom(Parser* parser) {
    Token token = parser->current_token;

    switch (token.type) {
        case TOKEN_NUMBER:
            parser_advance(parser);
            return create_number_node(token.value);
            
        case TOKEN_IDENTIFIER:
            parser_advance(parser);
            return create_variable_node(token.text);
            
        case TOKEN_FUNCTION:
            return parse_function_call(parser, token.text);
            
        case TOKEN_LPAREN:
            parser_advance(parser);
            ASTNode* node = parse_expression(parser);
            if (parser->has_error) return NULL;
            
            if (!parser_expect(parser, TOKEN_RPAREN)) {
                free_ast(node);
                parser_set_error(parser, get_error_expected_rparen());
                return NULL;
            }
            parser_advance(parser);
            return node;
            
        case TOKEN_OPERATOR:
            if (token.operator == '-') {
                parser_advance(parser);
                ASTNode* operand = parse_atom(parser);
                if (parser->has_error) return NULL;
                return create_unary_op_node('-', operand);
            }
            break;

        case TOKEN_ERROR:
            parser_set_error(parser, token.text);
            return NULL;
        default:
            parser_set_error(parser, get_error_unexpected_token());
            break;
    }
    
    parser_set_error(parser, get_error_invalid_expression());
    return NULL;
}

/*
 * function_call := FUNCTION '(' argument_list ')'
 * argument_list := expression (',' expression)*
 */
ASTNode* parse_function_call(Parser* parser, const char* function_name) {
    parser_advance(parser);
    
    if (!parser_expect(parser, TOKEN_LPAREN)) {
        parser_set_error(parser, get_error_expected_lparen_after_func());
        return NULL;
    }
    parser_advance(parser);
    
    ASTNode** args = A89ALLOC(10 * sizeof(ASTNode*));
    int arg_count = 0;
    
    if (!parser_expect(parser, TOKEN_RPAREN)) {
        args[arg_count] = parse_expression(parser);
        if (parser->has_error) {
            free_function_args(args, arg_count);
            return NULL;
        }
        arg_count++;
        
        while (parser_expect(parser, TOKEN_COMMA)) {
            parser_advance(parser);
            if (arg_count >= 10) {
                parser_set_error(parser, get_error_max_args_exceeded());
                free_function_args(args, arg_count);
                return NULL;
            }
            args[arg_count] = parse_expression(parser);
            if (parser->has_error) {
                free_function_args(args, arg_count);
                return NULL;
            }
            arg_count++;
        }
    }
    
    if (!validate_function_args(parser, function_name, arg_count)) {
        free_function_args(args, arg_count);
        return NULL;
    }
    
    if (!parser_expect(parser, TOKEN_RPAREN)) {
        parser_set_error(parser, get_error_expected_rparen_after_args());
        free_function_args(args, arg_count);
        return NULL;
    }
    parser_advance(parser);
    
    return create_function_node(function_name, args, arg_count);
}

/*
 * Função PRINCIPAL DE PARSING
 */
ASTNode* parse(Lexer* lexer) {
    Parser parser;
    parser_init(&parser, lexer);
    
    if (parser.current_token.type == TOKEN_EOF) {
        return NULL;
    }
    
    ASTNode* result = parse_expression(&parser);
    
    if (parser.has_error) {
        if (result != NULL) {
            free_ast(result);
        }
        printf("%s: %s\n", get_error_syntax(), parser.error_message);
        return NULL;
    }
    
    if (parser.current_token.type != TOKEN_EOF) {
        if (result != NULL) {
            free_ast(result);
        }
        printf("%s\n", get_error_incomplete_expression());
        return NULL;
    }
    
    return result;
}

/*
 * IMPRESSAO DA AST (PARA DEBUG)
 */
void print_ast(ASTNode* node, int indent) {
    if (node == NULL) return;
    
    for (int i = 0; i < indent; i++) printf("    ");
    
    switch (node->type) {
        case NODE_NUMBER:
            printf("NUMBER: %.2f\n", node->value);
            break;
        case NODE_VARIABLE:
            printf("VARIABLE: %s\n", node->variable);
            break;
        case NODE_BINARY_OP:
            printf("BINARY_OP: %c\n", node->operator);
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case NODE_UNARY_OP:
            printf("UNARY_OP: %c\n", node->operator);
            print_ast(node->operand, indent + 1);
            break;
        case NODE_FUNCTION:
            printf("FUNCTION: %s\n", node->function);
            for (int i = 0; i < node->arg_count; i++) {
                print_ast(node->args[i], indent + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGNMENT: %s =\n", node->variable);
            print_ast(node->right, indent + 1);
            break;
    }
}