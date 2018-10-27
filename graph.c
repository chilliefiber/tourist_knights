#include "graph.h"
#include "pointers.h"

int isValidPoint(unsigned int _row, unsigned int _column, 
                 unsigned int _height, unsigned int _width,
                 unsigned int **map){
  if (_row < 0 || _row >= _height || _column < 0 || _column >= _width
       || ! map[_row][_column])
    return 0;
  return 1;
}

unsigned int updateCost(unsigned int _row, unsigned int _column, 
                        unsigned int _width, unsigned int _height,
                        unsigned int ** map, unsigned int **result,
                        unsigned int _cost){
  if (isValidPoint(_row, _column, _height, _width, map) &&
      (_cost == 0 || map[_row][_column] < _cost)){
    (*result)[0] = _row;
    (*result[1]) = _column;
    return map[_row][_column];
  }
  return 0;
}

// devolve NULL se não houver nenhum ponto
unsigned int *findLowestCost(unsigned int *origin, unsigned int **map, 
                             unsigned int _height, unsigned int _width){
  unsigned int cost = 0;
  unsigned int *result = safeMalloc(sizeof(unsigned int) * 2);
  cost = updateCost(origin[0] + 3, origin[1] + 1, _width, _height, 
                    map, &result, cost);
  cost = updateCost(origin[0] + 3, origin[1] - 1, _width, _height, 
                    map, &result, cost);
  cost = updateCost(origin[0] + 1, origin[1] + 3, _width, _height, 
                    map, &result, cost);
  cost = updateCost(origin[0] + 1, origin[1] - 3, _width, _height, 
                    map, &result, cost);
   
  
  cost = updateC
    
