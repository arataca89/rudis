#ifndef VALUE_H
#define VALUE_H

#include "common.h"
#include "color.h"

typedef enum {
    VAL_NUMBER,
    VAL_STRING,
    VAL_NULL,
    VAL_ERROR
} ValueType;

typedef struct Value {
    ValueType type;
    double number;
    char string[STR_SIZE];
} Value;

Value create_number_value(double num);
Value create_string_value(const char* str);
Value create_null_value(void);
void print_value(Value val, int decimal_places);
Value number_to_string_value(double number, int decimal_places);
Value value_to_string_value(Value value, int decimal_places);



//===================================================================
// FUNÇÕES DE CORES DO TEXTO
//===================================================================
Value black(Value text);
Value red(Value text);
Value green(Value text);
Value yellow(Value text);
Value blue(Value text);
Value magenta(Value text);
Value cyan(Value text);
Value white(Value text);
Value bright_black(Value text);
Value bright_red(Value text);
Value bright_green(Value text);
Value bright_yellow(Value text);
Value bright_blue(Value text);
Value bright_magenta(Value text);
Value bright_cyan(Value text);
Value bright_white(Value text);

//===================================================================
// FUNÇÕES DE CORES DE FUNDO
//===================================================================
Value bg_black(Value text);
Value bg_red(Value text);
Value bg_green(Value text);
Value bg_yellow(Value text);
Value bg_blue(Value text);
Value bg_magenta(Value text);
Value bg_cyan(Value text);
Value bg_white(Value text);
Value bg_bright_black(Value text);
Value bg_bright_red(Value text);
Value bg_bright_green(Value text);
Value bg_bright_yellow(Value text);
Value bg_bright_blue(Value text);
Value bg_bright_magenta(Value text);
Value bg_bright_cyan(Value text);
Value bg_bright_white(Value text);

//===================================================================
// FUNÇÕES DE ESTILOS
//===================================================================
Value bold(Value text);
Value dim(Value text);
Value italic(Value text);
Value underline(Value text);
Value blink(Value text);
Value inverse(Value text);
Value hidden(Value text);
Value strikethrough(Value text);


//===================================================================
// FUNÇÕES DE ALINHAMENTO
//===================================================================
Value left(Value args[], int arg_count);
Value center(Value args[], int arg_count);
Value right(Value args[], int arg_count);

//===================================================================
// FUNÇÃO REPEAT
//===================================================================
Value repeat(Value caractere, Value quantidade);

#endif