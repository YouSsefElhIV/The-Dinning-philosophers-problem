# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-haya <yel-haya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/08 16:33:52 by yel-haya          #+#    #+#              #
#    Updated: 2025/04/12 16:20:41 by yel-haya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BONUS_NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = philosophers.c helpers.c helpers2.c helpers3.c helpers4.c
B_SRC = bonus_file/philosophers_bonus.c bonus_file/helpers1_bonus.c bonus_file/helpers2_bonus.c\
bonus_file/helpers3_bonus.c bonus_file/helpers4_bonus.c

OBJ = $(SRC:.c=.o)
OBJB = $(B_SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%_bonus.o: %_bonus.c bonus_file/philosophers_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $(BONUS_NAME)

all: $(NAME) $(BONUS_NAME)

clean:
	rm -rf $(OBJ) $(OBJB)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all
