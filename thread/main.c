#include "filosofos.h"

int ft_isnum(char *arg)
{
    int prueba; //diseñar atoi que no acepte espacios

    prueba = atoi(arg);
    if (0 < prueba && prueba< INT_MAX )
    {
        return 1;
    }
    ft_error(0, arg);
    return 0;
}

int ft_parseo(int arc, char **argc)
{
    int i;

    i = 1;
    while (argc[i])
    {
        if (!ft_isnum(argc[i]))
            return 0;
        i++;
    }
    return 1;
}

t_info *ft_iniciar(t_info *info, t_instruc *instrucciones)
{
    info = malloc(sizeof(t_info));

}


static void ft_init(t_instruc *instrucciones, char **argc, t_info *philos)
{
    
    t_info *filo = ft_iniciar(filo, instrucciones);
    if (atoi(argc[1]) == 1)
        ft_error(1, argc[1]);
    else
    {
        instrucciones = ft_initList(instrucciones, argc);
        philos = ft_listConcatenacion(instrucciones);
        instrucciones->info = philos;
        ft_create_thread(philos, atoi(argc[1]), instrucciones);
    }
    
}

int main(int arc, char **argc) //cantidad de filosofos,tiempo de muerte,tiempo para comer,tiempo para dormir,op(numero de comidas)
{
    t_instruc *instrucciones = malloc(sizeof(t_instruc));
    t_info *philos = malloc(sizeof(t_info));
    if (arc == 5 || arc == 6)
    {
        if (ft_parseo(arc, argc))
        {
            ft_init(instrucciones, argc, philos);
        }
    }
    else
    {
        printf("Numero de argumentos incorrecto\n");
        printf("Los argumentos ha introducir son [numero de filosofos], [tiempo de muerte], [tiempo de comida], [tiempo de dormir], [opcional]");
        free(instrucciones);
        return 0;
    }
    return 0;
}