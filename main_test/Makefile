#############################
#         VARIABLES         #
#############################
#### FILE STRUCTURE ####
NAME	:=	test_printf

SRC		=	\
	main.c				\


SRCDIR	:=	src
INCDIR	:=	inc
LIBDIR	:=	ft_printf

BUILDDIR	:=	build
OBJDIR		:=	$(BUILDDIR)/obj
DBGDIR		:=	$(BUILDDIR)/debug
DEPDIR		:=	$(BUILDDIR)/dep

# File used as a command output buffer
TMP		:=	build/tmp.txt

#### LIBRARY ####
# Libft
LIBFT_PRTF_PATH	:= $(LIBDIR)/
include $(LIBFT_PRTF_PATH)/include.mk

#### COMPILER ####
CC		?=	cc

INCFLAG	:= -I $(INCDIR) $(LIB_INC)
# Using gnu insted of c11 because of lstat which, guess what,
# is not ansi compilant
STDFLAG	?=	-std=gnu11
WFLAGS	?=	-Wall -Wextra -Werror -pedantic
CFLAGS	=	$(WFLAGS) $(INCFLAG) $(STDFLAG)

DEPGEN	:=	$(CC)
DEPFLAG	:=	-MM $(INCFLAG)

LD		:=	$(CC)
LDFLAG	=	$(LIB_LINK) $(WFLAGS)

#############################
#    MAKEFILE VARIABLES     #
#############################
#### FILE STRUCTURE ####
# *LOCA is the list of all subdirectory in a directory
SRCLOCA	:=	$(shell find $(SRCDIR) -type d)
OBJLOCA	:=	$(subst $(SRCDIR), $(OBJDIR), $(SRCLOCA))
DBGLOCA	:=	$(subst $(SRCDIR), $(DBGDIR), $(SRCLOCA))
DEPLOCA	:=	$(subst $(SRCDIR), $(DEPDIR), $(SRCLOCA))

OBJ		:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DBG		:=	$(addprefix $(DBGDIR)/, $(SRC:.c=.o))
DEP		:=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))
SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))

#### COMMAND ####
# Fill the variable if the command exist, note &> does not work
CLANG_INSTALLED	:= $(shell which clang > /dev/null 2> /dev/null && echo yes)

#### COLORS ####
ifdef TERM
# Ansi excape color sequences
RED			:=	"\033[1;31m"
GREEN		:=	"\033[0;32m"
BGREEN		:=	"\033[1;32m"
BLUE		:=	"\033[0;34m"
YELLOW		:=	"\033[0;33m"
PURPLE		:=	"\033[0;35m"
CYAN		:=	"\033[0;36m"
GREY		:=	"\033[0;37m"

# When printed reset the color
COLRESET	:=	"\033[0m"

# Move the cursor at the begining of the line
MOVELINE	:=	"\033[1A"
# Erase current line
CLEARLINE	:=	"\033[K"

COMPCOLOR	:=	$(GREEN)
LINKCOLOR	:=	$(PURPLE)
ONGOINGCOL	:=	$(YELLOW)
KOCOLOR		:=	$(RED)
RMCOLOR		:=	$(GREY)
DEBUGCOLOR	:=	$(YELLOW)

CFLAGS	+=  -fcolor-diagnostics
LDFLAG	+=  -fcolor-diagnostics
endif

#############################
#           RULES           #
#############################
#### COMPILE ####
# Standard rule used when just calling $> make
all:		$(NAME)

# Program linkage
$(NAME):	$(OBJ) | $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(LD) -o $(NAME) $(OBJ) $(LDFLAG) 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(LINKCOLOR)[sh]$(COLRESET)"	: created" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP)) \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: linkage fail" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)

# Compilation and .d generation
$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(CC) -c $< $(CFLAGS) -o  $@ 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(COMPCOLOR)[OK]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g") \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

# Lib Compilation
$(LIBFT_PRTF_PATH)/$(LIBFT_PRTF):
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory > $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(CYAN)[OK]$(COLRESET)"	: "$@ ; rm $(TMP)) \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)

# Dir created to store build cache
$(OBJDIR):
	@ mkdir -p $(OBJLOCA)
$(DBGDIR):
	@ mkdir -p $(DBGLOCA)
$(DEPDIR):
	@ mkdir -p $(DEPLOCA)
$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)

# Recompile with as much warning as possible
warn:	WFLAGS := -Wall -Wextra -ansi -Wpedantic -Wno-vla
warn:	WFLAGS += -Wstrict-prototypes -Wunreachable-code  -Wwrite-strings
warn:	WFLAGS += -Wpointer-arith -Wbad-function-cast -Wcast-align -Wcast-qual
# If clang is installed also add this exclusive warning
ifdef CLANG_INSTALLED
warn:	CC := clang
warn:	WFLAGS += -Weverything
endif
warn:	lre

#### FORBIDEN FUNCTION ####
# Check forbiden funcion call
# All functions listed in .function_whitelist.txt are authorised
ffcheck:	$(NAME)
	@ nm -u $(NAME) \
		| sed -e 's/^\s*U\s//g' \
		| grep -Ev '^\s*w\s|^__|dyld_stub_binder' \
		| grep -Ev 1> $(TMP) 2> $(TMP) \
			`cat .function_whitelist.txt \
			| sed -e 's/^/\^_?/g' \
			| sed -e 's/$$/|/g' \
			| tr -d '\n' \
			| sed 's/|$$//g'` \
		; wc -l < $(TMP) \
		| grep -e '^\s*\0$$' 1> /dev/null 2> /dev/null \
	&& echo $(BGREEN)[func]$(COLRESET)"	: no forbiden functions found" \
	|| (echo $(RED)[func]$(COLRESET)"	: forbiden functions found" \
		; cat $(TMP) \
		| sed -e "s/^/    /g" \
		; rm $(TMP))

#### NORM ####
norm:	| $(BUILDDIR)
ifdef TERM
	@ echo $(ONGOINGCOL)[norm]$(COLRESET)"	: "Will it pass ?$(MOVELINE)
endif
	@ norminette $(SRC) $(INCDIR) \
		| (! grep -E -B 1 "(^Warning|^Error)" 1> $(TMP) 2> $(TMP)) \
		&& echo $(CLEARLINE)$(CYAN)[NORM]$(COLRESET)"	:" \
				"pass, it's ok for now" \
		|| (echo $(CLEARLINE)$(RED)[NORM]$(COLRESET)"	:" \
				"you failed miserably !" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP))

sure: warn ffcheck norm

#### DEBUGING ####
$(DBGDIR)/%.o:		$(SRCDIR)/%.c | $(DBGDIR) $(DEPDIR)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(CC) -c $< $(CFLAGS) -o  $@ 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(COMPCOLOR)[OK]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g") \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: "$@ \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)
	@ $(DEPGEN) -c $< $(DEPFLAG) -MQ $@ \
		> $(subst $(SRCDIR), $(DEPDIR), $(<:.c=.d))

debug:	WFLAGS		:= -g -ggdb
debug:	COMPCOLOR	:=	$(DEBUGCOLOR)
debug:	LINKCOLOR	:=	$(DEBUGCOLOR)
debug:	$(DBG) | $(LIBFT_PRTF_PATH)/$(LIBFT_PRTF)
ifdef TERM
	@ echo $(ONGOINGCOL)[...]$(COLRESET)"	: "$@$(MOVELINE)
endif
	@ $(LD) -o $(NAME) $(DBG) $(LDFLAG) 1> $(TMP) 2> $(TMP) \
		&& (echo $(CLEARLINE)$(LINKCOLOR)[sh]$(COLRESET)"	:"\
				"ready to be beaten" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP)) \
		|| (echo $(CLEARLINE)$(KOCOLOR)[KO]$(COLRESET)"	: linkage fail" \
			; cat $(TMP) \
			| sed -e "s/^/    /g" \
			; rm $(TMP) \
			; exit 1)

debugclean:
	@ rm -r $(DBGDIR) 1> /dev/null 2> /dev/null \
		&& echo $(DEBUGCOLOR)[CLR]$(COLRESET)"	:" debug obj \
		; (exit 0)

rdebug: debugclean debug

#### LOCAL (Don't recompile lib) ####
lclean:
	@ rm -r $(BUILDDIR) 1> /dev/null 2> /dev/null \
		&& echo $(RMCOLOR)[CLR]$(COLRESET)"	:" obj \
		; (exit 0)

lfclean: lclean
	@ rm -Rf *.dSYM 1> /dev/null 2> /dev/null
	@ rm $(NAME) 1> /dev/null 2> /dev/null \
		&& echo $(RMCOLOR)[CLR]$(COLRESET)"	:" $(NAME) \
		; (exit 0)

lre: lfclean all

#### MANDATORY ####
clean: lclean
	@ rm -f $(TMP)
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory clean
	@ $(MAKE) -C $(TESTDIR) --no-print-directory clean

fclean:	lfclean
	@ $(MAKE) -C $(LIBFT_PRTF_PATH) --no-print-directory fclean

re:		fclean all

#############################
#          SETTING          #
#############################
# Add rule to phony if they are not based on actual files.
.PHONY: all clean fclean re
.PHONY: callg ffcheck norm sure
.PHONY: debug rdebug debugclean
.PHONY: warn
.PHONY: lclean lfclean lre

#############################
#         DEPENDENCY        #
#############################
# Include all custom dependency rules created in .d's
# the '-' prevent error in case of non existing files
-include $(DEP)
