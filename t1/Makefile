# Fábio Augusto Romanini Pinto
# Número USP 9791312

# Nome do Projeto
PROJECT = octree

# Formato
FORMAT = .c

# Nome do arquivo principal
SOURCE = $(PROJECT)$(FORMAT)
# A razão para usarmos executáveis com .bin é para que o .gitignore possa ignorá-los
EXECUTABLE = $(PROJECT)$(OUTPUTFORMAT)


#Saída
OUTPUTFLAG = -o
OUTPUTFORMAT = .bin

# Bibliotecas:
LIBS = src/

# Diretório dos includes
INCLUDES = inc/

# Compilador
CC = gcc
# 	-Wall = Warnings
# 	-g = debugar
# 	-O3 = pra ficar bolado
# 	-sdt=c99 = trabalhos de grafos
CFLAGS = -g -Wall -std=c99

# Executar
RUN = ./

# Depuração
DEBUGGING = valgrind

# Flags
#  --leak-check=full == ver linhas linhas que estão causando leak
FLAGS = --leak-check=full

all:
	$(CC) $(CFLAGS) $(SOURCE) $(OUTPUTFLAG) $(EXECUTABLE) $(LIBS)* -I$(INCLUDES)

run:
	$(RUN)$(EXECUTABLE)

leak:
	$(MAKE) clean
	$(MAKE) all
	$(DEBUGGING) $(FLAGS) $(RUN)$(EXECUTABLE)

clean:
	rm $(EXECUTABLE)

install:
	mkdir -p src
	mkdir -p inc
	touch $(SOURCE)