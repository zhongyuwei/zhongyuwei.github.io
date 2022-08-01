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

int f[110][110];
int n,m;
char s1[110],s2[110];
int main() {
	scanf("%s",s1+1),n=strlen(s1+1);
	scanf("%s",s2+1),m=strlen(s2+1);
	for(int i=1;i<=n;++i) f[i][0]=s1[i]-'0';
	for(int i=1;i<=m;++i) f[0][i]=s2[i]-'0';
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			f[i][j]=!(f[i-1][j]&f[i][j-1]);
	for(int i=n;i>=1;--i,puts("")) {
		cout<<s1[i]<<':';
		for(int j=1;j<=m;++j) cout<<f[i][j]<<' ';
	}
	cout<<"  ";
	for(int i=1;i<=m;++i) cout<<s2[i]<<' ';
	return 0;
}
