#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

#include "route.h"


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
    // TODO
    return 0;
}

