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
int gcd(int a,int b) { return b?gcd(b,a%b):a; }
int f[1010],buc[1010];
int main() {
	int n=60,M=100;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=i;++j) if(gcd(i,j)==1) buc[f[i-j]]++;
		for(int j=0;j<=M;++j) if(!buc[j]) { f[i]=j; break; }
		for(int j=0;j<=M;++j) buc[j]=0;
		cout<<i<<':'<<f[i]<<endl;
	}
	return 0;
}
/*
1:1
2:0
3:2
4:0
5:3
6:0
7:4
8:0
9:2
10:0
11:5
12:0
13:6
14:0
15:2
16:0
17:7
18:0
19:8
20:0
21:2
22:0
23:9
24:0
25:3
26:0
27:2
28:0
29:10
30:0
31:11
32:0
33:2
34:0
35:3
36:0
37:12
38:0
39:2
40:0
41:13
42:0
43:14
44:0
45:2
46:0
47:15
48:0
49:4
50:0
51:2
52:0
53:16
54:0
55:3
56:0
57:2
58:0
59:17
60:0
*/
