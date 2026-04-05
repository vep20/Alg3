# makefile Arvore b
# Alunos: Victor Eduardo e Ronaldo Pereira

CC      = $(shell command -v gcc-14 2> /dev/null || echo gcc)
CFLAGS  = -Wall -Wextra -Werror -g -std=c2x 	#gcc utilizado é o antigo
LDLIBS  = -lm
MAIN    = test
ENTREGA = $(MAIN)

# arquivo cabecalho
HDR = arvoreB.h 

# arquivos objetos
OBJ = arvoreB.o test.o

# construção do executavel
$(MAIN): $(MAIN).o $(OBJ)

# construção dos arquivos-objeto
$ (MAIN).o: $(MAIN).c $(HDR)

# contrução TAD
arvoreB.o: arvoreB.c arvoreB.h 

# execução
run: $(MAIN)
	./$(MAIN)

# teste com valgrind 
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h conjunto.o makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz
