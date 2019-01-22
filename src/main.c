#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

#include "route.h"


int main(int argc, char *argv[]) {
    bool true_input = 0;  // -t
    int smoothness = 3;   // -s, --smoothness
    char* output = NULL;  // -o, --output
    // parse arguments
    const char* short_options = "ts:o:";
    const struct option long_options[] = {
        {"smoothness", required_argument, NULL, 's'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };
    int c, option_index;
    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (c) {
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
            case 'o':
                strcpy(output, optarg);
                break;
            default:
                return 1;
        }
    }
    
    return 0;
}

