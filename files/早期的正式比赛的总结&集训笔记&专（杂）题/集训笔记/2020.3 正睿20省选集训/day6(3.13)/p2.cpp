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
	int n=20,M=100;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<i;++j) buc[f[j]^f[i-j]]++;
		for(int j=0;j<i;++j) buc[f[j]]++;
		for(int j=0;j<=M;++j) if(!buc[j]) { f[i]=j; break; }
		for(int j=1;j<=M;++j) buc[j]=0;
		cout<<i<<':'<<f[i]<<endl;
	}
	return 0;
}
/*
1:1
2:2
3:4
4:3
5:5
6:6
7:8
8:7
9:9
10:10
11:12
12:11
13:13
14:14
15:16
16:15
17:17
18:18
19:20
20:19
*/
