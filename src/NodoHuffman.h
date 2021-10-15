//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H
#include <vector>
#include<string>

class NodoHuffman{
  public:
    NodoHuffman();
    int getValor();
    int getFrecuencia();
    NodoHuffman* getHijoIzq();
    NodoHuffman* getHijoDer();
    void setValor(int p_val);
    void setFrecuencia(int p_frec);
    void* setHijoIzq(NodoHuffman* p_n);
    void* setHijoDer(NodoHuffman* p_n);
    bool esHoja();
    void calcularFrecuencia();

  private:
    unsigned int valor;
    unsigned int frecuencia;
    NodoHuffman* hijoIzq;
    NodoHuffman* hijoDer;
};
#include "NodoHuffman.hxx"
#endif
