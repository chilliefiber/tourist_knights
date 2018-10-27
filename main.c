#include <stdio.h>
#include "process.h"
#include "pointers.h"

int main(int argc, char **argv){
  char *ending = strstr(argv[1], ".cities");
  if (ending == NULL || strlen(ending) != strlen(".cities"){
    printf("O ficheiro não tem a extensão correta.\n");
    return 1;
  }
  FILE *input = fopen(argv[1], "r");
  if (input == NULL){
    printf("Erro a abrir ficheiro\n");
    return 2;
  }
  unsigned int width, height, num_tur_points, **map = NULL, 
               **tur_points = NULL;
  char objective;
  do {
    fscanf(input, "%u", &height);
    fscanf(input, "%u", &width);
    fscanf(input, "%c", &objective);
    fscanf(input, "%u", &num_tur_points);
    tur_points = safeMalloc(sizeof(unsigned int*) * num_tur_points);
    for (int point_ix = 0; point_ix < num_tur_points; point_ix++){
      tur_points[point_ix] = safeMalloc(sizeof(unsigned int) * 2);
      fscanf(input, "%u %u", tur_points[point_ix], tur_points[point_ix] + 1);
    }
    map = createMap(input, width, height);
    if (objective == 'A'){
      int *answer = findLowestCost(tur_points[0], map, height, width);  
    freeAll(num_tur_points, &tur_points, height, &map);
  } while (fgetc(input) != EOF);
  
}
