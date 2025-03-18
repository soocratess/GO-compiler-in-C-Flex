# Makefile para compilar P1

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g -D_POSIX_C_SOURCE=200809L
LFLAGS = -lfl

# Directorios de inclusión
INCLUDES = -I. -IHashTable -ITablaSimbolos -IAnalizadorSintactico -IAnalizadorLexico -ISistemaEntrada -IError

# Archivos fuente (en esta fase se utiliza lex.yy.c, no el .l)
SRC_P1 = main.c \
        HashTable/hashTable.c \
        TablaSimbolos/tablaSimbolos.c \
        AnalizadorSintactico/analizadorSintactico.c \
        AnalizadorLexico/lex.yy.c \
        Error/error.c

# Archivos objeto
OBJ_P1 = $(SRC_P1:.c=.o)

# Ejecutable
TARGET_P1 = P1

# Regla principal: compila el ejecutable y elimina los archivos objeto intermedios
all: $(TARGET_P1)
	rm -f $(OBJ_P1)

# Regla para generar lex.yy.c a partir del archivo Flex (.l)
AnalizadorLexico/lex.yy.c: AnalizadorLexico/analizadorLexico.l
	flex -o AnalizadorLexico/lex.yy.c AnalizadorLexico/analizadorLexico.l

# Regla para compilar el ejecutable
$(TARGET_P1): $(OBJ_P1)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS)

# Regla genérica para compilar cada archivo objeto
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regla para limpiar archivos generados (no elimina lex.yy.c)
clean:
	rm -f $(OBJ_P1) $(TARGET_P1)

.PHONY: all clean
