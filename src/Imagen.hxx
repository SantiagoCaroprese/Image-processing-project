//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#include "Imagen.h"

Imagen::Imagen(){
}

std::vector<std::vector<Pixel>> Imagen::getPixeles(){
  return pixeles;
}

void Imagen::setPixeles(std::vector<std::vector<Pixel>> p_pixeles){
  pixeles = p_pixeles;
}

unsigned int Imagen::getAltura(){
  return altura;
}

void Imagen::setAltura(unsigned int p_a){
  altura = p_a;
}

unsigned int Imagen::getAncho(){
  return ancho;
}

void Imagen::setAncho(unsigned int p_a){
  ancho = p_a;
}

bool Imagen::cargarImagen(std::string p_arch, bool p_bn){
  bool lectura = true, comentario = false;
	std::ifstream arch (p_arch.c_str());
  bn = p_bn;

  std::string linea;
  std::string palabra;
  int max;

  if (arch.is_open()) {
    //Se revisa si la linea es comentario
    do
    {
      comentario = false;
      std::getline(arch, linea);

      if (linea[0] == '#')
      {
        comentario = true;
      }
    } while (comentario == true);

    //Se revisa el formato
    if(!bn && linea.substr(0,2)!="P3")
    {
      lectura = false;
    }
    if(bn && linea.substr(0,2)!="P2")
    {
      lectura = false;
    }

    if(lectura)
    {
      //Se obtienen las dimensiones de la imagen
      //Se revisa si la linea es comentario
      do
      {
        comentario = false;
        std::getline(arch, linea);

        if (linea[0] == '#')
        {
          comentario = true;
        }
      } while (comentario == true);

      //Se separan las palabras de la linea
      std::stringstream ss(linea);
      std::vector<std::string> palabras;
      palabras.clear();

      while(getline(ss, palabra, ' ')) {
        palabras.push_back(palabra);
      }

      if(palabras.size() > 2)
      {
        lectura = false;
      }

      else
      {
        ancho = atoi(palabras[0].c_str());
        altura = atoi(palabras[1].c_str());

        //Se obtiene la intensidad maxima de la imagen
        //Se revisa si la linea es comentario
        do
        {
          comentario = false;
          std::getline(arch, linea);

          if (linea[0] == '#')
          {
            comentario = true;
          }
        } while (comentario == true);

        max = atoi(linea.c_str());

        //Se validan las dimensiones y el maximo valor
        if (ancho < 1 || altura < 1 || max < 1 || max > 255)
        {
          lectura = false;
        }
      }

      if(lectura)
      {
        //Lectura para archivo P2
        if(bn)
        {
          std::vector<std::string> palabras;
          //Se leen las lineas correspondientes a las filas de la imagen
          while(!arch.eof())
          {
            //Se revisa si la linea es comentario
            do
            {
              comentario = false;
              std::getline(arch, linea);

              if (linea[0] == '#')
              {
                comentario = true;
              }
            } while (comentario == true);

            //Se separan las palabras de la linea
            std::stringstream ss(linea);

            while(getline(ss, palabra, ' ')) {
              palabras.push_back(palabra);
            }
          }

          int lr;
          int count = 0;
          for(int i = 0; i < altura; i++)
          {
            std::vector<Pixel> *fila = new std::vector<Pixel>;
            pixeles.push_back(*fila);

            //Se crean los pixeles de la imagen y se les asignan los valores leidos
            for(int j = 0; j < ancho; j++)
            {
              lr = atoi(palabras[count].c_str()); //le asignan los valores leidos a los pixeles de la imagen

              if(lr > max || lr < 0)
              {
                lectura = false;
                break;
              }

              Pixel *p = new Pixel;

              p->setR(lr);
              p->setG(0);
              p->setB(0);

              pixeles[i].push_back(*p);

              count++;
            }
          }
        }
        //Lectura para archivo P3
        else
        {
          std::vector<std::string> palabras;
          //Se leen las lineas correspondientes a las filas de la imagen
          while(!arch.eof())
          {
            //Se revisa si la linea es comentario
            do
            {
              comentario = false;
              std::getline(arch, linea);

              if (linea[0] == '#')
              {
                comentario = true;
              }
            } while (comentario == true);

            //Se separan las palabras de la linea
            std::stringstream ss(linea);

            while(getline(ss, palabra, ' ')) {
              palabras.push_back(palabra);
            }
          }

          int lr, lg, lb;
          int count = 0;
          for(int i = 0; i < altura; i++)
          {
            std::vector<Pixel> *fila = new std::vector<Pixel>;
            pixeles.push_back(*fila);

            //Se crean los pixeles de la imagen y se les asignan los valores leidos
            for(int j = 0; j < ancho; j++)
            {
              lr = atoi(palabras[count].c_str()); //le asignan los valores leidos a los pixeles de la imagen
              count++;
              lg = atoi(palabras[count].c_str());
              count++;
              lb = atoi(palabras[count].c_str());
              count++;
              if(lr > max || lr < 0)
              {
                lectura = false;
                break;
              }

              Pixel *p = new Pixel;

              p->setR(lr);
              p->setG(lg);
              p->setB(lb);

              pixeles[i].push_back(*p);
            }
          }
        }

      }
    }
    arch.close();
  }
  else
  {
    lectura = false;
  }
  return lectura;
}


std::vector<Pixel>* Imagen::proyectarX(std::string p_criterio){
  std::vector<Pixel> *res = new std::vector<Pixel>;
  for(int i = 0; i < ancho; i++)
  {
      Pixel *p = new Pixel;
      for(int j = 0; j < altura; j++)
      {
          p->agregarPixelProyeccion(pixeles[j][i]);
      }
      p->proyectar(p_criterio);
      res->push_back(*p);
  }
  return res;
}

std::vector<Pixel>* Imagen::proyectarY(std::string criterio){
  std::vector<Pixel> *res = new std::vector<Pixel>;
  for(int i = 0; i < altura; i++)
  {
      Pixel *p = new Pixel;
      for(int j = 0; j < ancho; j++)
      {
        p->agregarPixelProyeccion(pixeles[i][j]);
      }
      p->proyectar(criterio);
      res->push_back(*p);
  }
  return res;
}

void Imagen::proyectarZ(std::vector<std::vector<Pixel>>& p_pixeles){
  for(int i = 0; i < altura; i++)
  {
    for(int j = 0; j < ancho; j++)
    {
      p_pixeles[i][j].agregarPixelProyeccion(pixeles[i][j]);
    }
  }
}

bool Imagen::getBn(){
  return bn;
}

void Imagen::setBn(bool p_bn){
  bn = p_bn;
}

//Podría llamarse cuando se crea la imagen, pero haría que se demoren más componentes anteriores, por lo que podría solo llamarse al principio de procesarSemillas
void Imagen::generarAristas()
{
  //Se recorre matriz de pixeles de la imagen
  for(int i = 0; i < altura; i++)
  {
    for(int j = 0; j < ancho; j++)
    {
      //Arriba
      if(i > 0)
      {
        //Arista con pixel destino en fila = i-1 y columna = j
        std::pair<std::pair<int, int>, float> *aristaSup = new std::pair<std::pair<int, int>, float>();
        aristaSup->first.first = i-1;
        aristaSup->first.second = j;
        //Se calcula peso
        aristaSup->second = calcularCosto(i, j, i-1, j);
        //push back en vector de aristas del pixel actual
        std::vector<std::pair<std::pair<int, int>, float>> nuevasAristas = pixeles[i][j].getAristas();
        nuevasAristas.push_back(*aristaSup);
        pixeles[i][j].setAristas(nuevasAristas);
      }
      //Abajo
      if(i < altura - 1)
      {
        //Arista con pixel destino en fila = i+1 y columna = j
        std::pair<std::pair<int, int>, float> *aristaInf = new std::pair<std::pair<int, int>, float>();
        aristaInf->first.first = i+1;
        aristaInf->first.second = j;
        //Se calcula peso
        aristaInf->second = calcularCosto(i, j, i+1, j);
        //push back en vector de aristas del pixel actual
        std::vector<std::pair<std::pair<int, int>, float>> nuevasAristas = pixeles[i][j].getAristas();
        nuevasAristas.push_back(*aristaInf);
        pixeles[i][j].setAristas(nuevasAristas);
      }
      //Izquierda
      if(j > 0)
      {
        //Arista con pixel destino en fila = i y columna = j-1
        std::pair<std::pair<int, int>, float> *aristaIzq = new std::pair<std::pair<int, int>, float>();
        aristaIzq->first.first = i;
        aristaIzq->first.second = j-1;
        //Se calcula peso
        aristaIzq->second = calcularCosto(i, j, i, j-1);
        //push back en vector de aristas del pixel actual
        std::vector<std::pair<std::pair<int, int>, float>> nuevasAristas = pixeles[i][j].getAristas();
        nuevasAristas.push_back(*aristaIzq);
        pixeles[i][j].setAristas(nuevasAristas);
      }
      //Derecha
      if(j < ancho - 1)
      {
        //Arista con pixel destino en fila = i y columna = j+1
        std::pair<std::pair<int, int>, float> *aristaDer = new std::pair<std::pair<int, int>, float>();
        aristaDer->first.first = i;
        aristaDer->first.second = j+1;
        //Se calcula peso
        aristaDer->second = calcularCosto(i, j, i, j+1);
        //push back en vector de aristas del pixel actual
        std::vector<std::pair<std::pair<int, int>, float>> nuevasAristas = pixeles[i][j].getAristas();
        nuevasAristas.push_back(*aristaDer);
        pixeles[i][j].setAristas(nuevasAristas);
      }
    }
  }
}

float Imagen::calcularCosto(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal){
  float rI = pixeles[filaInicial][columnaInicial].getR();
  float gI = pixeles[filaInicial][columnaInicial].getG();
  float bI = pixeles[filaInicial][columnaInicial].getB();
  float rF = pixeles[filaFinal][columnaFinal].getR();
  float gF = pixeles[filaFinal][columnaFinal].getG();
  float bF = pixeles[filaFinal][columnaFinal].getB();

  return sqrt(pow(rI - rF, 2) + pow(gI - gF, 2) + pow(bI - bF, 2));
}

//Se recibe vector de cadenas con parámetros del comando (semillas)
bool Imagen::procesarSemillas(std::vector<std::string> semillas, std::string archIn, std::string archOut){
  std::vector<std::vector<float>> costos;
  //Se determina si la imagen es pgm o ppm
  bool blancoNegro;
  if(archIn[archIn.size()-2] == 'p')
  {
    blancoNegro = false;
  }
  else if(archIn[archIn.size()-2] == 'g')
  {
    blancoNegro = true;
  }
  else
  {
    return false;
  }
  //Se carga imagen
  if(!cargarImagen(archIn, blancoNegro))
  {
    return false;
  }
  //Se generan aristas
  generarAristas();
  //Se inicializa matriz de costos en infinito
  for(int i = 0; i < altura; i++)
  {
    std::vector<float> fila;
    for(int j = 0; j < ancho; j++)
    {
      fila.push_back(std::numeric_limits<float>::infinity());
    }
    costos.push_back(fila);
  }
  //Se valida cantidad de parámetros
  if(semillas.size()%3 == 0)
  {
    int numSemillas = semillas.size()/3;
    //Se recorren semillas
    for(int i = 0; i < numSemillas; i++)
    {
      int columna = stoi(semillas[i*3]);
      int fila = stoi(semillas[i*3 +1]);
      int etiqueta = stoi(semillas[i*3 +2]);
      if(columna >= 0 && columna < ancho && fila >= 0 && fila < altura && etiqueta >= 0 && etiqueta < 256)
      {
        //Se actualizan etiquetas de los pixeles y matriz de costos si se encuentra un costo menor para un pixel
        dijkstra(fila, columna, etiqueta, costos);
      }
      else
      {
        return false;
      }
    }
    guardarImgSeg(archOut);
    return true;
  }
  return false;
}

void Imagen::dijkstra(int fila, int columna, int etiqueta, std::vector<std::vector<float>> &costos){
  std::vector<std::vector<float>> nuevosCostos;
  std::vector<std::pair<int, int>> noVisitados;
  std::vector<std::pair<int, int>> visitados;
  std::pair<int, int> coordenadas;
  //Se llena vector de pixeles no visitados y se inicializa matriz de costos
  for(int i = 0; i < altura; i++)
  {
    std::vector<float> filaC;
    for(int j = 0; j < ancho; j++)
    {
      coordenadas.first = i;
      coordenadas.second = j;
      noVisitados.push_back(coordenadas);
      if(i == fila && j == columna)
      {
        filaC.push_back(0);
      }
      else
      {
        filaC.push_back(std::numeric_limits<float>::infinity());
      }
    }
    nuevosCostos.push_back(filaC);
  }
  while(!noVisitados.empty())
  {
    //Se busca al pixel no visitado con el costo menor
    float min = std::numeric_limits<float>::infinity();
    int pos;
    for(int i = 0; i < noVisitados.size(); i++)
    {
      float cost = nuevosCostos[noVisitados[i].first][noVisitados[i].second];
      if(cost < min)
      {
        min = cost;
        pos = i;
      }
    }
    std::pair<int, int> nuevoV = noVisitados[pos];
    visitados.push_back(nuevoV);
    noVisitados.erase(noVisitados.begin() + pos);
    //Se relajan las aristas
    int tam = pixeles[nuevoV.first][nuevoV.second].getAristas().size();
    std::pair<std::pair<int, int>, float> arista;
    for(int i = 0; i < tam; i++)
    {
      arista = pixeles[nuevoV.first][nuevoV.second].getAristas()[i];
      if(nuevosCostos[arista.first.first][arista.first.second] > nuevosCostos[nuevoV.first][nuevoV.second] + arista.second)
      {
        nuevosCostos[arista.first.first][arista.first.second] = nuevosCostos[nuevoV.first][nuevoV.second] + arista.second;
      }
    }
  }
  //Se compara nueva matriz de costos con los costos anteriores para actualizar vértices para los cuales se obtuvieron costos menores
  for(int i = 0; i < altura; i++)
  {
    for(int j = 0; j < ancho; j++)
    {
      if(nuevosCostos[i][j] < costos[i][j])
      {
        costos[i][j] = nuevosCostos[i][j];
        pixeles[i][j].setEtiqueta(etiqueta);
      }
    }
  }
}

void Imagen::guardarImgSeg(std::string nombre_archivo)
{

  bool creado=false;
  std::ofstream nImagen (nombre_archivo);
  int max;

  if(nImagen.is_open())
  {

  if(bn)
    {

        max = 0;
        for(int i = 0; i < altura; i++)
        {
          for(int j = 0; j < ancho; j++)
          {
            if(pixeles[i][j].getEtiqueta() > max)
            {
              max = pixeles[i][j].getEtiqueta();
            }
          }
        }

          nImagen << "P2" << "\n";
          nImagen << ancho << " " <<altura <<"\n";
          nImagen << max <<"\n";

          for(int i=0 ; i<altura ;i++)
          {
            for(int j=0; j<ancho ; j++)
            {

                nImagen <<pixeles[i][j].getEtiqueta()<<" ";
            }
            nImagen <<"\n";

          }
          creado = true;


    }

    if(!bn)
    {



          nImagen << "P3" << "\n";
          nImagen << ancho << " " <<altura <<"\n";
          nImagen << max <<"\n";

          for(int i=0 ; i<altura ;i++)
          {
            for(int j=0; j<ancho ; j++)
            {
              nImagen <<pixeles[i][j].getEtiqueta()<<" ";
              nImagen <<pixeles[i][j].getEtiqueta()<<" ";
              nImagen <<pixeles[i][j].getEtiqueta()<<" ";
            }

           nImagen <<"\n";

          }
          creado = true;



    }
    nImagen.close();
  }else
        {
          std::cout<<"No se puedo abrir el archivo"<<std::endl;
        }

  if(!creado)
  {
    std::cout << "No se pudo crear la imagen" << std::endl;
  }
  else
  {
    std::cout << "La imagen se ha creado correctamente" << std::endl;
  }

}
