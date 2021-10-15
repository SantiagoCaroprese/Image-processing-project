//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#include "NodoHuffman.h"

NodoHuffman::NodoHuffman(){
  hijoDer=nullptr;
  hijoIzq=nullptr;
}

int NodoHuffman::getValor(){
  return valor;
}

int NodoHuffman::getFrecuencia(){
  return frecuencia;
}

NodoHuffman* NodoHuffman::getHijoIzq(){
  return hijoIzq;
}

NodoHuffman* NodoHuffman::getHijoDer(){
  return hijoDer;
}

void NodoHuffman::setValor(int p_val){
  valor = p_val;
}

void NodoHuffman::setFrecuencia(int p_frec){
  frecuencia = p_frec;
}

void* NodoHuffman::setHijoIzq(NodoHuffman* p_n){
  hijoIzq = p_n;
}

void* NodoHuffman::setHijoDer(NodoHuffman* p_n){
  hijoDer = p_n;
}

bool NodoHuffman::esHoja(){
  return hijoIzq == nullptr && hijoDer == nullptr;
}

void NodoHuffman::calcularFrecuencia(){
  frecuencia = 0;
  if(hijoIzq != nullptr)
  {
    frecuencia += hijoIzq->getFrecuencia();
  }
  if(hijoDer != nullptr)
  {
    frecuencia += hijoDer->getFrecuencia();
  }
}
