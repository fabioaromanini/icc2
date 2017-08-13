# Nome do Projeto
PROJECT = octree

# Nome dos arquivos
SOURCE = $(PROJECT).c
EXECUTABLE = $(PROJECT).bin

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

leak:
	$(MAKE) clean
	$(MAKE) all
	valgrind --leak-check=full ./$(EXECUTABLE) < teste.txt

clean:
# Checa que existe algum executável antes de tentar remover, se não buga
ifneq (,$(wildcard $(EXECUTABLE)))
	rm $(EXECUTABLE)
endif


INFO = "Fábio Augusto Romanini Pinto\ngithub: fabioaromanini\nNúmero USP: 9791312\n\nRepositório da disciplina: github.com/fabioaromanini/icc2/\n\nA razão para usarmos executáveis com .bin é para \nque o .gitignore consiga reconhecer os arquivo facilmente.\n"

install:
	mkdir -p src
	mkdir -p inc
	printf $(INFO) > README.txt