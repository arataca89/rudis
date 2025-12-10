# Linguagem Rudis - referência das funções C usadas

```
/*
 * REFERÊNCIA DE FUNÇÕES DE BIBLIOTECA C
 * Rudis Language - Versão 0.2.0
 * 
 * Lista completa das funções de biblioteca padrão C utilizadas
 * na implementação do interpretador Rudis
 * Última atualização: 10/12/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif
```

### 1. Biblioteca `<stdio.h>` - Entrada/Saída
- [`printf()`](#printf) - Saída formatada para stdout
- [`sprintf()`](#sprintf) - Saída formatada para buffer
- [`snprintf()`](#snprintf) - Saída formatada segura
- [`fprintf()`](#fprintf) - Saída formatada para stream
- [`fgets()`](#fgets) - Leitura de linha
- [`fopen()`](#fopen) - Abrir arquivo
- [`fclose()`](#fclose) - Fechar arquivo
- [`fflush()`](#fflush) - Descarregar buffer

### 2. Biblioteca `<stdlib.h>` - Utilidades Gerais
- [`malloc()`](#malloc) - Alocação de memória
- [`free()`](#free) - Liberação de memória
- [`exit()`](#exit) - Terminar programa
- [`system()`](#system) - Executar comando do sistema
- [`qsort()`](#qsort) - Ordenar array
- [`atoi()`](#atoi) - Converter string para inteiro
- [`strtod()`](#strtod) - Converter string para double

### 3. Biblioteca `<string.h>` - Manipulação de Strings
- [`strcpy()`](#strcpy) - Copiar string
- [`strncpy()`](#strncpy) - Copiar string com limite
- [`strcmp()`](#strcmp) - Comparar strings
- [`strncmp()`](#strncmp) - Comparar strings com limite
- [`strlen()`](#strlen) - Comprimento da string
- [`strncat()`](#strncat) - Concatenar strings
- [`strchr()`](#strchr) - Encontrar caractere
- [`strcspn()`](#strcspn) - Comprimento até caractere

### 4. Biblioteca `<math.h>` - Funções Matemáticas
- [`sqrt()`](#sqrt) - Raiz quadrada
- [`pow()`](#pow) - Potência
- [`log10()`](#log10) - Logaritmo base 10
- [`log()`](#log) - Logaritmo natural
- [`exp()`](#exp) - Exponencial
- [`sin()`, `cos()`, `tan()`](#sin-cos-tan) - Trigonométricas
- [`fabs()`](#fabs) - Valor absoluto
- [`isinf()`](#isinf) - Verificar infinito
- [`isnan()`](#isnan) - Verificar NaN

### 5. Biblioteca `<ctype.h>` - Classificação de Caracteres
- [`isspace()`](#isspace) - Espaço em branco
- [`isalnum()`](#isalnum) - Alfanumérico
- [`isdigit()`](#isdigit) - Dígito decimal
- [`isxdigit()`](#isxdigit) - Dígito hexadecimal
- [`isalpha()`](#isalpha) - Letra

### 6. Biblioteca `<time.h>` - Tempo e Data
- [`time_t`, `struct tm`](#time_t-struct-tm) - Tipos de tempo

### 7. Biblioteca `windows.h` (Windows)
- [`SetConsoleOutputCP()`](#setconsoleoutputcp) - UTF-8 saída
- [`SetConsoleCP()`](#setconsolecp) - UTF-8 entrada

### 8. Operadores e Palavras-chave
- [`sizeof`](#sizeof) - Tamanho em bytes
- [`size_t`](#size_t) - Tipo para tamanhos
- [`return`](#return) - Retornar de função

### 9. Estruturas e Tipos
- [`FILE`](#file) - Tipo de arquivo

---

## 1. BIBLIOTECA `<stdio.h>` - ENTRADA/SAÍDA

### <a name="printf"></a>`printf()`
```c
int printf(const char *format, ...);
```
**Descrição**: Envia saída formatada para stdout (saída padrão).

**Parâmetros**:
- `format`: String de formato com especificadores (`%d`, `%f`, `%s`, `%c`, etc.)
- `...`: Argumentos variáveis correspondentes aos especificadores

**Retorno**: Número de caracteres escritos, ou valor negativo em caso de erro.

**Exemplo**:
```c
printf("Resultado: %f\n", 3.14159);          // Resultado: 3.141590
printf("%s: %d\n", "Valor", 42);             // Valor: 42
printf(ERROR_COLOR "Erro: %s\n" RESET, msg); // Mensagem colorida
```

**Observações**:
- Usado extensivamente no REPL para mostrar resultados
- Cores ANSI são incorporadas nas strings de formato
- Especificador `%.*f` usado para casas decimais dinâmicas

### <a name="sprintf"></a>`sprintf()`
```c
int sprintf(char *str, const char *format, ...);
```
**Descrição**: Envia saída formatada para um buffer de string.

**Parâmetros**:
- `str`: Buffer de destino para a string formatada
- `format`: String de formato
- `...`: Argumentos variáveis

**Retorno**: Número de caracteres escritos (excluindo o null terminator).

**Exemplo**:
```c
char buffer[50];
sprintf(buffer, "Valor: %.2f", 3.14159);     // buffer = "Valor: 3.14"
sprintf(buffer, "Erro: %s", "Divisão por zero");
```

**Observações**:
- Usado para formatar mensagens de erro, ajuda e resultados
- Risco de buffer overflow (preferir `snprintf`)

### <a name="snprintf"></a>`snprintf()`
```c
int snprintf(char *str, size_t size, const char *format, ...);
```
**Descrição**: Versão segura de `sprintf()` com limite de tamanho.

**Parâmetros**:
- `str`: Buffer de destino
- `size`: Tamanho máximo do buffer
- `format`: String de formato
- `...`: Argumentos variáveis

**Retorno**: Número de caracteres que seriam escritos se não houvesse limite.

**Exemplo**:
```c
char buffer[256];
snprintf(buffer, sizeof(buffer), "Nome: %s", nome);
snprintf(buffer, sizeof(buffer), "%s%s%s", RED, texto, RESET);
```

**Observações**:
- Prevenção de buffer overflow crítica para segurança
- Usado em todas as formatações de strings no projeto
- `sizeof(buffer)` garante não exceder capacidade

### <a name="fprintf"></a>`fprintf()`
```c
int fprintf(FILE *stream, const char *format, ...);
```
**Descrição**: Envia saída formatada para um stream específico.

**Parâmetros**:
- `stream`: Stream de saída (`stdout`, `stderr`, arquivo)
- `format`: String de formato
- `...`: Argumentos variáveis

**Retorno**: Número de caracteres escritos.

**Exemplo**:
```c
fprintf(stderr, "Erro: %s\n", mensagem);     // Saída para erro padrão
fprintf(stdout, "Resultado: %f\n", valor);    // Equivalente a printf()
```

**Observações**:
- Usado para mensagens de erro em `stderr`
- Diferenciar saída normal de mensagens de erro

### <a name="fgets"></a>`fgets()`
```c
char *fgets(char *str, int n, FILE *stream);
```
**Descrição**: Lê uma linha de um stream (arquivo ou stdin).

**Parâmetros**:
- `str`: Buffer para armazenar a linha lida
- `n`: Número máximo de caracteres a ler
- `stream`: Stream de entrada (`stdin`, arquivo)

**Retorno**: Ponteiro para `str` em sucesso, `NULL` em erro ou EOF.

**Exemplo**:
```c
char input[256];
fgets(input, sizeof(input), stdin);           // Lê entrada do usuário

FILE *file = fopen("script.rudis", "r");
while (fgets(line, sizeof(line), file)) {
    // Processa cada linha
}
```

**Observações**:
- Inclui o newline (`\n`) na string lida
- Usado no REPL para entrada do usuário
- Usado na execução de arquivos para ler scripts

### <a name="fopen"></a>`fopen()`
```c
FILE *fopen(const char *filename, const char *mode);
```
**Descrição**: Abre um arquivo para leitura/escrita.

**Parâmetros**:
- `filename`: Nome do arquivo
- `mode`: Modo de abertura ("r", "w", "a", "rb", etc.)

**Retorno**: Ponteiro para `FILE` em sucesso, `NULL` em erro.

**Exemplo**:
```c
FILE *file = fopen("script.rudis", "r");      // Abre para leitura
if (!file) {
    fprintf(stderr, "Erro ao abrir arquivo\n");
    return;
}
```

**Observações**:
- Usado na execução de arquivos `.rudis`
- Sempre verificar retorno `NULL` para tratamento de erro

### <a name="fclose"></a>`fclose()`
```c
int fclose(FILE *stream);
```
**Descrição**: Fecha um arquivo aberto.

**Parâmetros**:
- `stream`: Ponteiro para arquivo aberto

**Retorno**: 0 em sucesso, EOF em erro.

**Exemplo**:
```c
FILE *file = fopen("script.rudis", "r");
// ... processamento ...
fclose(file);  // Libera recursos do arquivo
```

**Observações**:
- Importante para evitar vazamento de recursos
- Sempre fechar arquivos após uso

### <a name="fflush"></a>`fflush()`
```c
int fflush(FILE *stream);
```
**Descrição**: Descarga (flush) do buffer de saída.

**Parâmetros**:
- `stream`: Stream para descarregar (`stdout`)

**Retorno**: 0 em sucesso, EOF em erro.

**Exemplo**:
```c
printf("rudis> ");
fflush(stdout);  // Garante que o prompt apareça imediatamente
```

**Observações**:
- Usado no REPL para garantir prompt visível
- Importante para interfaces interativas

## 2. BIBLIOTECA `<stdlib.h>` - UTILIDADES GERAIS

### <a name="malloc"></a>`malloc()`
```c
void *malloc(size_t size);
```
**Descrição**: Aloca memória dinamicamente no heap.

**Parâmetros**:
- `size`: Número de bytes a alocar

**Retorno**: Ponteiro para memória alocada, `NULL` em falha.

**Exemplo**:
```c
int *array = malloc(10 * sizeof(int));        // Array de 10 inteiros
Variable *var = malloc(sizeof(Variable));     // Estrutura de variável
```

**Observações**:
- Usado para estruturas de dados dinâmicas (AST, variáveis)
- Sempre verificar retorno `NULL`
- Deve ser pareado com `free()`

### <a name="free"></a>`free()`
```c
void free(void *ptr);
```
**Descrição**: Libera memória alocada dinamicamente.

**Parâmetros**:
- `ptr`: Ponteiro para memória previamente alocada

**Retorno**: Nenhum.

**Exemplo**:
```c
Variable *var = malloc(sizeof(Variable));
// ... uso ...
free(var);  // Libera memória
var = NULL; // Boa prática: nullificar após free
```

**Observações**:
- Prevenção de memory leaks
- Sempre liberar o que foi alocado com `malloc()`
- Não usar ponteiro após `free()`

### <a name="exit"></a>`exit()`
```c
void exit(int status);
```
**Descrição**: Termina o programa imediatamente.

**Parâmetros**:
- `status`: Código de saída (0 = sucesso, ≠0 = erro)

**Retorno**: Nunca retorna.

**Exemplo**:
```c
if (error) {
    fprintf(stderr, "Erro crítico\n");
    exit(1);  // Termina com código de erro
}
```

**Observações**:
- Usado para erros fatais ou saída normal
- `exit(0)` para saída bem-sucedida
- Libera buffers e chama funções registradas com `atexit()`

### <a name="system"></a>`system()`
```c
int system(const char *command);
```
**Descrição**: Executa um comando do sistema operacional.

**Parâmetros**:
- `command`: Comando a executar

**Retorno**: Valor retornado pelo comando.

**Exemplo**:
```c
system("clear");      // Limpa tela no Unix/Linux
system("cls");        // Limpa tela no Windows
```

**Observações**:
- Usado no comando `clear` do REPL
- Depende do sistema operacional
- Potencial risco de segurança se usar entrada não confiável

### <a name="qsort"></a>`qsort()`
```c
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));
```
**Descrição**: Ordena um array usando algoritmo quicksort.

**Parâmetros**:
- `base`: Ponteiro para primeiro elemento do array
- `nmemb`: Número de elementos
- `size`: Tamanho de cada elemento em bytes
- `compar`: Função de comparação

**Retorno**: Nenhum.

**Exemplo**:
```c
int compare_doubles(const void *a, const void *b) {
    double da = *(const double*)a;
    double db = *(const double*)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

double values[] = {5.2, 1.7, 3.8, 2.1};
qsort(values, 4, sizeof(double), compare_doubles);
```

**Observações**:
- Usado em funções estatísticas (`median`, `mode`)
- Requer função de comparação customizada
- Ordenação in-place (modifica o array original)

### <a name="atoi"></a>`atoi()`
```c
int atoi(const char *nptr);
```
**Descrição**: Converte string para inteiro.

**Parâmetros**:
- `nptr`: String a converter

**Retorno**: Valor inteiro convertido.

**Exemplo**:
```c
int page = atoi("5");        // Converte "5" para 5
int num = atoi(argument);     // Usado no comando help
```

**Observações**:
- Usado no parser de argumentos do `help`
- Não detecta erros (preferir `strtol` para código robusto)
- Retorna 0 se conversão falhar

### <a name="strtod"></a>`strtod()`
```c
double strtod(const char *nptr, char **endptr);
```
**Descrição**: Converte string para double (ponto flutuante).

**Parâmetros**:
- `nptr`: String a converter
- `endptr`: Ponteiro para armazenar posição após conversão

**Retorno**: Valor double convertido.

**Exemplo**:
```c
char *endptr;
double num = strtod("123.45", &endptr);
double hex = strtod("0xFF", &endptr);     // Suporta hexadecimal
double sci = strtod("1.23e4", &endptr);   // Suporta notação científica
```

**Observações**:
- Usado em `input_number()` para conversão de entrada
- Suporta múltiplos formatos: decimal, hexadecimal (0x), notação científica
- Detecta overflow/underflow via variável global `errno`
- `endptr` indica onde parou a conversão (útil para validação)

## 3. BIBLIOTECA `<string.h>` - MANIPULAÇÃO DE STRINGS

### <a name="strcpy"></a>`strcpy()`
```c
char *strcpy(char *dest, const char *src);
```
**Descrição**: Copia uma string para outro buffer.

**Parâmetros**:
- `dest`: Buffer de destino
- `src`: String fonte

**Retorno**: Ponteiro para `dest`.

**Exemplo**:
```c
char dest[50];
strcpy(dest, "Hello World");  // dest = "Hello World"
```

**Observações**:
- Não verifica limites (risco de buffer overflow)
- Usado onde tamanho é conhecido e controlado
- Preferir `strncpy` quando possível

### <a name="strncpy"></a>`strncpy()`
```c
char *strncpy(char *dest, const char *src, size_t n);
```
**Descrição**: Copia no máximo n caracteres de uma string.

**Parâmetros**:
- `dest`: Buffer de destino
- `src`: String fonte
- `n`: Número máximo de caracteres a copiar

**Retorno**: Ponteiro para `dest`.

**Exemplo**:
```c
char dest[10];
strncpy(dest, "Texto longo", sizeof(dest)-1);
dest[sizeof(dest)-1] = '\0';  // Garante terminação nula
```

**Observações**:
- Mais seguro que `strcpy`
- Usado extensivamente no projeto
- Sempre garantir terminação nula manualmente

### <a name="strcmp"></a>`strcmp()`
```c
int strcmp(const char *s1, const char *s2);
```
**Descrição**: Compara duas strings.

**Parâmetros**:
- `s1`: Primeira string
- `s2`: Segunda string

**Retorno**: 
- `< 0` se `s1` < `s2`
- `0` se `s1` == `s2`
- `> 0` se `s1` > `s2`

**Exemplo**:
```c
if (strcmp(command, "help") == 0) {
    show_help();
}
if (strcmp(func.name, "sqrt") == 0) {
    return sqrt_function(args);
}
```

**Observações**:
- Usado para comparação de comandos e nomes de funções
- Comparação case-sensitive
- Retorna 0 quando strings são iguais

### <a name="strncmp"></a>`strncmp()`
```c
int strncmp(const char *s1, const char *s2, size_t n);
```
**Descrição**: Compara no máximo n caracteres de duas strings.

**Parâmetros**:
- `s1`: Primeira string
- `s2`: Segunda string
- `n`: Número máximo de caracteres a comparar

**Retorno**: Mesmo que `strcmp`, mas só para primeiros n chars.

**Exemplo**:
```c
if (strncmp(input, "help", 4) == 0) {
    // Comando começa com "help"
}
```

**Observações**:
- Usado para detecção de comandos (ex: `help`, `help 2`)
- Permite comparação parcial

### <a name="strlen"></a>`strlen()`
```c
size_t strlen(const char *s);
```
**Descrição**: Retorna o comprimento de uma string.

**Parâmetros**:
- `s`: String a medir

**Retorno**: Número de caracteres antes do null terminator.

**Exemplo**:
```c
size_t len = strlen("Hello");  // len = 5
if (strlen(input) == 0) {
    // String vazia
}
```

**Observações**:
- Usado extensivamente para verificação e manipulação de strings
- Não conta o null terminator
- Complexidade O(n)

### <a name="strncat"></a>`strncat()`
```c
char *strncat(char *dest, const char *src, size_t n);
```
**Descrição**: Concatena no máximo n caracteres de src ao final de dest.

**Parâmetros**:
- `dest`: String destino (deve ter espaço suficiente)
- `src`: String fonte
- `n`: Número máximo de caracteres a concatenar

**Retorno**: Ponteiro para `dest`.

**Exemplo**:
```c
char path[100] = "C:\\";
strncat(path, "Windows", sizeof(path)-strlen(path)-1);
```

**Observações**:
- Mais seguro que `strcat`
- Usado em concatenação de caminhos e strings
- Garante não exceder buffer

### <a name="strchr"></a>`strchr()`
```c
char *strchr(const char *s, int c);
```
**Descrição**: Localiza primeira ocorrência de um caractere em uma string.

**Parâmetros**:
- `s`: String a pesquisar
- `c`: Caractere a buscar (convertido para char)

**Retorno**: Ponteiro para primeira ocorrência, ou `NULL` se não encontrado.

**Exemplo**:
```c
char *newline = strchr(input, '\n');
if (newline) {
    *newline = '\0';  // Remove newline
}
```

**Observações**:
- Usado para processamento de entrada do usuário
- Encontrar delimitadores em strings

### <a name="strcspn"></a>`strcspn()`
```c
size_t strcspn(const char *s, const char *reject);
```
**Descrição**: Calcula comprimento do segmento inicial que NÃO contém caracteres de reject.

**Parâmetros**:
- `s`: String a analisar
- `reject`: String com caracteres a rejeitar

**Retorno**: Número de caracteres antes do primeiro caractere de reject.

**Exemplo**:
```c
size_t len = strcspn(input, "\n");  // Comprimento até newline
input[len] = '\0';  // Trunca no newline
```

**Observações**:
- Usado para remover newline de entrada do REPL
- Alternativa mais segura que `strchr` para truncamento

## 4. BIBLIOTECA `<math.h>` - FUNÇÕES MATEMÁTICAS

### <a name="sqrt"></a>`sqrt()`
```c
double sqrt(double x);
```
**Descrição**: Calcula raiz quadrada.

**Parâmetros**:
- `x`: Valor não negativo

**Retorno**: Raiz quadrada de x.

**Observações**:
- Implementa função `sqrt()` do Rudis
- Retorna `NaN` para valores negativos
- Precisão dupla

### <a name="pow"></a>`pow()`
```c
double pow(double base, double exponent);
```
**Descrição**: Calcula potência.

**Parâmetros**:
- `base`: Base
- `exponent`: Expoente

**Retorno**: `base` elevado a `exponent`.

**Observações**:
- Implementa operador `^` do Rudis
- Suporta expoentes fracionários e negativos
- Casos especiais: `pow(0,0)` = 1, `pow(x,0)` = 1

### <a name="log10"></a>`log10()`
```c
double log10(double x);
```
**Descrição**: Logaritmo na base 10.

**Parâmetros**:
- `x`: Valor positivo

**Retorno**: Log10(x).

**Observações**:
- Implementa função `log()` do Rudis
- Domínio: x > 0

### <a name="log"></a>`log()`
```c
double log(double x);
```
**Descrição**: Logaritmo natural (base e).

**Parâmetros**:
- `x`: Valor positivo

**Retorno**: ln(x).

**Observações**:
- Implementa função `ln()` do Rudis
- Mesmo que `log()` em C (natural, não base 10)

### <a name="exp"></a>`exp()`
```c
double exp(double x);
```
**Descrição**: Exponencial (e^x).

**Parâmetros**:
- `x`: Expoente

**Retorno**: e elevado a x.

**Observações**:
- Implementa função `exp()` do Rudis
- Inverso do logaritmo natural

### <a name="sin-cos-tan"></a>`sin()`, `cos()`, `tan()`
```c
double sin(double x);
double cos(double x);
double tan(double x);
```
**Descrição**: Funções trigonométricas.

**Parâmetros**:
- `x`: Ângulo em radianos

**Retorno**: Valor trigonométrico.

**Observações**:
- Implementam funções `sin()`, `cos()`, `tan()` do Rudis
- `x` deve estar em radianos
- `tan()` pode retornar valores muito grandes próximo a π/2

### <a name="fabs"></a>`fabs()`
```c
double fabs(double x);
```
**Descrição**: Valor absoluto.

**Parâmetros**:
- `x`: Valor numérico

**Retorno**: |x| (valor absoluto).

**Observações**:
- Implementa função `abs()` do Rudis
- Funciona com floats/doubles (diferente de `abs()` para inteiros)

### <a name="isinf"></a>`isinf()`
```c
int isinf(double x);
```
**Descrição**: Verifica se valor é infinito.

**Parâmetros**:
- `x`: Valor a verificar

**Retorno**: Não-zero se x é ±inf, 0 caso contrário.

**Observações**:
- Usado em `number_to_string_value()` para detectar infinito
- Importante para tratamento de casos especiais

### <a name="isnan"></a>`isnan()`
```c
int isnan(double x);
```
**Descrição**: Verifica se valor é NaN (Not a Number).

**Parâmetros**:
- `x`: Valor a verificar

**Retorno**: Não-zero se x é NaN, 0 caso contrário.

**Observações**:
- Usado em `number_to_string_value()` para detectar NaN
- Resultado de operações inválidas (sqrt(-1), 0/0, etc.)

## 5. BIBLIOTECA `<ctype.h>` - CLASSIFICAÇÃO DE CARACTERES

### <a name="isspace"></a>`isspace()`
```c
int isspace(int c);
```
**Descrição**: Verifica se caractere é espaço em branco.

**Parâmetros**:
- `c`: Caractere a verificar (convertido para unsigned char)

**Retorno**: Não-zero se é espaço, 0 caso contrário.

**Exemplo**:
```c
while (isspace(*input)) {
    input++;  // Pula espaços iniciais
}
```

**Observações**:
- Inclui: espaço, tab, newline, carriage return, etc.
- Usado no lexer para ignorar espaços em branco

### <a name="isalnum"></a>`isalnum()`
```c
int isalnum(int c);
```
**Descrição**: Verifica se caractere é alfanumérico.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Não-zero se é letra ou dígito, 0 caso contrário.

**Observações**:
- Letras (a-z, A-Z) ou dígitos (0-9)
- Usado no lexer para identificadores

### <a name="isdigit"></a>`isdigit()`
```c
int isdigit(int c);
```
**Descrição**: Verifica se caractere é dígito decimal.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Não-zero se é dígito (0-9), 0 caso contrário.

**Exemplo**:
```c
if (isdigit(*ptr)) {
    // Começa com dígito - é um número
}
```

**Observações**:
- Usado no lexer para detectar números
- Apenas dígitos decimais (0-9)

### <a name="isxdigit"></a>`isxdigit()`
```c
int isxdigit(int c);
```
**Descrição**: Verifica se caractere é dígito hexadecimal.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Não-zero se é dígito hex (0-9, a-f, A-F), 0 caso contrário.

**Exemplo**:
```c
if (isxdigit(*ptr)) {
    // Dígito hexadecimal válido
}
```

**Observações**:
- Usado no lexer para números hexadecimais (0x...)
- Inclui 0-9, a-f, A-F

### <a name="isalpha"></a>`isalpha()`
```c
int isalpha(int c);
```
**Descrição**: Verifica se caractere é letra.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Não-zero se é letra (a-z, A-Z), 0 caso contrário.

**Observações**:
- Usado no lexer para identificadores
- Apenas letras, não inclui dígitos

## 6. BIBLIOTECA `<time.h>` - TEMPO E DATA

### <a name="time_t-struct-tm"></a>Tipos: `time_t`, `struct tm`
**Descrição**: Tipos para representar tempo.

**Exemplo**:
```c
time_t now = time(NULL);
struct tm *local = localtime(&now);
```

**Observações**:
- Usado para timestamp de compilação no banner
- `__DATE__` e `__TIME__` são macros do pré-processador

## 7. BIBLIOTECA WINDOWS.H (APENAS WINDOWS)

### <a name="setconsoleoutputcp"></a>`SetConsoleOutputCP()`
```c
BOOL SetConsoleOutputCP(UINT wCodePageID);
```
**Descrição**: Define a página de código de saída do console.

**Parâmetros**:
- `wCodePageID`: Código da página (CP_UTF8 = 65001)

**Retorno**: Não-zero em sucesso, 0 em erro.

**Observações**:
- Usado para suporte a UTF-8 no Windows
- Necessário para caracteres acentuados

### <a name="setconsolecp"></a>`SetConsoleCP()`
```c
BOOL SetConsoleCP(UINT wCodePageID);
```
**Descrição**: Define a página de código de entrada do console.

**Parâmetros**:
- `wCodePageID`: Código da página (CP_UTF8 = 65001)

**Retorno**: Não-zero em sucesso, 0 em erro.

**Observações**:
- Configura entrada UTF-8 no Windows
- Pareado com `SetConsoleOutputCP()`

## 8. OPERADORES E PALAVRAS-CHAVE DA LINGUAGEM C

### <a name="sizeof"></a>`sizeof`
**Descrição**: Operador que retorna tamanho em bytes de um tipo ou variável.

**Exemplo**:
```c
char buffer[256];
size_t size = sizeof(buffer);          // size = 256
size_t elem_size = sizeof(double);     // elem_size = 8 (normalmente)
```

**Observações**:
- Avaliado em tempo de compilação
- Usado com `malloc()` e `strncpy()` para segurança
- Retorna `size_t`

### <a name="size_t"></a>`size_t`
**Descrição**: Tipo inteiro sem sinal para tamanhos.

**Observações**:
- Usado para índices, tamanhos e contagens
- Garante portabilidade entre arquiteturas
- Retorno de `strlen()`, `sizeof`, etc.

### <a name="return"></a>`return`
**Descrição**: Retorna controle da função ao chamador.

**Observações**:
- Pode retornar valor ou apenas controle
- Funções `void` podem usar `return` sem valor
- Ponto de saída padrão de funções

## 9. ESTRUTURAS E TIPOS PERSONALIZADOS

### <a name="file"></a>`FILE`
**Descrição**: Tipo opaque para streams de arquivo.

**Observações**:
- Manipulado apenas por funções da biblioteca padrão
- Ponteiro `FILE*` usado em todas operações de arquivo

## RESUMO DE USO POR MÓDULO

### **`main.c`**:
- `printf`, `fprintf`, `fgets`, `fopen`, `fclose`, `fflush`, `exit`
- `strcmp`, `strncmp`, `strlen`, `strcspn`, `system`
- `SetConsoleOutputCP`, `SetConsoleCP` (Windows)

### **`lexer.c`**:
- `isspace`, `isalnum`, `isdigit`, `isxdigit`, `isalpha`
- `strcmp`, `strncmp`

### **`parser.c`**:
- `malloc`, `free`
- `strcmp`, `strncmp`, `strcpy`, `strncpy`

### **`evaluator.c`**:
- `sqrt`, `pow`, `log10`, `log`, `exp`, `sin`, `cos`, `tan`, `fabs`
- `isinf`, `isnan`
- `strcmp`, `strncmp`, `qsort`
- `malloc`, `free`, `strtod` (NOVO)

### **`value.c`**:
- `snprintf`, `sprintf`, `strncpy`, `strncat`, `strlen`, `memset`
- `isinf`, `isnan`, `fabs`, `pow`, `sqrt`, `log10`, `log`, `exp`, `sin`, `cos`, `tan`
- `malloc`, `free`

### **`help.c`**:
- `printf`, `snprintf`
- `strcmp`

### **`lang.c`**:
- `strcmp`

---

**NOTAS FINAIS**:
1. **Segurança**: Uso predominante de funções seguras (`snprintf`, `strncpy`, `strncat`)
2. **Portabilidade**: Código funciona em Windows (com UTF-8) e Unix/Linux
3. **Memória**: Gerenciamento manual com `malloc`/`free`, sem garbage collection
4. **Performance**: Operações matemáticas delegadas à biblioteca C otimizada
5. **Manutenção**: Documentação completa de todas dependências externas
6. **NOVO NA 0.2.0**: Função `strtod()` adicionada para suporte a `input_number()`
