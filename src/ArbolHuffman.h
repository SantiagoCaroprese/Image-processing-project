//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H
#include "NodoHuffman.h"
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include "Imagen.h"

struct Registro
{
  unsigned short W;
  unsigned short H;
  unsigned char M;
  unsigned long frecuencias[256];
};

class ArbolHuffman{
  public:
    ArbolHuffman();
    bool esVacio();
    NodoHuffman* getRaiz();
    void setRaiz(NodoHuffman* p_raiz);
    bool buscar(NodoHuffman* p_inicio,int p_valor);
    int getAltura(NodoHuffman* n_inicio, int altura);
    int getTamano(NodoHuffman* n_inicio);
    void preOrden(NodoHuffman* n_inicio);
    void posOrden(NodoHuffman* n_inicio);
    void inOrden(NodoHuffman* n_inicio);
    void nivelOrdenado(NodoHuffman* n_inicio, int altura);//0 para iniciar
    void verNivel(NodoHuffman* n_inicio,int nivelBuscado, int nivelActual);
    bool codificarImagen(std::string arch_imagen, std::string arch_huf);
    void crearArbol(unsigned long* frecuencias);
    bool decodificarArchivo(std::string arch_Huff,std::string arch_imagen);
    bool codificarEnArchivo(std::string arch_huf, Imagen* p_img, unsigned long* p_frec);
    std::string codificarValor(int val, NodoHuffman* inicio);
    Imagen* getFrecuencias(std::string arch_imagen, unsigned long *res);
    void decodificarEnArchivo(std::string arch_imagen,Imagen* p_img,Registro p_reg, std::vector<char> p_bits);
    int decodificarValor(std::string codigo ,NodoHuffman* nodo, int pos);
    std::vector<int> obtenerValores(std::vector<char> c, int cant);
    char getCharCodigo(std::string cadena);
    std::string getStringCodigo(char caracter);
    std::vector<char> obtenerCaracteres(std::vector<std::string> codigos);

  private:
    NodoHuffman* raiz;
};
#include "ArbolHuffman.hxx"
#endif
