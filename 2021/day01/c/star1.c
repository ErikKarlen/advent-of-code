#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
        FILE *fp;
        int depth, prev_depth;
        unsigned int num_incs = 0;
        char line[256];

        fp = fopen(argv[1], "r");
        fgets(line, sizeof(line), fp);
        prev_depth = atoi(line);

        while (fgets(line, sizeof(line), fp)) {
                depth = atoi(line);
                if (depth - prev_depth > 0) {
                        num_incs++;
                }
                prev_depth = depth;
        }

        printf("%u\n", num_incs);

        fclose(fp);
        return 0;

}
