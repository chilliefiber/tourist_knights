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
    exit (0);
  }
  FILE *input = fopen(argv[1], "r");
  if (input == NULL){
    printf("Erro a abrir ficheiro\n");
    exit (0);
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
    exit (0);
  }
  unsigned int width, height, num_tur_points, **tur_points = NULL;
  unsigned char **map = NULL;
  int not_over;
  int valid_challenge;
  unsigned int aux1, aux2;
  char objective;
  do {
    if(fscanf(input, "%u", &height)!=1)
      exit(0);
    if(fscanf(input, "%u", &width)!=1)
      exit(0);
    if(fscanf(input, " %c", &objective)!=1)
      exit(0);
    if(fscanf(input, "%u", &num_tur_points)!=1)
      exit(0);
    fprintf(output, "%u ", height);
    fprintf(output, "%u ", width);
    fprintf(output, "%c ", objective);
    fprintf(output, "%u ", num_tur_points);
    valid_challenge = 1;
    if (objective != 'A' && objective != 'B')
      valid_challenge = 0;
    if (valid_challenge)
      tur_points = safeMalloc(sizeof(unsigned int*) * num_tur_points);
    for (int point_ix = 0; point_ix < num_tur_points; point_ix++){
      if (valid_challenge){
        tur_points[point_ix] = safeMalloc(sizeof(unsigned int) * 2);
        if(fscanf(input, "%u %u", tur_points[point_ix], tur_points[point_ix] + 1)!=2)
          exit(0);
      }
      else{
        if(fscanf(input, "%u %u", &aux1, &aux2)!=2)
          exit(0);
      }
    }
    map = createMap(input, width, height, valid_challenge);
    if (objective == 'A'){
      unsigned int answer = findLowestCost(tur_points[0], map, height, width);
      if (!answer || num_tur_points != 1)
        fprintf(output, "-1 0");
      else
        fprintf(output, "1 %u", answer);
    }
    else if(objective == 'B'){
      unsigned int answer = checkPathLight(tur_points, map, height, width,
                                       num_tur_points);
      if (!answer)
        fprintf(output, "-1 0");
      else
        fprintf(output, "1 %u", answer);
    }
    else
      fprintf(output, "-1 0");
    fprintf(output, "\n\n");
    if (valid_challenge)
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
  exit (0);
}
