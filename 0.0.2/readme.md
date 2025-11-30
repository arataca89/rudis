# Rudis - versão 0.0.2

## METADADOS DO PROJETO
- **Nome**: Rudis
- **Versão**: 0.0.2 (Múltiplas Instruções e Sistema de Print)
- **Filosofia**: Simplicidade, Acessibilidade, Flexibilidade
- **Paradigma**: Interpretada, Dinâmica, Multipropósito
- **Implementação**: C (interpretador)
- **Repositório**: https://github.com/arataca89/rudis

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

### 3. SISTEMA DE TRADUÇÃO IMPLEMENTADO
**Padrões Adotados**:

#### 3.1 PARA MENSAGENS SIMPLES:
```c
if (current_lang == LANG_PT)
    return create_error_result("Divisão por zero");
else 
    return create_error_result("Division by zero");
```

#### 3.2 PARA MENSAGENS COMPLEXAS (help.c):
```c
const char* get_help_operator_add() {
    return (current_lang == LANG_PT) 
        ? "Operador: + (Adição)\nSintaxe: a + b\nDescrição: Soma dois valores..."
        : "Operator: + (Addition)\nSyntax: a + b\nDescription: Adds two values...";
}
```

#### 3.3 PARA MENSAGENS DINÂMICAS (evaluator.c):
```c
void build_arg_error_msg(char* buffer, size_t size, const char* func_name, int required_args, int is_minimum) {
    if (current_lang == LANG_PT) {
        snprintf(buffer, size, "%s requer %d argumento%s", func_name, required_args, required_args > 1 ? "s" : "");
    } else {
        snprintf(buffer, size, "%s requires %d argument%s", func_name, required_args, required_args > 1 ? "s" : "");
    }
}
```

---

## EXEMPLOS DA VERSÃO 0.0.2:

### MÚLTIPLAS INSTRUÇÕES:
```python
rudis> nome = "João"; idade = 25; salario = 2500.50
rudis> a=3; b=5; c=a*b; c
15.0
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

## OBSERVAÇÕES INTERESSANTES

### 1. ARQUITETURA DE INTERNACIONALIZAÇÃO
- **Sistema Híbrido**: Combina funções de tradução com verificações inline
- **Performance**: Verificações de idioma só ocorrem quando necessário
- **Manutenção**: Mensagens organizadas por contexto de uso
- **Extensibilidade**: Fácil adição de novos idiomas no futuro

### 2. DECISÕES TÉCNICAS
- **`help.c`**: Usa funções dedicadas para textos longos
- **`evaluator.c`**: Usa verificações inline para mensagens curtas
- **`main.c`**: Mix de ambos os approaches conforme apropriado
- **Consistência**: Todas as mensagens do usuário são internacionalizadas

### 3. IMPACTO NA EXPERIÊNCIA DO USUÁRIO
- **Profissionalismo**: Sistema coerente em ambos os idiomas
- **Acessibilidade**: Suporte a usuários internacionais
- **Consistência**: Mesmo comportamento, diferentes idiomas
- **Qualidade**: Mensagens de erro claras e informativas

### 4. COMPATIBILIDADE
- **Retrocompatibilidade**: API mantida intacta
- **Comportamento**: Funcionalidades idênticas em PT/EN
- **Performance**: Impacto mínimo no tempo de execução

---

## ROADMAP VERSÃO 0.0.2

### ✅ CONCLUÍDO:
- ✅ Sistema de múltiplas instruções por linha (`;`)
- ✅ Processamento sequencial com persistência de variáveis
- ✅ Internacionalização completa do `help.c`
- ✅ Internacionalização completa do `main.c` 
- ✅ Internacionalização completa do `evaluator.c`
- ✅ Manutenção de compatibilidade com v0.0.1
- ✅ Testes de todos os cenários de internacionalização

### 🚧 PRÓXIMOS PASSOS:
- [ ] Implementação do comando `print` avançado
- [ ] Sistema de cores ANSI integrado
- [ ] Controle de alinhamento (left, center, right)
- [ ] Especificação de largura de campo
- [ ] Separadores (`,` = tabulação, `;` = concatenação)

### 🎯 VERSÕES FUTURAS (PREVIEW):
- **v0.0.3**: Comando `print` avançado (cores + formatação)
- **v0.0.4**: Estruturas de controle (if/else básico)
- **v0.0.5**: Loops simples (for, while)
- **v0.1.0**: Funções definidas pelo usuário

---

## ESTADO ATUAL DO PROJETO

**Progresso da v0.0.2**: 80% completo
- ✅ Múltiplas instruções - 100%
- ✅ Internacionalização - 100%  
- 🚧 Sistema print - 0%
- 🔲 Correções e polimento - 0%

**Próximo marco**: Comando `print` totalmente funcional


