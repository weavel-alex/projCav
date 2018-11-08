#------------------------------------------------------------------------------
# Makefile C
#------------------------------------------------------------------------------

# fichiers c et h dans le dossier src
CPP_FILES := $(wildcard src/*.c)

#fichiers objet dans un dossier obj
OBJ_FILES := $(patsubst src/%.c, obj/%.o, $(CPP_FILES))

application: $(OBJ_FILES)
	gcc $^ -o  $@

obj/%.o: src/%.c
	gcc -c -o $@ $<

clean:
	rm -rf obj/*.o application
