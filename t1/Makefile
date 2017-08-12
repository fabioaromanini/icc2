# Fábio Augusto Romanini Pinto
# Número USP 9791312

# Nome do Projeto
PROJECT = octree

# Formato
FORMAT = .c

# Nome do arquivo principal
TARGET = $(PROJECT)$(FORMAT)

#Saída
OUTPUTFLAG = -o
OUTPUT = $(OUTPUTFLAG)$(PROJECT).bin

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
	$(CC) $(CFLAGS) $(TARGET) $(OUTPUT) $(LIBS)* -I$(INCLUDES)

run:
	$(RUN)$(PROJECT)

leak:
	$(MAKE) clean
	$(MAKE) all
	$(DEBUGGING) $(FLAGS) $(RUN)$(PROJECT)

clean:
	rm $(PROJECT)

install:
	mkdir -p src
	mkdir -p inc
	touch $(TARGET)