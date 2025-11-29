Aqui está o markdown completo com licença, autor e agradecimentos:

```markdown
# Rudis Language

<div align="center">

**Rudis Language - projeto didático de uma linguagem de programação simples e funcional. Escrito em C.**  

![Version](https://img.shields.io/badge/version-0.0.1-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-em%20desenvolvimento-orange)

</div>

## 🎯 Sobre o Projeto

O **Rudis** é uma linguagem de programação interpretada escrita em C, projetada com foco em:
- **Simplicidade** - Sintaxe intuitiva e fácil aprendizado
- **Acessibilidade** - Documentação em português e inglês
- **Evolução Orgânica** - Começa como calculadora, vira linguagem completa

## ✨ Características da Versão 0.0.1

### 🧮 Funcionalidades Atuais
- **REPL interativo** com histórico e ajuda
- **35+ funções built-in** (matemáticas, estatísticas, financeiras)
- **Sistema de variáveis** com atribuição encadeada
- **Aliases em português** (`raiz`, `sen`, `media`, `vpl`, `tir`)
- **Suporte a números** decimais, hexadecimais (0xFF) e binários (0b1010)
- **Internacionalização** PT/EN
- **Múltiplos estilos de comentário** (#, //, /* */)

### 📊 Exemplos de Uso
```python
# Matemática básica
> 5 + 3 * 2 ^ 2!
25.0

# Estatística
> media(7.5, 8.0, 6.5, 9.0)
7.75

# Financeiro
> vpl(0.05, -1000, 300, 400, 500)
80.4449

# Variáveis
> a = 5; b = 10; raiz(a + b)
3.87298
```

## 🚀 Começando

### Compilação
```bash
# Clone o repositório
git clone https://github.com/seu-usuario/rudis.git
cd rudis

# Compile
make

# Execute
./rudis
```

### Uso Básico
```bash
# REPL interativo
./rudis

# Com ajuda em inglês
./rudis --lang en

# Ver ajuda
./rudis --help
```

## 📋 Roadmap

### Versão 0.0.2 (Em Desenvolvimento)
- [ ] Múltiplas instruções por linha (`;`)
- [ ] Comando `print` com formatação estilo BASIC + cores
- [ ] Parser completo e robusto

### Versões Futuras
- [ ] Estruturas de controle (if/else, loops)
- [ ] Funções definidas pelo usuário
- [ ] Arrays e estruturas de dados
- [ ] Sistema de módulos

## 🏗️ Estrutura do Projeto
```
rudis/
├── main.c          # Ponto de entrada
├── lang.c          # Núcleo da linguagem
├── lexer.c         # Analisador léxico
├── parser.c        # Analisador sintático
├── evaluator.c     # Avaliador de expressões
├── functions.c     # Funções built-in
├── help.c          # Sistema de ajuda
├── a89alloc.c      # Gerenciamento de memória
├── Makefile        # Script de compilação
└── README.md       # Este arquivo
```

## 👤 Autor

**Seu Nome**
- GitHub: [@seu-usuario](https://github.com/seu-usuario)
- Email: seu-email@exemplo.com
- LinkedIn: [Seu Perfil](https://linkedin.com/in/seu-perfil)

## 🙏 Agradecimentos

Um agradecimento especial para:

- **Comunidade de desenvolvedores** que compartilham conhecimento aberto
- **Projetos inspiradores** como Python, Lua e BASIC
- **Calculadoras científicas** pela inspiração na abordagem prática
- **Todos os contribuidores** que ajudam a melhorar este projeto

## 🤝 Contribuindo

Contribuições são bem-vindas! Este é um projeto educacional aberto para aprendizado coletivo.

1. Fork o projeto
2. Crie uma branch para sua feature (`git checkout -b feature/AmazingFeature`)
3. Commit suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. Push para a branch (`git push origin feature/AmazingFeature`)
5. Abra um Pull Request

## 📄 Licença

Distribuído sob licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais informações.

---

<div align="center">

Feito com 💻 e ☕ por [Seu Nome](https://github.com/seu-usuario)

</div>
```

## 📄 ARQUIVO LICENSE (crie separado):

```text
MIT License

Copyright (c) 2025 Seu Nome

Permissão é concedida, gratuitamente, a qualquer pessoa que obtenha uma cópia
deste software e dos arquivos de documentação associados (o "Software"), para lidar
no Software sem restrição, incluindo, sem limitação, os direitos de usar, copiar, modificar,
fundir, publicar, distribuir, sublicenciar e/ou vender cópias do Software, e para
permitir que as pessoas a quem o Software é fornecido o façam, sujeitas às seguintes condições:

O aviso de copyright acima e este aviso de permissão devem ser incluídos em todas
as cópias ou partes substanciais do Software.

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA,
INCLUINDO, MAS NÃO SE LIMITANDO ÀS GARANTIAS DE COMERCIALIZAÇÃO, ADEQUAÇÃO A UM DETERMINADO
FIM E NÃO VIOLAÇÃO. EM NENHUM CASO OS AUTORES OU DETENTORES DOS DIREITOS AUTORAIS SERÃO
RESPONSÁVEIS POR QUALQUER REIVINDICAÇÃO, DANOS OU OUTRA RESPONSABILIDADE, SEJA EM UMA AÇÃO
DE CONTRATO, ATO ILÍCITO OU OUTRO, DECORRENTE DE, FORA DE OU EM CONEXÃO COM O SOFTWARE
OU O USO OU OUTRAS NEGOCIAÇÕES NO PROGRAMAS.
```

Agora é só substituir "Seu Nome", "@seu-usuario" e os links com suas informações! 🚀
