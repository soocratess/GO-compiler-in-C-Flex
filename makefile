# Makefile para compilar goCompiler

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g -D_POSIX_C_SOURCE=200809L
LFLAGS = -lfl

# Directorios de inclusión
INCLUDES = -I. -IHashTable -ITablaSimbolos -IAnalizadorSintactico -IAnalizadorLexico -ISistemaEntrada -IError

# Archivos fuente (en esta fase se utiliza lex.yy.c, no el .l)
SRC_goCompiler = main.c \
        HashTable/hashTable.c \
        TablaSimbolos/tablaSimbolos.c \
        AnalizadorSintactico/analizadorSintactico.c \
        AnalizadorLexico/lex.yy.c \
        Error/error.c

# Archivos objeto
OBJ_goCompiler = $(SRC_goCompiler:.c=.o)

# Ejecutable
TARGET_goCompiler = goCompiler

# Regla principal: compila el ejecutable y elimina los archivos objeto intermedios
all: $(TARGET_goCompiler)
	rm -f $(OBJ_goCompiler)

# Regla para generar lex.yy.c a partir del archivo Flex (.l)
AnalizadorLexico/lex.yy.c: AnalizadorLexico/analizadorLexico.l
	flex -o AnalizadorLexico/lex.yy.c AnalizadorLexico/analizadorLexico.l

# Regla para compilar el ejecutable
$(TARGET_goCompiler): $(OBJ_goCompiler)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS)

# Regla genérica para compilar cada archivo objeto
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regla para limpiar archivos generados (no elimina lex.yy.c)
clean:
	rm -f $(OBJ_goCompiler) $(TARGET_goCompiler)

.PHONY: all clean
