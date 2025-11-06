#ifndef BSQ_H
#define BSQ_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map_info {
    int rows;        
    char empty;      
    char obstacle;   
    char full;       
} t_map_info;

typedef struct s_map {
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_squere {
    int size;
    int i;
    int j;
} t_squere;

typedef struct s_bsq {
    t_map       map;
    t_squere    squere;
    t_map_info  info;
} t_bsq;

void init_app(t_bsq *bsq);
int get_data_from_stream(FILE *stream, t_bsq *bsq);

#endif
