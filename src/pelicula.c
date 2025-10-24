/*
ID: Entero mayor o igual a 0.
T´ıtulo: Cadena de hasta 100 caracteres.
Genero: Cadena de hasta 30 caracteres.
Clasificaci´on: Cadena de hasta 10 caracteres.
Duraci´on: Entero mayor a 0.
A˜no: Entero desde 1990 hasta 2025.
Director: Cadena de hasta 50 caracteres.
Puntuaci´on: Punto flotante entre 0.0 hasta 10.0.
Nodo siguiente: Direcci´on de memoria que apunte a la siguiente pel´ıcula.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pelicula.h"

const char rutaArchivoPeliculas[] = "../peliculas.txt";

Pelicula *leerLinea(const char *linea);

Pelicula *leerLinea(const char *linea)
{
  Pelicula *pelicula = (Pelicula *)malloc(sizeof(Pelicula));

  int resultado = sscanf(
      linea,
      "%d,%20[^,],%20[^,],%10[^,],%d,%d,%50[^,],%f\n",
      &pelicula->id,

      pelicula->titulo,
      pelicula->genero,
      pelicula->clasificacion,
      &pelicula->duracion,
      &pelicula->anio,
      pelicula->director,
      &pelicula->puntuacion);

  if (resultado != 8)
  {
    printf("Linea con formato erroneo: %s\n", linea);
    free(pelicula);
    return NULL;
  }

  pelicula->siguiente = NULL;

  return pelicula;
}

void cargarPeliculas(Pelicula **inicio)
{
  FILE *archivo = fopen(rutaArchivoPeliculas, "r");
  char linea[300];
  Pelicula *actual = NULL;
  Pelicula *nueva = NULL;
  int n = 0;

  if (archivo == NULL)
  {
    printf("Error al abrir el archivo para lectura");
    return;
  }

  *inicio = NULL;

  while (fgets(linea, sizeof(linea), archivo))
  {
    linea[strcspn(linea, "\n")] = '\0';
    nueva = leerLinea(linea);

    if (nueva == NULL)
    {
      continue;
    }

    if (actual != NULL)
    {
      actual->siguiente = nueva;
    }
    else
    {
      *inicio = nueva;
    }

    actual = nueva;
    n++;
  }

  if (n == 0)
  {
    printf("No se encontraron peliculas en el archivo.\n");
  }
  else
  {
    printf("Se cargaron %d peliculas exitosamente.\n", n);
  }

  fclose(archivo);
}

void mostrarPelicula(Pelicula *pelicula)
{
  printf(
      "ID: %d | Titulo: %s | Genero: %s | Clasificacion: %s | Duracion: %d minutos | Anio: %d | Director: %s | Puntuación: %.1f |\n",
      pelicula->id,
      pelicula->titulo,
      pelicula->genero,
      pelicula->clasificacion,
      pelicula->duracion,
      pelicula->anio,
      pelicula->director,
      pelicula->puntuacion);
}

void mostrarCartelera(Pelicula *inicio)
{
  if (inicio == NULL)
  {
    printf("No hay peliculas para mostrar.\n");
    return;
  }

  Pelicula *aux = inicio;

  while (aux != NULL)
  {
    mostrarPelicula(aux);
    aux = aux->siguiente;
  }
}