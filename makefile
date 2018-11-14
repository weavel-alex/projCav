#------------------------------------------------------------------------------
# Makefile C
#------------------------------------------------------------------------------

# fichiers c et h dans le dossier src
C_FILES := $(wildcard src/*.c)

#fichiers objet dans un dossier obj
OBJ_FILES := $(patsubst src/%.c, obj/%.o, $(C_FILES))

#Commande de compilation
CC_FLAGS = -Wall

application: $(OBJ_FILES)
	gcc $^ -o  $@

obj/%.o: src/%.c
	gcc $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf obj/*.o application
