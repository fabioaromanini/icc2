# Nome do Projeto
PROJECT = colisao

# Nome dos arquivos
SOURCE = $(PROJECT).c
EXECUTABLE = $(PROJECT).bin

# Teste Atual
TESTE = 24

# Flags
# 	-Wall = Warnings
# 	-g = debugar
# 	-O3 = pra ficar bolado
#	-o = Saída

# Flags do valgrind
#  --leak-check=full == ver quais linhas estão causando leak

all:
	$(MAKE) clean
	gcc -g -Wall -o $(EXECUTABLE) $(SOURCE) src/*.c -Iinc/

run:
	./$(EXECUTABLE)

teste:
	./$(EXECUTABLE) < casos/$(TESTE).in > saidas/$(TESTE).out

leak:
	$(MAKE) clean
	$(MAKE) all
	valgrind --leak-check=full ./$(EXECUTABLE) < casos/$(TESTE).in

clean:
# Checa que existe algum executável antes de tentar remover, se não buga
ifneq (,$(wildcard $(EXECUTABLE)))
	rm $(EXECUTABLE)
endif


INFO = "Fábio Augusto Romanini Pinto\ngithub: fabioaromanini\nNúmero USP: 9791312\n\nRepositório da disciplina: github.com/fabioaromanini/icc2/\n\nA razão para usarmos executáveis com .bin é para \nque o .gitignore consiga reconhecer os arquivo facilmente.\n"

install:
	mkdir -p src
	mkdir -p inc
	mkdir -p casos
	mkdir -p saidas
	printf $(INFO) > README.txt