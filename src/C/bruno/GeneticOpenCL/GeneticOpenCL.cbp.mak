#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = -IC:\\Users\\BrunoM\\Dropbox\\GET\\GIT\\ciml-lib\\src\\C\\bruno\\GeneticOpenCL\\include
CFLAGS = -DPROB_MUT="$(PROB_MUT)" -DSEED="$(SEED)" -DTWODEVICES="$(TWODEVICES)" -DEVOLOCL="$(EVOLOCL)" -DAVALOCL="$(AVALOCL)" -DEVOLOMP="$(EVOLOMP)" -DAVALGPU="$(AVALGPU)" -fexceptions -std=c++11 -fopenmp -Wall
RESINC = 
LIBDIR = -LC:\\Users\\BrunoM\\Dropbox\\GET\\GIT\\ciml-lib\\src\\C\\bruno\\GeneticOpenCL\\x86
LIB = 
LDFLAGS = -lOpenCL -lgomp -pthread

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -Wmissing-prototypes -Wmissing-declarations
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\GeneticOpenCL.exe

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\GeneticOpenCL.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\arvore.o $(OBJDIR_DEBUG)\\bitwise.o $(OBJDIR_DEBUG)\\genetica.o $(OBJDIR_DEBUG)\\main.o $(OBJDIR_DEBUG)\\pilha.o $(OBJDIR_DEBUG)\\utilitarios.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\arvore.o $(OBJDIR_RELEASE)\\bitwise.o $(OBJDIR_RELEASE)\\genetica.o $(OBJDIR_RELEASE)\\main.o $(OBJDIR_RELEASE)\\pilha.o $(OBJDIR_RELEASE)\\utilitarios.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG) md $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\arvore.o: arvore.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c arvore.c -o $(OBJDIR_DEBUG)\\arvore.o

$(OBJDIR_DEBUG)\\bitwise.o: bitwise.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c bitwise.c -o $(OBJDIR_DEBUG)\\bitwise.o

$(OBJDIR_DEBUG)\\genetica.o: genetica.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c genetica.c -o $(OBJDIR_DEBUG)\\genetica.o

$(OBJDIR_DEBUG)\\main.o: main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.cpp -o $(OBJDIR_DEBUG)\\main.o

$(OBJDIR_DEBUG)\\pilha.o: pilha.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c pilha.c -o $(OBJDIR_DEBUG)\\pilha.o

$(OBJDIR_DEBUG)\\utilitarios.o: utilitarios.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c utilitarios.c -o $(OBJDIR_DEBUG)\\utilitarios.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE) md $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\arvore.o: arvore.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c arvore.c -o $(OBJDIR_RELEASE)\\arvore.o

$(OBJDIR_RELEASE)\\bitwise.o: bitwise.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c bitwise.c -o $(OBJDIR_RELEASE)\\bitwise.o

$(OBJDIR_RELEASE)\\genetica.o: genetica.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c genetica.c -o $(OBJDIR_RELEASE)\\genetica.o

$(OBJDIR_RELEASE)\\main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)\\main.o

$(OBJDIR_RELEASE)\\pilha.o: pilha.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c pilha.c -o $(OBJDIR_RELEASE)\\pilha.o

$(OBJDIR_RELEASE)\\utilitarios.o: utilitarios.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c utilitarios.c -o $(OBJDIR_RELEASE)\\utilitarios.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

