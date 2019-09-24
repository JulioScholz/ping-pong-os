SAIDA = pingpong-scheduler
C_COMPILER = gcc
FLAGS = -Wall
# Arquivos .c
C_SOURCE = $(patsubst %.c, %.o, $(wildcard *.c))
# Arquivos .h
H_SOURCE = $(wildcard *.h) 

RM = -rm -f

.PHONY: default all clean

default: $(SAIDA)

all: default

debug: default
debug: DEBUG = -DDEBUG


%.o: %.c $(H_SOURCE)
	$(C_COMPILER) $(FLAGS) $(DEBUG) -c $< -o $@
# Se o make for interrompido a saida nao vai ser deletada
.PRECIOUS: $(SAIDA) $(C_SOURCE)

$(SAIDA): $(C_SOURCE)
	$(C_COMPILER) $(C_SOURCE) $(FLAGS)  -o $@
	@echo "\nCompilado! Arquivo gerado: pingpong-scheduler"
# função de limpeza
clean:
	$(RM) *.o 
	$(RM) $(SAIDA)
	@echo "Foi Limpo"
c: 
	$(RM) *.o 
	$(RM) $(SAIDA)
	@echo "Foi Limpo"
