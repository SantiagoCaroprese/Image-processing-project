//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#ifndef VOLUMEN_H
#define VOLUMEN_H
#include <vector>
#include <list>
#include "Imagen.h"
#include <string>

class Volumen{
  public:
    Volumen();
    std::vector<Imagen> getImagenes();
    void setImagenes(std::vector<Imagen> p_imgs);
    bool cargarVolumen(std::string p_nombreBase, int p_nImgs);
    void proyeccion2D(std::string criterio, std::string arch, char direccion);
    Imagen* proyectarX(std::string criterio);
    Imagen* proyectarY(std::string criterio);
    Imagen* proyectarZ(std::string criterio);
    bool GuardarProyeccion(std::vector<std::vector<Pixel>>*);


  private:
    std::vector<Imagen> imagenes;
};

#include "Volumen.hxx"
#endif
