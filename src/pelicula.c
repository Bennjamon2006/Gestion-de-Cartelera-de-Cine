#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
  pelicula->titulo[0] = '\0';
  buffer = ingresarConLimite("Titulo:", 100);
  strcpy(pelicula->titulo, buffer);
  free(buffer);

  pelicula->genero[0] = '\0';
  buffer = ingresarConLimite("Genero: ", 30);
  strcpy(pelicula->genero, buffer);
  free(buffer);

  pelicula->clasificacion[0] = '\0';
  buffer = ingresarConLimite("Clasificacion: ", 10);
  strcpy(pelicula->clasificacion, buffer);
  free(buffer);

  pelicula->duracion = ingresarEnteroEnRango("Duracion (minutos): ", 1, 500);

  pelicula->anio = ingresarEnteroEnRango("Anio (1990-2025): ", 1990, 2025);

  pelicula->director[0] = '\0';
  buffer = ingresarConLimite("Director: ", 50);
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

void liberarMemoria(Pelicula **inicio)
{
  if (inicio == NULL)
  {
    printf("No hay memoria para liberar.\n");
    return;
  }

  Pelicula *actual = *inicio;
  Pelicula *siguiente;
  int n = 0;

  while (actual != NULL)
  {
    siguiente = actual->siguiente;
    free(actual);
    actual = siguiente;
    n++;
  }

  *inicio = NULL;

  printf("Se liberaron %d nodos de memoria.\n", n);
}

Pelicula *buscarPorTitulo(Pelicula *inicio, const char *titulo)
{
  Pelicula *actual = inicio;

  while (actual != NULL)
  {
    if (strcasecmp(actual->titulo, titulo) == 0)
    {
      return actual;
    }
    actual = actual->siguiente;
  }

  printf("Pelicula con titulo '%s' no encontrada.\n", titulo);

  return NULL;
}

void buscarPeliculaPorTitulo(Pelicula *inicio)
{
  char *titulo;
  Pelicula *encontrada;

  titulo = ingresarConLimite("Ingrese el titulo de la pelicula a buscar: ", 100);

  encontrada = buscarPorTitulo(inicio, titulo);

  if (encontrada != NULL)
  {
    printf("Pelicula encontrada:\n");
    mostrarPelicula(encontrada);
  }

  free(titulo);
}

int contarPeliculas(Pelicula *inicio)
{
  int contador = 0;
  Pelicula *actual = inicio;

  while (actual != NULL)
  {
    contador++;
    actual = actual->siguiente;
  }

  return contador;
}

void llenarVector(Pelicula *inicio, Pelicula *vector[])
{
  Pelicula *actual = inicio;
  int indice = 0;

  while (actual != NULL)
  {
    vector[indice] = actual;
    indice++;
    actual = actual->siguiente;
  }
}

void ordenarVectorPorPuntuacion(Pelicula *vector[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (vector[j]->puntuacion < vector[j + 1]->puntuacion)
      {
        Pelicula *temp = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = temp;
      }
    }
  }
}

void mostrarPeliculasOrdenadasPorPuntuacion(Pelicula *inicio)
{
  int totalPeliculas = contarPeliculas(inicio);

  if (totalPeliculas == 0)
  {
    printf("No hay peliculas para mostrar.\n");
    return;
  }

  Pelicula *vector[totalPeliculas];
  llenarVector(inicio, vector);
  ordenarVectorPorPuntuacion(vector, totalPeliculas);

  printf("Top Peliculas por Puntuacion:\n");
  for (int i = 0; i < totalPeliculas; i++)
  {
    mostrarPelicula(vector[i]);
  }
}

void guardarPeliculasEnArchivo(Pelicula *inicio)
{
  if (inicio == NULL)
  {
    printf("No hay peliculas para guardar.\n");
    return;
  }

  FILE *archivo = fopen(rutaArchivoPeliculas, "w");
  Pelicula *actual = inicio;
  int n = 0;

  if (archivo == NULL)
  {
    printf("Error al abrir el archivo para escritura.\n");
    return;
  }

  while (actual != NULL)
  {
    fprintf(
        archivo,
        "%d,%s,%s,%s,%d,%d,%s,%.1f\n",
        actual->id,
        actual->titulo,
        actual->genero,
        actual->clasificacion,
        actual->duracion,
        actual->anio,
        actual->director,
        actual->puntuacion);

    actual = actual->siguiente;
    n++;
  }

  fclose(archivo);

  printf("Se guardaron %d peliculas en el archivo exitosamente.\n", n);
}