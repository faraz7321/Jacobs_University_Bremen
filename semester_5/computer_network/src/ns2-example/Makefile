NAME = ns-simple

all: $(NAME).nam $(NAME).pdf

clean:
	rm $(NAME).data $(NAME).nam

$(NAME).nam $(NAME).data: $(NAME).tcl
	ns $(NAME).tcl

$(NAME).pdf: $(NAME).gp $(NAME).data
	gnuplot $(NAME).gp > $(NAME).pdf
