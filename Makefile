# Project's name
PROJECT = process-scheduler

SOURCE = $(PROJECT).c
EXECUTABLE = $(PROJECT).bin
RELEASE = $(PROJECT).zip

TEST = 1

# List used to iterate trough the test files
FIRST = 1
LAST = 12
NUMBERS = $(shell seq ${FIRST} ${LAST})

# Compiler's flags
# 	-Wall = Warnings
# 	-g = debugging
#	-o = output

# Valgrind's flags
#  --leak-check=full == see wich lines are causing leak

all:
	gcc -std=c99 -g -Wall -o $(EXECUTABLE) $(SOURCE) src/*.c -Iinc/

run:
	./$(EXECUTABLE)

clean:
# Check if there is any executable before removing
ifneq (,$(wildcard $(EXECUTABLE)))
	rm $(EXECUTABLE)
endif

cleanrelease:
ifneq (,$(wildcard $(RELEASE)))
	rm $(RELEASE)
endif

zip:
	$(MAKE) clean
	$(MAKE) cleanrelease
	$(MAKE) all
	zip $(PROJECT).zip ./$(SOURCE) ./Makefile src/* inc/* README.txt

cleantesting:
ifneq (,$(wildcard testing/*))
	rm -rf testing/*
endif

test:
	$(MAKE) clean
	$(MAKE) all
	./$(EXECUTABLE) < testing/input/$(TEST).in > testing/my_output/$(TEST).out

testfull:
	$(MAKE) all
	$(foreach var,$(NUMBERS), ./$(EXECUTABLE) < testing/input/$(var).in > testing/my_output/$(var).out;)

organizetests:
	mkdir testing/input
	mv testing/*.in testing/input/ 
	mkdir testing/output
	mv testing/*.out testing/output/ 
	mkdir testing/my_output
	mkdir testing/my_leak_output
	rm testing/README.txt

leak:
	$(MAKE) clean
	$(MAKE) all
	valgrind --leak-check=full ./$(EXECUTABLE) < testing/input/$(TEST).in

leakfull:
	$(MAKE) all
	$(foreach var,$(NUMBERS), echo '$(var)'; valgrind --leak-check=full ./$(EXECUTABLE) < testing/input/$(var).in > testing/my_leak_output/$(var).out;)

leakfulllog:
	$(MAKE) all
	$(foreach var,$(NUMBERS), echo '$(var)'; valgrind --leak-check=full ./$(EXECUTABLE) < testing/input/$(var).in;)
