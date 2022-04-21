#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 3


int main(int argc, char *argv[])
{
        FILE *fp;
        int avg_depth[WINDOW_SIZE];
        int depth_sum = 0, prev_depth_sum, i;
        long int fpos;
        unsigned int num_incs = 0;
        char line[256];

        fp = fopen(argv[1], "r");

        fpos = ftell(fp);
        for (i = 0; i < WINDOW_SIZE; ++i) {
                fgets(line, sizeof(line), fp);
                depth_sum += atoi(line);
        }
        fseek(fp, fpos, SEEK_SET);

        while (fgets(line, sizeof(line), fp)) {
                prev_depth_sum = depth_sum;
                depth_sum = 0;
                fpos = ftell(fp);
                for (i = 0; i < WINDOW_SIZE; ++i) {
                        if (fgets(line, sizeof(line), fp)) {
                                depth_sum += atoi(line);
                        }
                        else {
                                break;
                        }
                }
                fseek(fp, fpos, SEEK_SET);
                if (depth_sum - prev_depth_sum > 0) {
                        num_incs++;
                }
        }

        printf("%u\n", num_incs);

        fclose(fp);
        return 0;

}
