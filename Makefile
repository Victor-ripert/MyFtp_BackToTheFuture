##
## EPITECH PROJECT, 2026
## plazza
## File description:
## Makefile
##

NAME        =   MyFtp

CXX         =   g++

SRC         =   src/main.cpp

OBJ         =   $(SRC:.cpp=.o)

CXXFLAGS    =   -Wall -Wextra -Wno-deprecated-declarations -I./include
DEBUGFLAGS  =   -g3

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all debug clean fclean re