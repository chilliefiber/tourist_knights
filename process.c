/*
Ficheiro com as funções associadas ao processamento dos ficheiros de input
*/

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "pointers.h"

/**
 * Allocs just enough memory for a 2D array that is fillled  with costs
 * @param  fp              file with the map
 * @param  _width  map numb of columns
 * @param  _height map numb of lines
 * @param  valid_challenge boolean that prevents the program from spending memory
 * if the challange isn't a recognized one
 * @return array map filled
 */
unsigned char **createMap(FILE *fp, int _width, int _height, int valid_challenge){
  unsigned char aux;
  unsigned char **map = NULL;
  if (valid_challenge){
    // alocar memória para o mapa
    map = safeMalloc(sizeof(unsigned char*) * _height);
    for (int row = 0; row < _height; row++)
       map[row] = safeMalloc(sizeof(unsigned char) * _width);
  }
  // preencher mapa
  for (int row = 0; row < _height; row++){
    for (int column = 0; column < _width; column++){
      if (valid_challenge){
        if (fscanf(fp, "%hhu", map[row] + column) != 1)
          exit (0);
      }
      else{
        if (fscanf(fp, "%hhu", &aux) != 1)
          exit (0);
      }
    }
  }
  return map;
}
