## loj2538 Slay the Spire

### Sol

将强化牌和攻击牌按照权值从大到小排序。设$w_i$表示第$i$大的攻击牌的权值，$v_i$表示第$i$大的强化牌的权值。

首先，由于$v_i>1$，所以策略一定是尽可能多地出强化牌，等到强化牌都出完了或者已经是最后一张牌的时候才出攻击牌。

设随机选出的$m$张牌中有$L$张是强化牌。

#### Case 1: $L\ge k-1$

对强化牌进行$dp$，设$f_{i,j}$表示从前$i$张强化牌中选出$j$张，所有方案的$\prod v_x$的和。设$ff_{i,j}$表示$f_{i,j}$中那些选了$i$的方案的$\prod v_x$的和。则这一部分对答案的贡献为：

$$
(\sum_{i=1}^n ff_{i,k-1}\cdot{n-i\choose L-(k-1)} ) \cdot (\sum_{i=1}^n w_i \cdot {n-i\choose m-L-1})
$$

#### Case 2: $0 \le L < k-1$

设$h_{i,j}$表示从前$i$张攻击牌中选出$j$张，所有方案的$\sum w_x$的和。设$hh_{i,j}$表示$h_{i,j}$中那些选了$i$的方案的$\sum w_x$的和。则这一部分对答案的贡献为：

$$
(\sum_{i=1}^n hh_{i,k-L}\cdot {n-i\choose m-k})\cdot f_{n,L}
$$

注意特判$k=1$的情况。

时间复杂度$O(n^2)$。

### Code

``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}

const int N=3e3+10,mod=998244353;
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
int w[N],v[N],n,m,q;
int f[N][N],h[N][N],C[N][N];
int ff[N][N],hh[N][N];
int main() {
	for(int i=0;i<=3000;++i) for(int j=0;j<=i;++j) C[i][j]=j?(C[i-1][j]+C[i-1][j-1])%mod:1;
	int T; rd(T);
	while(T--) {
		rd(n),rd(m),rd(q);
		for(int i=1;i<=n;++i) rd(v[i]); sort(v+1,v+n+1,greater<int> ());
		for(int i=1;i<=n;++i) rd(w[i]); sort(w+1,w+n+1,greater<int> ());
		if(q==1) {
			int ans=0;
			for(int i=1;i<=n;++i) {
				int t=0;
				for(int j=0;j<=n-i&&j<=m-1;++j)
					Add(t,C[n-i][j]*(ll)C[n][m-1-j]%mod);
				Add(ans,w[i]*(ll)t%mod);
			}
			printf("%d\n",ans);
			continue;
		}
		int ans=0;
		for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) f[i][j]=h[i][j]=0;
		f[0][0]=1;
		for(int i=0;i<n;++i)
			for(int j=0;j<=m;++j) {
				Add(f[i+1][j],f[i][j]);
				Add(h[i+1][j],h[i][j]);
				if(j<m) {
					ff[i+1][j+1]=f[i][j]*(ll)v[i+1]%mod;
					Add(f[i+1][j+1],ff[i+1][j+1]);
					hh[i+1][j+1]=(h[i][j]+w[i+1]*(ll)C[i][j])%mod;
					Add(h[i+1][j+1],hh[i+1][j+1]);
				}
			}
		for(int L=q-1;L<m;++L) {
			int R=m-L,t1=0,t2=0;
			for(int i=1;i<=n;++i) Add(t1,C[n-i][R-1]*(ll)w[i]%mod);
			for(int i=1;i<=n;++i) Add(t2,ff[i][q-1]*(ll)C[n-i][L-(q-1)]%mod);
			Add(ans,t1*(ll)t2%mod);
		}
		for(int L=0;L<q-1;++L) {
			int R=m-L,x=q-L,t1=0;
			for(int i=1;i<=n;++i)
				Add(t1,hh[i][x]*(ll)C[n-i][R-x]%mod);
			Add(ans,t1*(ll)f[n][L]%mod);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## loj2541 猎人杀

### Sol

可以将问题等价地转化成：有$n$种颜色的球，第$i$种颜色的球有$w_i$个，将这些球随机排列，按照该颜色的位置最靠前的球的位置对颜色进行排名，问颜色$1$排在最后一名的概率。

这也等价于不存在一个$j\not= i$，满足$j$颜色的所有的球都在$i$颜色的第一个球的后面。

枚举$j$构成的进行容斥得到：

$$
Ans = \sum_{S\subset\{1,2,3\cdots n\},1\in S} (-1)^{|S|-1} {(\sum_{i\in S} w_i -1)!\over (w_1-1)!\prod_{j\in S,j\not =1}w_j!} \over {(\sum_{i\in S} w_i)! \over \prod_{i\in S}w_i!}\\
=\sum_{S\subset\{1,2,3\cdots n\},1\in S} (-1)^{|S|-1} {w_1\over \sum_{i\in S} w_i}
$$

只需要对于每一个$V$，求出满足$\sum_{i\in S} w_i = V$的所有$S$的$|S|-1$的和就可以了。构造生成函数$f(x)=\prod_{i=2}^n (1-x^{w_i})$，那么$V$对应的就是$f(x)[x^{V-w_1}]$。

### Code

``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int N=1e5+10,mod=998244353;
const int M=(1<<19)+10;
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
int Pow(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*(ll)x%mod;
		x=x*(ll)x%mod,y>>=1;
	}
	return res;
}
namespace Poly {
	const int N=(1<<19)+10;
	int wn[2][N];
	void getwn(int l) {
		for(int i=1;i<(1<<l);i<<=1) {
			int w0=Pow(3,(mod-1)/(i<<1)),w1=Pow(3,mod-1-(mod-1)/(i<<1));
			wn[0][i]=wn[1][i]=1;
			for(int j=1;j<i;++j) {
				wn[0][i+j]=wn[0][i+j-1]*(ll)w0%mod;
				wn[1][i+j]=wn[1][i+j-1]*(ll)w1%mod;
			}
		}
	}
	int rev[N];
	void getr(int l) { for(int i=0;i<(1<<l);++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<l-1); }
	void FFT(int *A,int len,int f) {
		for(int i=0;i<len;++i) if(rev[i]<i) swap(A[i],A[rev[i]]);
		for(int l=1;l<len;l<<=1)
			for(int i=0,p=l<<1;i<len;i+=p)
				for(int k=0;k<l;++k) {
					ll t1=A[i+k],t2=A[i+l+k]*(ll)wn[f][l+k]%mod;
					A[i+k]=(t1+t2)%mod;
					A[i+l+k]=(t1-t2+mod)%mod;
				}
		if(f==1) {
			int ilen=Pow(len,mod-2);
			for(int i=0;i<len;++i) A[i]=A[i]*(ll)ilen%mod;
		}
	}
	void MUL(int *A,int *B,int *C,int l1,int l2,int l3) {
		static int a[N],b[N],len,cnt;
		len=1,cnt=0; while(len<=l1+l2-2||len<l3) len<<=1,cnt++; getr(cnt);
		for(int i=0;i<len;++i) a[i]=b[i]=0;
		for(int i=0;i<l1;++i) a[i]=A[i];
		for(int i=0;i<l2;++i) b[i]=B[i];
		FFT(a,len,0),FFT(b,len,0);
		for(int i=0;i<len;++i) a[i]=a[i]*(ll)b[i]%mod;
		FFT(a,len,1);
		for(int i=0;i<l3;++i) C[i]=a[i];
	}
	int C[N],D[N],E[N];
	void INV(int *A,int *B,int n) {
		if(n==1) { B[0]=Pow(A[0],mod-2); return ; }
		int l=n+1>>1; INV(A,B,l);
		MUL(B,B,C,l,l,n);
		MUL(A,C,C,n,n,n);
		for(int i=l;i<n;++i) B[i]=0;
		for(int i=0;i<n;++i)
			B[i]=((2ll*B[i]-C[i]+mod)%mod+mod)%mod;
	}
	void DERI(int *A,int n) {
		for(int i=1;i<n;++i) A[i-1]=A[i]*(ll)i%mod;
		A[n-1]=0;
	}
	void INTE(int *A,int n) {
		for(int i=n-1;i>0;--i) A[i]=A[i-1]*(ll)Pow(i,mod-2)%mod;
		A[0]=0;
	}
	void LN(int *A,int *B,int n) {
		for(int i=0;i<n;++i) B[i]=A[i],D[i]=0;
		INV(B,D,n),DERI(B,n),MUL(B,D,B,n,n,n);
		INTE(B,n);
	}
	void EXP(int *A,int *B,int n) {
		if(n==1) { B[0]=1; return; }
		int l=n+1>>1; EXP(A,B,l);
		for(int i=l;i<n;++i) B[i]=0;
		LN(B,E,n);
		for(int i=0;i<n;++i) E[i]=(A[i]-E[i]+mod)%mod;
		E[0]=(E[0]+1+mod)%mod;
		MUL(E,B,B,n,n,n);
	}
}
int w[N],n,m;
int A[M],B[M],w1;
int inv[N];
int main() {
	Poly::getwn(19);
	rd(n),rd(w1),m=w1;
	for(int i=2,x;i<=n;++i) rd(x),w[x]++,m+=x;
	inv[1]=1; for(int i=2;i<=m;++i) inv[i]=(mod-mod/i)*(ll)inv[mod%i]%mod;
	for(int i=1;i<=m;++i) if(w[i])
		for(int j=1;i*j<=m;++j)
			Add(A[i*j],w[i]*(ll)(mod-inv[j])%mod);
	Poly::EXP(A,B,m+1);
	int ans=0;
	for(int i=0;i<=m;++i) ans=(ans+B[i]*(ll)Pow(i+w1,mod-2)%mod)%mod;
	ans=ans*(ll)w1%mod;
	printf("%d",ans);
	return 0;
}
```

---

## loj2540 随机算法

### Sol 1

考虑逐位确定这个排列。

1. 对于已经求出的一个独立集$S$，如果$x$无法加入$S$得到一个更大的独立集，那么显然对于$S$的任意一个超集，$x$也无法加入。
2. 我们在判断一个点是否无法加入的时候只需要关心独立集有哪些点，而不需要关心已经加入到排列中的点有哪些。

设$f[i][s]$为考虑完排列的前$i$个位置，得到的独立集的点集为$s$的方案数。如果下一步往独立集中加入了新的点，直接枚举、判断即可；如果下一步选择的点不能加入独立集，这样的方案数是（$\complement_U s$中不能够加入独立集的点数-（$i-|s|$））。

时间复杂度$O(2^n \cdot n^2)$。

``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int mod=998244353;
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
int Pow(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*(ll)x%mod;
		x=x*(ll)x%mod,y>>=1;
	}
	return res;
}
int f[21][1<<20],n,m;
int sz[1<<20];
int e[21];
int main() {
	rd(n),rd(m);
	for(int i=1,x,y;i<=m;++i) {
		rd(x),rd(y),x--,y--;
		e[x]|=1<<y,e[y]|=1<<x;
	}
	for(int i=1;i<(1<<n);++i) sz[i]=sz[i&(i-1)]+1;
	f[0][0]=1;
	for(int i=0;i<n;++i)
		for(int s=0;s<(1<<n);++s) if(f[i][s]) {
			int cnt=0;
			for(int k=0;k<n;++k) if(!(s>>k&1))
				if(!(e[k]&s)) Add(f[i+1][s|1<<k],f[i][s]);
				else cnt++;
			Add(f[i+1][s],(cnt-(i-sz[s]))*(ll)f[i][s]%mod);
		}
	int mx=0,ans=0;
	for(int i=0;i<(1<<n);++i) if(f[n][i]&&sz[i]>=mx) {
		if(sz[i]>mx) mx=sz[i],ans=0;
		Add(ans,f[n][i]);
	}
	for(int i=1;i<=n;++i) ans=ans*(ll)Pow(i,mod-2)%mod;
	printf("%d",ans);
	return 0;
}
```

### Sol 2

设$f_{S,i}$表示最大独立集以及与最大独立集中的点相邻的点构成的集合为$S$，已经确定了排列中$S$中的数的位置，最大独立集的大小为$i$的方案数。

考虑还没有填数的第一个位置：这个位置上的数一定能加入最大独立集；所有与它有边相邻且不属于$S$的点则可以在它后面的空位任意排列。

设$w_i$表示与$i$相邻的点（包括$i$本身）构成的集合，则转移为
$$
f_{S,i} \times A_{n-|S|-1}^{|w_j\setminus(w_j\cap S)|-1}(j\not\in S) \to f_{S\cup\{w_j\},i+1}
$$

又由于要求的得到最大独立集的期望，所以只有$i$为$S$的最大的独立集大小的状态是有用的。

状态数$O(2^n)$，总复杂度$O(n2^n)$。

``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int mod=998244353;
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
int Pow(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*(ll)x%mod;
		x=x*(ll)x%mod,y>>=1;
	}
	return res;
}
int f[1<<20],mx[1<<20],sz[1<<20];
int e[22],n,m;
int fac[22],inv[22];
void getfac(int n) {
	fac[0]=1; for(int i=1;i<=n;++i) fac[i]=fac[i-1]*(ll)i%mod;
	inv[n]=Pow(fac[n],mod-2); for(int i=n;i>=1;--i) inv[i-1]=inv[i]*(ll)i%mod;
}
inline int A(int n,int m) { return fac[n]*(ll)inv[n-m]%mod; }
void upd(int s,int v,int m) {
	if(m+1>mx[s]) mx[s]=m+1,f[s]=0;
	if(m+1==mx[s]) Add(f[s],v);
}
int main() {
	rd(n),rd(m);
	for(int i=1,x,y;i<=m;++i) {
		rd(x),rd(y),x--,y--;
		e[x]|=1<<y,e[y]|=1<<x;
	}
	getfac(n);
	for(int i=1;i<(1<<n);++i) sz[i]=sz[i&(i-1)]+1;
	f[0]=1;
	for(int s=0;s<(1<<n);++s)
		for(int j=0;j<n;++j) if(!(s>>j&1))
			upd(s|1<<j|e[j],f[s]*(ll)A(n-sz[s]-1,sz[e[j]-(e[j]&s)])%mod,mx[s]);
	int ans=f[(1<<n)-1]*(ll)inv[n]%mod;
	printf("%d",ans);
	return 0;
}
```

### Sol 3

设$w_i$表示与$i$相邻的点构成的集合（包括$i$）。

设$g_S$为$S$集合中的点的最大独立集大小。

设$f_S$表示$S$集合中的点进行随机排列，最后能够得到最大独立集的概率。

考虑枚举排列的第一个点$i\in S$，则与$i$有边相邻的点一定不在最大独立集中：
$$
g_S = \max_{i\in S}\{g_{S\cap \complement w_i} \} + 1\\
f_S = {1\over |S|} \sum_{i\in S,g_{S\cap \complement w_i}+1=g_S} f_{S\cap \complement w_i}
$$

时间复杂度$O(2^n \cdot n)$。

``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int mod=998244353;
inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
int Pow(int x,int y) {
	int res=1;
	while(y) {
		if(y&1) res=res*(ll)x%mod;
		x=x*(ll)x%mod,y>>=1;
	}
	return res;
}
int f[1<<20],mx[1<<20];
int e[22],n,m;
int main() {
	rd(n),rd(m);
	for(int i=1,x,y;i<=m;++i) {
		rd(x),rd(y),x--,y--;
		e[x]|=1<<y,e[y]|=1<<x;
	}
	f[0]=1;
	for(int s=1;s<(1<<n);++s) {
		int sz=0,_mx=0,_f=0;
		for(int i=0;i<n;++i) if(s>>i&1) {
			sz++;
			int to=s&(~(e[i]|1<<i));
			if(mx[to]+1>_mx) _mx=mx[to]+1,_f=0;
			if(mx[to]+1==_mx) Add(_f,f[to]);
		}
		f[s]=_f*(ll)Pow(sz,mod-2)%mod;
		mx[s]=_mx;
	}	
	printf("%d",f[(1<<n)-1]);
	return 0;
}
```
