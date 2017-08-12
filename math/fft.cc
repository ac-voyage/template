#include <cmath>
using namespace std;
namespace fft
{
    #define eps (1e-9)
    template < typename T = double >
    struct dbl
    {
        T x;
        dbl(void):x(0.0){}
        template <typename U>
        dbl(U a):x((T)a){}
        inline char sgn(void){return ((x>=-eps)&&(x<=eps))?(0):((x>eps)?(1):(-1));}
        inline T tabs(void){return ((x>=-eps)&&(x<=eps))?(0.0):((x>eps)?(x):(-x));}
        inline dbl abs(void){return dbl(tabs());}
        template <typename U> inline dbl &operator=(const U b) {x=(T)b;return (*this);}
        inline T *operator&(void) {return &x;}
        inline dbl operator-(void) const {return dbl(-x);}
        inline dbl operator+(const dbl &b) const {return dbl(x+b.x);}
        inline dbl operator-(const dbl &b) const {return dbl(x-b.x);}
        inline dbl operator*(const dbl &b) const {return dbl(x*b.x);}
        inline dbl operator/(const dbl &b) const {return dbl(x/b.x);}
        template <typename U> inline dbl operator^(const U &b) const {T ret=1.0,base=x;while(b){if(b&1)ret*=base;base*=base;b>>=1;}return dbl(ret);}
        inline dbl operator+=(const dbl &b) {return dbl(x+=b.x);}
        inline dbl operator-=(const dbl &b) {return dbl(x-=b.x);}
        inline dbl operator*=(const dbl &b) {return dbl(x*=b.x);}
        inline dbl operator/=(const dbl &b) {return dbl(x/=b.x);}
        template <typename U> inline dbl operator^=(const U &b) {dbl tmp=(*this)^b;*this=tmp;return tmp;}
        inline bool operator==(const dbl &b) const {return (0 == ((*this)-b).sgn());}
        inline bool operator!=(const dbl &b) const {return (0 != ((*this)-b).sgn());}
        inline bool operator<(const dbl &b) const {return (-1 == ((*this)-b).sgn());}
        inline bool operator<=(const dbl &b) const {return (((*this)==b) || ((*this)<b));}
        inline bool operator>(const dbl &b) const {return (b < (*this));}
        inline bool operator>=(const dbl &b) const {return (((*this)==b) || ((*this)>b));}
        template <typename U> inline operator U() const {return (U)x;}
        inline char operator[](unsigned n) {if(n >= 0){long long int ret=x;while(n--){ret/=10;}return (ret%10);}else{T ret=x;n=-n;while(n--)ret*=10.0;return ((long long int)ret)%10;}}
    };
    template <typename T>
    struct Complex
    {
        T x,y;  /* x + iy */
        Complex(void):x(T()),y(T()){}
        Complex(T xx):x(xx){}
        Complex(T xx,T yy):x(xx),y(yy){}
        inline Complex operator-(void) const {return Complex(-x,-y);}
        inline Complex operator+(const Complex& b) const {return Complex(x+b.x,y+b.y);}
        inline Complex operator-(const Complex& b) const {return Complex(x-b.x,y-b.y);}
        inline Complex operator*(const Complex& b) const {return Complex(x*b.x-y*b.y,x*b.y+y*b.x);}
        inline Complex operator/(const Complex& b) const {T bo=b.x*b.x+b.y*b.y;return Complex((x*b.x+y*b.y)/bo,(y*b.x-x*b.y)/bo);}
        inline Complex& operator+=(const Complex& b) {Complex tmp=(*this)+b;(*this)=tmp;return (*this);}
        inline Complex& operator-=(const Complex& b) {Complex tmp=(*this)-b;(*this)=tmp;return (*this);}
        inline Complex& operator*=(const Complex& b) {Complex tmp=(*this)*b;(*this)=tmp;return (*this);}
        inline Complex& operator/=(const Complex& b) {Complex tmp=(*this)/b;(*this)=tmp;return (*this);}
        inline friend Complex operator+(const T& a, const Complex& b) {return Complex(a)+b;}
        inline friend Complex operator-(const T& a, const Complex& b) {return Complex(a)-b;}
        inline friend Complex operator*(const T& a, const Complex& b) {return Complex(a)*b;}
        inline friend Complex operator/(const T& a, const Complex& b) {return Complex(a)/b;}
    };
    typedef dbl<> Double;
    typedef Complex<Double> ComplexD;
    typedef long long int ll;
    const int maxn = 2000000; /* !! */
    const Double pi(acos(-1.0));

    void build(ComplexD _P[], ComplexD P[], int n, int m, int curr, int &cnt)
    {
        if(m == n) {
            _P[curr] = P[cnt++];
        } else {
            build(_P, P, n, m*2, curr, cnt);
            build(_P, P, n, m*2, curr+m, cnt);
        }
    }

    void FFT(ComplexD P[], int n, int oper) /* n should be 2^k. */
    {
        static ComplexD _P[maxn];
        int cnt = 0;
        build(_P, P, n, 1, 0, cnt);
        copy(_P, _P+n, P);
        for(int d = 0;(1<<d)<n;++d)
        {
            int m = 1<<d;
            int m2 = m*2;
            Double p0 = pi / m * oper;
            ComplexD unit_p0(cos(p0.x), sin(p0.x));
            for(int i = 0;i < n;i += m2)
            {
                ComplexD unit(1,0);
                for(int j = 0;j < m;++j)
                {
                    ComplexD &P1 = P[i+j+m], &P2 = P[i+j];
                    ComplexD t = unit * P1;
                    P1 = P2 - t;
                    P2 = P2 + t;
                    unit *= unit_p0;
                }
            }
        }
        if(-1 == oper)
        {
            for(int i = 0;i < n;++i)
                P[i] /= Double(n);
        }
    }
}
