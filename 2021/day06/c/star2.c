#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
        FILE *fp;
        int i, j;
        long long counts[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        long long babies, num_fishies = 0;
        char line[1024];
        const char* tok;
        const char* sep = ",";

        fp = fopen(argv[1], "r");
        fgets(line, sizeof(line), fp);
        tok = strtok(line, sep);
        while (tok != NULL) {
                counts[atoi(tok)] += 1;
                tok = strtok(NULL, sep);
        }

        for (i = 0; i < 256; ++i) {
                babies = counts[0];
                for (j = 1; j < 9; ++j) {
                        counts[j-1] = counts[j];
                        counts[j] = 0;
                }
                counts[6] += babies;
                counts[8] = babies;
        }
        for (i = 0; i < 9; ++i) {
                num_fishies += counts[i];
        }

        printf("%llu\n", num_fishies);

        fclose(fp);
        return 0;

}
