# Rudis - versão 0.1.0

## METADADOS DO PROJETO
- **Nome**: Rudis
- **Versão**: 0.1.0 (Sistema Avançado de Output + Linha de Comando Completa + Cores ANSI)
- **Filosofia**: Simplicidade, Acessibilidade, Flexibilidade
- **Paradigma**: Interpretada, Dinâmica, Multipropósito
- **Implementação**: C (interpretador)
- **Repositório**: https://github.com/arataca89/rudis
- **Data de Release**: 07/12/2025

---

## RESUMO DAS VERSÕES ANTERIORES

### VERSÃO 0.0.1 (BASE)
- Sistema de tipos: único tipo numérico `double`
- Identificadores: `[a-zA-Z_][a-zA-Z0-9_]*`
- Comentários multi-estilo: `#`, `//`, `/* */`
- Fim de instrução flexível: `\n` e `;`
- Operadores matemáticos: `+`, `-`, `*`, `/`, `%`, `^`, `!` (fatorial pós-fixo)
- Sistema de atribuição encadeada
- 35+ funções built-in (matemáticas, estatísticas, financeiras)
- Sistema de numeração: decimal, hexadecimal (0x), binário (0b)
- REPL interativo com histórico e ajuda básica

### VERSÃO 0.0.2 (SISTEMA DE TIPOS + INTERNACIONALIZAÇÃO)
- ✅ **Sistema de tipos `Value`**: `VAL_NUMBER`, `VAL_STRING`, `VAL_NULL`
- ✅ **Múltiplas instruções**: Suporte a `;` como separador
- ✅ **Internacionalização completa**: PT/EN em todo o sistema
- ✅ **Controle de precisão**: Função `setdec(n)` (0-15 casas)
- ✅ **Comando `reset`**: Limpeza completa de variáveis
- ✅ **Correção crítica**: Bug `5/0` (divisão por zero vs. erro de hexa)

---

## DESIGN DA VERSÃO 0.1.0

### 1. OPERADOR `+` PARA CONCATENAÇÃO DE STRINGS
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- Extensão do operador `+` para suportar strings
- Comportamento polimórfico: números → soma, strings → concatenação
- Conversão automática número→string quando necessário
- Outros operadores matemáticos mantêm restrição a números

**Comportamento**:
```python
# 1. String + String → Concatenação
rudis> "Hello" + "World"           # "HelloWorld"
rudis> "Hello" + " " + "World"     # "Hello World"

# 2. String + Número → Conversão e concatenação  
rudis> "Idade: " + 25              # "Idade: 25"
rudis> "Preço: R$ " + 99.99        # "Preço: R$ 99.99"

# 3. Número + String → Conversão e concatenação
rudis> 10 + " apples"              # "10 apples"
rudis> 3.14 + " é pi"              # "3.14 é pi"

# 4. Número + Número → Soma (comportamento original mantido)
rudis> 10 + 5                      # 15
rudis> 3.14 + 2.86                 # 6.0

# 5. Outros operadores com strings → ERRO
rudis> "10" - "5"                  # ERRO: "Operações aritméticas requerem números"
rudis> "a" * "b"                   # ERRO: "Operações aritméticas requerem números"
```

**Implementação Técnica**:
```c
// value.c - Sistema de Conversão de Tipos
Value number_to_string_value(double number, int decimal_places);
Value value_to_string_value(Value value, int decimal_places);

// evaluator.c - Sistema de Concatenação
EvaluatorResult string_concatenate(EvaluatorResult* left, 
                                   EvaluatorResult* right,
                                   int decimal_places);

// Formatação inteligente: inteiros não mostram ".000000"
if (number == (int)number) {
    snprintf(buffer, STR_SIZE, "%d", (int)number);  // 25 → "25"
} else {
    snprintf(buffer, STR_SIZE, "%.*f", decimal_places, number);
}
```

### 2. SISTEMA COMPLETO DE CORES ANSI (34 FUNÇÕES)
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- 34 funções específicas em vez de função genérica `color()`
- Reset automático após cada aplicação
- Funções não podem ser usadas como nomes de variáveis
- Documentação completa integrada ao sistema de ajuda

**Funções Implementadas**:
```c
// CORES DO TEXTO (16)
black(), red(), green(), yellow(), blue(), magenta(), cyan(), white()
bright_black(), bright_red(), bright_green(), bright_yellow()
bright_blue(), bright_magenta(), bright_cyan(), bright_white()

// CORES DE FUNDO (16)
bg_black(), bg_red(), bg_green(), bg_yellow(), bg_blue(), bg_magenta()
bg_cyan(), bg_white(), bg_bright_black(), bg_bright_red()
bg_bright_green(), bg_bright_yellow(), bg_bright_blue()
bg_bright_magenta(), bg_bright_cyan(), bg_bright_white()

// ESTILOS DE TEXTO (8)
bold(), dim(), italic(), underline(), blink(), inverse(), hidden(), strikethrough()
```

**Comportamento**:
```python
# Uso básico
rudis> red("Erro!")                     # Texto vermelho
rudis> green("Sucesso!")                # Texto verde
rudis> bold("Importante")               # Texto em negrito

# Combinações aninhadas
rudis> bold(red("ERRO CRÍTICO!"))       # Texto vermelho em negrito
rudis> underline(blue("Link"))          # Texto azul sublinhado
rudis> bg_red(white(" ALERTA "))        # Fundo vermelho com texto branco

# Composição com operador +
rudis> red("Erro: ") + yellow("Aviso")  # "Erro: " vermelho + "Aviso" amarelo

# Funções como palavras reservadas
rudis> red("texto")                     # ✓ Funciona como função
rudis> red = 5                          # ✗ Erro: Esperado '(' após nome da função
rudis> x = red("teste")                 # ✓ Pode atribuir resultado a variável
```

**Implementação Técnica**:
```c
// value.c - Função genérica para evitar repetição
static Value apply_ansi(Value text, const char* ansi_code) {
    if (text.type != VAL_STRING) {
        text = value_to_string_value(text, -1);
    }
    Value result;
    result.type = VAL_STRING;
    snprintf(result.string, STR_SIZE, "%s%s%s", ansi_code, text.string, RESET);
    return result;
}

// Cada função específica chama apply_ansi()
Value red(Value text) { return apply_ansi(text, RED); }
Value bold(Value text) { return apply_ansi(text, BOLD); }
// ... 32 outras funções
```

### 3. FUNÇÕES DE FORMATAÇÃO DE TEXTO
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- Funções específicas para alinhamento: `left()`, `center()`, `right()`
- Função `repeat()` para criação de separadores
- Assinatura consistente: `Value func(Value arg1, Value arg2)`
- Conversão automática de tipos

**Funções Implementadas**:
```python
# left(largura, texto) - Alinhamento à esquerda
rudis> left(30, "Texto")           # "Texto                         "
rudis> print("[" + left(10,"teste") + "]")  # "[teste     ]"

# center(largura, texto) - Alinhamento ao centro  
rudis> center(30, "Texto")         # "            Texto            "
rudis> print("[" + center(10,"teste") + "]")  # "[  teste   ]"

# right(largura, texto) - Alinhamento à direita
rudis> right(30, "Texto")          # "                         Texto"
rudis> print("[" + right(10,"teste") + "]")   # "[     teste]"

# repeat(caractere, quantidade) - Repetição
rudis> repeat("-", 40)             # "----------------------------------------"
rudis> repeat("*", 20)             # "********************"
rudis> green(repeat("=", 70))      # Linha verde de 70 caracteres
```

**Implementação Técnica**:
```c
// Função auxiliar para alinhamento
static Value apply_alignment(Value text, int width, const char* align_type) {
    // Implementação usando printf com width dinâmico
    if (strcmp(align_type, "left") == 0) {
        snprintf(result.string, STR_SIZE, "%-*s", width, temp);
    } else if (strcmp(align_type, "right") == 0) {
        snprintf(result.string, STR_SIZE, "%*s", width, temp);
    }
    // ... implementação de center
}

// Funções públicas com verificação de tipos
Value left(Value largura, Value texto) {
    if (largura.type != VAL_NUMBER) {
        // Retorna erro: primeiro argumento deve ser número
    }
    int width = (int)largura.number;
    return apply_alignment(texto, width, "left");
}
```

### 4. SISTEMA DE LINHA DE COMANDO COMPLETO
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- Interface padrão seguindo convenções de outras linguagens
- Modo REPL como padrão (sem argumentos)
- Execução de arquivos simples: `rudis arquivo.rudis`
- Opção `-e` para one-liners (inspirado em Perl/Python)

**Sintaxe de Linha de Comando**:
```bash
rudis                     # Modo REPL interativo (padrão)
rudis script.rudis        # Executa arquivo (caso mais comum)
rudis -e "código"         # Executa código inline (one-liner)
rudis -h, --help          # Mostra ajuda da linha de comando
rudis -v, --version       # Mostra versão
rudis --lang pt|en        # Define idioma (mantido da v0.0.2)
```

**Implementação Técnica**:
```c
// Estrutura para argumentos
typedef struct {
    int show_help;
    int show_version;
    int interactive_mode;
    int execute_string;
    char* filename;
    char* code_string;
    int has_error;
    char error_message[256];
} CommandLineArgs;

// Parser de argumentos
CommandLineArgs parse_arguments(int argc, char *argv[]) {
    // Lógica para detectar -h, -v, -e, arquivos, etc.
}

// Execução de arquivo
int execute_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    // Lê linha por linha, chama process_input()
}

// Execução de string (-e)
void execute_string(const char* code) {
    process_input(code);  // Reusa mesma engine do REPL
}
```

**Exemplos de Uso**:
```bash
# 1. Cálculos rápidos no terminal
rudis -e "pv(0.05, 10, 100)"
rudis -e "mean(1,2,3,4,5)"
rudis -e "print(bold(red('ERRO!')))"

# 2. Executar scripts
rudis relatorio_financeiro.rudis

# 3. Pipeline em shell scripts
echo "1 2 3 4 5" | xargs rudis -e "mean($@)"

# 4. Modo REPL interativo
rudis
```

### 5. SISTEMA DE AJUDA EXPANDIDO (PÁGINA 5)
**Status**: ✅ IMPLEMENTADO COMPLETAMENTE

**Decisão de Design**:
- Página 5 dedicada a cores e estilos
- Documentação completa para todas as 34 funções de cores
- Exemplos práticos de uso e combinações
- Integração na ajuda geral

**Acesso**:
```bash
rudis> help 5                    # Página completa de cores
rudis> help red                  # Ajuda específica da função red
rudis> help bold                 # Ajuda específica da função bold
```

**Conteúdo da Página 5**:
- **16 cores de texto** (normais e brilhantes)
- **16 cores de fundo** (prefixo `bg_`)
- **8 estilos de texto** (negrito, sublinhado, itálico, etc.)
- **Exemplos práticos** de combinações
- **Casos de uso** realistas (alertas, tabelas, destaques)

---

## EXEMPLOS COMPLETOS DA VERSÃO 0.1.0:

### EXEMPLO 1: RELATÓRIO FORMATADO COM CORES
```python
# Configura precisão para dinheiro
setdec(2)

# Dados
receita = 50000.75
despesa = 32500.30
lucro = receita - despesa

# Relatório formatado
print(bold(green(repeat("=", 60))))
print(center(60, bold("RELATÓRIO FINANCEIRO")))
print(bold(green(repeat("=", 60))))

print("Receita:  " + right(20, green(string(receita))))
print("Despesa:  " + right(20, red(string(despesa))))
print(repeat("-", 40))
print("Lucro:    " + right(20, bold(cyan(string(lucro)))))

print(bold(green(repeat("=", 60))))
```

### EXEMPLO 2: TABELA COM BORDAS DECORATIVAS
```python
# Cabeçalho decorativo
print(bold(cyan(repeat("═", 50))))
print(center(50, bold(blue("TABELA DE PRODUTOS"))))
print(bold(cyan(repeat("═", 50))))

# Cabeçalho da tabela
print(left(20, "PRODUTO") + center(10, "QTD") + right(15, "PREÇO"))

# Separador
print(repeat("-", 45))

# Dados
print(left(20, "Caneta") + center(10, "100") + right(15, "2.50"))
print(left(20, "Caderno") + center(10, "50") + right(15, "15.99"))
print(left(20, "Borracha") + center(10, "200") + right(15, "1.25"))

# Rodapé
print(bold(cyan(repeat("═", 50))))
```

---

## OBSERVAÇÕES TÉCNICAS

### 1. ARQUITETURA DO SISTEMA DE CORES
- **Abordagem**: 34 funções específicas vs. função genérica `color()`
- **Vantagens**: Mais intuitivo para o usuário, auto-documentado
- **Implementação**: Função genérica `apply_ansi()` evita repetição de código
- **Performance**: Código ANSI direto, não interpretação de strings

### 2. SISTEMA DE TIPOS E CONVERSÃO
- **Polimorfismo do operador `+`**: Detecta tipos em tempo de execução
- **Conversão inteligente**: Inteiros não mostram ".000000"
- **Proteção**: Buffer overflow prevenido com `STR_SIZE` fixo (256 chars)
- **Extensibilidade**: Base pronta para mais operadores polimórficos

### 3. LINHA DE COMANDO PROFISSIONAL
- **Padrões seguidos**: `-e` (Perl/Python), `-h`/`-v` (convenção POSIX)
- **Simplicidade**: `rudis arquivo` mais intuitivo que `rudis -f arquivo`
- **Utilidade**: `-e` permite integração com shell scripts
- **Compatibilidade**: Mantém `--lang` da versão anterior

### 4. SISTEMA DE AJUDA UNIFICADO
- **Organização**: 5 páginas temáticas
- **Cobertura**: Todas as 59 funções documentadas (35 antigas + 24 novas)
- **Internacionalização**: PT/EN para toda a documentação
- **Exemplos**: Casos práticos de uso real

### 5. EXPERIÊNCIA DO USUÁRIO
- **Consistência**: Mesmo comportamento em REPL e arquivos
- **Feedback**: Mensagens de erro claras em operações de tipo
- **Flexibilidade**: Combinação livre de cores, alinhamento, repetição
- **Produtividade**: `-e` para cálculos rápidos, arquivos para projetos

### 6. PREPARAÇÃO PARA O FUTURO
- **Base para formatação avançada**: Cores e alinhamento preparam terreno para `print` melhorado
- **Estrutura para execução de arquivos**: Base para futuros `include`, `import`
- **Sistema de tipos extensível**: Pronto para booleanos, arrays, etc.
- **Arquitetura de execução**: REPL e arquivos usam mesma engine

---

## ✅ **ESTADO ATUAL DO PROJETO**

**Progresso da v0.1.0**: 100% completo
- ✅ **Operador `+` para strings** - Concatenação e conversão automática
- ✅ **34 funções de cores ANSI** - Cores, fundos, estilos
- ✅ **3 funções de alinhamento** - `left()`, `center()`, `right()`
- ✅ **Função `repeat()`** - Criação de separadores
- ✅ **Sistema de linha de comando** - REPL, arquivos, one-liners
- ✅ **Sistema de ajuda expandido** - Página 5 para cores
- ✅ **Arquitetura unificada** - Mesma engine para REPL e arquivos

**Compatibilidade com v0.0.2**: 100% mantida

**Base para versões futuras**: Sistema robusto para formatação avançada

---

## 🎯 VERSÕES FUTURAS (PREVIEW):

### **v0.2.0** (PRÓXIMA)
- Função `input()` para entrada de dados
 
### **v0.3.0**
- **Estruturas de controle** - `if`, `else`, `while`, `for`
- **Funções definidas pelo usuário** - `function nome() ... end`
- **Escopo de variáveis** - Locais vs. globais

### **v0.4.0** 
- **Operações com strings** - Comparação, extração, substituição
- **Expressões regulares básicas** - Busca e substituição
- **Funções string avançadas** - `split()`, `join()`, `trim()`

---

**Última atualização**: 07/12/2025  
**Status da versão**: ✅ PRONTA PARA RELEASE  
**Nota Técnica**: O Rudis agora é uma ferramenta completa com interface profissional, preparada para uso em scripts reais e integração em pipelines de shell. A base estabelecida permite expansão natural para formatação avançada na próxima versão.
