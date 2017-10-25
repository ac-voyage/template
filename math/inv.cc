#include <bits/stdc++.h>
using namespace std;

const int n=10000000;      /*  */
const long long mod=1e9+7;  /*　prime required. */

long long fact[n],fiv[n],inv[n];

int main(){
    fact[0]=fact[1]=1;
    fiv[0]=fiv[1]=1;
    inv[1]=1;
    for (int i=2;i<n;i++){
        fact[i]=fact[i-1]*i%mod;
        inv[i]=(mod-mod/i)*inv[mod%i]%mod;
        fiv[i]=inv[i]*fiv[i-1]%mod;
    }
    for (int i=1;i<n;i++){
        if (fact[i]*fiv[i]%mod!=1)  printf("fact wrong: %d\n",i);
        if (inv[i]*i%mod!=1)        printf("intv wrong: %d\n",i);
    }
    cout<<"complete"<<endl;
    return 0;
}
