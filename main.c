
#include "bsq.h"

int main(int ac, char **av) {
    t_bsq bsq;
    init_app(&bsq);
    
    if (ac == 1)
    {
        if (get_data_from_stream(stdin, &bsq)){
            printf("Error\n");
            return 1;
        }
    }
    else if (ac == 2)
    {
        FILE  *stream = fopen(av[1], "r");
        if (!stream) {
            printf("Error\n");
            return 1;
        }
        if (get_data_from_stream(stream, &bsq)){
            printf("Error\n");
            return 1;
        }
        fclose(stream);
    }
    return 0;
}

