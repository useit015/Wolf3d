# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 22:15:58 by ebatchas          #+#    #+#              #
#    Updated: 2019/01/05 18:26:05 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

SRCDIR=srcs
LIBDIR=libs
HEADDIR=includes
CFLAGS=-Wall -Wextra -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -I$(HEADDIR) -L$(LIBDIR)/ -lft -lm -lSDL2main \
		 -lSDL2

SRC=$(SRCDIR)/main.c\
	$(SRCDIR)/sdl_init.c\
	$(SRCDIR)/input.c\
	$(SRCDIR)/sdl_draw.c\
	$(SRCDIR)/complex.c\
	$(SRCDIR)/utils.c\
	$(SRCDIR)/tools.c\
	$(SRCDIR)/draw.c\
	$(SRCDIR)/wolf.c\
	$(SRCDIR)/wolf_type.c\
	$(SRCDIR)/wolf_draw_helper.c\
	$(SRCDIR)/read_file.c

OBJ=$(LIBDIR)/main.o\
	$(LIBDIR)/sdl_init.o\
	$(LIBDIR)/input.o\
	$(LIBDIR)/sdl_draw.o\
	$(LIBDIR)/complex.o\
	$(LIBDIR)/utils.o\
	$(LIBDIR)/tools.o\
	$(LIBDIR)/draw.o\
	$(LIBDIR)/wolf_draw_helper.o\
	$(LIBDIR)/wolf_type.o\
	$(LIBDIR)/wolf.o\
	$(LIBDIR)/read_file.o

NAME=wolf

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBDIR)/libft/ fclean && make -C $(LIBDIR)/libft
	cp $(LIBDIR)/libft/libft.a $(LIBDIR)/
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean fclean

clean:
	rm -rf $(LIBDIR)/*.o
	make -C $(LIBDIR)/libft clean

fclean:clean
	rm -rf $(NAME)
	make -C $(LIBDIR)/libft fclean

re : fclean all
