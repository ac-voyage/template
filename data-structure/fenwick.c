/* Fenwick Tree (Binary Indexed Tree), by Abreto <m@abreto.net>. */

#define MAXN 100001
#define LOWBIT(x)   ((x)&(-(x)))

int N;
int fen[MAXN];

void update(int i, int dx)
{
    while(i <= N)
    {
        fen[i] += dx;
        i += LOWBIT(i);
    }
}

int sum(int i)
{
    int s = 0;
    while(i > 0)
    {
        s += fen[i];
        i -= LOWBIT(i);
    }
    return s;
}
