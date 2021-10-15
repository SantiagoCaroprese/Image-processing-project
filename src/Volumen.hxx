//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#include "Volumen.h"

Volumen::Volumen(){
}

std::vector<Imagen> Volumen::getImagenes(){
    return imagenes;
}

void Volumen::setImagenes(std::vector<Imagen> p_imgs){
    imagenes = p_imgs;
}

bool Volumen::cargarVolumen(std::string p_nombreBase, int p_nImgs){
  bool exito = true, bn;

  if (p_nImgs > 99 || p_nImgs < 1)
  {
    exito = false;
    return exito;
  }

  //Se revisa es P2 o P3
  std::stringstream ss1;
  ss1 << p_nombreBase << "01.ppm";
  std::string nomP3 = ss1.str();

  std::stringstream ss2;
  ss2 << p_nombreBase << "01.pgm";
  std::string nomP2 = ss2.str();

  std::ifstream archP3 (nomP3.c_str());
  if(archP3.is_open())
  {
    bn = false;
    archP3.close();
  }
  else
  {
    std::ifstream archP2 (nomP2.c_str());
    if(archP2.is_open())
    {
      bn = true;
      archP2.close();
    }
    else
    {
      exito = false;
    }
  }

  if(exito)
  {
    if(!bn)
    {
      for(int i = 0; i < p_nImgs; i++)
      {
        Imagen *im = new Imagen;
        std::stringstream ss;

        if(i < 9)
        {
          ss << p_nombreBase << 0 << i+1 << ".ppm";
        }
        else
        {
          ss << p_nombreBase << i+1 << ".ppm";
        }

        std::string nomArch = ss.str();

        exito = im->cargarImagen(nomArch, bn);

        imagenes.push_back(*im);
      }
    }
    else
    {
      for(int i = 0; i < p_nImgs; i++)
      {
        Imagen *im = new Imagen;
        std::stringstream ss;

        if(i < 9)
        {
          ss << p_nombreBase << 0 << i+1 << ".pgm";
        }
        else
        {
          ss << p_nombreBase << i+1 << ".pgm";
        }

        std::string nomArch = ss.str();

        exito = im->cargarImagen(nomArch, bn);

        imagenes.push_back(*im);
      }
    }

  }
  if(imagenes.empty()){
    exito=false;
  }
  return exito;
}

//Crea la imagen, le asigna el resultado de la proyeccion y la guarda en un archivo
void Volumen::proyeccion2D(std::string criterio, std::string arch, char direccion){
  bool exito = true;
  Imagen img;
  if(imagenes.empty()){
    std::cout<<"El volumen aun no ha sido cargado en memoria"<<std::endl;
    exito = false;
    return;
  }
  if(criterio!="maximo" && criterio!="minimo" && criterio!="promedio" && criterio!="mediana"){
    std::cout<<"Criterio de proyeccion2D no reconocido"<<std::endl;
    exito = false;
    return;
  }

  if(direccion == 'x')
  {
    img = *proyectarX(criterio);
  }else{
    if(direccion == 'y')
    {
      img = *proyectarY(criterio);
    }else{
      if(direccion == 'z')
      {
        img = *proyectarZ(criterio);
      }
      else
      {
        std::cout<<"Direccion de proyeccion2D no reconocida"<<std::endl;
        exito = false;
        return;
      }
    }
  }


  std::ofstream archivo(arch);

  if(archivo.is_open())
  {
    if(img.getBn())
    {
      archivo << "P2" << std::endl;
    }
    else
    {
      archivo << "P3" << std::endl;
    }

    int ancho = img.getAncho();
    int altura = img.getAltura();

    archivo << ancho << " " << altura << std::endl;
    std::vector<std::vector<Pixel>> pixelasos = img.getPixeles();
    int max = 0;
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
    if(img.getBn())
    {
      for(int i = 0; i < altura; i++)
      {
        for(int j = 0; j < ancho; j++)
        {
          archivo << pixelasos[i][j].getR() << " ";
        }
        archivo << std::endl;
      }

    }
    else
    {
      for(int i = 0; i < altura; i++)
      {
        for(int j = 0; j < ancho; j++)
        {
          archivo << pixelasos[i][j].getR() << " " << pixelasos[i][j].getG() << " " << pixelasos[i][j].getB() << " ";
        }
        archivo << std::endl;
      }
    }

    archivo.close();
  }
  else
  {
    std::cout<<"Archivo no encontrado."<<std::endl;
    exito = false;
  }

  if(!exito)
  {
    std::cout << "La proyeccion 2D del volumen en memoria no se ha podido generar." << std::endl;
  }
  else
  {
    std::cout << "La proyeccion 2D del volumen en memoria ha sido generada." << std::endl;
  }
}

Imagen* Volumen::proyectarX(std::string criterio){
  Imagen* res = new Imagen;
  std::vector<std::vector<Pixel>> *mat = new std::vector<std::vector<Pixel>>;
  int nimgs = imagenes.size();
  res->setAltura(nimgs);
  res->setAncho(imagenes[0].getAncho());
  res->setBn(imagenes[0].getBn());

  for(int i = 0; i < nimgs; i++)
  {
    std::vector<Pixel>* p;
    p = imagenes[i].proyectarX(criterio);
    mat->push_back(*p);
  }
  res->setPixeles(*mat);
  return res;

}

Imagen* Volumen::proyectarY(std::string criterio){
  Imagen* res = new Imagen;
  std::vector<std::vector<Pixel>> *mat = new std::vector<std::vector<Pixel>>;
  int nimgs = imagenes.size();
  int alt = imagenes[0].getAltura();
  res->setAncho(nimgs);
  res->setAltura(imagenes[0].getAltura()); //Deberia ser igual para todas las imagenes
  res->setBn(imagenes[0].getBn());
  //Se crean las filas
  for(int i = 0; i < alt; i++)
  {
    std::vector<Pixel>* fila = new std::vector<Pixel>;
    mat->push_back(*fila);
  }
  //Se recorren las imagenes y se obtienen una por una las columnas de la imagen resultado
  for(int i = 0; i < nimgs; i++)
  {
    std::vector<Pixel>* col;
    col = imagenes[i].proyectarY(criterio);
    //Se recorre el vector obtenido y se asignan los pixeles en sus filas correspondientes de la matriz. Esto se hace porque el metodo de imagen retorna una columna, mientras que la matriz esta organizda en filas.
    for(int j = 0; j < alt; j++)
    {
      mat[0][j].push_back((*col)[j]);
    }
  }
  res->setPixeles(*mat);
  return res;
}

Imagen* Volumen::proyectarZ(std::string criterio){
  //Se crea la martriz de pixeles
  std::vector<std::vector<Pixel>>* mat = new std::vector<std::vector<Pixel>>;
  int altura = imagenes[0].getAltura();
  int ancho = imagenes[0].getAncho();

  for(int i = 0; i < altura; i++)
  {
    std::vector<Pixel> *fila = new std::vector<Pixel>;
    for(int j = 0; j < ancho; j++)
    {
      Pixel *p = new Pixel;
      fila->push_back(*p);
    }
    mat->push_back(*fila);
  }

  //Se agregan los pixeles proyeccion de todas las imagenes
  int nimgs = imagenes.size();

  for(int i = 0; i < nimgs; i++)
  {

    imagenes[i].proyectarZ(*mat);
  }

  //Se hace la proyeccion de cada uno de los pixeles del vector
  for(int i = 0; i < altura; i++)
  {

    for(int j = 0; j < ancho; j++)
    {
      (*mat)[i][j].proyectar(criterio);
    }

  }

  Imagen* res = new Imagen;
  res->setAncho(ancho);
  res->setAltura(altura);
  res->setBn(imagenes[0].getBn());
  res->setPixeles(*mat);

  return res;
}
