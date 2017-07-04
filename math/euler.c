/* Euler function phi(x), by Abreto<m@abreto.net>. */

#define MAXX    3000000

int phi[MAXX];
void get_euler(void)
{
    int i = 0, j = 0;
    phi[1] = 1;
    for(i = 2;i < MAXX;++i)
        if(!phi[i])
            for(j = i;j < MAXX;j += i)
            {
                if(!phi[j]) phi[j] = j;
                phi[j] = phi[j]/i * (i-1);
            }
}
