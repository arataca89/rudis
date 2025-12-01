# Makefile para Rudis - Linux
# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -pedantic -O2 -D_POSIX_C_SOURCE=200809L
# -D_POSIX_C_SOURCE=200809L para garantir compatibilidade com funções POSIX

# Flags para debug (descomente se necessário)
# CFLAGS = -Wall -Wextra -std=c99 -pedantic -g -DDEBUG -D_POSIX_C_SOURCE=200809L

# Nome do executável
TARGET = rudis

# Arquivos objeto
OBJS = main.o lang.o lexer.o a89alloc.o parser.o functions.o evaluator.o help.o

# Regra principal
all: $(TARGET)

# Ligação
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

# Dependências dos arquivos objeto
main.o: main.c lang.h a89alloc.h
	$(CC) $(CFLAGS) -c main.c

lang.o: lang.c lang.h lexer.h parser.h evaluator.h functions.h a89alloc.h
	$(CC) $(CFLAGS) -c lang.c

lexer.o: lexer.c lexer.h a89alloc.h
	$(CC) $(CFLAGS) -c lexer.c

a89alloc.o: a89alloc.c a89alloc.h
	$(CC) $(CFLAGS) -c a89alloc.c

parser.o: parser.c parser.h lexer.h a89alloc.h
	$(CC) $(CFLAGS) -c parser.c

functions.o: functions.c functions.h a89alloc.h
	$(CC) $(CFLAGS) -c functions.c -lm

evaluator.o: evaluator.c evaluator.h parser.h functions.h a89alloc.h
	$(CC) $(CFLAGS) -c evaluator.c

help.o: help.c help.h
	$(CC) $(CFLAGS) -c help.c

# Regra para limpar arquivos de compilação
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para reinstalar
re: clean all

# Regra para instalação no sistema (opcional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Regra para desinstalar
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Regra para debug
debug: CFLAGS = -Wall -Wextra -std=c99 -pedantic -g -DDEBUG -D_POSIX_C_SOURCE=200809L
debug: $(TARGET)

# Regra para testar
test: $(TARGET)
	./$(TARGET) --test

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  all      - Compila o Rudis (padrão)"
	@echo "  debug    - Compila com informações de debug"
	@echo "  clean    - Remove arquivos objeto e executável"
	@echo "  re       - Recompila completamente"
	@echo "  install  - Instala no sistema (requer privilégios)"
	@echo "  test     - Executa testes básicos"
	@echo "  help     - Mostra esta ajuda"

.PHONY: all clean re install uninstall debug test help