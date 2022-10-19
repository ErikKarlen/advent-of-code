#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
        FILE *fp;
        int answer = 0;

        fp = fopen(argv[1], "r");

        fclose(fp);

        printf("Answer is : %d\n", answer);

        return 0;

}
