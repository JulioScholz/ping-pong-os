SAIDA0 = pingpong-sleep

LIBS = 
C_COMPILER = gcc
FLAGS = -Wall

RM = -rm -f

.PHONY: default all clean

default: $(SAIDA0) $(SAIDA1) 

all: default
debug: default

debug: DEBUG = -DDEBUG

OBJECTS = pingpong.o
OBJECT_0 = pingpong-sleep.o
OBJECT_1 = queue.o
H_SOURCE = $(wildcard *.h)


%.o: %.c $(H_SOURCE)
	$(C_COMPILER) $(FLAGS) $(DEBUG) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

pingpong-contab:
$(SAIDA0): $(OBJECTS) $(OBJECT_0) $(OBJECT_1)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_0) $(OBJECT_1) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> ./pingpong-sleep\n"

clean: 
	$(RM) *.o
	$(RM) $(SAIDA0) 
	@echo "\nFoi Limpo!\n"

c:
	$(RM) *.o
	$(RM) $(SAIDA0) 
	@echo "\nFoi Limpo!\n"

