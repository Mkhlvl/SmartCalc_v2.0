CC=g++
FLAGS=-std=gnu++17 -Wall -Wextra -Werror

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=--coverage -lgtest -lpthread 
  CHECK_LEAKS=valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=log.txt
else
  LIBS=--coverage -lgtest
  CHECK_LEAKS= leaks -atExit -- 
endif

all: clean tests gcov_report

gcov_report: tests
	@gcovr --html --html-details -o report.html  
	@open report.html

style:
	clang-format -n Calculator/*.cc Calculator/*.h

tests: clean
	$(CC) $(FLAGS) -g ./Calculator/my_smartcalc.cc test.cc $(LIBS) && ./a.out

leaks: tests
	$(CHECK_LEAKS) ./a.out

install:
	@cd ../build && tar -xf SmartCalc.tar 
	@cd ../build/Calculator; cmake cmakelists.txt
	@make -C ../build/Calculator
	@cp -rf ../build/Calculator/CalcCPP.app  $(HOME)/Desktop

uninstall: clean
	@rm -rf $(HOME)/Desktop/CalcCPP.app
	@rm -rf ../build

dist: clean
	@mkdir -p ../build
	@tar -czvf ../build/SmartCalc.tar ./Calculator/*

dvi:
	@open dvi.txt

clean:
	@rm -rf rep* ../build ../.vscode a.out *.gcno *.gcda 