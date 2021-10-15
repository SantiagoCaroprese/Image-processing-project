//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#include "Pixel.h"

Pixel::Pixel(unsigned int p_r, unsigned int p_g, unsigned int p_b){
  r = p_r;
  g = p_g;
  b = p_b;
}

Pixel::Pixel(){

}

unsigned int Pixel::getR(){
  return r;
}

void Pixel::setR(unsigned int p_r){
  r = p_r;
}

unsigned int Pixel::getG(){
  return g;
}

void Pixel::setG(unsigned int p_g){
  g = p_g;
}

unsigned int Pixel::getB(){
  return b;
}

void Pixel::setB(unsigned int p_b){
  b = p_b;
}

std::list<unsigned int> Pixel::getProyeccionR(){
    return proyeccionR;
}

void Pixel::setProyeccionR(std::list<unsigned int> p_pro){
  proyeccionR = p_pro;
}

std::list<unsigned int> Pixel::getProyeccionG(){
  return proyeccionG;
}

void Pixel::setProyeccionG(std::list<unsigned int> p_pro){
  proyeccionG = p_pro;
}

std::list<unsigned int> Pixel::getProyeccionB(){
  return proyeccionB;
}

void Pixel::setProyeccionB(std::list<unsigned int> p_pro){
  proyeccionB = p_pro;
}

void Pixel::agregarPixelProyeccion(Pixel p_pix){
  int p_r = p_pix.getR();
  int p_g = p_pix.getG();
  int p_b = p_pix.getB();
  bool insertado = false;

  for(std::list<unsigned int>::iterator it = proyeccionR.begin(); it != proyeccionR.end(); it++)
  {
    if(p_r > *it)
    {
      proyeccionR.insert(it, p_r);
      insertado = true;
      break;
    }
  }
  if(!insertado)
  {
    proyeccionR.push_back(p_r);
  }

  insertado = false;
  for(std::list<unsigned int>::iterator it = proyeccionG.begin(); it != proyeccionG.end(); it++)
  {
    if(p_g > *it)
    {
      proyeccionG.insert(it, p_g);
      insertado = true;
      break;
    }
  }
  if(!insertado)
  {
    proyeccionG.push_back(p_g);
  }

  insertado = false;
  for(std::list<unsigned int>::iterator it = proyeccionB.begin(); it != proyeccionB.end(); it++)
  {
    if(p_b > *it)
    {
      proyeccionB.insert(it, p_b);
      insertado = true;
      break;
    }
  }
  if(!insertado)
  {
    proyeccionB.push_back(p_b);
  }
}

bool Pixel::proyectar(std::string criterio){
  int crit=0;
  if(criterio=="maximo"){
    crit=1;
  }
  if(criterio=="minimo"){
    crit=2;
  }
  if(criterio=="promedio"){
    crit=3;
  }
  if(criterio=="mediana"){
    crit=4;
  }
  unsigned int rmax = 0;
  unsigned int gmax = 0;
  unsigned int bmax = 0;

  unsigned int rmin = 255;
  unsigned int gmin = 255;
  unsigned int bmin = 255;

  unsigned int rtotal = 0;
  unsigned int gtotal = 0;
  unsigned int btotal = 0;

  std::list<unsigned int>::iterator itr;
  std::list<unsigned int>::iterator itg;
  std::list<unsigned int>::iterator itb;

  bool res;
  switch (crit){
    case 1:

      for(std::list<unsigned int>::iterator it = proyeccionR.begin(); it != proyeccionR.end(); it++)
      {
        if(*it > rmax)
        {
          rmax = *it;
        }
      }

      for(std::list<unsigned int>::iterator it = proyeccionG.begin(); it != proyeccionG.end(); it++)
      {
        if(*it > gmax)
        {
          gmax = *it;
        }
      }

      for(std::list<unsigned int>::iterator it = proyeccionB.begin(); it != proyeccionB.end(); it++)
      {
        if(*it > bmax)
        {
          bmax = *it;
        }
      }

      r = rmax;
      g = gmax;
      b = bmax;

      res = true;
      break;

    case 2:

      for(std::list<unsigned int>::iterator it = proyeccionR.begin(); it != proyeccionR.end(); it++)
      {
        if(*it < rmin)
        {
          rmin = *it;
        }
      }

      for(std::list<unsigned int>::iterator it = proyeccionG.begin(); it != proyeccionG.end(); it++)
      {
        if(*it < gmin)
        {
          gmin = *it;
        }
      }

      for(std::list<unsigned int>::iterator it = proyeccionB.begin(); it != proyeccionB.end(); it++)
      {
        if(*it < bmin)
        {
          bmin = *it;
        }
      }

      r = rmin;
      g = gmin;
      b = bmin;

      res = true;
      break;

    case 3:

      for(std::list<unsigned int>::iterator it = proyeccionR.begin(); it != proyeccionR.end(); it++)
      {
        rtotal += *it;
      }

      for(std::list<unsigned int>::iterator it = proyeccionG.begin(); it != proyeccionG.end(); it++)
      {
        gtotal += *it;
      }

      for(std::list<unsigned int>::iterator it = proyeccionB.begin(); it != proyeccionB.end(); it++)
      {
        btotal += *it;
      }

      r = rtotal/proyeccionR.size();
      g = gtotal/proyeccionG.size();
      b = btotal/proyeccionB.size();

      res = true;
      break;

    case 4:
      int pos;
      itr = proyeccionR.begin();
      itg = proyeccionG.begin();
      itb = proyeccionB.begin();

      pos = proyeccionR.size()/2;
      for(int i = 0; i < pos; i++)
      {
        itr++;
        itg++;
        itb++;
      }

      if(proyeccionR.size()%2 == 0)
      {
        pos = proyeccionR.size()/2;
        unsigned int r1 = *itr;
        unsigned int g1 = *itg;
        unsigned int b1 = *itb;

        itr++;
        itg++;
        itb++;

        unsigned int r2 = *itr;
        unsigned int g2 = *itg;
        unsigned int b2 = *itb;

        r = (r1 + r2)/2;
        g = (g1 + g2)/2;
        b = (b1 + b2)/2;
      }
      else
      {
        r = *itr;
        g = *itg;
        b = *itb;
      }
      res = true;
      break;

    default:
      res = false;
  }
  return res;
}

unsigned int Pixel::getEtiqueta(){
  return etiqueta;
}

void Pixel::setEtiqueta(unsigned int p_etiqueta){
  etiqueta = p_etiqueta;
}

std::vector<std::pair<std::pair<int, int>, float>> Pixel::getAristas(){
  return aristas;
}

void Pixel::setAristas(std::vector<std::pair<std::pair<int, int>, float>> p_aristas){
  aristas = p_aristas;
}
