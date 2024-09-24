#include "filosofos.h"

void ft_error(int i, char *error)
{
    if (i == 0)
    {
        printf("Error al introducir el parametro %s\n", error);//cambiar por fd_putnbr
        printf("Solo se permiten numero entre 0 y %i\n", INT_MAX);
    }
    else if (i == 1)
    {
        printf("Numero de tenedores disponibles: 1\n");
        printf("No se puede puede ejecutar el programa, es necesario minimo 2 tenedores");
    }

}