#include "graph.h"
#include "pointers.h"
#include <stdio.h>
int isValidPoint(unsigned int _row, unsigned int _column, 
                 unsigned int _height, unsigned int _width,
                 unsigned int **map){
  if (_row < 0 || _row >= _height || _column < 0 || _column >= _width
       || ! map[_row][_column])
    return 0;
  return 1;
}

void updateCost(unsigned int _row, unsigned int _column, 
                        unsigned int _width, unsigned int _height,
                        unsigned int **map, unsigned int *cost){
  if (isValidPoint(_row, _column, _height, _width, map) &&
      (*cost == 0 || map[_row][_column] < *cost))
    *cost = map[_row][_column];
}

// devolve NULL se não houver nenhum ponto
unsigned int findLowestCost(unsigned int *origin, unsigned int **map, 
                             unsigned int _height, unsigned int _width){
  // verificar se o ponto está no mapa
  if (!isValidPoint(origin[0], origin[1], _height, _width, map))
    return 0;
  unsigned int cost = 0;
  updateCost(origin[0] + 2, origin[1] + 1, _width, _height, 
             map, &cost);
  updateCost(origin[0] + 2, origin[1] - 1, _width, _height, 
             map, &cost);
  updateCost(origin[0] + 1, origin[1] + 2, _width, _height, 
             map, &cost);
  updateCost(origin[0] + 1, origin[1] - 2, _width, _height,
             map, &cost); 
  updateCost(origin[0] - 2, origin[1] + 1, _width, _height,
             map, &cost);
  updateCost(origin[0] - 2, origin[1] - 1, _width, _height,
             map, &cost);
  updateCost(origin[0] - 1, origin[1] - 2, _width, _height,
             map, &cost);   
  updateCost(origin[0] - 1, origin[1] + 2, _width, _height,
             map, &cost);
  return cost;
}
