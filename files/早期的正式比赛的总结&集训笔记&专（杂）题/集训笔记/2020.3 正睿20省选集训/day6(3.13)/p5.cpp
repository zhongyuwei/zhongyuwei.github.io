#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
int f[1010],buc[1010];
int main() {
	int n=200,M=100;
	f[0]=f[1]=0;
	for(int i=2;i<=n;++i) {
		for(int j=1;j<i;++j) buc[f[j-1]^f[i-1-j]]++;
		for(int j=0;j<=M;++j) if(!buc[j]) { f[i]=j; break; }
		for(int j=0;j<=M;++j) buc[j]=0;
		cout<<f[i]<<' ';
	}
	return 0;
}
/*
1 1 2 0 3 1 1 0 3 3 2 2 4 0 5 2 2 3 3 0 1 1 3 0 2 1 1 0 4 5 2 7 4 0 1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 2 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8 1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8 1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8 1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4 5 3 7 4 8 1 1 2 0 3 1 1 0 3 3 2 2 4 4 5 5 9 3 3 0 1 1 3 0 2 1 1 0 4
*/
