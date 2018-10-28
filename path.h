typedef struct _point{
  unsigned int l;
  unsigned int c;
  unsigned int cost;
  struct _point *n_point;
} Point;

typedef struct _path{
  unsigned int n_points;
  unsigned int cost;
  Point *init_point;
} Path;
