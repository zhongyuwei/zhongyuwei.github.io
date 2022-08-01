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
	int n=60,M=100;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=i;++j) if(i%j==0) buc[f[i-j]]++;
		for(int j=0;j<=M;++j) if(!buc[j]) { f[i]=j; break; }
		for(int j=0;j<=M;++j) buc[j]=0;
		cout<<i<<':'<<f[i]<<endl;
	}
	return 0;
}
/*
1:1
2:2
3:1
4:3
5:1
6:2
7:1
8:4
9:1
10:2
11:1
12:3
13:1
14:2
15:1
16:5
17:1
18:2
19:1
20:3
21:1
22:2
23:1
24:4
25:1
26:2
27:1
28:3
29:1
30:2
31:1
32:6
33:1
34:2
35:1
36:3
37:1
38:2
39:1
40:4
41:1
42:2
43:1
44:3
45:1
46:2
47:1
48:5
49:1
50:2
51:1
52:3
53:1
54:2
55:1
56:4
57:1
58:2
59:1
60:3
*/
