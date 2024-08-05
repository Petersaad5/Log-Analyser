ECHO=@echo
RM=rm
EDL=g++
COMP=g++
CCFLAGS=-ansi -pedantic -Wall -std=c++17 # -g -DMAP
RMFLAGS=-f
LDFLAGS=$(CCFLAGS)
LIBS=
SRC=src
MAINFILE=$(SRC)/main
TESTFILE=$(SRC)/test
INT=$(addprefix $(SRC)/, Analyzer.h AnalyzerPage.h LogFile.h Log.h DateTime.h)
REAL=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
EFFACE=clean
BIN=bin
EXE=$(BIN)/analog
TEST_EXE=$(BIN)/test

.PHONY:$(EFFACE)

$(EXE): $(OBJ) $(MAINFILE).o
	$(ECHO) "Edition des liens de $(EXE)"
	$(EDL) -o $(EXE) $(MAINFILE).o $(OBJ) $(LIBS) $(LDFLAGS)

$(TEST_EXE): $(OBJ) $(TESTFILE).o
	$(ECHO) "Edition des liens de $(TESTFILE)"
	$(EDL) -o $(TESTFILE) $(TESTFILE).o $(OBJ) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(ECHO) "Compilation de <$<>"
	$(COMP) -o $@ -c $< $(CCFLAGS)

$(EFFACE):
	$(ECHO) "Nettoyage"
	$(RM) $(RMFLAGS) $(OBJ) $(EXE) $(TESTFILE) $(TESTFILE).o $(MAINFILE).o core
