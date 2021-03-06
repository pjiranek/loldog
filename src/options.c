#include "config.h"
#include "options.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(void)
{
    printf("Usage: loldog [OPTION]... [FILE]...\n\n"
           "Concatenate FILE(s) and/or standard input to standard output...\n"
           "...and do something funky.\n\n"
           "Options:\n\n"
           "-t TYPE            Type of the coloring. Accepted values are:\n"
           "                      rw  - row-wise coloring (default),\n"
           "                      rws - row-wise scaled coloring,\n"
           "                      dg  - diagonal coloring.\n"
           "-c SCHEME          Color scheme. Accepted values are:\n"
           "                      rainbow (default), gray, jet, hot, cool.\n"
           "-R N, -C N         Row and column increment. Depending on the scheme, the\n"
           "                   increments represent how many rows and/or columns are\n"
           "                   colored with the same color. The default increments are\n"
           "                   1 for rows and 3 for columns.\n"
           "-b                 Turn off the color bouncing. By default, the color map is\n"
           "                   traversed from the first color to the last one and then the\n"
           "                   colors 'bounces' back from the last one to the first one.\n"
           "                   Using this option, the bouncing is turned off and when the\n"
           "                   last color of the map is hit, the coloring continues again\n"
           "                   from the first one.\n"
           "-h                 Output this help and exit.\n"
           "-v                 Output version information and exit.\n\n"
           "With no FILE or when FILE is -, read standard input\n\n"
           "Report loldog bugs to pavel.jiranek@gmail.com\n");
}

void version()
{
    printf("   ___               ___        __\n"
           "  /\\_ \\             /\\_ \\      /\\ \\\n"
           "  \\//\\ \\      ___   \\//\\ \\     \\_\\ \\     ___      __\n"
           "    \\ \\ \\    / __`\\   \\ \\ \\    /'_` \\   / __`\\  /'_ `\\\n"
           "     \\_\\ \\_ /\\ \\L\\ \\   \\_\\ \\_ /\\ \\L\\ \\ /\\ \\L\\ \\/\\ \\L\\ \\\n"
           "     /\\____\\\\ \\____/   /\\____\\\\ \\___,_\\\\ \\____/\\ \\____ \\\n"
           "     \\/____/ \\/___/    \\/____/ \\/__,_ / \\/___/  \\/___L\\ \\\n"
           "                                                  /\\____/\n"
           "                                                  \\/___/\n"
           "Version %d.%d.%d\n\n"
           "Copyright (C) 2015 Pavel Jiranek, <pavel.jiranek@gmail.com>\n"
           "The MIT License <http://opensource.org/licenses/MIT>\n",
           VERSION_MAJOR,
           VERSION_MINOR,
           VERSION_BUILD);
}

int get_opts(int argc, char ** argv, options * opts)
{
    int opt;

    // Set default options.
    opts->lt     = LT_RW;
    opts->cs     = CS_RAINBOW;
    opts->rinc   = 1;
    opts->cinc   = 3;
    opts->bounce = 1;

    // Parse options from arguments.
    while ((opt = getopt(argc, argv, "hvt:R:C:c:b")) != -1)
    {
        switch (opt)
        {
            case 't':
                if (strcmp(optarg, "rw")  == 0) opts->lt = LT_RW;
                else if (strcmp(optarg, "rws") == 0) opts->lt = LT_RWS;
                else if (strcmp(optarg, "dg")  == 0) opts->lt = LT_DG;
                else
                {
                    fprintf(stderr, "Unknown LOL-type: %s\n\n", optarg);
                    help();

                    return -1;
                }

                break;

            case 'c':
                if (strcmp(optarg, "rainbow") == 0) opts->cs = CS_RAINBOW;
                else if (strcmp(optarg, "gray")    == 0) opts->cs = CS_GRAY;
                else if (strcmp(optarg, "jet")     == 0) opts->cs = CS_JET;
                else if (strcmp(optarg, "hot")     == 0) opts->cs = CS_HOT;
                else if (strcmp(optarg, "cool")    == 0) opts->cs = CS_COOL;
                else
                {
                    fprintf(stderr, "Unknown color scheme: %s\n\n", optarg);
                    help();

                    return -1;
                }

                break;

            case 'R':
                opts->rinc = atoi(optarg);
                break;

            case 'C':
                opts->cinc = atoi(optarg);
                break;

            case 'b':
                opts->bounce = 0;
                break;

            case 'h':
                help();
                return 0;

            case 'v':
                version();
                return 0;

            default:
                help();
                return -1;
        }
    }

    return optind;
}
