# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/29 20:14:15 by rexposit          #+#    #+#              #
#    Updated: 2026/09/29 20:46:16 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = identify_type

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp \
		Base.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re