# Rudis - versão 0.0.2

## METADADOS DO PROJETO
- **Nome**: Rudis
- **Versão**: 0.0.2 (Sistema de Tipos + Múltiplas Instruções + Controle de Precisão + Internacionalização Completa)
- **Filosofia**: Simplicidade, Acessibilidade, Flexibilidade
- **Paradigma**: Interpretada, Dinâmica, Multipropósito
- **Implementação**: C (interpretador)
- **Repositório**: https://github.com/arataca89/rudis
- **Data de Release**: 03/12/2025

---

## DECISÕES DE DESIGN DA VERSÃO 0.0.1 (RESUMO)

### CARACTERÍSTICAS ESTABELECIDAS:
- Sistema de tipos: único tipo numérico `double`
- Identificadores: `[a-zA-Z_][a-zA-Z0-9_]*`
- Comentários multi-estilo: `#`, `//`, `/* */`
- Fim de instrução flexível: `\n` e `;`
- Operadores matemáticos: `+`, `-`, `*`, `/`, `%`, `^`, `!` (fatorial pós-fixo)
- Sistema de atribuição encadeada
- 35+ funções built-in (matemáticas, estatísticas, financeiras)
- Sistema de numeração: decimal, hexadecimal (0x), binário (0b)
- Internacionalização: PT/EN
- REPL interativo com histórico e ajuda

---

## OBJETIVOS DE DESIGN DA VERSÃO 0.0.2

### 1. SISTEMA DE TIPOS `Value` (NOVO)
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- Unificação de todos os valores em uma única estrutura `Value`
- Suporte a três tipos primitivos: `VAL_NUMBER`, `VAL_STRING`, `VAL_NULL`
- Preparado para expansão futura (booleanos, arrays, etc.)
- Verificação de tipo em tempo de execução para segurança

**Implementação Técnica**:
```c
typedef enum {
    VAL_NUMBER,
    VAL_STRING,
    VAL_NULL
} ValueType;

typedef struct Value {
    ValueType type;
    union {
        double number;
        char string[256];
    };
} Value;
```

**Funções Auxiliares**:
```c
Value create_number_value(double num);
Value create_string_value(const char* str);
Value create_null_value(void);
void print_value(Value val, int decimal_places);
```

**Impacto no Sistema**:
- ✅ Parser: Nós da AST agora usam `Value` em vez de `double`
- ✅ Evaluator: Todas as operações verificam tipos
- ✅ Variáveis: Armazenam `Value` em vez de `double`
- ✅ REPL: Exibição unificada com `print_value()`

### 2. SUPORTE A MÚLTIPLAS INSTRUÇÕES POR LINHA
**Status**: ✅ IMPLEMENTADO

**Decisão de Design**: 
- O caractere `;` funciona como separador de instruções no REPL
- Cada instrução é processada sequencialmente
- Variáveis persistem entre instruções na mesma linha
- Mantém compatibilidade com instrução única

**Exemplo**:
```python
rudis> a=3; b=5; c=a+b; c
8.0
```

### 3. INTERNACIONALIZAÇÃO COMPLETA DO SISTEMA
**Status**: ✅ IMPLEMENTADO

**Arquivos Internacionalizados**:
- **`help.c`** - Sistema de ajuda completo em PT/EN
- **`main.c`** - Mensagens do REPL internacionalizadas
- **`evaluator.c`** - Mensagens de erro de avaliação
- **`lexer.c`** - ✅ Já internacionalizado
- **`parser.c`** - ✅ Já internacionalizado

**Mensagens Internacionalizadas**:
- Erros de sintaxe e avaliação
- Sistema de ajuda completo
- Mensagens do REPL e comandos
- Listagem de variáveis
- Confirmações de comando

**Comportamento**:
```bash
# Português (padrão)
rudis> set lang pt
rudis> 3++                 # "Erro de sintaxe na expressão"
rudis> help sqrt           # Ajuda em português

# Inglês
rudis> set lang en  
rudis> 3++                 # "Syntax error in expression"
rudis> help sqrt           # Help in English
```

### 4. TIPO STRING (HABILITADO PELO SISTEMA `Value`)
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- Strings são delimitadas por aspas duplas (`"`)
- Suporte a sequências de escape: `\n` (nova linha), `\\` (barra invertida), `\"` (aspas)
- Tamanho máximo: 256 caracteres por string
- Representação na AST: `NODE_STRING` com campo `value` do tipo `Value`

**Exemplo**:
```python
# Atribuição e uso de strings
rudis> nome = "João Silva"
"João Silva"
rudis> mensagem = "Texto\ncom\nmultilinhas"
"Texto
com
multilinhas"
rudis> caminho = "C:\\Windows\\System32"
"C:\Windows\System32"
```

### 5. CONTROLE DE CASAS DECIMAIS
**Status**: ✅ IMPLEMENTADO

**Função**: `setdec(n)`
- **Categoria**: Funções de Configuração (nova categoria)
- **Parâmetros**: `n` - número de casas decimais (0-15)
- **Padrão**: 6 casas decimais
- **Comportamento**: Modifica o `EvaluatorState`

**Implementação Técnica**:
- Uso do especificador `%.*f` para formatação dinâmica
- Validação de range (0-15 casas)
- Mensagens de erro internacionalizadas
- Função `print_value()` atualizada para receber `decimal_places`

**Exemplos**:
```python
# Padrão (6 casas)
rudis> 10/3
3.333333

# Controle de precisão
rudis> setdec(2)
rudis> 10/3
3.33

# Para valores monetários
rudis> setdec(0)
rudis> 10/3
3

# Precisão científica
rudis> setdec(8)
rudis> 1/7
0.14285714
```

### 6. NOVO COMANDO: `reset`
**Status**: ✅ IMPLEMENTADO

**Descrição**: Remove todas as variáveis do estado do evaluator
**Uso**: `reset`

**Comportamento**:
```bash
rudis> x = 10; y = 20
rudis> vars
=== VARIÁVEIS DEFINIDAS ===
  x = 10.000000
  y = 20.000000
Total: 2 variáveis

rudis> reset
Estado resetado. Todas as variáveis removidas.

rudis> vars
=== VARIÁVEIS DEFINIDAS ===
Nenhuma variável definida.
```

### 7. NOVA CATEGORIA: FUNÇÕES DE CONFIGURAÇÃO
**Status**: ✅ IMPLEMENTADO

**Organização**:
- Separa funções stateful das funções stateless
- Categoria dedicada no `execute_function()`
- Preparada para expansão futura

**Funções Atuais**:
- `setdec(n)` - Controla casas decimais da saída

---

## EXEMPLOS DA VERSÃO 0.0.2:

### SISTEMA DE TIPOS `Value`:
```python
# Números
rudis> x = 42
42.000000

# Strings  
rudis> nome = "Alice"
"Alice"

# Mix de tipos
rudis> idade = 30; nome = "Carlos"
rudis> vars
=== VARIÁVEIS DEFINIDAS ===
  idade = 30.000000
  nome = "Carlos"
Total: 2 variáveis

# Operações com verificação de tipo
rudis> 5 + "texto"
Erro: Operações aritméticas requerem números
```

### MÚLTIPLAS INSTRUÇÕES:
```python
rudis> nome = "João"; idade = 25; salario = 2500.50
rudis> salario
2500.500000

rudis> a=3; b=5; c=a*b; c
15.0
```

### STRINGS COMPLETAS:
```python
# Atribuição e uso de strings
rudis> nome = "Maria Silva"
"Maria Silva"
rudis> boas_vindas = "Bem-vindo ao Rudis v0.0.2"
"Bem-vindo ao Rudis v0.0.2"
rudis> texto_multilinha = "Linha 1\nLinha 2\nLinha 3"
"Linha 1
Linha 2
Linha 3"
```

### INTERNACIONALIZAÇÃO:
```python
# Português
rudis> set lang pt
rudis> 3++                 # "Erro de sintaxe na expressão"
rudis> x/0                 # "Divisão por zero"
rudis> sqrt()              # "sqrt requer 1 argumento"

# Inglês  
rudis> set lang en
rudis> 3++                 # "Syntax error in expression"
rudis> x/0                 # "Division by zero" 
rudis> sqrt()              # "sqrt requires 1 argument"
```

### CONTROLE DE PRECISÃO:
```python
# Aplicações práticas
rudis> setdec(2)           # Para dinheiro
rudis> 123.4567
123.46

rudis> setdec(0)           # Para contagens
rudis> 10/3
3

rudis> setdec(8)           # Para ciência
rudis> 1/7
0.14285714

# Mix de tipos com precisão
rudis> setdec(3)
rudis> pi = 3.141592653589793
3.142
rudis> nome = "π"
"π"
```

### SISTEMA DE AJUDA INTERNACIONALIZADO:
```python
rudis> set lang en
rudis> help +              # Operator: + (Addition)...
rudis> help sqrt           # Function: sqrt (Square Root)...

rudis> set lang pt  
rudis> help +              # Operador: + (Adição)...
rudis> help sqrt           # Função: sqrt (Raiz Quadrada)...
```

---

## OBSERVAÇÕES TÉCNICAS

### 1. ARQUITETURA DO SISTEMA DE TIPOS `Value`
- **Design**: Struct com enum de tipo + union para dados
- **Vantagens**: 
  - Extensibilidade fácil para novos tipos
  - Verificação de tipo em tempo de execução
  - Código mais seguro e manutenível
- **Desafios**: 
  - Conversão de código existente de `double` para `Value`
  - Verificações de tipo adicionais em operações
- **Resultado**: Base sólida para versões futuras

### 2. CORREÇÃO DE BUG CRÍTICO: `5/0`
**Problema**: Expressão `5/0` gerava erro de hexadecimal em vez de "Divisão por zero"
**Causa**: Lexer interpretava `0` seguido de `\n` como início de número hexadecimal
**Solução**: Adição de verificação explícita para `\0` após `0`:

```c
// CORREÇÃO NO lexer.c
if (lexer->current_char == '0') {
    if(lexer_peek_next(lexer) == 0) {  // Se próximo char é \0
        return lexer_read_number(lexer);  // Trata como número, não hexa
    }
    // ... resto do código
}
```

**Aprendizado**: Sempre testar casos de borda com `\0` e `\n`

### 3. MIGRAÇÃO DE `double` PARA `Value`
**Escopo da Mudança**:
- ✅ Parser: Todos os nós da AST agora usam `Value`
- ✅ Evaluator: Operações verificam tipos antes de executar
- ✅ Funções: Recebem `Value*` em vez de `double*`
- ✅ REPL: Exibição unificada via `print_value()`

**Exemplo de Refatoração**:
```c
// ANTES: double
double result = left + right;

// DEPOIS: Value
if (left.type != VAL_NUMBER || right.type != VAL_NUMBER) {
    return create_error_result("Operações aritméticas requerem números");
}
Value result = create_number_value(left.number + right.number);
```

### 4. ESPECIFICADOR `%.*f`
- **Recurso C**: Permite número dinâmico de casas decimais
- **Sintaxe**: `printf("%.*f", casas, valor)`
- **Vantagem**: Elimina necessidade de formatação manual de strings
- **Aplicação**: Usado em todas as saídas numéricas do REPL
- **Atualização**: Função `print_value()` agora recebe `decimal_places` como parâmetro

### 5. COMANDO `reset`
- **Utilidade**: Limpeza de estado durante desenvolvimento/debug
- **Implementação**: Simples chamada a `evaluator_free()` + `evaluator_init()`
- **I18N**: Mensagens bilíngues usando sistema centralizado

### 6. CATEGORIA DE CONFIGURAÇÃO
- **Inovação**: Primeira categoria de funções stateful no Rudis
- **Organização**: Separa claramente funções de cálculo vs. configuração
- **Expansão**: Base para futuras funções de controle do sistema

### 7. EXPERIÊNCIA DO USUÁRIO
- **Consistência**: Comportamento idêntico em PT/EN
- **Controle**: Precisão ajustável conforme necessidade
- **Profissionalismo**: Recursos de calculadora avançada
- **Flexibilidade**: Transição suave entre diferentes usos
- **Feedback**: Mensagens de erro claras e informativas

---

## ✅ **ESTADO ATUAL DO PROJETO**

**Progresso da v0.0.2**: 100% completo
- ✅ Sistema de tipos `Value` - 100%
- ✅ Múltiplas instruções - 100%
- ✅ Internacionalização completa - 100%  
- ✅ Controle de precisão (`setdec`) - 100%
- ✅ Tipo string - 100%
- ✅ Comando `reset` - 100%
- ✅ Correção de bug `5/0` - 100%

**Compatibilidade com v0.0.1**: 100% mantida

**Arquitetura Futura**: Base sólida para tipos adicionais (boolean, array, etc.)

---

## 🎯 VERSÕES FUTURAS (PREVIEW):

### **v0.1.0** 
  • Sistema completo de print com formatação
  
  • Cores ANSI, tabulação, campos
  
  • Parsing especial para sintaxe COR:CAMPO:valor

### **v0.2.0** 
  • Operações com strings (concatenação, comparação)
  
  • Funções string básicas

---

**Última atualização**: 03/12/2025  
**Status da versão**: ✅ PRONTA PARA RELEASE  
**Nota Técnica**: O sistema `Value` estabelece a base para todos os tipos futuros do Rudis
