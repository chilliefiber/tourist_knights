#include "graph.h"
#include "pointers.h"
#include "path.h"
#include <stdlib.h>

int isValidPoint(unsigned int _row, unsigned int _column,
                 unsigned int _height, unsigned int _width,
                 unsigned int **map){
  if (_row < 0 || _row >= _height || _column < 0 || _column >= _width
       || ! map[_row][_column])
    return 0;
  return 1;
}

int isReachablePoint(Point *tourist_shadow, unsigned int l,
                      unsigned int c){
  unsigned int vert=abs(tourist_shadow->l-l);
  unsigned int hori=abs(tourist_shadow->c-c);
  if( (vert+hori)!=3 )
    return 0;
  if( vert==0 || hori==0 )
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
  // verificar se o poninvalidoto está no mapa
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

//esta funcao deve ir para o pointers
void freePath(Path *route){
  Point *iter=route->init_point, *n_iter=NULL;
  while(iter->n_point!=NULL){
    n_iter=iter->n_point;
    free(iter);
    iter=n_iter;
  }
  free(route);
}

unsigned int checkPath(unsigned int **path, unsigned int **map,
                        unsigned int _height, unsigned int _width,
                        unsigned int _num_tur_points){
  if (!isValidPoint(path[0][0], path[0][1], _height, _width, map))
    return 0;
  Path *route=safeMalloc(sizeof(Path));
  route->n_points=0;
  route->cost=0;
  route->init_point=NULL;
  Point *tourist, *tourist_shadow;
  unsigned int cost=0;

  for (int point_ix = 0; point_ix < _num_tur_points; point_ix++){
    if (route->init_point!=NULL){
      if (!isValidPoint(path[point_ix][0], path[point_ix][1], _height,
          _width, map))
        break;
      if(!isReachablePoint(tourist_shadow, path[point_ix][0],
         path[point_ix][1]))
        break;
    }
    tourist=safeMalloc(sizeof(Point));
    tourist->l=path[point_ix][0];
    tourist->c=path[point_ix][1];
    tourist->cost=map[tourist->l][tourist->c];
    tourist->n_point=NULL;
    if(route->init_point!=NULL){
      tourist_shadow->n_point=tourist;
      route->cost+=tourist->cost;
    }
    else
      route->init_point=tourist;
    tourist_shadow=tourist;
    route->n_points++;
  }

  cost=route->cost;
  if(route->n_points != _num_tur_points)
    cost=0;
  freePath(route);
  return cost;
}
