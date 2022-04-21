#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int bin_to_dec(char *bin) {
        char digit;
        int i = 0;
        int dec = 0;

        while (digit = bin[i++]) {
                dec = dec << 1;
                if (digit == '1') {
                        dec += 1;
                }
        }
        return dec;
}


char find_col_max(char *lines[], unsigned int num_lines, unsigned int col)
{
        int i;
        char ret;
        unsigned int sum = 0;

        for (i = 0; i < num_lines; ++i) { 
                char c = lines[i][col];
                if (c == '1') {
                        ++sum;
                }
        }

        ret = sum > 0.5 * num_lines ? '1' : '0';
        return ret;
}


int main(int argc, char *argv[])
{
        FILE *fp;
        unsigned int i = 0, num_lines, num_digits;
        char line[256], max_char;
        char *lines[1024];
        char gamma[16];
        char epsilon[16];

        fp = fopen(argv[1], "r");

        while (fgets(line, sizeof(line), fp)) {
                lines[i++] = strdup(line);
        }

        num_lines = i;
        num_digits = strlen(line) - 1;

        for (i = 0; i < num_digits; ++i) {
                max_char = find_col_max(lines, num_lines, i);
                if (max_char == '1') {
                        snprintf(gamma + i, sizeof(gamma), "%c", '1');
                        snprintf(epsilon + i, sizeof(epsilon), "%c", '0');
                } else {
                        snprintf(gamma + i, sizeof(gamma), "%c", '0');
                        snprintf(epsilon + i, sizeof(epsilon), "%c", '1');
                }
        }
        printf("%d\n", bin_to_dec(gamma) * bin_to_dec(epsilon));

        fclose(fp);
        return 0;

}
