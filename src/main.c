#include <stdio.h>
#include <stdlib.h>

#include "../include/utilidades.h"
#include "../include/pelicula.h"

void mensajeMenu();
void menu();

int main()
{
  menu();

  return 0;
}

void menu()
{
  int opcion;
  Pelicula *cartelera = NULL;

  do
  {
    limpiarPantalla();
    mensajeMenu();
    opcion = ingresarEntero("Seleccione una opcion: ");

    switch (opcion)
    {
    case 1:
      agregaPelicula(&cartelera);

      break;
    case 2:
      mostrarCartelera(cartelera);
      break;
    case 3:
      printf("Mostrar Peliculas Ordenadas por Puntuacion seleccionado.\n");
      break;
    case 4:
      printf("Buscar Pelicula por Titulo seleccionado.\n");
      break;
    case 5:
      printf("Guardar Cartelera en Archivo seleccionado.\n");
      break;
    case 6:
      cargarPeliculas(&cartelera);
      break;
    case 0:
      printf("Saliendo del programa.\n");
      break;
    default:
      printf("Opcion invalida. Intente de nuevo.\n");
      break;
    }

    if (opcion != 0)
    {
      esperarTecla();
    }
  } while (opcion != 0);
}

void mensajeMenu()
{
  const char *opciones[] = {
      "Agregar Pelicula a la cartelera",
      "Mostrar Cartelera",
      "Mostrar Peliculas Ordenadas por Puntuacion",
      "Buscar Pelicula por Titulo",
      "Guardar Cartelera en Archivo",
      "Cargar Cartelera desde Archivo",
  };

  int i, cantidad = sizeof(opciones) / sizeof(opciones[0]);

  printf("===== Menu de Gestion de Cartelera de Cine =====\n");

  for (i = 0; i < cantidad; i++)
  {
    printf("%d. %s\n", i + 1, opciones[i]);
  }

  printf("0. Salir\n");
}
