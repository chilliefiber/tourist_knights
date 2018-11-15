unsigned int findLowestCost(unsigned int *origin, unsigned char **map,
                             unsigned int _height, unsigned int _width);
unsigned int checkPath(unsigned int **path, unsigned char **map,
                       unsigned int _height, unsigned int _width,
                       unsigned int _num_tur_points);
unsigned int checkPathLight(unsigned int **path, unsigned char **map,
                            unsigned int _height, unsigned int _width,
                            unsigned int _num_tur_points);
int isValidPoint(unsigned int _row, unsigned int _column,
                 unsigned int _height, unsigned int _width,
                 unsigned char **map);
int isReachablePoint(Point *tourist_shadow, unsigned int l,
                     unsigned int c);                 
int isReachablePointLight(unsigned int L, unsigned int C, unsigned int l,
                          unsigned int c);
void updateCost(unsigned int _row, unsigned int _column,
                        unsigned int _width, unsigned int _height,
                        unsigned char **map, unsigned int *cost);
