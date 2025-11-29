## 📚 **Linguagem Rudis - referência das funções C usadas**

```c
/*
 * REFERÊNCIA DE FUNÇÕES DE BIBLIOTECA C
 * Rudis Language
 * 
 * Lista completa das funções de biblioteca padrão C utilizadas
 * na implementação do Rudis 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
```

---

## **1. BIBLIOTECA <stdio.h> - ENTRADA/SAÍDA**

### **printf()**
```c
int printf(const char *format, ...);
```
**Descrição**: Envia saída formatada para stdout.

**Parâmetros**:
- `format`: String de formato com especificadores (%d, %f, %s, etc.)
- `...`: Argumentos variáveis correspondentes aos especificadores

**Retorno**: Número de caracteres escritos, ou negativo em caso de erro.

**Exemplo**:
```c
printf("Resultado: %f\n", 3.14159);  // Resultado: 3.141590
printf("%s: %d\n", "Valor", 42);     // Valor: 42
```

**Observações**:
- Usado extensivamente no REPL para mostrar resultados
- Cores ANSI são incorporadas nas strings de formato

---

### **sprintf()**
```c
int sprintf(char *str, const char *format, ...);
```
**Descrição**: Envia saída formatada para uma string.

**Parâmetros**:
- `str`: Buffer de destino para a string formatada
- `format`: String de formato
- `...`: Argumentos variáveis

**Retorno**: Número de caracteres escritos (excluindo o null terminator).

**Exemplo**:
```c
char buffer[50];
sprintf(buffer, "Valor: %.2f", 3.14159);  // buffer = "Valor: 3.14"
```

**Observações**:
- Usado para formatar mensagens de erro e ajuda

---

## **2. BIBLIOTECA <stdlib.h> - FUNÇÕES GERAIS**

### **malloc()**
```c
void *malloc(size_t size);
```
**Descrição**: Aloca memória dinamicamente.

**Parâmetros**:
- `size`: Número de bytes a alocar

**Retorno**: Ponteiro para a memória alocada, ou NULL em caso de erro.

**Exemplo**:
```c
int *arr = malloc(10 * sizeof(int));  // Aloca array de 10 inteiros
```

**Observações**:
- Fundamental para o gerenciamento de AST nodes e tokens
- Sempre verificar retorno NULL

---

### **free()**
```c
void free(void *ptr);
```
**Descrição**: Libera memória alocada dinamicamente.

**Parâmetros**:
- `ptr`: Ponteiro para a memória a ser liberada

**Retorno**: Nenhum.

**Exemplo**:
```c
free(arr);  // Libera memória previamente alocada
```

**Observações**:
- Usado em conjunto com malloc para evitar memory leaks
- Chamado ao liberar AST nodes e buffers

---

### **strtod()**
```c
double strtod(const char *str, char **endptr);
```
**Descrição**: Converte string para double.

**Parâmetros**:
- `str`: String a ser convertida
- `endptr`: Ponteiro para armazenar posição final da conversão

**Retorno**: Valor double convertido.

**Exemplo**:
```c
char *end;
double num = strtod("3.14", &end);  // num = 3.14
```

**Observações**:
- Pode ser usado no lexer para converter números, em vez da implementação manual feita
- `endptr` permite verificar se a conversão foi completa

---

### **abs()**
```c
int abs(int j);
```
**Descrição**: Retorna valor absoluto de inteiro.

**Parâmetros**:
- `j`: Valor inteiro

**Retorno**: Valor absoluto do inteiro.

**Exemplo**:
```c
int val = abs(-5);  // val = 5
```

---

## **3. BIBLIOTECA <string.h> - MANIPULAÇÃO DE STRINGS**

### **strlen()**
```c
size_t strlen(const char *str);
```
**Descrição**: Calcula comprimento de uma string.

**Parâmetros**:
- `str`: String a ser medida

**Retorno**: Comprimento da string (excluindo null terminator).

**Exemplo**:
```c
int len = strlen("Rudis");  // len = 5
```

**Observações**:
- Usado para validar inputs vazios no REPL

---

### **strcmp()**
```c
int strcmp(const char *str1, const char *str2);
```
**Descrição**: Compara duas strings.

**Parâmetros**:
- `str1`, `str2`: Strings a comparar

**Retorno**:
- `< 0` se str1 < str2
- `0` se str1 == str2  
- `> 0` se str1 > str2

**Exemplo**:
```c
if (strcmp(command, "help") == 0) {
    // Comando help detectado
}
```

**Observações**:
- Usado para identificar comandos do sistema (help, clear, vars)

---

### **strncmp()**
```c
int strncmp(const char *str1, const char *str2, size_t n);
```
**Descrição**: Compara primeiros n caracteres de duas strings.

**Parâmetros**:
- `str1`, `str2`: Strings a comparar
- `n`: Número máximo de caracteres a comparar

**Retorno**: Mesmo que strcmp, mas apenas para n caracteres.

**Exemplo**:
```c
if (strncmp(input, "help", 4) == 0) {
    // Input começa com "help"
}
```

**Observações**:
- Usado para detectar comandos com argumentos ("help sqrt")

---

### **strcpy()**
```c
char *strcpy(char *dest, const char *src);
```
**Descrição**: Copia string de origem para destino.

**Parâmetros**:
- `dest`: Buffer de destino
- `src`: String de origem

**Retorno**: Ponteiro para dest.

**Exemplo**:
```c
char dest[20];
strcpy(dest, "Rudis");  // dest = "Rudis"
```

---

### **strchr()**
```c
char *strchr(const char *str, int c);
```
**Descrição**: Localiza primeira ocorrência de caractere em string.

**Parâmetros**:
- `str`: String onde buscar
- `c`: Caractere a buscar

**Retorno**: Ponteiro para a ocorrência, ou NULL se não encontrado.

**Exemplo**:
```c
char *dot = strchr("3.14", '.');  // dot aponta para '.14'
```

**Observações**:
- Usado no lexer para detectar pontos decimais em números

---

### **strdup()** 

```c
char *strdup(const char *s);
```


**Descrição**: Duplica uma string (aloca e copia).

**Parâmetros**:
- `s`: String a ser duplicada

**Retorno**: Ponteiro para nova string, ou NULL em caso de erro.

**Exemplo**:
```c
char *copy = strdup("Rudis");
// Equivale a: malloc + strcpy
```

**Observações**:
- **Não é ANSI C** mas amplamente suportada
- Usada para fazer cópias seguras de strings
- **IMPORTANTE**: Sempre chamar free() depois

---

### **strtok()** 

```c
char *strtok(char *str, const char *delim);
```

**Descrição**: Divide string em tokens usando delimitadores.

**Parâmetros**:
- `str`: String a tokenizar (NULL para continuar tokenização)
- `delim`: String com caracteres delimitadores

**Retorno**: Ponteiro para próximo token, ou NULL se não há mais tokens.

**Exemplo**:
```c
char data[] = "a=1;b=2;c=3";
char *token = strtok(data, ";");  // "a=1"
while (token) {
    process(token);
    token = strtok(NULL, ";");    // "b=2", depois "c=3"
}
```

**Observações**:
- **Modifica a string original** - substitui delimitadores por '\0'
- **Não é thread-safe** - mantém estado interno
- Usada para parsing de comandos com múltiplas instruções

---

### **snprintf()** 

```c
int snprintf(char *str, size_t size, const char *format, ...);
```

**Descrição**: Versão segura de sprintf com limite de tamanho.

**Parâmetros**:
- `str`: Buffer de destino
- `size`: Tamanho máximo do buffer (incluindo '\0')
- `format`: String de formato
- `...`: Argumentos variáveis

**Retorno**: Número de caracteres que seriam escritos (excluindo '\0').

**Exemplo**:
```c
char buf[20];
int needed = snprintf(buf, sizeof(buf), "Result: %f", value);
if (needed >= sizeof(buf)) {
    // Buffer muito pequeno
}
```

**Observações**:
- Previne buffer overflow
- Retorna quantos caracteres seriam necessários
- Usada para formatação segura de mensagens

---

### **memset()** 

```c
void *memset(void *s, int c, size_t n);
```

**Descrição**: Preenche memória com um byte constante.

**Parâmetros**:
- `s`: Ponteiro para a memória
- `c`: Valor a preencher (convertido para unsigned char)
- `n`: Número de bytes a preencher

**Retorno**: Ponteiro para s.

**Exemplo**:
```c
struct Config config;
memset(&config, 0, sizeof(config));  // Zera toda a estrutura
```

**Observações**:
- Usada para inicialização de estruturas e arrays
- Eficiente para zerar grandes blocos de memória

---

## **4. BIBLIOTECA <math.h> - FUNÇÕES MATEMÁTICAS**

### **sqrt()**
```c
double sqrt(double x);
```
**Descrição**: Calcula raiz quadrada.

**Parâmetros**:
- `x`: Valor não negativo

**Retorno**: Raiz quadrada de x.

**Exemplo**:
```c
double raiz = sqrt(25.0);  // raiz = 5.0
```

**Observações**:
- Implementa a função `sqrt()` do Rudis
- Retorna erro se x < 0

---

### **sin(), cos(), tan()**
```c
double sin(double x);
double cos(double x); 
double tan(double x);
```
**Descrição**: Funções trigonométricas (seno, cosseno, tangente).

**Parâmetros**:
- `x`: Ângulo em radianos

**Retorno**: Valor da função trigonométrica.

**Exemplo**:
```c
double s = sin(3.14159);  // s ≈ 0
```

**Observações**:
- Implementam funções trigonométricas do Rudis
- Trabalham com radianos

---

### **log(), log10()**
```c
double log(double x);     // Logaritmo natural (base e)
double log10(double x);   // Logaritmo base 10
```
**Descrição**: Funções logarítmicas.

**Parâmetros**:
- `x`: Valor positivo

**Retorno**: Logaritmo de x.

**Exemplo**:
```c
double ln = log(2.71828);  // ln ≈ 1.0
double log10 = log10(100); // log10 = 2.0
```

**Observações**:
- `log()` implementa `ln()` no Rudis
- `log10()` implementa `log()` no Rudis

---

### **exp()**
```c
double exp(double x);
```
**Descrição**: Função exponencial (e elevado a x).

**Parâmetros**:
- `x`: Expoente

**Retorno**: e^x

**Exemplo**:
```c
double e = exp(1.0);  // e ≈ 2.71828
```

---

### **pow()**
```c
double pow(double base, double exponent);
```
**Descrição**: Calcula potência (base elevada ao expoente).

**Parâmetros**:
- `base`: Base
- `exponent`: Expoente

**Retorno**: base^exponent

**Exemplo**:
```c
double p = pow(2, 8);  // p = 256.0
```

**Observações**:
- Implementa o operador `^` do Rudis

---

### **fabs()**
```c
double fabs(double x);
```
**Descrição**: Valor absoluto para doubles.

**Parâmetros**:
- `x`: Valor double

**Retorno**: Valor absoluto de x.

**Exemplo**:
```c
double abs_val = fabs(-3.14);  // abs_val = 3.14
```

**Observações**:
- Implementa a função `abs()` do Rudis

---

## **5. BIBLIOTECA <ctype.h> - CLASSIFICAÇÃO DE CARACTERES**

### **isalpha()**
```c
int isalpha(int c);
```
**Descrição**: Verifica se caractere é alfabético.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Diferente de zero se for alfabético, zero caso contrário.

**Exemplo**:
```c
if (isalpha('A')) {  // Verdadeiro
    // É letra
}
```

**Observações**:
- Usado no lexer para identificar início de identificadores

---

### **isdigit()**
```c
int isdigit(int c);
```
**Descrição**: Verifica se caractere é dígito decimal.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Diferente de zero se for dígito, zero caso contrário.

**Exemplo**:
```c
if (isdigit('5')) {  // Verdadeiro
    // É dígito
}
```

**Observações**:
- Usado no lexer para identificar números

---

### **isalnum()**
```c
int isalnum(int c);
```
**Descrição**: Verifica se caractere é alfanumérico.

**Parâmetros**:
- `c`: Caractere a verificar

**Retorno**: Diferente de zero se for alfanumérico, zero caso contrário.

**Exemplo**:
```c
if (isalnum('a')) {  // Verdadeiro
    // É letra ou dígito
}
```

**Observações**:
- Usado no lexer para identificar corpo de identificadores

---

## 📊 **ESTATÍSTICAS DE USO**

| Biblioteca | Funções Usadas | Propósito Principal |
|------------|----------------|---------------------|
| `stdio.h` | 4 | Entrada/saída do REPL |
| `stdlib.h` | 6 | Gerenciamento de memória |
| `string.h` | 8 | Manipulação de strings |
| `math.h` | 10 | Funções matemáticas |
| `ctype.h` | 3 | Análise léxica |

**Total: 31 funções de biblioteca**

---

## 💡 **OBSERVAÇÕES GERAIS:**

1. **Gerenciamento de Memória**: Uso intensivo de `malloc/free` para AST e tokens
2. **Segurança**: Verificações de NULL e validação de inputs
3. **Performance**: Funções matemáticas otimizadas da libc
4. **Portabilidade**: Funções padrão ANSI C garantem compatibilidade

Esta referência será atualizada a cada nova versão do Rudis com as funções adicionais utilizadas.

---


**Última atualização**: 29 de Novembro de 2025  

---

arataca89@gmail.com