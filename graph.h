unsigned int findLowestCost(unsigned int *origin, unsigned int **map, 
                             unsigned int _height, unsigned int _width);
int isValidPoint(unsigned int _row, unsigned int _column, 
                 unsigned int _height, unsigned int _width,
                 unsigned int **map);
void updateCost(unsigned int _row, unsigned int _column, 
                        unsigned int _width, unsigned int _height,
                        unsigned int **map, unsigned int *cost);
