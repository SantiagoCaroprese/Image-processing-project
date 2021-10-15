//Realizado por Daniel Hernández, Santiago Caroprese y Juan Carlos Suárez
#include <iostream>
#include <stdlib.h>
#include "Volumen.h"
#include "Imagen.h"
#include "Pixel.h"
#include "ArbolHuffman.h"

int main(){
  Volumen vol;
  std::string comando, palabra;

  do
  {
    std::cout << "$";
    std::getline(std::cin, comando);

    std::stringstream ss(comando);
    std::vector<std::string> palabras;
    palabras.clear();

    while(getline(ss, palabra, ' ')) {
      palabras.push_back(palabra);
    }

    if(palabras[0]=="cargar_volumen")
    {
      if (palabras.size() == 3)
      {
        if(vol.cargarVolumen(palabras[1], atoi(palabras[2].c_str())))
        {
          std::cout << "El volumen " << palabras[1] << " ha sido cargado." << std::endl;
        }
        else
        {
          std::cout << "El volumen " << palabras[1] << " no ha podido ser cargado." << std::endl;
        }
      }
      else
      {
        std::cout << "Uso correcto: cargar_volumen <nombre_base> <n_im>" << std::endl;
      }
    }
    else if(palabras[0]=="proyeccion2D")
    {
      if (palabras.size() == 4)
      {
        char dir = palabras[1][0];
        vol.proyeccion2D(palabras[2], palabras[3], dir);
      }
      else
      {
        std::cout << "Uso correcto: proyeccion2D <dirección> <criterio> <nombre_archivo>" << std::endl;
      }
    }
    //revisar//
    else if(palabras[0]=="codificar_imagen"){
      if (palabras.size() == 3)
      {
        ArbolHuffman arbol;
        if(arbol.codificarImagen(palabras[1], palabras[2])){
          std::cout << "La Imagen "<<palabras[1]<<" ha sido codificada exitosamente" << std::endl;
        }else{
          std::cout << "La Imagen "<<palabras[1]<<" no ha podido ser codificada" << std::endl;
        }
      }
      else
      {
        std::cout << "Uso correcto: codificar_imagen <nombre_imagen.(ppm o pgm)> <nombre_archivo.huffman>" << std::endl;
      }
    }
    else if(palabras[0]=="decodificar_archivo"){
      if (palabras.size() == 3)
      {
        ArbolHuffman arbol;
        if(arbol.decodificarArchivo(palabras[1], palabras[2])){
          std::cout << "El Archivo "<<palabras[1]<<" ha sido decodificado exitosamente" << std::endl;
        }else{
          std::cout << "El Archivo "<<palabras[1]<<" no ha podido ser decodificado" << std::endl;
        }
      }
      else
      {
        std::cout << "Uso correcto: decodificar_archivo <nombre_archivo.huffman> <nombre_imagen.(ppm o pgm)>" << std::endl;
      }
    }
    else if(palabras[0]=="segmentar"){
      std::vector<std::string> semillas;
      for(int i = 3; i < palabras.size(); i++)
      {
        semillas.push_back(palabras[i]);
      }
      Imagen img;
      if(img.procesarSemillas(semillas, palabras[1], palabras[2]))
      {
        std::cout << "La imagen en " << palabras[1] << " fue segmentada correctamente y guardada en " << palabras[2] << std::endl;
      }
      else
      {
        std::cout << "La imagen " << palabras[1] << " no pudo ser segmentada" << std::endl;
      }
    }
    else if(comando == "ayuda")
    {
      std::cout << "Lista de comandos disponibles:" << std::endl;
      std::cout << "\tcargar_volumen <nombre_base> <n_im>" << std::endl;
      std::cout << "\tproyeccion2D <dirección> <criterio> <nombre_archivo>" << std::endl;
      std::cout << "\tcodificar_imagen <nombre_imagen.(ppm o pgm)> <nombre_archivo.huffman>" << std::endl;
      std::cout << "\tdecodificar_archivo <nombre_archivo.huffman> <nombre_imagen.(ppm o pgm)>" << std::endl;
      std::cout << "\tsegmentar <entrada_imagen.(ppm o pgm)> <salida_imagen.(ppm o pgm)> sx1 sy1 sl1 sx2 sy2 sl2 ..." << std::endl;
      std::cout << "\tsalir" << std::endl;
    }
    else if(comando == "ayuda cargar_volumen")
    {
      std::cout << "cargar_volumen <nombre_base> <n_im>" << std::endl;
    }
    else if(comando == "ayuda proyeccion2D")
    {
      std::cout << "proyeccion2D <dirección> <criterio> <nombre_archivo>" << std::endl;
    }
    else if(comando == "ayuda codificar_imagen")
    {
      std::cout << "codificar_imagen <nombre_imagen.(ppm o pgm)> <nombre_archivo.huffman>" << std::endl;
    }
    else if(comando == "ayuda decodificar_archivo")
    {
      std::cout << "decodificar_archivo <nombre_archivo.huffman> <nombre_imagen.(ppm o pgm)>" << std::endl;
    }
    else if(comando == "ayuda segmentar")
    {
      std::cout << "segmentar <entrada_imagen.(ppm o pgm)> <salida_imagen.(ppm o pgm)> sx1 sy1 sl1 sx2 sy2 sl2 ..." << std::endl;
    }
    else if(comando != "salir")
    {
      std::cout << "Comando no encontrado." << std::endl;
    }

  }while(comando!="salir");

}
