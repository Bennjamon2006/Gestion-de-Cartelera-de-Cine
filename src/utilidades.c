#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "../include/utilidades.h"

char *ingresar()
{
  int c, i = 0, tam = 10;

  char *cadena = (char *)malloc(tam * sizeof(char));

  if (cadena == NULL)
  {
    printf("Error al asignar memoria\n");
    exit(1);
  }

  while ((c = getchar()) != '\n' && c != EOF)
  {
    cadena[i++] = (char)c;

    if (i >= tam)
    {
      tam *= 2;

      char *nueva_cadena = (char *)realloc(cadena, tam * sizeof(char));

      if (nueva_cadena == NULL)
      {
        printf("Error al reasignar memoria\n");
        free(cadena);
        exit(1);
      }

      cadena = nueva_cadena;
    }
  }

  cadena[i] = '\0';

  return cadena;
}

int ingresarEntero(const char *mensaje)
{

  int valor;
  char *entrada, final;

  do
  {
    printf("%s", mensaje);
    entrada = ingresar();

    final = '\0';

    if (sscanf(entrada, "%d%c", &valor, &final) != 1 || final != '\0')
    {
      printf("Entrada invalida. Por favor, ingrese un numero entero.\n");
    }
    else
    {
      free(entrada);
      break;
    }

    free(entrada);

  } while (1);

  return valor;
}

float ingresarFlotante(const char *mensaje)
{
  float valor;
  char *entrada, final;

  do
  {
    printf("%s", mensaje);
    entrada = ingresar();

    final = '\0';

    if (sscanf(entrada, "%f%c", &valor, &final) != 1 || final != '\0')
    {
      printf("Entrada invalida. Por favor, ingrese un numero flotante.\n");
    }
    else
    {
      free(entrada);
      break;
    }

    free(entrada);

  } while (1);

  return valor;
}

int confirmarAccion(const char *mensaje)
{
  char *entrada;
  int largo;

  while (1)
  {
    printf("%s (s/n): ", mensaje);
    entrada = ingresar();
    largo = strlen(entrada);

    if (largo == 1 && (entrada[0] == 's' || entrada[0] == 'S'))
    {
      free(entrada);
      return 1;
    }
    else if (largo == 1 && (entrada[0] == 'n' || entrada[0] == 'N'))
    {
      free(entrada);
      return 0;
    }
    else
    {
      printf("Entrada invalida. Por favor, ingrese 's' para si o 'n' para no.\n");
    }

    free(entrada);
  }
}

void limpiarPantalla()
{
#if _WIN32 || _WIN64
  system("cls");
  return;
#endif

  // ANSI escape code para limpiar la pantalla
  printf("\033[2J\033[H");
}

void esperarTecla()
{
#if _WIN32 || _WIN64
  system("pause");
  return;
#endif

  struct termios oldt, newt;

  // Limpiar el buffer de entrada
  tcflush(STDIN_FILENO, TCIFLUSH);

  // Guardar la configuracion actual de la terminal
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  // Deshabilitar el modo canonico y el eco
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  printf("Presione cualquier tecla para continuar...\n");
  getchar();

  // Restaurar la configuracion original de la terminal
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}