/* I/O Plug-in, by Abreto <m@abreto.net>. */
#include <stdio.h>

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif

#define ISDIGIT(x) ((x>='0')&&(x<='9'))
int readn(int *n)
{
    int c=0;*n=0;
    for(;!ISDIGIT(c);c=getchar());
    for(;ISDIGIT(c);c=getchar())*n=(*n)*10+c-'0';
    return (*n);
}
void putn(int n)
{
    int ns[16]={0,n%10},nd=1;
    while(n/=10)ns[++nd]=n%10;
    while(nd)putchar(ns[nd--]+'0');
}
