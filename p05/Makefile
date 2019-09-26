SAIDA0 = pingpong-preempcao
SAIDA1 = signal
SAIDA2 = timer
LIBS = 
C_COMPILER = gcc
FLAGS = -Wall

RM = -rm -f

.PHONY: default all clean

default: $(SAIDA0) $(SAIDA1) $(SAIDA2) 

all: default
debug: default

debug: DEBUG = -DDEBUG

OBJECTS = pingpong.o
OBJECT_0 = pingpong-preempcao.o
OBJECT_1 = signal.o
OBJECT_2 = timer.o
OBJECT_3 = queue.o
H_SOURCE = $(wildcard *.h)


%.o: %.c $(H_SOURCE)
	$(C_COMPILER) $(FLAGS) $(DEBUG) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)


$(SAIDA0): $(OBJECTS) $(OBJECT_0) $(OBJECT_3)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_0) $(OBJECT_3) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> ./pingpong-preempcao\n"
signal:
$(SAIDA1):  $(OBJECT_1)
	$(C_COMPILER) $(OBJECT_1) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> ./signal\n"
timer:
$(SAIDA2):$(OBJECT_2)
	$(C_COMPILER) $(OBJECT_2) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> ./timer\n"

clean: 
	$(RM) *.o
	$(RM) $(SAIDA0) $(SAIDA1) $(SAIDA2) $(SAIDA3) 
	@echo "\nFoi Limpo!\n"

c:
	$(RM) *.o
	$(RM) $(SAIDA0) $(SAIDA1) $(SAIDA2) $(SAIDA3) 
	@echo "\nFoi Limpo!\n"

