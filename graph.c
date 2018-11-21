#include "graph.h"
#include "pointers.h"
#include "path.h"
#include <stdlib.h>

/**
 * Check if a point is inside the map
 * @param  _row    point y coordinate
 * @param  _column point x coordinate
 * @param  _height map numb of lines
 * @param  _width  map numb of columns
 * @param  map     2D array fulfilled with costs
 * @return         1-valid, 0-not valid
 */
int isValidPoint(unsigned int _row, unsigned int _column,
                 unsigned int _height, unsigned int _width,
                 unsigned char **map){
  if (_row < 0 || _row >= _height || _column < 0 || _column >= _width
       || ! map[_row][_column])
    return 0;
  return 1;
}

/**
 * Assures the kight is moving as one
 * @param  tourist_shadow struct storing previous point coord.
 * @param  l              point y to be tested
 * @param  c              point x tbt
 * @return                1-knight move, 0-smtg else
 */
int isReachablePoint(Point *tourist_shadow, unsigned int l,
                      unsigned int c){
  unsigned int vert=abs(tourist_shadow->l-l);
  unsigned int hori=abs(tourist_shadow->c-c);
  if( (vert+hori)==3 ){
    if( vert!=0 && hori!=0 )
        return 1;
  }
  return 0;
}

/**
 * Equivalent to isReachablePoin with both positions
 * stored in arrays
 */
int isReachablePointLight(unsigned int L, unsigned int C, unsigned int l,
                      unsigned int c){
  unsigned int vert=abs(L-l);
  unsigned int hori=abs(C-c);
  if( (vert+hori)==3 ){
    if( vert!=0 && hori!=0 )
        return 1;
  }
  return 0;
}

/**
 * Receiving the current lowest cost in the imediate move
 * updates it if it's lower
 * @param  _row    point y coordinate
 * @param  _column point x coordinate
 * @param  _height map numb of lines
 * @param  _width  map numb of columns
 * @param  map     2D array fulfilled with costs
 * @param cost     current cost
 */
void updateCost(unsigned int _row, unsigned int _column,
                        unsigned int _width, unsigned int _height,
                        unsigned char **map, unsigned int *cost){
  if (isValidPoint(_row, _column, _height, _width, map) &&
      (*cost == 0 || map[_row][_column] < *cost))
    *cost = map[_row][_column];
}

/**
 * using updateCost establishes lowest cost possible for
 * the imediate movement
 * @param  origin  point of departure
 * @param  map     2D array fulfilled with costs
 * @param  _height map numb of lines
 * @param  _width  map numb of columns
 * @return  cost value or NULL if no move is available
 */
unsigned int findLowestCost(unsigned int *origin, unsigned char **map,
                             unsigned int _height, unsigned int _width){
  /**
   * Assure origin point is inside the given map
   * @param  map     2D array fulfilled with costs
   */
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
/**
 * free allocated memory in structures and list of a path
 * @param path inicial node
 */
void freePath(Path *route){
  Point *iter=route->init_point, *n_iter=NULL;
  while(iter->n_point!=NULL){
    n_iter=iter->n_point;
    free(iter);
    iter=n_iter;
  }
  free(iter);
  free(route);
}

/**
 * Receiving a array with points coordinates test if it defiens a possi-
 * ble path
 * @param  path array saving the coordinates of each point of the path
 * @param  map     2D array fulfilled with costs
 * @param  _height map numb of lines
 * @param  _width  map numb of columns
 * @param  _num_tur_points number of points in the coordinates matrix
 * @return totalcost of the path or NULL if it isn't one
 */
unsigned int checkPath(unsigned int **path, unsigned char **map,
                        unsigned int _height, unsigned int _width,
                        unsigned int _num_tur_points){
  if (!isValidPoint(path[0][0], path[0][1], _height, _width, map))
    return 0;
  Path *route=safeMalloc(sizeof(Path));
  route->n_points=0;
  route->cost=0;
  route->init_point=NULL;
  Point *tourist=NULL, *tourist_shadow=NULL;
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

/**
 * Equivalent to checkPathLight implemented without using lists of structs
 */
unsigned int checkPathLight(unsigned int **path, unsigned char **map,
                        unsigned int _height, unsigned int _width,
                        unsigned int _num_tur_points){
  unsigned int point_ix=0, cost=0;

  if (!isValidPoint(path[point_ix][0], path[point_ix][1], _height,
        _width, map))
      return 0;

  for (point_ix = 1; point_ix < _num_tur_points; point_ix++){
    if (!isValidPoint(path[point_ix][0], path[point_ix][1], _height,
          _width, map))
        break;
    if(!isReachablePointLight(path[point_ix-1][0],path[point_ix-1][1],
                              path[point_ix][0], path[point_ix][1]))
      break;
    cost+= map[ path[point_ix][0] ][ path[point_ix][1] ];
  }

  if(_num_tur_points-point_ix!=0)
    return 0;

  return cost;
}
