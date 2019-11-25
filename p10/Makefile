CC		= gcc 
CFLAGS	= -g -Wall
HEADERS = datatypes.h pingpong.h queue.h
MAINFILE1 = pingpong-semaphore.o
MAINFILE2 = pingpong-racecond.o
MAINFILE3 = pingpong-prodcons.o

OBJECTS = pingpong.o queue.o
PROJECTNAME1 = semaphore
PROJECTNAME2 = racecond
PROJECTNAME3 = prodcons


debug: DEBUG = -DDEBUG

default: $(PROJECTNAME3)

all: $(MAINFILE1) $(MAINFILE2)  $(OBJECTS)
	$(CC) $(MAINFILE1) $(OBJECTS) -o $(PROJECTNAME1) $(CFLAGS)
	$(CC) $(MAINFILE2) $(OBJECTS) -o $(PROJECTNAME2) $(CFLAGS)
	$(CC) $(MAINFILE3) $(OBJECTS) -o $(PROJECTNAME3) $(CFLAGS)


debug: all

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< $(DEBUG) -o $@

$(PROJECTNAME1): $(MAINFILE1) $(OBJECTS)
	$(CC) $(MAINFILE1) $(OBJECTS) -o $@ $(CFLAGS)

$(PROJECTNAME2): $(MAINFILE2) $(OBJECTS)
	$(CC) $(MAINFILE2) $(OBJECTS) -o $@ $(CFLAGS)
	
$(PROJECTNAME3): $(MAINFILE3) $(OBJECTS)
	$(CC) $(MAINFILE3) $(OBJECTS) -o $@ $(CFLAGS)



# limpar os executáveis
clean:
	rm -f $(MAINFILE1) $(MAINFILE2) $(OBJECTS)
	rm -f $(PROJECTNAME1) $(PROJECTNAME2) 
c:
	rm -f $(MAINFILE1) $(MAINFILE2) $(MAINFILE3) $(OBJECTS)
	rm -f $(PROJECTNAME1) $(PROJECTNAME2) $(PROJECTNAME3)  