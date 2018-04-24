# Samantha Gant
# slg160330@utdallas.edu
# CS3377.502
# Prog 6 Makefile

CXX = g++
CXXFLAGS = -Wall -g -I /scratch/perkins/include
SRCS = cdkexample.cc
OBJS = $(SRCS:cc=o)

LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

all : program6.exe

clean : 
	rm -f $(OBJS) *~ \#~

backup : clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell pwd))
	@$(eval MKBKUPNAME := ~/backups/Program6-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to $(MKBKUPNAME) from $(CURDIRNAME)
	@echo
	@tar -cvzf $(MKBKUPNAME) $(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Backup Complete

program6.exe : $(OBJS) cs3377.bin
	$(CXX) $(OBJS) $(CXXFLAGS) -o program6.exe $(LDFLAGS) $(LDLIBS)

cdkexample.o : cdkexample.cc
	$(CXX) cdkexample.cc $(CXXFLAGS) -c

