# Nome do Projeto
PROJECT = colisao

# Nome dos arquivos
SOURCE = $(PROJECT).c
EXECUTABLE = $(PROJECT).bin
RELEASE = $(PROJECT).zip

# Teste Unitário
TESTE = 3

# Lista dos testes automatizados
COMECO := 1
FIM := 24
NUMBERS := $(shell seq ${COMECO} ${FIM})

# Flags
# 	-Wall = Warnings
# 	-g = debugar
# 	-O3 = pra ficar bolado
#	-o = Saída

# Flags do valgrind
#  --leak-check=full == ver quais linhas estão causando leak

INFO = "Fábio Augusto Romanini Pinto\ngithub: fabioaromanini\nNúmero USP: 9791312\n\nRepositório da disciplina: github.com/fabioaromanini/icc2/\n\nA razão para usarmos executáveis com .bin é para \nque o .gitignore consiga reconhecer os arquivo facilmente.\n"

all:
	gcc -g -Wall -o $(EXECUTABLE) $(SOURCE) src/*.c -Iinc/

run:
	./$(EXECUTABLE)

zip:
	$(MAKE) cleanfull
	$(MAKE) all
	zip $(PROJECT).zip ./$(SOURCE) ./Makefile src/* inc/*

teste:
	$(MAKE) clean
	$(MAKE) all
	./$(EXECUTABLE) < casos/$(TESTE).in > saidas/$(TESTE).out

testefull:
	$(MAKE) all
	$(foreach var,$(NUMBERS), ./$(EXECUTABLE) < casos/$(var).in > saidas/$(var).out; \
)

leak:
	$(MAKE) clean
	$(MAKE) all
	valgrind --leak-check=full ./$(EXECUTABLE) < casos/$(TESTE).in

clean:
# Checa que existe algum executável antes de tentar remover, se não buga
ifneq (,$(wildcard $(EXECUTABLE)))
	rm $(EXECUTABLE)
endif

cleancasos:
ifneq (,$(wildcard casos/))
	rm -rf casos
endif

cleanfull:
ifneq (,$(wildcard $(RELEASE)))
	rm $(RELEASE)
endif

ifneq (,$(wildcard $(EXECUTABLE)))
	rm $(EXECUTABLE)
endif

install:
	mkdir -p src
	mkdir -p inc
	mkdir -p casos
	mkdir -p saidas
	printf $(INFO) > README.txt