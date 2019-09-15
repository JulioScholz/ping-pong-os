SAIDA0 = contexts
SAIDA1 = pingpong-tasks1
SAIDA2 = pingpong-tasks2
SAIDA3 = pingpong-tasks3
LIBS = 
C_COMPILER = gcc
FLAGS = -Wall

RM = -rm -f

.PHONY: default all clean

default: $(SAIDA0) $(SAIDA1) $(SAIDA2) $(SAIDA3)

all: default
debug: default

debug: DEBUG = -DDEBUG


OBJECTS = pingpong.o
OBJECT_0 = contexts.o
OBJECT_1 = pingpong-tasks1.o
OBJECT_2 = pingpong-tasks2.o
OBJECT_3 = pingpong-tasks3.o
H_SOURCE = $(wildcard *.h)


%.o: %.c $(H_SOURCE)
	$(C_COMPILER) $(FLAGS) $(DEBUG) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(SAIDA0): $(OBJECTS) $(OBJECT_0)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_0) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> contexts!\n"

$(SAIDA1): $(OBJECTS) $(OBJECT_1)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_1) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> pingpong-tasks1\n"

$(SAIDA2): $(OBJECTS) $(OBJECT_2)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_2) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> pingpong-tasks2\n"

$(SAIDA3): $(OBJECTS) $(OBJECT_3)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_3) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> pingpong-tasks3\n"
c:
	$(RM) *.o
	$(RM) $(SAIDA0) $(SAIDA1) $(SAIDA2) $(SAIDA3) 
	@echo "\nFoi Limpo\n"

