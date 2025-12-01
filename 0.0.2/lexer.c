#include "lexer.h"
#include "lang.h"  

void lexer_init(Lexer* lexer, const char* input) {
    lexer->input = input;
    lexer->input_size = (int)strlen(input);
    lexer->position = 0;
    lexer->current_char = input[0];
}

void lexer_advance(Lexer* lexer) {
    lexer->position++;
    if (lexer->position >= lexer->input_size) {
        lexer->current_char = '\0';
    } else {
        lexer->current_char = lexer->input[lexer->position];
    }
}

void lexer_skip_whitespace(Lexer* lexer) {
    while (lexer->current_char != '\0' &&
           isspace(lexer->current_char)) {
        lexer_advance(lexer);
    }
}

// Retorna o próximo caractere sem avançar (lookahead)
char lexer_peek_next(Lexer* lexer) {
    if (lexer->position + 1 < lexer->input_size) {
        return lexer->input[lexer->position + 1];
    }
    return '\0';
}


// Verifica se o próximo caractere é o esperado
int lexer_peek_is(Lexer* lexer, char expected) {
    return lexer_peek_next(lexer) == expected;
}

// Verifica se o próximo caractere é um dos esperados (múltiplas opções)
int lexer_peek_in(Lexer* lexer, const char* options) {
    char next_char = lexer_peek_next(lexer);
    return strchr(options, next_char) != NULL;
}

int is_valid_identifier_char(char c) {
    return isalnum(c) || c == '_';
}

void lexer_skip_python_comment(Lexer* lexer) {
    while (lexer->current_char != '\0' && 
           lexer->current_char != '\n') {
        lexer_advance(lexer);
    }
    if (lexer->current_char == '\n') {
        lexer_advance(lexer);
    }
}

void lexer_skip_cpp_comment(Lexer* lexer) {
    while (lexer->current_char != '\0' && 
           lexer->current_char != '\n') {
        lexer_advance(lexer);
    }
    if (lexer->current_char == '\n') {
        lexer_advance(lexer);
    }
}

void lexer_skip_c_comment(Lexer* lexer) {
    while (lexer->current_char != '\0') {
        if (lexer->current_char == '*' && 
            lexer_peek_next(lexer) == '/') {
            lexer_advance(lexer);
            lexer_advance(lexer);
            break;
        }
        lexer_advance(lexer);
    }
}



/*
 * CONVERTE UMA STRING PARA DOUBLE
 * 
 * A string a ser convertida já deve ter sido verificada e
 * seu formato deve representar um double.
 * Exemplo: 123.45
 */
double lexer_str_to_double(const char* str){
    double value = 0.0;           
    double decimal_place = 0.1;   

    while (isdigit(*str) && *str) {
        int digit = *str - '0'; 
        value = value * 10 + digit;
        str++;
    }

    if (*str == '.') {
        str++;

        while (isdigit(*str) && 
               *str != '\0') {         
            int digit = *str - '0';
            value += digit * decimal_place;
            decimal_place *= 0.1;
            str++;
        }
    }

    return value;
}

/*
 * CONVERTE STRING HEXADECIMAL PARA DOUBLE
 *
 * Pré-condição: String contém apenas dígitos hexadecimais (0-9, A-F, a-f)
 * Não inclui o prefixo "0x" - apenas os dígitos
 */
double lexer_hex_str_to_double(const char* str) {
    double value = 0.0;
    
    while (*str) {
        int digit;
        
        if (isdigit(*str)) {
            digit = *str - '0';
        } else if (*str >= 'A' && *str <= 'F') {
            digit = *str - 'A' + 10;
        } else if (*str >= 'a' && *str <= 'f') {
            digit = *str - 'a' + 10;
        } else {
            break;
        }
        
        value = value * 16 + digit;
        str++;
    }
    
    return value;
}

/**
 * Converte string binária para double
 * Pré-condição: String contém apenas dígitos binários (0-1)
 * Não inclui o prefixo "0b" - apenas os dígitos
 */
double lexer_binary_str_to_double(const char* str) {
    double value = 0.0;
    
    while (*str) {
        if (*str == '0' || *str == '1') {
            int digit = *str - '0';
            value = value * 2 + digit;
        } else {
            break;
        }
        str++;
    }
    
    return value;
}

/*
 * LÊ UM NÚMERO DA ENTRADA
 *
 * O número pode ser:
 * - Inteiro: 123
 * - Decimal: 123.45
 * - Hexadecimal: 0xFF, 0x1A, 0X2B
 * 
 * Retorna um token do tipo TOKEN_NUMBER com o valor numérico.
 */
Token lexer_read_number(Lexer* lexer) {
    Token token;
    char buffer[64];
    int i = 0;

    while(isdigit(lexer->current_char) &&
                  lexer->current_char != '\0' &&
                  i < 63){
        buffer[i++] = lexer->current_char;
        lexer_advance(lexer);
    }

    if(lexer->current_char == '.'){
        buffer[i++] = lexer->current_char;
        lexer_advance(lexer);
        if(!isdigit(lexer->current_char)){
            buffer[i] = '\0';
            token.type = TOKEN_ERROR;
            strncpy(token.text, get_error_invalid_number(), sizeof(token.text) - 1);
            token.text[sizeof(token.text) - 1] = '\0';
            return token;
        }
        while(isdigit(lexer->current_char) &&
                      lexer->current_char != '\0' &&
                      i < 63){
            buffer[i++] = lexer->current_char;
            lexer_advance(lexer);
        } 
    } 

    buffer[i] = '\0';
    token.type = TOKEN_NUMBER;
    token.value = lexer_str_to_double(buffer);
    strcpy(token.text, buffer);
    return token;
}

/*
 * LÊ UM NÚMERO HEXADECIMAL
 *
 * É chamada quando o lexer já leu "0x" ou "0X"
 * current_char deve ser o primeiro dígito hexadecimal (ou erro)
 * Retorna um token do tipo TOKEN_NUMBER com o valor numérico.
 */
Token lexer_read_hexadecimal(Lexer *lexer) {
    Token token;
    char buffer[64];
    int i = 0;
    
    int has_hex_digits = 0;
    while (i < 63 && lexer->current_char != '\0' && 
           isxdigit(lexer->current_char)) {
        buffer[i++] = lexer->current_char;
        lexer_advance(lexer);
        has_hex_digits = 1;
    }
    
    if (!has_hex_digits) {
        buffer[i] = '\0';
        char error_message[100];
        snprintf(error_message, sizeof(error_message), get_error_hex_invalid(), buffer);
        return create_error_token(error_message);
    }
    
    if (i < 63 && lexer->current_char != '\0' && 
        (isalpha(lexer->current_char) || lexer->current_char == '_')) {
        
        while (i < 63 && lexer->current_char != '\0' && 
               (isalnum(lexer->current_char) || lexer->current_char == '_')) {
            buffer[i++] = lexer->current_char;
            lexer_advance(lexer);
        }
        buffer[i] = '\0';
        
        char error_message[100];
        snprintf(error_message, sizeof(error_message), get_error_hex_chars(), buffer);
        return create_error_token(error_message);
    }
    
    buffer[i] = '\0';
    token.type = TOKEN_NUMBER;
    token.value = lexer_hex_str_to_double(buffer);
    
    char display_buffer[66];
    snprintf(display_buffer, sizeof(display_buffer), "0x%s", buffer);
    strncpy(token.text, display_buffer, sizeof(token.text) - 1);
    token.text[sizeof(token.text) - 1] = '\0';
    
    return token;
}

/*
 * Lê um número binário
 * É chamada quando o lexer já leu "0b" ou "0B"
 * current_char deve ser o primeiro dígito binário (ou erro)
 * Retorna um token do tipo TOKEN_NUMBER com o valor numérico.
 */
Token lexer_read_binary(Lexer *lexer) {
    Token token;
    char buffer[64];
    int i = 0;
    
    int has_binary_digits = 0;
    while (i < 63 && lexer->current_char != '\0' && 
           (lexer->current_char == '0' || lexer->current_char == '1')) {
        buffer[i++] = lexer->current_char;
        lexer_advance(lexer);
        has_binary_digits = 1;
    }
    
    if (!has_binary_digits) {
        buffer[i] = '\0';
        char error_message[100];
        snprintf(error_message, sizeof(error_message), get_error_binary_invalid(), buffer);
        return create_error_token(error_message);
    }
    
    if (i < 63 && lexer->current_char != '\0' && 
        (isdigit(lexer->current_char) || isalpha(lexer->current_char) || 
         lexer->current_char == '_')) {
        
        while (i < 63 && lexer->current_char != '\0' && 
               (isalnum(lexer->current_char) || lexer->current_char == '_')) {
            buffer[i++] = lexer->current_char;
            lexer_advance(lexer);
        }
        buffer[i] = '\0';
        
        char error_message[100];
        snprintf(error_message, sizeof(error_message), get_error_binary_chars(), buffer);
        return create_error_token(error_message);
    }
    
    buffer[i] = '\0';
    token.type = TOKEN_NUMBER;
    token.value = lexer_binary_str_to_double(buffer);
    
    char display_buffer[66];
    snprintf(display_buffer, sizeof(display_buffer), "0b%s", buffer);
    strncpy(token.text, display_buffer, sizeof(token.text) - 1);
    token.text[sizeof(token.text) - 1] = '\0';
    
    return token;
}

/*
 * LEITURA DE IDENTIFICADORES E FUNÇÕES
 * 
 * Lê uma sequência de letras que pode ser:
 * - Uma variável: começa com letra ou _, pode ter letras, dígitos e _
 * - Uma função: sqrt, sin, mean, pv, etc.
 * 
 * Retorna TOKEN_IDENTIFIER para variáveis ou
 * TOKEN_FUNCTION para funções.
 */
Token lexer_read_identifier(Lexer* lexer) {
    Token token;
    char identifier[64];
    char error_msg[100];
    int index = 0;
    
    while (lexer->current_char != '\0' && 
           is_valid_identifier_char(lexer->current_char)) {
        identifier[index++] = lexer->current_char;
        lexer_advance(lexer);
    }
    
    identifier[index] = '\0';
    strcpy(token.text, identifier);
    
    if (is_function(identifier)) {
        token.type = TOKEN_FUNCTION;
    } else if (isalpha(identifier[0]) || identifier[0] == '_') {
        token.type = TOKEN_IDENTIFIER;
    } else {
        token.type = TOKEN_ERROR;
        sprintf(error_msg, get_error_identifier(), identifier);
        strcpy(token.text, error_msg);
    }
    
    return token;
}

/*
 * LEITURA DE STRINGS
 * 
 * Lê uma sequência de caracteres envolvidas em aspas duplas:
 * Tamanho máximo da string 256 caracteres.
 * 
 * Retorna TOKEN_STRING
 */
Token lexer_read_string(Lexer* lexer) {
    Token token;
    char string_value[256];
    char error_msg[100];
    int index = 0;
    
    char delimiter = lexer->current_char;  // " (aspas duplas)
    lexer_advance(lexer);  // Pula a aspas inicial
    
    // Lê o conteúdo da string
    while (lexer->current_char != '\0' && 
           lexer->current_char != delimiter) {
        
        // Trata caracteres de escape
        if (lexer->current_char == '\\') {
            lexer_advance(lexer);  // Pula a barra invertida
            
            if (lexer->current_char == '\0') {
                // Erro: string terminada abruptamente após \
                token.type = TOKEN_ERROR;
                sprintf(error_msg, get_error_unfinished_string(), "\\");
                strcpy(token.text, error_msg);
                return token;
            }
            
            // Processa sequência de escape
            switch (lexer->current_char) {
                case 'n':  string_value[index++] = '\n'; break;
                case 't':  string_value[index++] = '\t'; break;
                case 'r':  string_value[index++] = '\r'; break;
                case '"':  string_value[index++] = '"'; break;
                case '\\': string_value[index++] = '\\'; break;
                default:   // Escape desconhecido, mantém como está
                    string_value[index++] = '\\';
                    string_value[index++] = lexer->current_char;
                    break;
            }
            lexer_advance(lexer);
        } else {
            // Caractere normal
            string_value[index++] = lexer->current_char;
            lexer_advance(lexer);
        }
        
        // Verifica overflow do buffer
        if (index >= 255) {
            token.type = TOKEN_ERROR;
            sprintf(error_msg, get_error_string_too_long(), 255);
            strcpy(token.text, error_msg);
            return token;
        }
    }
    
    // Termina a string
    string_value[index] = '\0';
    
    // Verifica se encontrou a aspas final
    if (lexer->current_char == delimiter) {
        lexer_advance(lexer);  // Pula a aspas final
        token.type = TOKEN_STRING;
        strcpy(token.text, string_value);
    } else {
        // Erro: string não fechada
        token.type = TOKEN_ERROR;
        sprintf(error_msg, get_error_unfinished_string(), delimiter);
        strcpy(token.text, error_msg);
    }
    
    return token;
}


int is_function(const char* text) {
    // LISTA DE FUNÇÕES RUDIS
    const char* functions[] = {
        // ============ MATEMÁTICAS BÁSICAS ============
        "sqrt", "sin", "cos", "tan", "log", "ln", "exp", "abs",
        
        // ============ ESTATÍSTICAS ============
        "mean", "median", "std", "sum", "min", "max",
        "variance", "mode",  
        
        // ============ FINANCEIRAS ============
        "pv", "fv", "pmt", "nper", "rate",
        "si",           // Simple Interest
        "fv_si",        // Future Value Simple
        "ci",           // Compound Interest  
        "fv_ci",        // Future Value Compound
        "npv",          // Net Present Value - NOVA
        "irr",          // Internal Rate of Return - NOVA

        // ============ DE CONFIGURAÇÃO =====================
        "setdec",       // Ajusta o número de casas decimais

        // ============ DE ENTRADA/SAIDA =====================
        "print",       // Ajusta o número de casas decimais
        
        // ============ ALIAS/ATALHOS EM PORTUGUÊS ============
        "raiz",         // alias para sqrt
        "sen",          // alias para sin
        "cos",          // já existe
        "tan",          // já existe
        "log10",        // alias para log
        "media",        // alias para mean
        "mediana",      // alias para median
        "desvio",       // alias para std
        "soma",         // alias para sum
        "minimo",       // alias para min
        "maximo",       // alias para max
        "variancia",    // alias para variance
        "moda",         // alias para mode
        "vp",           // alias para pv (Valor Presente)
        "vf",           // alias para fv (Valor Futuro)
        "pagamento",    // alias para pmt
        "periodos",     // alias para nper
        "taxa",         // alias para rate
        "js",           // alias para si (Juros Simples)
        "montante_js",  // alias para fv_si
        "jc",           // alias para ci (Juros Compostos)
        "montante_jc",  // alias para fv_ci
        "vpl",          // alias para npv (Valor Presente Líquido)
        "tir"           // alias para irr (Taxa Interna de Retorno)

    };
    
    int num_functions = sizeof(functions) / sizeof(functions[0]);
    
    for (int i = 0; i < num_functions; i++) {
        if (strcmp(text, functions[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

Token lexer_get_next_token(Lexer* lexer) {
    char error_msg[100];
    Token token;
    
    while (lexer->current_char != '\0') {
        if (isspace(lexer->current_char)) {
            lexer_skip_whitespace(lexer);
            continue;
        }

        // COMENTÁRIOS
        if (lexer->current_char == '#') {
            lexer_skip_python_comment(lexer);
            continue;
        }
        
        if (lexer->current_char == '/') {
            if (lexer_peek_next(lexer) == '/') {
                lexer_advance(lexer);
                lexer_advance(lexer);
                lexer_skip_cpp_comment(lexer);
                continue;
            } else if (lexer_peek_next(lexer) == '*') {
                lexer_advance(lexer);
                lexer_advance(lexer);
                lexer_skip_c_comment(lexer);
                continue;
            }
        }

        // STRINGS
        if (lexer->current_char == '"') {
            return lexer_read_string(lexer);
        }

        // NÚMEROS
        if (isdigit(lexer->current_char)) {
            if (lexer->current_char == '0') {
                if (lexer_peek_in(lexer, "xX")) {
                    lexer_advance(lexer);
                    lexer_advance(lexer);
                    return lexer_read_hexadecimal(lexer);
                }
                else if (lexer_peek_in(lexer, "bB")) {
                    lexer_advance(lexer);
                    lexer_advance(lexer);
                    return lexer_read_binary(lexer);
                }
            }
            return lexer_read_number(lexer);
        }
        
        // IDENTIFICADORES E FUNÇÕES
        if (isalpha(lexer->current_char) || lexer->current_char == '_') {
            return lexer_read_identifier(lexer);
        }
        
        // OPERADORES E SÍMBOLOS
        switch (lexer->current_char) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '!':
            case '^':
                token.type = TOKEN_OPERATOR;
                token.operator = lexer->current_char;
                lexer_advance(lexer);
                return token;
                
            case '(':
                token.type = TOKEN_LPAREN;
                lexer_advance(lexer);
                return token;
                
            case ')':
                token.type = TOKEN_RPAREN;
                lexer_advance(lexer);
                return token;
                
            case ',':
                token.type = TOKEN_COMMA;
                lexer_advance(lexer);
                return token;

            case ';':
                token.type = TOKEN_SEMICOLON;
                lexer_advance(lexer);
                return token;
                
            case '=':
                token.type = TOKEN_ASSIGN;
                lexer_advance(lexer);
                return token;
                
            default:
                sprintf(error_msg, get_error_unknown_char(), lexer->current_char);
                strcpy(token.text, error_msg);
                return create_error_token(error_msg);
        }
    }
    
    token.type = TOKEN_EOF;
    return token;
}

Token create_error_token(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    strcpy(token.text, message);
    return token;
}

void lexer_print_token(Token token) {
    const char* type_names[] = {
        "NUMBER", "IDENTIFIER", "OPERATOR", "FUNCTION", 
        "LPAREN", "RPAREN", "COMMA", "ASSIGN", 
        "SEMICOLON", "COMMENT", "EOF", "ERROR", "STRING"
    };
    
    printf("[%s] ", type_names[token.type]);
    
    switch (token.type) {
        case TOKEN_STRING:
            printf("value: \"%s\"", token.text);
            break;

        case TOKEN_NUMBER:
            printf("value: %g", token.value);
            if (strlen(token.text) > 0) {
                printf(" (text: %s)", token.text);
            }
            break;
            
        case TOKEN_IDENTIFIER:
        case TOKEN_FUNCTION:
            printf("text: '%s'", token.text);
            break;
            
        case TOKEN_OPERATOR:
            printf("operator: '%c'", token.operator);
            break;
            
        case TOKEN_ERROR:
            printf("error: '%s'", token.text);
            break;
            
        case TOKEN_LPAREN:
            printf("(");
            break;
            
        case TOKEN_RPAREN:
            printf(")");
            break;
            
        case TOKEN_COMMA:
            printf(",");
            break;
            
        case TOKEN_ASSIGN:
            printf("=");
            break;
            
        case TOKEN_SEMICOLON:
            printf(";");
            break;
            
        case TOKEN_COMMENT:
            printf("comment: '%s'", token.text);
            break;
            
        case TOKEN_EOF:
            printf("END OF FILE");
            break;
    }
    
    printf("\n");
}

void lexer_print_all_tokens(const char* input) {
    Lexer lexer;
    Token token;
    
    printf("=== LEXER DEBUG ===\n");
    printf("Input: '%s'\n", input);
    printf("Tokens:\n");
    
    lexer_init(&lexer, input);
    
    int token_count = 0;
    do {
        token = lexer_get_next_token(&lexer);
        printf("%2d: ", ++token_count);
        lexer_print_token(token);
        
        if (token.type == TOKEN_ERROR) {
            printf("ERRO ENCONTRADO - parando análise\n");
            break;
        }
        
    } while (token.type != TOKEN_EOF);
    
    printf("=== FIM DA ANÁLISE ===\n\n");
}