NAME = 		parser.a

GREEN = 	"\033[1;32m"
BREAK = 	"\033[0m"

SRC = 		$(wildcard src/*.cpp)

INC =			$(wildcard includes/*.hpp)

CFLAGS =	-Wall -Wextra -Werror -std=c++17 -Iincludes

TFLAGS =	-lgtest -lgmock -pthread

TEST =		tests/tests.cpp

TEST_EX =	tests/tests

all: 			$(NAME)

$(NAME): 	Makefile $(SRC) $(INC)
					@c++ $(CFLAGS) -c $(SRC)
					@ar rcs $(NAME) *.o
					@mv -f *.o obj
					@echo $(GREEN)"Compile $(NAME) done!"$(BREAK)

re:				fclean all

clean:
					@rm -rf $(TEST_EX) tests/tests_report.xml coverage/* obj/* output/*

fclean:		clean
					@rm -f $(NAME)

linter:
					@clang-format -n $(SRC) $(INC)

test:			all
					@c++ $(CFLAGS) $(TEST) $(NAME) -o $(TEST_EX) $(TFLAGS)
					@$(TEST_EX) --gtest_filter=-*skip* --gtest_output="xml:tests/tests_report.xml"

leaks:		all
					@c++ $(CFLAGS) $(TEST) $(NAME) -o $(TEST_EX) $(TFLAGS)
					@leaks --atExit -- $(TEST_EX)

cover:		clean
					@c++ $(CFLAGS) -c $(SRC) --coverage -g -O1
					@ar rcs cover.a *.o
					@c++ $(CFLAGS) --coverage $(TEST) cover.a -o $(TEST_EX) $(TFLAGS)
					@mv -f *.o obj
					@$(TEST_EX)
					@gcovr -s --html-details cover_out.html
					@mv -f cover_out* *gcda *gcno coverage
					@rm -f cover.a

.PHONY:		all re clean fclean test linter leaks cover
