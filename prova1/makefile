# makefile Arvore b
# Alunos: Victor Eduardo e Ronaldo Pereira

GRR = 20203937_20240514

# Detectar se possui gcc 14 na maquina 
CC      = $(shell command -v gcc-14 2> /dev/null || echo gcc)

CFLAGS  = -Wall -Wextra -Werror -g -std=c23
LDLIBS  = -lm

TARGET  = prova1_$(GRR)
DIR     = prova1_$(GRR)

# arquivo cabecalho
HDR = arvoreB.h 

# arquivos objetos
OBJ = arvoreB.o test.o fila.o

# construção do executavel
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDLIBS)

# contrução .o
test.o: test.c $(HDR)
	$(CC) $(CFLAGS) -c test.c

arvoreB.o: arvoreB.c arvoreB.h 
	$(CC) $(CFLAGS) -c arvoreB.c

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c

# execução
run: $(TARGET)
	./$(TARGET)

# teste com valgrind 
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# gerar arquivo TGZ para entregar
tgz: clean
	mkdir -p $(DIR)
	cp *.c *.h makefile $(DIR)
	tar czvf $(DIR).tar.gz $(DIR)
	rm -rf $(DIR)
	@echo "Arquivo $(DIR).tar.gz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *.o $(TARGET) $(DIR).tar.gz