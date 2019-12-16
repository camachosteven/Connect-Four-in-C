# Steven Camacho's Connect-Four game makefile

# used to identify what files are desired to be deleted
objects = MainConnect.o GameFunctions.o 

CC = gcc # Compiler
EXECUTE = -o # create custom exe file name
COMPILE = -c -std=c99 # compile using c99 standard
HEADER = ProtoConstDef.h # user-defined header file

# all target used to both build executable and delete object 
# files afterwards
all: build clean

# Once prerequisites are met, create excecutable file MainServer
# to run the program.
build:  $(objects)
	 $(CC) $(objects) $(EXECUTE) FinalGame

# Create object code file for source file with main
MainConnect.o: $(HEADER)
	$(CC) $(COMPILE) MainConnect.c 

# Create object code file for ParentFunctions source file
GameFunctions.o: $(HEADER)
	$(CC) $(COMPILE) GameFunctions.c 

# delete all specified object files
# can be performed both before and after build
clean: 
	rm -f $(objects)
