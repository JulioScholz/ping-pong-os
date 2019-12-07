SAIDA0 = pingpong-mqueue

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
OBJECT_0 = pingpong-mqueue.o
OBJECT_1 = queue.o
H_SOURCE = $(wildcard *.h)


%.o: %.c $(H_SOURCE)
	$(C_COMPILER) $(FLAGS) $(DEBUG) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

pingpong-contab:
$(SAIDA0): $(OBJECTS) $(OBJECT_0) $(OBJECT_1)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_0) $(OBJECT_1) $(FLAGS) $(LIBS) -o $@ -lm
	@echo "Compilado -> ./pingpong-mqueue\n"

clean: 
	$(RM) *.o
	$(RM) $(SAIDA0) 
	@echo "\nFoi Limpo!\n"

c:
	$(RM) *.o
	$(RM) $(SAIDA0) 
	@echo "\nFoi Limpo!\n"

