IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../obj
LDIR=../lib
BIN=../bin

LIBS=-lm

_DEPS = dynamic_tree.h path.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = dynamic_tree.o path.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dtree: $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

run:
	$(BIN)/dtree


# mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

# SRC=src
# INCLUDES=include
# ODIR =obj
# LDIR=lib

# # SRC=$(mkfile_path)/src
# # INCLUDES=$(mkfile_path)/include
# # ODIR =$(mkfile_path)/obj
# # LDIR=$(mkfile_path)/lib


# CC=gcc
# CFLAGS=-I $(INCLUDES) -Wall

# # _DEPS = path.h dynamic_tree.h
# # DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# # _OBJ = dynamic_tree.o path.o
# # OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# LIBS = -lm

# dtree: $(OBJ)
# 	gcc -o $@ $^ $(CFLAGS) $(LIBS) $(SRC)/dynamic_tree.c

# $(ODIR)/%.o: $(SRC)/%.c $(DEPS)
# 	$(CC) -c -o ../$(ODIR)@ $< $(CFLAGS)

# clean:
# 	rm -rf *.o

# run:
# 	./dtree
