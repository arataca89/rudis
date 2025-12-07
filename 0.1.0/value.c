#include <stdio.h>
#include <string.h>
#include <math.h>

#include "value.h"
#include "lang.h"

Value create_number_value(double num) {
    Value val;
    val.type = VAL_NUMBER;
    val.number = num;
    val.string[0] = '\0';  // String vazia
    return val;
}

Value create_string_value(const char* str) {
    Value val;
    val.type = VAL_STRING;
    val.number = 0.0;      // Número zerado
    strncpy(val.string, str, sizeof(val.string) - 1);
    val.string[sizeof(val.string) - 1] = '\0';
    return val;
}

Value create_null_value(void){
    Value val;
    val.type = VAL_NULL;
    val.number = 0.0;
    val.string[0] = '\0';
    return val;
}

void print_value(Value val, int decimal_places) {
    switch (val.type) {
        case VAL_NUMBER:
            printf("%.*f", decimal_places, val.number);
            break;
        case VAL_STRING:
            printf("%s", val.string);
            break;
        case VAL_NULL:
            printf("null");
            break;
        default:
            printf("unknown");
            break;
    }
}

Value number_to_string_value(double number, int decimal_places) {
    Value result;
    result.type = VAL_STRING;
    
    char buffer[STR_SIZE];
    
    // Casos especiais primeiro
    if (isnan(number)) {
        strcpy(result.string, "nan");
        return result;
    }
    
    if (isinf(number)) {
        if (number > 0) {
            strcpy(result.string, "inf");
        } else {
            strcpy(result.string, "-inf");
        }
        return result;
    }
    
    // Número muito grande ou muito pequeno? Usar notação científica
    if (fabs(number) >= 1e9 || (fabs(number) <= 1e-9 && number != 0)) {
        snprintf(buffer, STR_SIZE, "%g", number);
    } else {
        // Formato normal
        if (decimal_places < 0) {
            // Formato inteligente: remove .0 se for inteiro
            if (number == (int)number) {
                snprintf(buffer, STR_SIZE, "%d", (int)number);
            } else {
                snprintf(buffer, STR_SIZE, "%g", number);
            }
        } else {
            // Número fixo de casas decimais
            snprintf(buffer, STR_SIZE, "%.*f", decimal_places, number);
        }
    }
    
    // Copiar para a string do resultado
    strncpy(result.string, buffer, STR_SIZE - 1);
    result.string[STR_SIZE - 1] = '\0';
    
    return result;
}

Value value_to_string_value(Value value, int decimal_places) {
    switch (value.type) {
        case VAL_STRING:
            // Já é string, retornar cópia
            return create_string_value(value.string);
            
        case VAL_NUMBER:
            // Converter número para string
            return number_to_string_value(value.number, decimal_places);
            
        case VAL_NULL:
            // Null vira "null"
            return create_string_value("null");
            
        default:
            // Tipo desconhecido
            return create_string_value("[unknown]");
    }
}

//===================================================================
// FUNÇÕES DE CORES DO TEXTO
//===================================================================
static Value apply_ansi(Value text, const char* ansi_code) {
    if (text.type != VAL_STRING) {
        text = value_to_string_value(text, -1);
    }
    Value result;
    result.type = VAL_STRING;
    snprintf(result.string, STR_SIZE, "%s%s%s", ansi_code, text.string, RESET);
    return result;
}

// ==================== CORES DO TEXTO ====================
Value black(Value text) {
    return apply_ansi(text, BLACK);
}

Value red(Value text) {
    return apply_ansi(text, RED);
}

Value green(Value text) {
    return apply_ansi(text, GREEN);
}

Value yellow(Value text) {
    return apply_ansi(text, YELLOW);
}

Value blue(Value text) {
    return apply_ansi(text, BLUE);
}

Value magenta(Value text) {
    return apply_ansi(text, MAGENTA);
}

Value cyan(Value text) {
    return apply_ansi(text, CYAN);
}

Value white(Value text) {
    return apply_ansi(text, WHITE);
}

Value bright_black(Value text) {
    return apply_ansi(text, BRIGHT_BLACK);
}

Value bright_red(Value text) {
    return apply_ansi(text, BRIGHT_RED);
}

Value bright_green(Value text) {
    return apply_ansi(text, BRIGHT_GREEN);
}

Value bright_yellow(Value text) {
    return apply_ansi(text, BRIGHT_YELLOW);
}

Value bright_blue(Value text) {
    return apply_ansi(text, BRIGHT_BLUE);
}

Value bright_magenta(Value text) {
    return apply_ansi(text, BRIGHT_MAGENTA);
}

Value bright_cyan(Value text) {
    return apply_ansi(text, BRIGHT_CYAN);
}

Value bright_white(Value text) {
    return apply_ansi(text, BRIGHT_WHITE);
}

// ==================== CORES DE FUNDO ====================
Value bg_black(Value text) {
    return apply_ansi(text, BG_BLACK);
}

Value bg_red(Value text) {
    return apply_ansi(text, BG_RED);
}

Value bg_green(Value text) {
    return apply_ansi(text, BG_GREEN);
}

Value bg_yellow(Value text) {
    return apply_ansi(text, BG_YELLOW);
}

Value bg_blue(Value text) {
    return apply_ansi(text, BG_BLUE);
}

Value bg_magenta(Value text) {
    return apply_ansi(text, BG_MAGENTA);
}

Value bg_cyan(Value text) {
    return apply_ansi(text, BG_CYAN);
}

Value bg_white(Value text) {
    return apply_ansi(text, BG_WHITE);
}

Value bg_bright_black(Value text) {
    return apply_ansi(text, BG_BRIGHT_BLACK);
}

Value bg_bright_red(Value text) {
    return apply_ansi(text, BG_BRIGHT_RED);
}

Value bg_bright_green(Value text) {
    return apply_ansi(text, BG_BRIGHT_GREEN);
}

Value bg_bright_yellow(Value text) {
    return apply_ansi(text, BG_BRIGHT_YELLOW);
}

Value bg_bright_blue(Value text) {
    return apply_ansi(text, BG_BRIGHT_BLUE);
}

Value bg_bright_magenta(Value text) {
    return apply_ansi(text, BG_BRIGHT_MAGENTA);
}

Value bg_bright_cyan(Value text) {
    return apply_ansi(text, BG_BRIGHT_CYAN);
}

Value bg_bright_white(Value text) {
    return apply_ansi(text, BG_BRIGHT_WHITE);
}

// ==================== ESTILOS ====================
Value bold(Value text) {
    return apply_ansi(text, BOLD);
}

Value dim(Value text) {
    return apply_ansi(text, DIM);
}

Value italic(Value text) {
    return apply_ansi(text, ITALIC);
}

Value underline(Value text) {
    return apply_ansi(text, UNDERLINE);
}

Value blink(Value text) {
    return apply_ansi(text, BLINK);
}

Value inverse(Value text) {
    return apply_ansi(text, INVERSE);
}

Value hidden(Value text) {
    return apply_ansi(text, HIDDEN);
}

Value strikethrough(Value text) {
    return apply_ansi(text, STRIKETHROUGH);
}

//===================================================================
// FUNÇÕES DE ALINHAMENTO
//===================================================================

// REMOVE CÓDIGOS ANSI PARA CONTAR APENAS O TEXTO VISÍVEL:
static int visible_length(const char* str) {
    int len = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        // Detecta sequência ANSI: ESC [ ... m
        if (str[i] == '\033' && str[i+1] == '[') {
            // Pula a sequência ANSI
            i += 2; // Pula ESC [
            while (str[i] != '\0' && str[i] != 'm') {
                i++;
            }
            if (str[i] == 'm') i++;
        } else {
            // Caractere normal
            len++;
            i++;
        }
    }
    
    return len;
}

static Value apply_alignment(Value text, int width, const char* align_type) {
    if (text.type != VAL_STRING) {
        text = value_to_string_value(text, -1);
    }
    
    Value result;
    result.type = VAL_STRING;
    
    // Calcula comprimento visível (sem códigos ANSI)
    int visible_len = visible_length(text.string);
    
    if (visible_len >= width) {
        // Texto já é maior ou igual à largura visível
        // Podemos truncar mantendo códigos ANSI?
        // Por simplicidade, retornamos o texto original
        strncpy(result.string, text.string, STR_SIZE - 1);
        result.string[STR_SIZE - 1] = '\0';
    } else {
        int spaces = width - visible_len;
        
        if (strcmp(align_type, "left") == 0) {
            // Alinhamento à esquerda: texto + espaços
            // Precisamos construir manualmente para manter códigos ANSI
            strncpy(result.string, text.string, STR_SIZE - 1);
            for (int i = 0; i < spaces; i++) {
                strncat(result.string, " ", STR_SIZE - strlen(result.string) - 1);
            }
        } 
        else if (strcmp(align_type, "right") == 0) {
            // Alinhamento à direita: espaços + texto
            result.string[0] = '\0';
            for (int i = 0; i < spaces; i++) {
                strncat(result.string, " ", STR_SIZE - strlen(result.string) - 1);
            }
            strncat(result.string, text.string, STR_SIZE - strlen(result.string) - 1);
        }
        else if (strcmp(align_type, "center") == 0) {
            // Alinhamento ao centro
            int left_spaces = spaces / 2;
            int right_spaces = spaces - left_spaces;
            
            result.string[0] = '\0';
            
            // Espaços à esquerda
            for (int i = 0; i < left_spaces; i++) {
                strncat(result.string, " ", STR_SIZE - strlen(result.string) - 1);
            }
            
            // Texto
            strncat(result.string, text.string, STR_SIZE - strlen(result.string) - 1);
            
            // Espaços à direita
            for (int i = 0; i < right_spaces; i++) {
                strncat(result.string, " ", STR_SIZE - strlen(result.string) - 1);
            }
        }
    }
    
    return result;
}

// left(CAMPO, TEXTO) - Alinha à esquerda
Value left(Value args[], int arg_count) {
    if (arg_count != 2) {
        Value error;
        error.type = VAL_STRING;
        if (current_lang == LANG_PT) {
            snprintf(error.string, STR_SIZE, 
                     "Erro: left requer exatamente 2 argumentos (largura, texto)");
        } else {
            snprintf(error.string, STR_SIZE,
                     "Error: left requires exactly 2 arguments (width, text)");
        }
        return error;
    }
    
    // Primeiro argumento deve ser número (largura)
    if (args[0].type != VAL_NUMBER) {
        Value error;
        error.type = VAL_STRING;
        if (current_lang == LANG_PT) {
            snprintf(error.string, STR_SIZE,
                     "Erro: primeiro argumento de left deve ser número (largura)");
        } else {
            snprintf(error.string, STR_SIZE,
                     "Error: first argument of left must be a number (width)");
        }
        return error;
    }
    
    int width = (int)args[0].number;
    if (width < 0) width = 0;
    if (width >= STR_SIZE) width = STR_SIZE - 1;
    
    return apply_alignment(args[1], width, "left");
}

// center(CAMPO, TEXTO) - Alinha ao centro
Value center(Value args[], int arg_count) {
    if (arg_count != 2) {
        Value error;
        error.type = VAL_STRING;
        if (current_lang == LANG_PT) {
            snprintf(error.string, STR_SIZE,
                     "Erro: center requer exatamente 2 argumentos (largura, texto)");
        } else {
            snprintf(error.string, STR_SIZE,
                     "Error: center requires exactly 2 arguments (width, text)");
        }
        return error;
    }
    
    if (args[0].type != VAL_NUMBER) {
        Value error;
        error.type = VAL_STRING;
        if (current_lang == LANG_PT) {
            snprintf(error.string, STR_SIZE,
                     "Erro: primeiro argumento de center deve ser número (largura)");
        } else {
            snprintf(error.string, STR_SIZE,
                     "Error: first argument of center must be a number (width)");
        }
        return error;
    }
    
    int width = (int)args[0].number;
    if (width < 0) width = 0;
    if (width >= STR_SIZE) width = STR_SIZE - 1;
    
    return apply_alignment(args[1], width, "center");
}

// right(CAMPO, TEXTO) - Alinha à direita
Value right(Value args[], int arg_count) {
    if (arg_count != 2) {
        Value error;
        error.type = VAL_STRING;
        if (current_lang == LANG_PT) {
            snprintf(error.string, STR_SIZE,
                     "Erro: right requer exatamente 2 argumentos (largura, texto)");
        } else {
            snprintf(error.string, STR_SIZE,
                     "Error: right requires exactly 2 arguments (width, text)");
        }
        return error;
    }
    
    if (args[0].type != VAL_NUMBER) {
        Value error;
        error.type = VAL_STRING;
        if (current_lang == LANG_PT) {
            snprintf(error.string, STR_SIZE,
                     "Erro: primeiro argumento de right deve ser número (largura)");
        } else {
            snprintf(error.string, STR_SIZE,
                     "Error: first argument of right must be a number (width)");
        }
        return error;
    }
    
    int width = (int)args[0].number;
    if (width < 0) width = 0;
    if (width >= STR_SIZE) width = STR_SIZE - 1;
    
    return apply_alignment(args[1], width, "right");
}

//===================================================================
// FUNÇÃO REPEAT 
//===================================================================
Value repeat(Value caractere, Value quantidade) {
    Value result;
    result.type = VAL_STRING;
    
    // Verifica se caractere é string
    if (caractere.type != VAL_STRING) {
        if (current_lang == LANG_PT) {
            snprintf(result.string, STR_SIZE, 
                     "Erro: primeiro argumento de repeat deve ser string");
        } else {
            snprintf(result.string, STR_SIZE,
                     "Error: first argument of repeat must be a string");
        }
        return result;
    }

    // Verifica se quantidade é número
    if (quantidade.type != VAL_NUMBER) {
        if (current_lang == LANG_PT) {
            snprintf(result.string, STR_SIZE, 
                     "Erro: segundo argumento de repeat deve ser número (quantidade)");
        } else {
            snprintf(result.string, STR_SIZE,
                     "Error: second argument of repeat must be a number (count)");
        }
        return result;
    }
    
    int count = (int)quantidade.number;
    if (count < 0) count = 0;
    
    // Limita o tamanho para evitar overflow
    if (count >= STR_SIZE) {
        count = STR_SIZE - 1;
    }
    
    // Obtém o caractere a repetir
    char repeat_char = ' ';
    
    // String vazia, retorna string vazia
    if (strlen(caractere.string) == 0) {
        result.string[0] = '\0';
        return result;
    }

    // Pega o primeiro caractere da string
    repeat_char = caractere.string[0];
    
    // NULL = espaço
    if(caractere.type == VAL_NULL) {
        repeat_char = ' ';
    }
    
    // Cria a string repetida
    for (int i = 0; i < count; i++) {
        result.string[i] = repeat_char;
    }
    result.string[count] = '\0';
    
    return result;
}
