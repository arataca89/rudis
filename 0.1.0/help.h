#ifndef HELP_H
#define HELP_H

#include "color.h"

// Funções de ajuda
void print_general_help(void);
void print_function_help(const char* function_name);
void print_help_page(int page);
int get_total_help_pages(void);

#endif // HELP_H