NAME=../cedomp
SRC=main.cpp Scope/Scope.cpp Semantic/VarAssign.cpp Type/Types.cpp Exceptions/VarAssignExceptions.cpp AST/AST.cpp \
	Exceptions/TypeExceptions.cpp Exceptions/CedompException.cpp
BISON=bison
FLEX=flex
CC=g++
INCLUDE=-I../include -I ../grammar
LIBS=-lfl
CFLAGS=-Wall -std=c++11
BISONSRCFILE=parser.tab.c
LEXSRCFILE=lex.yy.c
OBJS=$(SRC:.cpp=.o)
BISOBJ=$(BISONSRCFILE:.c=.o)
LEXOBJ=$(LEXSRCFILE:.c=.o)

all: $(SRC) $(BISONSRCFILE) $(LEXSRCFILE) $(NAME)

$(BISONSRCFILE): ../grammar/parser.y
	$(BISON) -d ../grammar/parser.y

$(LEXSRCFILE): ../grammar/lex.l
	$(FLEX) ../grammar/lex.l

.cpp.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@ $(LIBS) 

$(NAME): $(OBJS) $(BISOBJ) $(LEXOBJ)
	$(CC) -o $@ $(OBJS) $(BISOBJ) $(LEXOBJ) $(LIBS)

clean:
	rm $(OBJS) $(BISOBJ) $(LEXOBJ) parser.tab.h $(BISONSRCFILE) $(LEXSRCFILE) $(NAME)


