unsigned int findLowestCost(unsigned int *origin, unsigned int **map,
                             unsigned int _height, unsigned int _width);
unsigned int checkPath(unsigned int **path, unsigned int **map,
                        unsigned int _height, unsigned int _width,
                        unsigned int _num_tur_points);
int isValidPoint(unsigned int _row, unsigned int _column,
                 unsigned int _height, unsigned int _width,
                 unsigned int **map);
void updateCost(unsigned int _row, unsigned int _column,
                        unsigned int _width, unsigned int _height,
                        unsigned int **map, unsigned int *cost);
