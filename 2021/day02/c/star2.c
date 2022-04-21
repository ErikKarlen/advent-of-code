#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
        FILE *fp;
        unsigned int pos = 0, depth = 0, aim = 0, val;
        char line[256];
        char *command;

        fp = fopen(argv[1], "r");

        while (fgets(line, sizeof(line), fp)) {
                command = strtok(line, " ");
                val = atoi(strtok(NULL, " "));
                if (!strcmp(command, "forward")) {
                        pos += val;
                        depth += aim * val;
                }
                if (!strcmp(command, "down")) {
                        aim += val;
                }
                if (!strcmp(command, "up")) {
                        aim -= val;
                }
        }
        printf("%d\n", depth * pos);

        fclose(fp);
        return 0;

}
