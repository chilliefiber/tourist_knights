#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "process.h"
#include "pointers.h"
#include "graph.h"

int main(int argc, char **argv){
  char *ending = strstr(argv[1], ".cities");
  if (ending == NULL || strlen(ending) != strlen(".cities")){
    printf("O ficheiro não tem a extensão correta.\n");
    return 1;
  }
  FILE *input = fopen(argv[1], "r");
  if (input == NULL){
    printf("Erro a abrir ficheiro\n");
    return 2;
  }
  char *name = strtok(argv[1], ".");
  char *output_name = safeMalloc(sizeof(char) * (strlen(name) + strlen(".valid") + 1));
  strcpy(output_name, name);
  strcat(output_name, ".valid");
  FILE* output = fopen(output_name, "w");
  free(output_name);
  if (output == NULL){
    printf("Erro a criar ficheiro de output\n");
    fclose(input);
    return 3;
  }
  unsigned int width, height, num_tur_points, **map = NULL,
               **tur_points = NULL;
  int not_over;
  char objective;
  do {
    fscanf(input, "%u", &height);
    fscanf(input, "%u", &width);
    fscanf(input, " %c", &objective);
    fscanf(input, "%u", &num_tur_points);
    fprintf(output, "%u ", height);
    fprintf(output, "%u ", width);
    fprintf(output, "%c ", objective);
    fprintf(output, "%u ", num_tur_points);
    tur_points = safeMalloc(sizeof(unsigned int*) * num_tur_points);
    for (int point_ix = 0; point_ix < num_tur_points; point_ix++){
      tur_points[point_ix] = safeMalloc(sizeof(unsigned int) * 2);
      fscanf(input, "%u %u", tur_points[point_ix], tur_points[point_ix] + 1);
    }
    map = createMap(input, width, height);
    if (objective == 'A'){
      unsigned int answer = findLowestCost(tur_points[0], map, height, width);
      if (!answer)
        fprintf(output, "-1 0");
      else
        fprintf(output, "1 %u", answer);
    }
    else if(objective == 'B'){
      unsigned int answer = checkPath(tur_points, map, height, width,
                                       num_tur_points);
      if (!answer)
        fprintf(output, "-1 0");
      else
        fprintf(output, "1 %u", answer);
    }
    fprintf(output, "\n\n");
    freeAll(num_tur_points, &tur_points, height, &map);
    not_over = 0;
    while((objective = fgetc(input)) != EOF){
      if (objective != ' '  && objective != '\n' && objective != '\r'){
        fseek(input, -1, SEEK_CUR);
        not_over = 1;
        break;
      }
    }
  } while (not_over);
  fclose(output);
  fclose(input);
  return 0;
}
