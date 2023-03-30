NAME = btc

SRCS =	main.cpp \
		BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

CXX = c++

#CXXFLAGS = -Wall -Werror -Wextra -std=c++98

CXXFLAGS =

SANIT = -g3 -fsanitize=address

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

debug:
	clang++ $(CXXFLAGS) $(SANIT) $(SRCS) -o $(NAME)

re: fclean all

.PHONY: all clean fclean re