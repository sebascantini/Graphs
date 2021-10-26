CC=g++

NAME=tp2

_DEPS = goloso.h agm.h busquedaLocal.h tabuSearch.h adicional.h 
DEPS = $(_DEPS)

_OBJ = main.o goloso.o agm.o busquedaLocal.o tabuSearch.o adicional.o
OBJ = $(_OBJ)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean

clean:
	rm -f $(NAME) *.o *~ core $(INCDIR)/*~