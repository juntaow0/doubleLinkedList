# Makefile for Rational class

#target: dependencies
#	command to create the target

PROG = anglosaxon
PROGRAMS = \
    anglosaxon

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

CPPOPTIONS = -I../StanfordCPPLib -fvisibility-inlines-hidden -std=c++11 -g
CPPOPTIONSS = -c -g -Wall -std=c++11 
LDOPTIONS = -L../StanfordCPPLib
LIB = -lStanfordCPPLib

all: $(PROGRAMS) spl.jar

spl.jar:
	@ln -s ../StanfordCPPLib/spl.jar

$(PROG).o: $(PROG).cpp Dlist.h Dlist.cpp
	g++ $(CPPOPTIONS) -c $(PROG).cpp 

$(PROG): $(PROG).o
	g++ $(LDOPTIONS) -o $(PROG) $(PROG).o $(LIB)

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAMS)
