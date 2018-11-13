/*
Ficheiro com as funções associadas ao processamento dos ficheiros de input
*/

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "pointers.h"

unsigned char **createMap(FILE *fp, int _width, int _height){
  // alocar memória para o mapa
  unsigned char **map = safeMalloc(sizeof(unsigned char*) * _height);
  for (int row = 0; row < _height; row++)
     map[row] = safeMalloc(sizeof(unsigned char) * _width);
  // preencher mapa
  for (int row = 0; row < _height; row++){
    for (int column = 0; column < _width; column++)
      if (fscanf(fp, "%hhu", map[row] + column) != 1)
        exit (0);
  }
  return map;
}
