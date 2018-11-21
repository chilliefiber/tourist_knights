/*
Funções relacionadas com alocação de memória
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * malloc func with safety condition included
 * @param  _size amount of memory to alloc
 * @return pointer to the memory allocated or end of
 * the program if an error happens
 */
void *safeMalloc(size_t _size){
  void *p = malloc(_size);
  if (p == NULL){
    exit (0);
  }
  return p;
}

/**
 * agglomerated of free funcs used dispite which program variant is called
 * @param _num_tur_points    num of points in tur_points array
 * @param tur_points         coordinates of each step of a path
 * @param  _height           map numb of lines
 * @param  _num_tur_points   number of points in the coordinates matrix
 */
void freeAll(unsigned int _num_tur_points, unsigned int ***tur_points,
              unsigned int  _height, unsigned char ***map){
  for (int point_ix = 0; point_ix < _num_tur_points; point_ix++)
    free((*tur_points)[point_ix]);
  free(*tur_points);
  *tur_points = NULL;
  for (int row = 0; row < _height; row++)
    free((*map)[row]);
  free(*map);
  *map = NULL;
}
