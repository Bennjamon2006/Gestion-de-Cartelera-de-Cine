typedef struct Pelicula
{
  int id;
  char titulo[101];
  char genero[31];
  char clasificacion[11];
  int duracion;
  int anio;
  char director[51];
  float puntuacion;
  struct Pelicula *siguiente;
} Pelicula;

void cargarPeliculas(Pelicula **inicio);
void mostrarPelicula(Pelicula *pelicula);
void mostrarCartelera(Pelicula *inicio);
void agregaPelicula(Pelicula **inicio);
void liberarMemoria(Pelicula **inicio);
void buscarPeliculaPorTitulo(Pelicula *inicio);
void mostrarPeliculasOrdenadasPorPuntuacion(Pelicula *inicio);
void guardarPeliculasEnArchivo(Pelicula *inicio);