# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kebris-c <kebris-c@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 13:07:54 by kebris-c          #+#    #+#              #
#    Updated: 2026/02/12 16:19:11 by kebris-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re \
	iflib setup help norm norm_bonus norm_libft norm_all val val_bonus

# 📚 Basic project variables
#	Notes:
#		P = PROJECT ; B = BONUS ; N = NAME of it's library *.a
#
PROJECT		= minishell
P_BONUS		= $(PROJECT)_bonus

NAME		= $(PROJECT).a
N_BONUS		= $(P_BONUS).a

# 🔧 Compiler and flags
#
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -D_XOPEN_SOURCE=700

# 🔨 Tools
#
AR      = ar rcs
RM      = rm -rf
NORM    = norminette

# 📂 Fast path variables / dirs
#
SRC_DIR		= src/
INCL_DIR	= include/
OBJS_DIR	= objs/
DEPS_DIR	= deps/
# If there is bonus
#
BONUS_DIR		= bonus/
B_SRC_DIR		= bonus/src/
B_INCL_DIR		= bonus/include/
B_OBJS_DIR		= bonus/objs/
B_DEPS_DIR		= bonus/deps/
# If there is Libft
#
LIB_DIR			= libft/
L_SRC_DIR		= libft/src/
L_INCL_DIR		= libft/include/
L_OBJS_DIR		= libft/objs/
L_DEPS_DIR		= libft/deps/

# 🎯 Sources, Objects and Deps	! Remember to update the list wvery project
#
SRCS	= $(shell find src/ -name '*.c')
OBJS	= $(patsubst $(SRC_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
DEPS	= $(patsubst $(OBJS_DIR)%.o,$(DEPS_DIR)%.d,$(OBJS))
# And if there is bonus...
#
B_SRCS	= $(shell find bonus/src/ -name '*.c')
B_OBJS	= $(patsubst $(B_SRC_DIR)%.c,$(B_OBJS_DIR)%.o,$(B_SRCS))
B_DEPS	= $(patsubst $(B_OBJS_DIR)%.o,$(B_DEPS_DIR)%.d,$(B_OBJS))

# 📄 Headers. First, we need to check if there is a libft dir
#
HAS_LIBFT = $(shell \
    if [ -d libft ]; then \
        echo yes; \
    else \
        echo no; \
    fi)
HEADERS = -I$(INCL_DIR)
ifeq ($(HAS_LIBFT),yes)
    HEADERS += -I$(L_INCL_DIR)
endif

# ------------------------------------------------ #
#    COMPILE COMMANDS 			                   #
# ------------------------------------------------ #
#	Notes:
#		$(1) == flags	$(2) == Dependency (library *.a)	$(3) == Executable Name
#
define COMPILE_PROJECT
	@if [ -d $(LIB_DIR) ]; then \
		$(CC) $(1) $(2) -L$(LIB_DIR) -lft -lreadline -o $(3); \
	else \
		$(CC) $(1) $(2) -o $(3); \
	fi
endef

-include $(DEPS)
-include $(B_DEPS)

#------------------------------------------------#
#   BASIC RULES / LIBRARY COMMANDS               #
#------------------------------------------------#

#	Basic options
#
all: iflib $(PROJECT)

bonus: iflib $(N_BONUS) $(P_BONUS)

iflib:
	@if [ -d $(LIB_DIR) ]; then \
		$(MAKE) -C $(LIB_DIR); \
	fi

#	Headers compilers
#
$(NAME): $(OBJS) | setup
	@$(AR) $(NAME) $(OBJS);

$(N_BONUS): $(B_OBJS) | setup
	@$(AR) $(N_BONUS) $(B_OBJS);

#	Objects & bonus objects Compilers
#
$(OBJS_DIR)%.o: $(SRC_DIR)%.c | setup
	@echo "🔨 Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP $(HEADERS) -g -c $< -o $@
	@mv $(OBJS_DIR)$*.d $(DEPS_DIR)

$(B_OBJS_DIR)%.o: $(B_SRC_DIR)%.c | setup
	@echo "🔨 Compiling bonus $<..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP $(HEADERS) -c $< -o $@
	@mv $(B_OBJS_DIR)$*.d $(B_DEPS_DIR)

#	Cleaners
#
clean:
	@$(MAKE) clean -C $(LIB_DIR)
	@$(RM) \
		$(OBJS_DIR) $(B_OBJS_DIR) \
		$(DEPS_DIR) $(B_DEPS_DIR)

fclean:
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(RM) \
		$(OBJS_DIR) $(B_OBJS_DIR) \
		$(DEPS_DIR) $(B_DEPS_DIR) \
		$(NAME) $(N_BONUS) \
		$(PROJECT) $(P_BONUS)

#	Reworks from zero
#
re: fclean all

re_bonus: fclean bonus

#------------------------------------------------#
#   PROJECT COMPILATION                          #
#------------------------------------------------#

$(PROJECT): $(NAME)
	$(call COMPILE_PROJECT,$(CFLAGS),$(NAME),$(PROJECT))
	@if [ -f $(PROJECT) ]; then \
		echo "✅ $(PROJECT) linked"; \
	else \
		echo "⚠️ Failed to build $(PROJECT)"; \
	fi

$(P_BONUS): $(N_BONUS)
	$(call COMPILE_PROJECT,$(CFLAGS),$(N_BONUS),$(P_BONUS))
	@if [ -f $(P_BONUS) ]; then \
		echo "✅ $(P_BONUS) linked"; \
	else \
		echo "⚠️ Failed to build $(P_BONUS)"; \
	fi

#------------------------------------------------#
#   NORMINETTE & VALGRIND                        #
#------------------------------------------------#

norm:
	@if $(NORM) $(INCL_DIR) $(SRC_DIR) 2>/dev/null; then \
		exit 0; \
	else \
		exit 1; \
	fi

norm_bonus:
	@if $(NORM) $(B_INCL_DIR) $(B_SRC_DIR) 2>/dev/null; then \
		exit 0; \
	else \
		exit 1; \
	fi

norm_libft:
	@if $(NORM) $(L_INCL_DIR) $(L_SRC_DIR) 2>/dev/null; then \
		exit 0; \
	else \
		exit 1; \
	fi

norm_all: norm norm_bonus norm_libft

val: $(PROJECT)
	valgrind -s \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		--trace-children=yes \
		--track-fds=yes \
		--suppressions=.valgrind.sup \
		--log-file=.val_logs.txt \
		./$(PROJECT)

val_bonus: $(P_BONUS)
	valgrind -s \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		--trace-children=yes \
		--track-fds=yes \
		--suppressions=.valgrind.sup \
		--log-file=.val_logs.txt \
		./$(P_BONUS)

# ------------------------------------------------ #
#  Setup rule: normalize project structure         #
# ------------------------------------------------ #

setup:
	@mkdir -p $(SRC_DIR) $(INCL_DIR) $(OBJS_DIR) $(DEPS_DIR)
	@if [ -d $(BONUS_DIR) ]; then \
		mkdir -p $(B_SRC_DIR) $(B_INCL_DIR) $(B_OBJS_DIR) $(B_DEPS_DIR); \
		find . -maxdepth 1 -name "*_bonus.c" ! -path "./$(B_SRC_DIR)*" -exec mv -n {} $(B_SRC_DIR)/ \;; \
		find . -maxdepth 1 -name "*_bonus.h" ! -path "./$(B_INCL_DIR)*" -exec mv -n {} $(B_INCL_DIR)/ \;; \
		find . -maxdepth 1 -name "*_bonus.o" ! -path "./$(B_OBJS_DIR)*" -exec mv -n {} $(B_OBJS_DIR)/ \;; \
		find . -maxdepth 1 -name "*_bonus.d" ! -path "./$(B_DEPS_DIR)*" -exec mv -n {} $(B_DEPS_DIR)/ \;; \
	fi
	@find . -maxdepth 1 -name "*.c" ! -path "./$(SRC_DIR)*" -exec mv -n {} $(SRC_DIR)/ \;
	@find . -maxdepth 1 -name "*.h" ! -path "./$(INCL_DIR)*" -exec mv -n {} $(INCL_DIR)/ \;
	@find . -maxdepth 1 -name "*.o" ! -path "./$(OBJS_DIR)*" -exec mv -n {} $(OBJS_DIR)/ \;
	@find . -maxdepth 1 -name "*.d" ! -path "./$(DEPS_DIR)*" -exec mv -n {} $(DEPS_DIR)/ \;

# ------------------------------------------------ #
#  Help rule: Be user-friendly			           #
# ------------------------------------------------ #
# Make sure this rule is updated with correct data
#
help:
	@echo ""
	@echo "==================== HELP ===================="
	@echo ""
	@echo "📦 Basic build:"
	@echo "  all				-> build $(NAME) and $(PROJECT) (default)"
	@echo "  bonus				-> build $(N_BONUS) and $(P_BONUS)"
	@echo ""
	@echo "🧹 Cleaning:"
	@echo "  clean				-> remove .o and .d files (objs and deps)"
	@echo "  fclean			-> clean + remove binaries and .a"
	@echo "  re				-> full rebuild (fclean + all)"
	@echo ""
	@echo "🧠 Analysis & tools:"
	@echo "  norm				-> run norminette on main project"
	@echo "  norm_bonus			-> run norminette on bonus project"
	@echo "  norm_libft			-> run norminette on libft project"
	@echo "  norm_all			-> run norminette on main, bonus and libft projects"
	@echo "  val				-> run valgrind with roughness flags on mandatory project"
	@echo "  val_bonus			-> run valgrind with roughness flags on bonus project"
	@echo ""
	@echo "📁 Project setup:"
	@echo "  setup				-> create normalized folder structure"
	@echo ""
	@echo "==============================================="
	@echo ""

