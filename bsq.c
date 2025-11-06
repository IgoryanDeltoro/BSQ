#include "bsq.h"

void init_app(t_bsq *bsq)
{
    bsq->map.grid = NULL;
    bsq->map.height = 0;
    bsq->map.width = 0;
    bsq->info.rows = 0;
    bsq->squere.size = 0;
    bsq->squere.i = 0;
    bsq->squere.j = 0;
}

int str_len(const char *str){
    if (!str) return 0; 
    int i = 0;
    for (; str[i]; i++){}
    return i;
}

void clean_array(char **arr, int len){
    if (!arr) return;
    for (int i = 0; i < len; ++i)
    {
        if (arr[i])
            free(arr[i]);
    }
    free(arr);
}
void clean_seample_line (char *str){ if (str) free(str); }

char *strdup_nl(const char *str) 
{
    int len = 0;
    while (str[len] && str[len] != '\n') len++; 
    char *res = (char*)malloc((len + 1) * sizeof(char));
    if (!res) return NULL;
    int i = 0;
    while ( i < len)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return res;
}

void skip_spases(char *str, int *i) { while (str[*i] == 32 || str[*i] == 9) {++(*i);}}

int parse_info(char *info, t_bsq *bsq) {
    int i = 0;
    long rows = 0;

    // sckip whitespase
    skip_spases(info, &i);
    if (info[i] == 10) return 1;

    // get number of lines
    for (; info[i] != 32; i++) { 
        if (info[i] < 48 || info[i] > 57) 
            return 1;
        rows = rows * 10 + (info[i] - 48); 
    }
    if (rows <= 0 || rows > 10000000 || info[i] != 32) return 1;
    bsq->info.rows = (int)rows;
    skip_spases(info, &i);
    if (info[i] == 10) return 1;

    // get empty char 
    if (info[i] < 32 || info[i] > 126 || info[i + 1] != 32) 
        return 1;
    bsq->info.empty = info[i++];
    skip_spases(info, &i);
    if (info[i] == 10) return 1;

    // get obstacle char
    if (info[i] < 32 || info[i] > 126 || info[i + 1] != 32) 
        return 1;
    bsq->info.obstacle = info[i++];
    skip_spases(info, &i);
    if (info[i] == 10) return 1;

    // get full char
    if (info[i] < 32 || info[i] > 126) 
        return 1;
    bsq->info.full = info[i++];
    skip_spases(info, &i);

    if (info[i] && info[i] != '\n' && info[i] != '\0') return 1;

    if (bsq->info.obstacle == bsq->info.full || bsq->info.obstacle == bsq->info.empty || bsq->info.full == bsq->info.empty ) return 1;
    return 0;
}

int parse_map(FILE *stream, t_bsq *bsq)
{
     if (!stream || !bsq) return 1;

    bsq->map.grid = (char**)malloc((bsq->info.rows + 1) * sizeof(char*));
    bsq->map.grid[bsq->info.rows] = NULL;
    if (!bsq->map.grid) return 1;

    int rows = 0;
    int prev_len = -1;
    for (; rows < bsq->info.rows; ++rows)
    {
        char *line = NULL;
        size_t size = 0;
        ssize_t nread = getline(&line, &size, stream);
        if (nread == -1)
        {
            printf("getline error\n");
            clean_array(bsq->map.grid, rows);
            return 1;
        }
        char *l = strdup_nl(line);
        free(line);
        if (!l)
        {
            printf("strdup error\n");
            clean_array(bsq->map.grid, rows);
            return 1;
        }
        // printf("l: %s\n", l);

        // check size of the line 
        int len = str_len(l);
        if (prev_len == -1) prev_len = len;
        else if (prev_len != len) 
        {
            printf("size error\n");
            clean_seample_line(l);
            clean_array(bsq->map.grid, rows);
            return 1;
        }

        for (int j = 0; j < len; ++j)
        {
            if (l[j] != bsq->info.empty && l[j] != bsq->info.obstacle && l[j] != bsq->info.full) {
                printf("different chur error\n");
                clean_seample_line(l);
                clean_array(bsq->map.grid, rows);
                return 1;
            }
        }
        bsq->map.grid[rows] = l;
    }
    bsq->map.height = rows;
    bsq->map.width = prev_len;
    return 0;
}

int get_min(int top, int diag, int left){
    int min = top;
    if (left < min)
        min = left;
    if (diag < min)
        min = diag;
    return min;
}

int find_max_squere(t_bsq *bsq) 
{
    if (!bsq || !bsq->map.grid || !bsq->info.rows) return 1;

    int matrix[bsq->map.height][bsq->map.width];
    for (int i = 0; i < bsq->map.height; i++){
        for(int j = 0; j < bsq->map.width; j++)
            matrix[i][j] = 0;
    }

    for (int i = 0; i < bsq->map.height; ++i){
        for(int j = 0; j < bsq->map.width; ++j)
        {
            if (bsq->map.grid[i][j] == bsq->info.obstacle)
                matrix[i][j] = 0;
            else if (i == 0 || j == 0)
                matrix[i][j] = 1;
            else {
                int min = get_min(matrix[i - 1][j], matrix[i - 1][j - 1], matrix[i][j - 1]);
                matrix[i][j] = min + 1;
            }

            if (matrix[i][j] > bsq->squere.size)
            {
                bsq->squere.size = matrix[i][j];
                bsq->squere.i = i - matrix[i][j] + 1;
                bsq->squere.j = j - matrix[i][j] + 1;
			    // printf("size: %d i: %d j: %i \n", bsq->squere.size, i, j);
			    // printf("size: %d i: %d j: %i \n", bsq->squere.size, bsq->squere.i, bsq->squere.j);
                
            }
        }
    }
    return 0;
}

void print_filled_square(t_bsq* bsq)
{
	for(int i = bsq->squere.i; i < bsq->squere.i + bsq->squere.size; i++)
	{
		for(int j = bsq->squere.j; j < bsq->squere.j + bsq->squere.size; j++)
		{
			if((i < bsq->map.height) && (j < bsq->map.width))
				bsq->map.grid[i][j] = bsq->info.full;
		}
	}

	for(int i = 0; i < bsq->map.height; i++)
	{
		fprintf(stdout, "%s\n", bsq->map.grid[i]);
	}
}

int get_data_from_stream(FILE *stream, t_bsq *bsq) 
{
    if (!stream || !bsq) return 1;

    char *info = NULL;
    size_t size = 0;
    ssize_t nread = getline(&info, &size, stream);
    if (!info || nread <= 0) return 1;
    
    // get first line with map information
    if (parse_info(info, bsq)) { clean_seample_line(info); return 1; }
    // printf("Ok: %d %c %c %c\n", bsq->info.rows, bsq->info.empty, bsq->info.obstacle, bsq->info.full);
    clean_seample_line(info);

    // parse map
    if (parse_map(stream, bsq)) {
        return 1;
    }

    // find the bigest squere
    find_max_squere(bsq);

    // print the found max squere
    print_filled_square(bsq);
    // clean memory 
    clean_array(bsq->map.grid, bsq->map.height);
    return 0;
}
