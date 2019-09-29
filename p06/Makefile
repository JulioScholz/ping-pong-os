SAIDA0 = pingpong-contab
SAIDA1 = pingpong-contab-prio
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
OBJECT_0 = pingpong-contab.o
OBJECT_1 = pingpong-contab-prio.o
OBJECT_3 = queue.o
H_SOURCE = $(wildcard *.h)


%.o: %.c $(H_SOURCE)
	$(C_COMPILER) $(FLAGS) $(DEBUG) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

pingpong-contab:
$(SAIDA0): $(OBJECTS) $(OBJECT_0) $(OBJECT_3)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_0) $(OBJECT_3) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> ./pingpong-contab\n"
pingpong-contab-prio:
$(SAIDA1): $(OBJECTS) $(OBJECT_1) $(OBJECT_3)
	$(C_COMPILER) $(OBJECTS) $(OBJECT_1) $(OBJECT_3) $(FLAGS) $(LIBS) -o $@
	@echo "Compilado -> ./pingpong-contab-prio\n"


clean: 
	$(RM) *.o
	$(RM) $(SAIDA0) $(SAIDA1)
	@echo "\nFoi Limpo!\n"

c:
	$(RM) *.o
	$(RM) $(SAIDA0) $(SAIDA1) 
	@echo "\nFoi Limpo!\n"

