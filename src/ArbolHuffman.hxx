//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#include "ArbolHuffman.h"

ArbolHuffman::ArbolHuffman(){
 raiz=nullptr;
}

bool ArbolHuffman::esVacio(){
  return raiz == nullptr;
}

NodoHuffman* ArbolHuffman::getRaiz(){
  return raiz;
}

void ArbolHuffman::setRaiz(NodoHuffman* p_raiz){
  raiz = p_raiz;
}

bool ArbolHuffman::buscar(NodoHuffman* p_inicio,int p_valor){
  if(raiz==nullptr){
    return false;
  }
  if(p_inicio->getValor()==p_valor){
    return true;
  }
  if(p_inicio->getHijoIzq()!=nullptr){
    if(buscar(p_inicio->getHijoIzq(),p_valor)){
      return true;
    }
  }
  if(p_inicio->getHijoDer()!=nullptr){
    if(buscar(p_inicio->getHijoDer(),p_valor)){
      return true;
    }
  }
  return false;
}

int ArbolHuffman::getAltura(NodoHuffman* n_inicio, int altura){
  if(n_inicio==nullptr){
    return altura++;
  }
  int altL=getAltura(n_inicio->getHijoIzq(),altura);
  int altR=getAltura(n_inicio->getHijoDer(),altura);
  if(altL-altR>=0){
    return ++altL;
  }else{
    return ++altR;
  }
}

int ArbolHuffman::getTamano(NodoHuffman* n_inicio){
  if(raiz==nullptr){
    return 0;
  }
  return 1+getTamano(n_inicio->getHijoIzq())+
  getTamano(n_inicio->getHijoDer());
}

void ArbolHuffman::preOrden(NodoHuffman* n_inicio){
  if(raiz==nullptr){
    return;
  }
  if(n_inicio->esHoja()){
    std::cout<<"Valor: "<<n_inicio->getValor()<<", Frecuencia: "<<n_inicio->getFrecuencia()<<std::endl;
  }
  if(n_inicio->getHijoIzq()!=nullptr){
    preOrden(n_inicio->getHijoIzq());
  }
  if(n_inicio->getHijoDer()!=nullptr){
    preOrden(n_inicio->getHijoDer());
  }
}

void ArbolHuffman::posOrden(NodoHuffman* n_inicio){
  if(raiz==nullptr){
    return;
  }
  if(n_inicio->getHijoIzq()!=nullptr){
    posOrden(n_inicio->getHijoIzq());
  }
  if(n_inicio->getHijoDer()!=nullptr){
    posOrden(n_inicio->getHijoDer());
  }
  if(n_inicio->esHoja()){
    std::cout<<"Valor: "<<n_inicio->getValor()<<", Frecuencia: "<<n_inicio->getFrecuencia()<<std::endl;
  }
}

void ArbolHuffman::inOrden(NodoHuffman* n_inicio){
  if(raiz==nullptr){
    return;
  }
  if(n_inicio->getHijoIzq()!=nullptr){
    inOrden(n_inicio->getHijoIzq());
  }
  if(n_inicio->esHoja()){
    std::cout<<"Valor: "<<n_inicio->getValor()<<", Frecuencia: "<<n_inicio->getFrecuencia()<<std::endl;
  }
  if(n_inicio->getHijoDer()!=nullptr){
    inOrden(n_inicio->getHijoDer());
  }
}

void ArbolHuffman::nivelOrdenado(NodoHuffman* n_inicio, int altura){
  if(raiz==nullptr){
    return;
  }
  if(altura==0){
    if(n_inicio->esHoja()){
      std::cout<<"Valor: "<<n_inicio->getValor()<<", Frecuencia: "<<n_inicio->getFrecuencia()<<std::endl;
    }
  }else{
    if(n_inicio->getHijoIzq()!=nullptr){
      nivelOrdenado(n_inicio->getHijoIzq(),altura-1);
    }
    if(n_inicio->getHijoDer()!=nullptr){
      nivelOrdenado(n_inicio->getHijoDer(),altura-1);
    }
  }
  if(n_inicio==raiz){
    if(altura<=getAltura(raiz,-1)){
      std::cout<<std::endl;
      nivelOrdenado(n_inicio,++altura);
    }
  }
  return;
}

void ArbolHuffman::verNivel(NodoHuffman* n_inicio,int nivelBuscado, int nivelActual){
  if(raiz==nullptr){
    return;
  }
  if(nivelActual==0){
    std::cout<<"Valor: "<<n_inicio->getValor()<<", Frecuencia: "<<n_inicio->getFrecuencia()<<" ; ";
  }else{
    if(n_inicio->getHijoIzq()!=nullptr){
      verNivel(n_inicio->getHijoIzq(),nivelBuscado,nivelActual-1);
    }
    if(n_inicio->getHijoDer()!=nullptr){
      verNivel(n_inicio->getHijoDer(),nivelBuscado,nivelActual-1);
    }
  }
  return;
}

bool ArbolHuffman::codificarImagen(std::string arch_imagen, std::string arch_huf){
  bool res = false;
  unsigned long *frecuencias = new unsigned long[256];
  for(int i = 0; i < 256; i++)
  {
    frecuencias[i] = 0;
  }
  Imagen* img = getFrecuencias(arch_imagen,frecuencias);
  if(img != nullptr)
  {
    crearArbol(frecuencias);

    //Utilizar arbol para codificar imagen
    res = codificarEnArchivo(arch_huf, img, frecuencias);
  }
  return res;
}

bool ArbolHuffman::codificarEnArchivo(std::string arch_huf, Imagen* p_img, unsigned long p_frec[]){
    bool res = false;

  struct Registro reg;
  reg.W = p_img->getAncho();
  reg.H = p_img->getAltura();
  for(int i = 0; i < 256; i++)
  {
    reg.frecuencias[i] = p_frec[i];
  }

  std::vector<std::string> bitsPixeles;
  std::vector<std::vector<Pixel>> pixelasos = p_img->getPixeles();
  int max = 0;
  for(int i = 0; i < reg.H; i++)
  {

    for(int j = 0; j < reg.W; j++)
    {
      if((pixelasos[i][j]).getR() > max)
      {
        max = (pixelasos[i][j]).getR();
      }
      if((pixelasos[i][j]).getG() > max)
      {
        max = (pixelasos[i][j]).getG();
      }
      if((pixelasos[i][j]).getB() > max)
      {
        max = (pixelasos[i][j]).getB();
      }
    }
  }

  reg.M = max;

  int k = 0;
  for(int i = 0; i < reg.H; i++)
  {

    for(int j = 0; j < reg.W; j++)
    {
      bitsPixeles.push_back(codificarValor((pixelasos[i][j]).getR(), raiz));
      k++;
      if(!p_img->getBn())
      {
        bitsPixeles.push_back(codificarValor((pixelasos[i][j]).getG(), raiz));
        k++;

        bitsPixeles.push_back(codificarValor((pixelasos[i][j]).getB(), raiz));
        k++;
      }
    }
  }
  std::vector<char> caracteres = obtenerCaracteres(bitsPixeles);

  std::ofstream arch(arch_huf, std::ios::binary);
  if(arch.is_open())
  {
    char c[1];
    arch.write((char*)&reg, sizeof(reg));
    for(int i = 0; i < caracteres.size(); i++)
    {

      arch.write((char*)&caracteres[i], 1);
    }
    res = true;
  }
  arch.close();
  return res;
}

std::string ArbolHuffman::codificarValor(int val, NodoHuffman* inicio){
  std::string resI = "";
  std::string resD = "";
  if(inicio->esHoja())
  {
    if(inicio->getValor() == val)
    {
      return "ENCONTRADO";
    }
    else
    {
      return "";
    }
  }
  if(inicio->getHijoIzq() != nullptr)
  {
    resI = codificarValor(val, inicio->getHijoIzq());
    if(resI == "ENCONTRADO")
    {
      return "0";
    }
    else if(resI != "")
    {
      return "0" + resI;
    }
  }
  if(inicio->getHijoDer() != nullptr)
  {
    resD = codificarValor(val, inicio->getHijoDer());
    if(resD == "ENCONTRADO")
    {
      return "1";
    }
    else if(resD != "")
    {
      return "1" + resD;
    }
  }
  return "";
}

//En caso de error retorna nulo
Imagen* ArbolHuffman::getFrecuencias(std::string arch_imagen, unsigned long *res){

  bool bn;
  Imagen* img = new Imagen;
  std::string formato = arch_imagen;
  formato.erase(0, formato.size()-3);
  if(formato == "pgm")
  {
    bn = true;
  }
  else if(formato == "ppm")
  {
    bn = false;
  }
  else
  {
    return nullptr;
  }
  if(!img->cargarImagen(arch_imagen, bn))
  {
    return nullptr;
  }
  std::vector<std::vector<Pixel>> pixelasos = img->getPixeles();
  for(int i = 0; i < img->getAltura(); i++)
  {

    for(int j = 0; j < img->getAncho(); j++)
    {
      res[(pixelasos[i][j]).getR()]++;
      if(!bn)
        res[(pixelasos[i][j]).getG()]++;
      if(!bn)
        res[(pixelasos[i][j]).getB()]++;
    }
  }
  return img;
}

void ArbolHuffman::crearArbol(unsigned long* frecuencias){
  std::vector<NodoHuffman*> nodos;
  for(int i = 0; i < 256; i++)
  {
    NodoHuffman* nuevo_nodo = new NodoHuffman;
    nuevo_nodo->setValor(i);
    nuevo_nodo->setFrecuencia(frecuencias[i]);
    nodos.push_back(nuevo_nodo);
  }
  while(nodos.size() > 1)
  {

    //Se halla el nodo con menor frecuencia, que será el hijo izquierdo del nuevo nodo padre
    int menorFrecuencia = nodos[0]->getFrecuencia();
    int menorPos = 0;
    for(int i = 0; i < nodos.size(); i++)
    {
      if(nodos[i]->getFrecuencia() < menorFrecuencia)
      {
        menorFrecuencia = nodos[i]->getFrecuencia();
        menorPos = i;
      }
    }
    NodoHuffman* nuevo_padre = new NodoHuffman;
    nuevo_padre->setHijoIzq(nodos[menorPos]);
    nodos.erase(nodos.begin() + menorPos);
    //Se halla segundo nodo con menor frecuenciam que será el hijo derecho del nuevo nodo padre
    menorFrecuencia = nodos[0]->getFrecuencia();
    menorPos = 0;
    for(int i = 0; i < nodos.size(); i++)
    {
      if(nodos[i]->getFrecuencia() < menorFrecuencia)
      {
        menorFrecuencia = nodos[i]->getFrecuencia();
        menorPos = i;
      }
    }
    nuevo_padre->setHijoDer(nodos[menorPos]);
    nodos.erase(nodos.begin() + menorPos);
    //Se agrega nuevo nodo padre al vector de nodos
    nuevo_padre->calcularFrecuencia();
    nuevo_padre->setValor(-1);
    nodos.push_back(nuevo_padre);
  }
  //El nodo resultante es la raíz
  raiz = nodos[0];
}

bool ArbolHuffman::decodificarArchivo(std::string arch_Huff,std::string arch_imagen){
  bool bn;
  std::string formato = arch_imagen;
  std::vector<char> bitsPixeles;
  char buf[1];
  formato.erase(0, formato.size()-3);
  if(formato == "pgm")
  {
    bn = true;
  }
  else if(formato == "ppm")
  {
    bn = false;
  }
  else
  {
    return false;
  }

  struct Registro reg;
  std::ifstream arch(arch_Huff, std::ios::binary);
  if(arch.is_open()){
    arch.read((char*)&reg,sizeof(reg));

    while(!arch.eof())
    {
      arch.read(buf,1);
      bitsPixeles.push_back(buf[0]);
    }
  }else{
    return false;
  }

  if(reg.frecuencias==nullptr){
    return false;
  }

  Imagen* img = new Imagen;
  img->setBn(bn);

  crearArbol(reg.frecuencias);

  decodificarEnArchivo(arch_imagen,img,reg, bitsPixeles);
  arch.close();
}

void ArbolHuffman::decodificarEnArchivo(std::string arch_imagen,Imagen* p_img,Registro p_reg, std::vector<char> p_bits){
  std::vector<std::vector<Pixel>> matriz;
  int j_limit=p_reg.W;
  int i_limit=p_reg.H;
  if(!p_img->getBn()){
    j_limit=j_limit*3;
  }

  std::vector<int> valores = obtenerValores(p_bits, j_limit*i_limit);

  for(int i = 0; i <i_limit ; i++)
  {
    std::vector<Pixel> fila;
    for(int j = 0; j <j_limit ; j++)
    {
      int codigo = valores[i*j_limit+j];
      Pixel pix;
      pix.setR(codigo);

      if(!p_img->getBn())
      {
        j++;
        codigo = valores[i*j_limit+j];
        pix.setG(codigo);

        j++;
        codigo = valores[i*j_limit+j];
        pix.setB(codigo);
      }else{
        pix.setG(0);
        pix.setB(0);
      }
      fila.push_back(pix);
    }
    matriz.push_back(fila);
  }

  p_img->setPixeles(matriz);
  p_img->setAltura(p_reg.H);
  p_img->setAncho(p_reg.W);

  std::ofstream archivo(arch_imagen);
  if(archivo.is_open())
  {
    if(p_img->getBn())
    {
      archivo << "P2" << std::endl;
    }else{
      archivo << "P3" << std::endl;
    }
    int ancho = p_img->getAncho();
    int altura = p_img->getAltura();
    archivo << ancho << " " << altura << std::endl;
    int max = 0;
    std::vector<std::vector<Pixel>> pixelasos = p_img->getPixeles();
    for(int i = 0; i < altura; i++)
    {
      for(int j = 0; j < ancho; j++)
      {
        if(pixelasos[i][j].getR() > max)
        {
          max = pixelasos[i][j].getR();
        }
        if(pixelasos[i][j].getG() > max)
        {
          max = pixelasos[i][j].getG();
        }
        if(pixelasos[i][j].getB() > max)
        {
          max = pixelasos[i][j].getB();
        }
      }
    }
    archivo << max << std::endl;
    if(p_img->getBn())
    {
      for(int i = 0; i < altura; i++)
      {
        for(int j = 0; j < ancho; j++)
        {
          archivo << (pixelasos[i][j]).getR() << " ";
        }
        archivo << std::endl;
      }
    }  else  {
      for(int i = 0; i < altura; i++)
      {
        for(int j = 0; j < ancho; j++)
        {
          archivo << (pixelasos[i][j]).getR() << " " << (pixelasos[i][j]).getG() << " " << (pixelasos[i][j]).getB() << " ";
        }
        archivo << std::endl;
      }
    }
    archivo.close();
  } else {
    std::cout<<" Error al decodificar archivo " <<std::endl;
  }
}

int ArbolHuffman::decodificarValor(std::string codigo ,NodoHuffman* nodo, int pos){
  if(nodo==nullptr){
    return -1;
  }
  else if(pos == codigo.size())
  {
    return nodo->getValor();
  }
  else if(nodo->getValor() == -1)
  {
    if(codigo[pos] == '0')
    {
      return decodificarValor(codigo, nodo->getHijoIzq(), pos+1);
    }
    else if(codigo[pos] == '1')
    {
      return decodificarValor(codigo, nodo->getHijoDer(), pos+1);
    }
  }
}

std::vector<int> ArbolHuffman::obtenerValores(std::vector<char> caracteres, int cantidad)
{
  std::string todo = "";
  std::vector<int> res;

  for(int i = 0; i < caracteres.size(); i++)
  {
    todo = todo + getStringCodigo(caracteres[i]);
  }

  //Ciclo que se repite por cada pixel
  for(int i = 0; i < cantidad; i++)
  {
    //Se repite para probar con los posibles codigos
    for(int j = 0; j < todo.size(); j++)
    {
      std::string sub = todo.substr(0, j+1);

      int val = decodificarValor(sub, raiz, 0);
      if(val != -1)
      {
        res.push_back(val);
        todo = todo.substr(j+1, todo.size()-j-1);
        break;
      }
    }
  }
  return res;
}

std::vector<char> ArbolHuffman::obtenerCaracteres(std::vector<std::string> codigos)
{
  std::string todo = "";
  std::vector<char> res;
  for(int i = 0; i < codigos.size(); i++)
  {
    todo = todo + codigos[i];
  }

  while(todo.size() > 8)
  {
    std::string sub = todo.substr(0, 8);
    todo = todo.substr(8, todo.size()-8);
    char c = getCharCodigo(sub);
    res.push_back(c);
  }
  int ceros = 8 - todo.size();
  for(int i = 0; i < ceros; i++)
  {
    todo = todo + "0";
  }
  char c = getCharCodigo(todo);
  res.push_back(c);

  return res;
}

char ArbolHuffman::getCharCodigo(std::string cadena){
  char caracter=0x00;
  char mask=0x01;
  int limit=8;
  for(int i=0;i<limit;i++){
    caracter=caracter<<1;
    if(cadena[i]=='1'){
      caracter=caracter | mask;
    }
  }
  return caracter;
}

std::string ArbolHuffman::getStringCodigo(char caracter){
  std::string cadena;
  char mask=0x80;
  int limit=8;
  for(int i=0;i<limit;i++){
    if((caracter & mask)==mask){
      cadena=cadena+'1';
    }else{
      cadena=cadena+'0';
    }
    caracter=caracter<<1;
  }
  return cadena;
}
