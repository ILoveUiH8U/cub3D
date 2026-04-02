NAME = cub3D

all: mandatory

mandatory:
	$(MAKE) -C mandatory

bonus:
	$(MAKE) -C bonus

clean:
	$(MAKE) clean -C mandatory
	$(MAKE) clean -C bonus
	$(MAKE) clean -C libft

fclean:
	$(MAKE) fclean -C mandatory
	$(MAKE) fclean -C bonus
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all mandatory bonus clean fclean re
