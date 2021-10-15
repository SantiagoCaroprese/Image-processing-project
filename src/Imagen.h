//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#ifndef IMAGEN_H
#define IMAGEN_H
#include <vector>
#include <list>
#include "Pixel.h"
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <tgmath.h>
#include <limits>

class Imagen{
  public:
    Imagen();
    std::vector<std::vector<Pixel>> getPixeles();
    void setPixeles(std::vector<std::vector<Pixel>> p_pixeles);
    unsigned int getAltura();
    void setAltura(unsigned int p_a);
    unsigned int getAncho();
    void setAncho(unsigned int p_a);
    bool cargarImagen(std::string p_arch, bool p_bn);
    std::vector<Pixel>* proyectarX(std::string p_criterio);
    std::vector<Pixel>* proyectarY(std::string p_criterio);
    void proyectarZ(std::vector<std::vector<Pixel>>&  p_pixeles);
    bool getBn();
    void setBn(bool p_bn);
    void generarAristas();
    bool procesarSemillas(std::vector<std::string> semillas, std::string archIn, std::string archOut);//Llamar cargar imagen
    void dijkstra(int fila, int columna, int etiqueta, std::vector<std::vector<float>> &costos);
    float calcularCosto(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal);
    void guardarImgSeg(std::string nombreArchivo);

  private:
    std::vector<std::vector<Pixel>> pixeles;
    unsigned int altura;
    unsigned int ancho;
    bool bn;
};

#include "Imagen.hxx"
#endif
