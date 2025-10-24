#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pelicula.h"
#include "../include/utilidades.h"

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

Pelicula *ingresarPelicula(int id)
{
  Pelicula *pelicula = malloc(sizeof(Pelicula));
  char *buffer;

  printf("Ingrese los datos de la pelicula:\n");
  printf("Titulo: ");
  pelicula->titulo[0] = '\0';
  buffer = ingresarConLimite(100);
  strcpy(pelicula->titulo, buffer);
  free(buffer);

  printf("Genero: ");
  pelicula->genero[0] = '\0';
  buffer = ingresarConLimite(30);
  strcpy(pelicula->genero, buffer);
  free(buffer);

  printf("Clasificacion: ");
  pelicula->clasificacion[0] = '\0';
  buffer = ingresarConLimite(10);
  strcpy(pelicula->clasificacion, buffer);
  free(buffer);

  pelicula->duracion = ingresarEnteroEnRango("Duracion (minutos): ", 1, 500);

  pelicula->anio = ingresarEnteroEnRango("Anio (1990-2025): ", 1990, 2025);

  printf("Director: ");
  pelicula->director[0] = '\0';
  buffer = ingresarConLimite(50);
  strcpy(pelicula->director, buffer);
  free(buffer);

  pelicula->puntuacion = ingresarFlotanteEnRango("Puntuacion (0.0 - 10.0): ", 0.0, 10.0);

  pelicula->id = id;

  pelicula->siguiente = NULL;

  printf("Pelicula con ID %d ingresada exitosamente.\n", pelicula->id);

  return pelicula;
}

void agregaPelicula(Pelicula **inicio)
{
  if (*inicio == NULL)
  {
    *inicio = ingresarPelicula(1);
    return;
  }

  Pelicula *actual = *inicio;

  while (actual->siguiente != NULL)
  {
    actual = actual->siguiente;
  }

  actual->siguiente = ingresarPelicula(actual->id + 1);
}