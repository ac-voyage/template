
typedef long long int ll;
template <class T, int maxn, ll mod> /* template <class T=int/ll, int maxn, ll mod> */
struct mat
{
    int N;
    T a[maxn][maxn];    /* 1-based. */
    mat(void):N(0){}
    mat(int n, int v = 0)
    {
        N = n;
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                a[i][j] = 0;
        for(int i = 1;i <= N;++i)
            a[i][i] = v;
    }
    mat operator-(void) const
    {
        mat ret(N);
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                ret.a[i][j] = (mod-a[i][j])%mod;
        return ret;
    }
    mat operator+(const mat &b) const
    {
        mat ret(N);
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                ret.a[i][j] = (a[i][j] + b.a[i][j])%mod;
        return ret;
    }
    mat operator-(const mat &b) const
    {
        mat ret(N);
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                ret.a[i][j] = (a[i][j] - b.a[i][j] + mod) % mod;
        return ret;
    }
    mat operator*(const mat &b) const
    {
        mat ret(N);
        for(int i = 1;i <= N;++i)
            for(int j = 1;j <= N;++j)
                for(int k = 1;k <= N;++k)
                {
                    /* T t = (a[i][k] * b.a[k][j]) % mod; // delete %mod if get TLE. */
                    ret.a[i][j] = (ret.a[i][j] + a[i][k] * b.a[k][j]) % mod; /* seprate this line if get WA. */
                }
        return ret;
    }
    mat operator^(long long int p) const
    {
        mat ret(N,1);
        mat base = (*this);
        while(p)
        {
            if(p & 1) ret = ret * base;
            base = base * base;
            p >>= 1;
        }
        return ret;
    }
};
