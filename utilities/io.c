/* I/O Plug-in, by Abreto <m@abreto.net>. */
#include <stdio.h>

#define ISDIGIT(x) ((x>='0')&&(x<='9'))
void readn(int *n)
{
    int c=0;*n=0;
    for(;!ISDIGIT(c);c=getchar());
    for(;ISDIGIT(c);c=getchar())*n=(*n)*10+c-'0';
}
void putn(int n)
{
    int ns[16]={0,n%10},nd=1;
    while(n/=10)ns[++nd]=n%10;
    while(nd)putchar(ns[nd--]+'0');
}
