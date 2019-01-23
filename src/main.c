#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "route.h"

#define DATA_ALLOC_SIZE 128
#define LINE_ALLOC_SIZE 32


static const char* help = "Usage: route-curvature [options] -i file\n"
                          "Options:\n"
                          "-h, --help          prints this help message and exit\n"
                          "-s, --smoothness    number of points to calculate curvature from.\n"
                          "                    The more points, the smoother the output gets.\n"
                          "                    (Default value: 5)\n"
                          "-t                  treat input values as cartesic coordinates instead of\n"
                          "                    using mercator projection on geographic coordinates\n"
                          "-i, --input         input file\n"
                          "-o, --output        output file\n";

int main(int argc, char *argv[]) {
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
    // read input file
    unsigned int length = 0, max_length = DATA_ALLOC_SIZE;
    double** data = (double**)malloc(max_length*sizeof(double*));
    char* line = malloc(LINE_ALLOC_SIZE*sizeof(char));
    double lat, lon;
    while (!feof(input)) {
        if (fgets(line, LINE_ALLOC_SIZE, input) == NULL)
            continue;
        if (sscanf(line, "%lf %lf", &lat, &lon) != 2)
            continue;
        if (length == max_length) {
            max_length += DATA_ALLOC_SIZE;
            data = (double**)realloc(data, max_length*sizeof(double*));
        }
        data[length] = (double*)malloc(2*sizeof(double));
        data[length][0] = lat;
        data[length][1] = lon;
        length++;
    }
    free(line);
    data = (double**)realloc(data, length*sizeof(double*));
    // calculate curvature and print result
    unsigned int result_length;
    double** result_data = calc_curvature(data, length, true_input, &result_length);
    for (unsigned int i = 0; i < result_length; i++)
        fprintf(output, "%lf %lf\n", result_data[i][0], result_data[i][1]);
    // free allocated memory
    for (unsigned int i = 0; i < length; i++)
        free(data[i]);
    free(data);
    for (unsigned int i = 0; i < result_length; i++)
        free(result_data[i]);
    free(result_data);
    return 0;
}

