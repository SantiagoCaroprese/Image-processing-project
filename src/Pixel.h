//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#ifndef PIXEL_H
#define PIXEL_H
#include <list>
#include<string>

class Pixel{
  public:
    Pixel(unsigned int p_r, unsigned int p_g, unsigned int p_b);
    Pixel();
    unsigned int getR();
    void setR(unsigned int p_r);
    unsigned int getG();
    void setG(unsigned int p_g);
    unsigned int getB();
    void setB(unsigned int p_b);
    std::list<unsigned int> getProyeccionR();
    void setProyeccionR(std::list<unsigned int> p_pro);
    std::list<unsigned int> getProyeccionG();
    void setProyeccionG(std::list<unsigned int> p_pro);
    std::list<unsigned int> getProyeccionB();
    void setProyeccionB(std::list<unsigned int> p_pro);
    void agregarPixelProyeccion(Pixel p_pix);
    bool proyectar(std::string criterio);
    unsigned int getEtiqueta();
    void setEtiqueta(unsigned int p_etiqueta);
    std::vector<std::pair<std::pair<int, int>, float>> getAristas();
    void setAristas(std::vector<std::pair<std::pair<int, int>, float>> p_aristas);


  private:
    unsigned int r;
    unsigned int g;
    unsigned int b;
    std::list<unsigned int> proyeccionR;
    std::list<unsigned int> proyeccionG;
    std::list<unsigned int> proyeccionB;
    unsigned int etiqueta;
    std::vector<std::pair<std::pair<int, int>, float>>  aristas;
};

#include "Pixel.hxx"
#endif
