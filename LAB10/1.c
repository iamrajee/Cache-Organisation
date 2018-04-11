#include <stdio.h>
int tag[8];
int main( )
{
    int addr;
    int i, j, t;
    int hits, accesses;
    FILE *fp;
    fp = fopen("trace.txt", "r");
    hits = 0;
    accesses = 0;
    while (fscanf(fp, "%x", &addr) > 0) {
        /* simulate a direct-mapped cache with 8 words */
        accesses += 1;
        printf("%3d: 0x%08x ", accesses, addr);
        i = (addr >> 2) & 7;
        t = addr | 0x1f;
        if (tag[i] == t) {
            hits += 1;
            printf("Hit%d ", i);
        } else {
            /* allocate entry */
            printf("Miss ");
            tag[i] = t;

        }
        for (i = 0; i < 8; i++)
            printf("0x%08x ", tag[i]);
        printf("\n");
    }

printf("Hits=%d,Accesses=%d,Hitratio=%f\n",hits,accesses,((float)hits)/accesses);
    fclose(fp);
}

