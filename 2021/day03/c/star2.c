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

void remove_line(char *lines[], int index, int num_lines)
{
           int i;
           for(i = index; i < num_lines - 1; i++) {
                   lines[i] = lines[i + 1];
           }
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


unsigned int clear_lines(char *lines[], unsigned int num_lines, char max_char)
{
        int i, j = 0;
        unsigned int num_removed_lines = 0;

        for (i = num_lines - 1; i >= 0; --i) {
                if (lines[i][0] != max_char) {
                        printf("%c\n", max_char);
                        printf("%s\n", lines[i]);
                        remove_line(lines, i, num_lines);
                        num_removed_lines++;
                }
        }

        printf("\n\n");
        for (j = 0; j < num_lines - num_removed_lines; ++j) {
                printf("%s", lines[j]);
        }
        printf("%d\n", num_removed_lines);
        return num_removed_lines;
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
                } else if (max_char == '0') {
                        snprintf(gamma + i, sizeof(gamma), "%c", '0');
                        snprintf(epsilon + i, sizeof(epsilon), "%c", '1');
                }
                num_lines -= clear_lines(lines, num_lines, max_char);
        }
        printf("%d\n", bin_to_dec(gamma) * bin_to_dec(epsilon));

        fclose(fp);
        return 0;

}
