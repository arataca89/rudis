#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "tools.h"

int main() {
    const char expr[256] = "2.65 + 3.14 * 123;\"Hello World\\nteste 1 2 3\"";
    lexer_print_all_tokens(expr);
    return 0;
}  