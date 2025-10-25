#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

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

int ingresarEnteroEnRango(const char *mensaje, int min, int max)
{
  int valor;

  do
  {
    valor = ingresarEntero(mensaje);

    if (valor < min || valor > max)
    {
      printf("Entrada fuera de rango. Por favor, ingrese un numero entre %d y %d.\n", min, max);
    }
    else
    {
      break;
    }

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

float ingresarFlotanteEnRango(const char *mensaje, float min, float max)
{
  float valor;

  do
  {
    valor = ingresarFlotante(mensaje);

    if (valor < min || valor > max)
    {
      printf("Entrada fuera de rango. Por favor, ingrese un numero entre %.2f y %.2f.\n", min, max);
    }
    else
    {
      break;
    }

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

char *ingresarConLimite(char *mensaje, int limite)
{
  char *cadena = (char *)malloc((limite + 1) * sizeof(char));
  int c, cursor = 0, largo = 0;
  struct termios oldt, newt;
  char msg[] = " (límite alcanzado)";
  int msg_len = strlen(msg), msgMostrado = 0;

  if (cadena == NULL)
  {
    printf("Error al asignar memoria\n");
    exit(1);
  }

  printf("%s", mensaje);

  tcflush(STDIN_FILENO, TCIFLUSH);

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  while ((c = getchar()) != '\n' && c != EOF)
  {

    if (isprint(c))
    {
      if (largo < limite)
      {
        for (int i = largo; i > cursor; i--)
        {
          cadena[i] = cadena[i - 1];
        }

        cadena[cursor] = (char)c;
        largo++;
        cursor++;

        int cursor_temp = cursor - 1;

        while (cursor_temp < largo)
        {
          putchar(cadena[cursor_temp]);
          cursor_temp++;
        }

        while (cursor_temp > cursor)
        {
          putchar('\b');
          cursor_temp--;
        }
      }
      else
      {
        int cursor_temp = cursor;

        while (cursor_temp < largo)
        {
          putchar(cadena[cursor_temp]);
          cursor_temp++;
        }

        printf("%s", msg);

        cursor_temp += msg_len;

        while (cursor_temp > cursor + 1)
        {
          putchar('\b');
          cursor_temp--;
        }

        msgMostrado = 1;
      }
    }
    else if (c == 127 || c == 8) // Manejar retroceso
    {
      if (cursor > 0)
      {
        cursor--;
        largo--;

        putchar('\b');

        int cursor_temp = cursor;

        while (cursor_temp < largo)
        {
          cadena[cursor_temp] = cadena[cursor_temp + 1];
          putchar(cadena[cursor_temp]);
          cursor_temp++;
        }

        putchar(' ');

        if (msgMostrado)
        {

          while (cursor_temp < limite)
          {
            if (cursor_temp < largo)
            {
              putchar(cadena[cursor_temp]);
            }
            else
            {
              putchar(' ');
            }

            cursor_temp++;
          }

          while (cursor_temp < largo + msg_len)
          {
            putchar(' ');
            cursor_temp++;
          }

          msgMostrado = 0;
        }

        while (cursor_temp > cursor - 1)
        {
          putchar('\b');
          cursor_temp--;
        }
      }
    }
    else if (c == 27) // Manejar secuencias de escape (flechas)
    {
      getchar();     // Ignorar el siguiente caracter '['
      c = getchar(); // Leer la tecla real

      if (c == 'C') // Flecha derecha
      {
        if (cursor < largo)
        {
          putchar(cadena[cursor]);
          cursor++;
        }
      }
      else if (c == 'D') // Flecha izquierda
      {
        if (cursor > 0)
        {
          putchar('\b');
          cursor--;
        }
      }
    }
  }

  if (largo == 0)
  {
    printf("\nNo se ingreso ningun caracter.\n");

    free(cadena);

    return ingresarConLimite(mensaje, limite);
  }

  cadena[largo] = '\0';
  printf("\n");

  // Restaurar la configuracion original de la terminal
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return cadena;
}