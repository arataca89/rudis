# Rudis - versão 0.0.2

## METADADOS DO PROJETO
- **Nome**: Rudis
- **Versão**: 0.0.2 (Internacionalização Completa + Múltiplas Instruções + Controle de Precisão + Tipo String)
- **Filosofia**: Simplicidade, Acessibilidade, Flexibilidade
- **Paradigma**: Interpretada, Dinâmica, Multipropósito
- **Implementação**: C (interpretador)
- **Repositório**: https://github.com/arataca89/rudis
- **Data de Release**: Dezembro 2025

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

### 1. SUPORTE A MÚLTIPLAS INSTRUÇÕES POR LINHA
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

### 2. INTERNACIONALIZAÇÃO COMPLETA DO SISTEMA
**Status**: ✅ IMPLEMENTADO

**Arquivos Corrigidos**:
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

### 3. TIPO STRING (NOVO)
**Status**: ✅ IMPLEMENTADO NO LEXER E PARSER | 🚧 EM ANDAMENTO NO EVALUATOR

**Decisão de Design**:
- Strings são delimitadas por aspas duplas (`"`)
- Suporte a sequências de escape: `\n` (nova linha), `\\` (barra invertida), `\"` (aspas)
- Tamanho máximo: 256 caracteres por string
- Representação na AST: campo `text[256]` para strings e nomes de variáveis
- Tipo de nó na AST: `NODE_STRING`

**Exemplo**:
```python
# Atribuição de strings
rudis> nome = "Buzz Lightyear"
rudis> mensagem = "Olá,\nMundo!"

# Representação na AST:
# ASSIGNMENT: nome =
#     STRING: Buzz Lightyear
```

**Implementação Técnica**:
- Lexer: Reconhece `TOKEN_STRING` com tratamento de escapes
- Parser: Adicionado `NODE_STRING` como átomo na gramática
- AST: Campo `variable[64]` expandido para `text[256]`
- Evaluator: 🚧 Suporte a string em implementação

### 4. CONTROLE DE CASAS DECIMAIS
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

### 5. NOVA CATEGORIA: FUNÇÕES DE CONFIGURAÇÃO
**Status**: ✅ IMPLEMENTADO

**Organização**:
- Separa funções stateful das funções stateless
- Categoria dedicada no `execute_function()`
- Preparada para expansão futura

**Funções Atuais**:
- `setdec(n)` - Controla casas decimais da saída

---

## EXEMPLOS DA VERSÃO 0.0.2:

### MÚLTIPLAS INSTRUÇÕES:
```python
rudis> nome = "João"; idade = 25; salario = 2500.50
rudis> a=3; b=5; c=a*b; c
15.0
```

### STRINGS:
```python
# Atribuição e uso de strings (parcialmente implementado)
rudis> nome = "Maria Silva"
rudis> boas_vindas = "Bem-vindo ao Rudis v0.0.2"
rudis> texto_multilinha = "Linha 1\nLinha 2\nLinha 3"
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

### 1. ARQUITETURA DE INTERNACIONALIZAÇÃO
- **Sistema Híbrido**: Combina funções de tradução com verificações inline
- **Performance**: Verificações de idioma só ocorrem quando necessário
- **Manutenção**: Mensagens organizadas por contexto de uso
- **Extensibilidade**: Fácil adição de novos idiomas no futuro

### 2. TIPO STRING
- **Implementação Gradual**: Lexer e parser completos, evaluator em desenvolvimento
- **Campo Unificado**: Uso de `text[256]` para strings e nomes de variáveis na AST
- **Sequências de Escape**: Suporte básico para formatação de texto
- **Próximo Passo**: Integração completa com sistema de tipos do evaluator

### 3. ESPECIFICADOR `%.*f`
- **Recurso C**: Permite número dinâmico de casas decimais
- **Sintaxe**: `printf("%.*f", casas, valor)`
- **Vantagem**: Elimina necessidade de formatação manual de strings
- **Aplicação**: Usado em todas as saídas numéricas do REPL

### 4. CATEGORIA DE CONFIGURAÇÃO
- **Inovação**: Primeira categoria de funções stateful no Rudis
- **Organização**: Separa claramente funções de cálculo vs. configuração
- **Expansão**: Base para futuras funções de controle do sistema

### 5. EXPERIÊNCIA DO USUÁRIO
- **Consistência**: Comportamento idêntico em PT/EN
- **Controle**: Precisão ajustável conforme necessidade
- **Profissionalismo**: Recursos de calculadora avançada
- **Flexibilidade**: Transição suave entre diferentes usos

---

## ROADMAP VERSÃO 0.0.2

### ✅ CONCLUÍDO:
- ✅ Sistema de múltiplas instruções por linha (`;`)
- ✅ Processamento sequencial com persistência de variáveis
- ✅ Internacionalização completa do `help.c`
- ✅ Internacionalização completa do `main.c` 
- ✅ Internacionalização completa do `evaluator.c`
- ✅ Implementação da função `setdec(n)`
- ✅ Controle dinâmico de casas decimais
- ✅ Categoria "Funções de Configuração"
- ✅ Uso do especificador `%.*f`
- ✅ Validação de range (0-15 casas)
- ✅ Mensagens de erro internacionalizadas para `setdec`
- ✅ Manutenção de compatibilidade com v0.0.1
- ✅ Implementação do tipo string no lexer e parser
- ✅ Suporte a sequências de escape em strings (`\n`, `\\`, `\"`)
- ✅ Atualização da AST com campo `text[256]`
- ✅ Testes de parsing de strings funcionando

### 🚧 PRÓXIMOS PASSOS:
- [ ] Suporte a strings no evaluator (tipo `VAL_STRING`)
- [ ] Implementação do comando `print` para strings
- [ ] Sistema de cores ANSI integrado
- [ ] Controle de alinhamento (left, center, right)
- [ ] Especificação de largura de campo
- [ ] Separadores (`,` = tabulação, `;` = concatenação)

**Perfeito!** Vou atualizar o documento com o roadmap corrigido:

---

## 🎯 VERSÕES FUTURAS (PREVIEW):

### **v0.0.2** (em desenvolvimento)
- ✅ Lexer com strings
- ✅ Parser com strings  
- ✅ AST com NODE_STRING
- 🚧 Evaluator com string
- 🚧 `print()`


### **v0.0.3** 
- Concatenação `"a" + "b"`
- Comparação `"a" == "b"`
- Função `len("texto")`

### **v0.0.4** 
- Funções para o tipo string

### **v0.0.5** 
- Função de entrada de dados:`input()` 

---

## ✅ **ESTADO ATUAL DO PROJETO**

**Progresso da v0.0.2**: 95% completo
- ✅ Múltiplas instruções - 100%
- ✅ Internacionalização - 100%  
- ✅ Controle de precisão - 100%
- ✅ Tipo string (lexer/parser) - 100%
- 🚧 Tipo string (evaluator) - 50%
- 🚧 Sistema print - 0%

---

**Última atualização**: 02/12/2025  
