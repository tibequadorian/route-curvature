#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "route.h"

#define DATA_ALLOC_SIZE 128
#define LINE_ALLOC_SIZE 32


int main(int argc, char *argv[]) {
    const char* help = "Usage: route-curvature [options] -i file\n"
                       "Options:\n"
                       "-h, --help          prints this help message and exit\n"
                       "-s, --smoothness    number of points to calculate curvature from.\n"
                       "                    The more points, the smoother the output gets.\n"
                       "                    (Default value: 5)\n"
                       "-t                  treat input values as cartesic coordinates instead of\n"
                       "                    using mercator projection on geographic coordinates\n"
                       "-i, --input         input file\n"
                       "-o, --output        output file\n";
    bool true_input = 0;    // -t
    int smoothness = 3;     // -s, --smoothness
    FILE* input = NULL;     // -i, --input
    FILE* output = stdout;  // -o, --output
    // parse arguments
    const char* short_options = "hts:i:o:";
    const struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"smoothness", required_argument, NULL, 's'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };
    int c, option_index;
    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                printf(help);
                return 0;
            case 't':
                true_input = true;
                break;
            case 's':
                smoothness = atoi(optarg);
                if (smoothness < 3) {
                    fprintf(stderr, "-s, --smoothness option expects integer value > 3\n");
                    return 1;
                }
                break;
            case 'i':
                if (optarg != NULL) {
                    input = fopen(optarg, "r");
                    if (input == NULL) {
                        fprintf(stderr, "input file \"%s\" could not be opened.\n", optarg);
                        return 1;
                    }
                }
                break;
            case 'o':
                output = fopen(optarg, "w");
                if (output == NULL) {
                    fprintf(stderr, "output file \"%s\" could not be created.\n", optarg);
                    return 1;
                }
                break;
            default:
                return 1;
        }
    }
    if (input == NULL) {
        fprintf(stderr, "input file not specified.\n"
                "Usage: route-curvature [options] -i file\n");
        return 1;
    }
    // read input
    unsigned int length = 0, max_length = DATA_ALLOC_SIZE;
    struct Vector* data = (struct Vector*)malloc(max_length*sizeof(struct Vector));
    char* line = malloc(LINE_ALLOC_SIZE*sizeof(char));
    while (!feof(input)) {
        struct Vector d;
        if (fgets(line, LINE_ALLOC_SIZE, input) == NULL ||
                sscanf(line, "%lf %lf", &d.x, &d.y) != 2)
            continue;
        if (length == max_length) {
            max_length += DATA_ALLOC_SIZE;
            data = (struct Vector*)realloc(data, max_length*sizeof(struct Vector));
        }
        data[length++] = d;
    }
    free(line);
    data = (struct Vector*)realloc(data, length*sizeof(struct Vector));
    // calculate curvature and print result
    int result_length = length-smoothness+1;
    if (result_length <= 0) {
        fprintf(stderr, "ERROR: empty result\n"
                "not enough waypoints on route or smoothness value too high?\n");
        return 1;
    }
    struct Vector* result_data = calc_curvature(data, length, true_input, smoothness);
    for (int i = 0; i < result_length; i++)
        fprintf(output, "%lf %lf\n", result_data[i].x, result_data[i].y); 
    // free allocated memory
    free(data);
    free(result_data);
    return 0;
}

