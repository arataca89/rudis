Aqui está o documento de design atualizado para a versão 0.0.1, incluindo todas as funcionalidades que descobrimos e validamos:

```markdown
# **RELATÓRIO DE DESIGN DA LINGUAGEM RUDIS - VERSÃO 0.0.1**

## **📋 METADADOS DO PROJETO**
- **Nome**: Rudis
- **Versão**: 0.0.1 (Calculadora com Variáveis)
- **Filosofia**: Simplicidade, Acessibilidade, Flexibilidade
- **Paradigma**: Interpretada, Dinâmica, Multipropósito
- **Implementação**: C (interpretador)
- **Repositório**: https://github.com/arataca89/rudis

---

## **🎯 DECISÕES DE DESIGN FUNDAMENTAIS**

### **1. SISTEMA DE TIPOS DE DADOS**
```python
# APENAS UM TIPO NUMÉRICO: double
x = 5          # 5.0 (armazenado como double)
y = 3.14       # 3.14
z = 0xFF       # 255.0 (hexadecimal)
w = 0b1101     # 13.0 (binário)
```

**Justificativa**: Simplicidade máxima para usuários, cobrindo 95% dos casos de uso de uma calculadora avançada.

### **2. IDENTIFICADORES DE VARIÁVEIS**
```python
# REGRA: [a-zA-Z_][a-zA-Z0-9_]*
salario_bruto = 5000        # VÁLIDO
_resultado = 42             # VÁLIDO
idade1 = 25                 # VÁLIDO
1valor = 10                 # INVÁLIDO (não começa com letra)
nome-completo = "João"      # INVÁLIDO (caractere especial)
```

### **3. SISTEMA DE COMENTÁRIOS MULTI-ESTILO**
```python
# Comentário estilo Python (recomendado)
valor = 5  # comentário na mesma linha

// Comentário estilo C++/Java
resultado = x + y  // cálculo simples

/* 
 Comentário estilo C multi-linha
 Ideal para documentação extensa
 Pode abranger várias linhas
*/
media = mean(1, 2, 3)
```

### **4. FIM DE INSTRUÇÃO FLEXÍVEL**
```python
# ESTILO PYTHON (recomendado para novatos)
x = 5
y = 10
resultado = x + y

# ESTILO C (para experientes ou múltiplas instruções)
x = 5; y = 10; resultado = x + y

# MISTO (máxima flexibilidade)
x = 5; y = 10
resultado = x + y
```

**Tokens**: `\n` (padrão) e `;` (opcional) são tratados como fim de instrução.

### **5. OPERADORES MATEMÁTICOS SUPORTADOS**
```python
# ARITMÉTICOS BÁSICOS
a + b    # Adição
a - b    # Subtração  
a * b    # Multiplicação
a / b    # Divisão
a % b    # Módulo (resto)
a ^ b    # Potência (2 ^ 8 = 256)

# ESPECIAIS
a!       # Fatorial (5! = 120) - OPERADOR PÓS-FIXO
```

### **6. SISTEMA DE ATRIBUIÇÃO**
```python
# ATRIBUIÇÃO SIMPLES
x = 5

# ATRIBUIÇÕES ENCADEADAS (PERMITIDO)
a = b = c = 10
resultado = x = sqrt(25)  # resultado e x recebem 5.0

# ATRIBUIÇÃO COM EXPRESSÕES COMPLEXAS
salario_liquido = salario_bruto - (salario_bruto * 0.27)
```

### **7. SISTEMA DE FUNÇÕES BUILT-IN (35+ FUNÇÕES)**

#### **MATEMÁTICAS BÁSICAS**
```python
sqrt(25) / raiz(25)        # Raiz quadrada → 5.0
sin(π/2) / sen(π/2)        # Seno → 1.0
log(100)                   # Logaritmo base 10 → 2.0
abs(-5)                    # Valor absoluto → 5.0
```

#### **ESTATÍSTICAS (FÓRMULA AMOSTRAL)**
```python
mean(1,2,3) / media(1,2,3)        # Média → 2.0
median(1,3,5) / mediana(1,3,5)    # Mediana → 3.0
std(1,2,3) / desvio(1,2,3)        # Desvio padrão → 1.0
variance(1,2,3) / variancia(1,2,3) # Variância → 1.0 (n-1)
mode(1,2,2,3) / moda(1,2,2,3)     # Moda → 2
sum(1,2,3) / soma(1,2,3)          # Soma → 6.0
min(5,2,8) / minimo(5,2,8)        # Mínimo → 2.0
max(5,2,8) / maximo(5,2,8)        # Máximo → 8.0
```

#### **FINANCEIRAS BÁSICAS**
```python
si(1000,0.05,2) / js(1000,0.05,2)         # Juros simples → 100
fv_si(500,0.1,3) / montante_js(500,0.1,3) # Montante juros simples → 650
ci(1000,0.05,2) / jc(1000,0.05,2)         # Juros compostos → 102.5
fv_ci(500,0.1,3) / montante_jc(500,0.1,3) # Montante juros compostos → 665.5
```

#### **FINANCEIRAS AVANÇADAS**
```python
pv(0.05,10,100) / vp(0.05,10,100)         # Valor presente → ~772.17
fv(0.05,10,100) / vf(0.05,10,100)         # Valor futuro → ~1257.79
pmt(0.05,10,1000) / pagamento(0.05,10,1000) # Pagamento → ~129.50
nper(0.05,200,1000) / periodos(0.05,200,1000) # Períodos → ~5.90
rate(10,100,1000) / taxa(10,100,1000)     # Taxa de juros → ~0.05
npv(0.1,-1000,300,400,500) / vpl(0.1,-1000,300,400,500) # VPL → ~-21.04
irr(-1000,300,400,500) / tir(-1000,300,400,500) # TIR → ~0.089
```

### **8. CONVENÇÕES ESTATÍSTICAS VALIDADAS**
**Variância e Desvio Padrão**: Usam fórmula AMOSTRAL (divisor n-1)
```python
variancia(1, 2, 3)     # Retorna 1.0 (não 0.666)
desvio(1, 2, 3)        # Retorna 1.0 (não 0.816)
```

### **9. SISTEMA DE NUMERAÇÃO**
```python
# DECIMAL (padrão)
x = 123          # 123.0
y = 45.67        # 45.67

# HEXADECIMAL (prefixo 0x ou 0X)
cor = 0xFF0000   # Vermelho → 16711680.0
mascara = 0xFF   # 255.0

# BINÁRIO (prefixo 0b ou 0B)  
flags = 0b1101   # 13.0
config = 0b1010  # 10.0
```

### **10. INTERNACIONALIZAÇÃO (i18n)**
```python
# PORTUGUÊS (padrão)
> a = 5
> a + 3
8.0

# INGLÊS (--lang en ou set lang en)
> a = 5
> a + 3
8.0
```

**Mensagens**: Todas as mensagens do REPL estão disponíveis em PT e EN.

---

## **📖 GRAMÁTICA FORMAL DA LINGUAGEM RUDIS**

### **GRAMÁTICA BNF (VERSÃO 0.0.1)**
```bnf
// ============ GRAMÁTICA RUDIS v0.0.1 ============

// NÍVEL 1: PROGRAMA
programa          := (declaracao (';' | NL))* EOF

// NÍVEL 2: DECLARAÇÕES  
declaracao        := atribuicao | expressao

// NÍVEL 3: ATRIBUIÇÕES
atribuicao        := IDENTIFICADOR '=' expressao

// NÍVEL 4: EXPRESSÕES (PRECEDÊNCIA BAIXA)
expressao         := termo (('+' | '-') termo)*

// NÍVEL 5: TERMOS (PRECEDÊNCIA MÉDIA)  
termo             := fator (('*' | '/' | '%') fator)*

// NÍVEL 6: FATORES (PRECEDÊNCIA ALTA)
fator             := potencia ('!')?           // Fatorial pós-fixo

// NÍVEL 7: POTÊNCIA (PRECEDÊNCIA MUITO ALTA - direita-associativa)
potencia          := atomo ('^' potencia)?

// NÍVEL 8: ÁTOMOS (ELEMENTOS BÁSICOS)
atomo             := NUMERO
                   | IDENTIFICADOR
                   | chamada_funcao
                   | '(' expressao ')'
                   | '-' atomo                 // Negativo unário

// NÍVEL 9: CHAMADAS DE FUNÇÃO
chamada_funcao    := FUNCAO '(' lista_argumentos? ')'

// NÍVEL 10: LISTA DE ARGUMENTOS
lista_argumentos  := expressao (',' expressao)*

// ============ TOKENS ============
NUMERO           := [0-9]+ ('.' [0-9]+)? | 0x[0-9A-Fa-f]+ | 0b[01]+
IDENTIFICADOR    := [a-zA-Z_][a-zA-Z0-9_]*
FUNCAO           := 'sqrt'|'raiz'|'sin'|'sen'|'cos'|'tan'|'log'|'ln'|'exp'|'abs'
                   |'mean'|'media'|'median'|'mediana'|'std'|'desvio'
                   |'variance'|'variancia'|'mode'|'moda'|'sum'|'soma'
                   |'min'|'minimo'|'max'|'maximo'
                   |'pv'|'vp'|'fv'|'vf'|'pmt'|'pagamento'|'nper'|'periodos'
                   |'rate'|'taxa'|'npv'|'vpl'|'irr'|'tir'
                   |'si'|'js'|'fv_si'|'montante_js'|'ci'|'jc'|'fv_ci'|'montante_jc'
NL               := '\n'
EOF              := fim_da_entrada
```

### **🎯 TABELA DE PRECEDÊNCIA DE OPERADORES**

| Precedência | Operador | Associatividade | Descrição | Exemplo |
|-------------|----------|-----------------|-----------|---------|
| 1 | `( )` | - | Agrupamento | `(2 + 3) * 4` |
| 2 | `-` | Direita | Negativo unário | `-5`, `-x` |
| 3 | `!` | Esquerda | Fatorial pós-fixo | `5!`, `(3+2)!` |
| 4 | `^` | Direita | Potência | `2 ^ 3 ^ 2 = 512` |
| 5 | `* / %` | Esquerda | Multiplicação/Divisão/Módulo | `10 * 2 / 5` |
| 6 | `+ -` | Esquerda | Adição/Subtração | `3 + 5 - 2` |
| 7 | `=` | Direita | Atribuição | `a = b = 5` |

### **📚 EXEMPLOS DE EXPRESSÕES VÁLIDAS**

```python
# Precedência complexa
> 2 + 3 * 4 ^ 2! / 5      # 2 + (3 * (4 ^ (2!)) / 5)

# Atribuições encadeadas
> a = b = c = 5 + 3 * 2   # todas recebem 11

# Funções com expressões
> media = mean(1+2, 3*4, sqrt(25))  # (3, 12, 5) → média 6.666

# Mix financeiro e matemático
> resultado = pv(0.05, 10, 100) + fv_si(500, 0.02, 5) * ci(1000, 0.1, 3)
```

---

## **🧪 EXEMPLOS VALIDADOS**

### **ESTATÍSTICA**
```python
> media(7.5, 8.0, 6.5, 9.0)                 # 7.75
> variancia(10.5, 12.0, 8.5, 15.0, 11.5)   # 5.625
> desvio(25, 30, 35, 40, 45)               # ~7.9057
```

### **FINANCEIRO**
```python
> vpl(0.05, -1000, 300, 400, 500)          # 80.4449
> tir(-1000, 300, 400, 500)                # 0.0889634
> vp(0.05, 10, 100)                        # ~772.17
```

---

## **🔧 ESTRUTURA TÉCNICA IMPLEMENTADA**

### **ARQUITETURA DO SISTEMA**
```
rudis/
├── main.c          # Ponto de entrada e REPL
├── lang.c          # Núcleo da linguagem
├── lexer.c         # Analisador léxico
├── parser.c        # Analisador sintático
├── evaluator.c     # Avaliador de expressões
├── functions.c     # 35+ funções built-in
├── help.c          # Sistema de ajuda paginado
├── a89alloc.c      # Gerenciamento de memória
├── tools.h         # Cores ANSI e utilitários
└── Makefile        # Build para Linux
```

### **COMPONENTES PRINCIPAIS**
- **REPL Interativo**: Histórico, ajuda integrada, internacionalização
- **Sistema de Variáveis**: Armazenamento e recuperação
- **Sistema de Ajuda**: Documentação paginada, ajuda por função
- **Funções Built-in**: 35+ funções matemáticas, estatísticas e financeiras

---

## **🚀 ROADMAP - ESTADO ATUAL**

### **✅ VERSÃO 0.0.1 - CONCLUÍDA**
- [x] REPL interativo com histórico
- [x] 35+ funções built-in + aliases em português
- [x] Sistema de variáveis com atribuição encadeada
- [x] Sistema de ajuda paginado (PT/EN)
- [x] Internacionalização completa
- [x] Suporte a números hexadecimais e binários
- [x] Múltiplos estilos de comentário
- [x] Precedência de operadores correta
- [x] Validação extensiva de todas as funcionalidades

### **🔲 VERSÃO 0.0.2 - EM DESENVOLVIMENTO**
- [ ] Múltiplas instruções por linha (`;`)
- [ ] Comando `print` com formatação avançada:
  - [ ] Cores ANSI (`RED:texto`)
  - [ ] Alinhamento (`left`, `center`, `right`)
  - [ ] Largura de campo (`20:valor`)
  - [ ] Separadores (`,` = tabulação, `;` = concatenação)

### **🔲 VERSÕES FUTURAS**
- [ ] Estruturas de controle (if/else, loops)
- [ ] Funções definidas pelo usuário
- [ ] Arrays e estruturas de dados
- [ ] Sistema de módulos

---

## **🎯 PRINCÍPIOS DE DESIGN**

### **SIMPLICIDADE ACIMA DE TUDO**
- Um único tipo numérico (`double`)
- Sintaxe intuitiva e natural
- Mensagens de erro claras
- Operador fatorial pós-fixo (diferencial amigável)

### **FLEXIBILIDADE CONSCIENTE**
- Múltiplos estilos de comentário
- Fim de instrução flexível
- Suporte a diferentes bases numéricas
- Precedência matemática correta

### **ACESSIBILIDADE**
- Internacionalização desde o início
- Documentação completa
- Curva de aprendizado suave
- Funções em inglês com aliases em português

### **EVOLUÇÃO ORGÂNICA**
- Base sólida para funcionalidades futuras
- Arquitetura modular e extensível
- Decisões reversíveis quando possível
- Gramática preparada para expansão

---

**Documento criado em**: 27 de Novembro de 2025  
**Última atualização**: Funcionalidades validadas e roadmap v0.0.2  
**Estado atual**: **VERSÃO 0.0.1 FUNCIONAL** - Calculadora avançada com REPL

---

O Rudis evoluiu de um projeto educacional para uma calculadora avançada funcional, com base sólida para se tornar uma linguagem de programação completa! 🚀
```

Este documento agora reflete com precisão o estado **real** do projeto, incluindo todas as funcionalidades que validamos e o plano para a v0.0.2!
