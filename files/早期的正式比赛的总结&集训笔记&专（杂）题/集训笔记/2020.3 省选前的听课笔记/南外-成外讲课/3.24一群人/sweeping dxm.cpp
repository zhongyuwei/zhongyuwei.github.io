#include<bits/stdc++.h>
using namespace std;

namespace io{
	const int size=1<<22|1;
	char iBuf[size],*iS,*iT,c;
	char oBuf[size],*oS=oBuf,*oT=oBuf+size;
	#define getc() (iS==iT?iT=iBuf+fread(iS=iBuf,1,size,stdin),(iS==iT?EOF:(*iS++)):(*iS++))
	template<class T>void qread(T &x){
		int f=1;
		for(c=getc();c<'0'||c>'9';c=getc())
			if(c=='-')f=-1;
		for(x=0;c>='0'&&c<='9';c=getc())
			x=(x<<3)+(x<<1)+(c&15);
		x*=f;
	}
	void flush(){
		fwrite(oBuf,1,oS-oBuf,stdout);
		oS=oBuf;
	}
	void putc(char x){
		*oS++=x;
		if(oS==oT)flush();
	}
	template<class T>void qwrite(T x){
		static char qu[55];
		char *tmp=qu;
		do *tmp++=(x%10)^'0';while(x/=10);
		while(tmp--!=qu)putc(*tmp);
	}
	struct flusher{
		~flusher(){flush();}
	}_;
}

const int maxn=500005;
const int maxm=1000005;
int n,m,mm,q,rt,cnt;
int x[maxn],y[maxn],rev[maxn],now[maxm+maxn];
int qt[maxm],qx[maxm],qy[maxm],qc[maxm];
pair<int,int>ord[maxn],ans[maxm];
bool del[maxn];
vector<int>ver;

namespace Segtree{
	vector<int>t[maxn*4];
	void build(int cur,int l,int r){
		t[cur].clear();
		if(l==r){
			t[cur].push_back(ord[l].second);
			return;
		}
		int mid=l+r>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		int pt_l=0,pt_r=0;
		while(pt_l<int(t[cur<<1].size())||pt_r<int(t[cur<<1|1].size())){
			if(pt_r==int(t[cur<<1|1].size())||
				(pt_l<int(t[cur<<1].size())&&y[t[cur<<1][pt_l]]>y[t[cur<<1|1][pt_r]]))
				t[cur].push_back(t[cur<<1][pt_l++]);
			else t[cur].push_back(t[cur<<1|1][pt_r++]);
		}
	}
	void query(int cur,int l,int r,int vl,int vr,int vvr,vector<int>&res){
		if(vl>vr)return;
		if(l>=vl&&r<=vr){
			while(!t[cur].empty()&&y[t[cur].back()]<=vvr){
				if(!del[t[cur].back()]){
					res.push_back(t[cur].back());
					del[t[cur].back()]=true;
				}
				t[cur].pop_back();
			}
			return;
		}
		int mid=l+r>>1;
		if(mid>=vl)query(cur<<1,l,mid,vl,vr,vvr,res);
		if(mid<vr)query(cur<<1|1,mid+1,r,vl,vr,vvr,res);
	}
}

namespace Treap{
	int tot;
	class Node{
	public:
		int l,r,par,fix,valx,valy,tagx,tagy;
		void apply(int _tagx,int _tagy){
			valx=max(valx,_tagx);
			tagx=max(tagx,_tagx);
			valy=max(valy,_tagy);
			tagy=max(tagy,_tagy);
		}
	}t[maxn];
	int newnode(int _valx,int _valy){
		tot++;
		t[tot].l=t[tot].r=t[tot].tagx=t[tot].tagy=t[tot].par=0;
		t[tot].fix=rand();
		t[tot].valx=_valx;
		t[tot].valy=_valy;
		return tot;
	}
	void pushdown(int cur){
		if(t[cur].tagx||t[cur].tagy){
			if(t[cur].l)t[t[cur].l].apply(t[cur].tagx,t[cur].tagy);
			if(t[cur].r)t[t[cur].r].apply(t[cur].tagx,t[cur].tagy);
			t[cur].tagx=t[cur].tagy=0;
		}
	}
	void split_x(int cur,int &x,int &y,int val){
		if(cur)pushdown(cur);
		if(!cur)x=y=0;
		else if(t[cur].valx<=val){
			x=cur;
			t[x].par=0;
			split_x(t[cur].r,t[x].r,y,val);
			if(t[x].r)t[t[x].r].par=x;
		}
		else{
			y=cur;
			t[y].par=0;
			split_x(t[cur].l,x,t[y].l,val);
			if(t[y].l)t[t[y].l].par=y;
		}
	}
	void split_y(int cur,int &x,int &y,int val){
		if(cur)pushdown(cur);
		if(!cur)x=y=0;
		else if(t[cur].valy<=val){
			y=cur;
			t[y].par=0;
			split_y(t[cur].l,x,t[y].l,val);
			if(t[y].l)t[t[y].l].par=y;
		}
		else{
			x=cur;
			t[x].par=0;
			split_y(t[cur].r,t[x].r,y,val);
			if(t[x].r)t[t[x].r].par=x;
		}
	}
	void merge(int &cur,int x,int y){
		if(x)pushdown(x);
		if(y)pushdown(y);
		if(!x||!y)cur=x?x:y;
		else if(t[x].fix<t[y].fix){
			cur=x;
			merge(t[cur].r,t[x].r,y);
			if(t[cur].r)t[t[cur].r].par=cur;
		}
		else{
			cur=y;
			merge(t[cur].l,x,t[y].l);
			if(t[cur].l)t[t[cur].l].par=cur;
		}
		t[cur].par=0;
	}
	void insert(int id,int _valx,int _valy){
		int a,b,c; 
		split_x(rt,a,b,_valx);
		split_y(a,a,c,_valy-1);
		merge(rt,a,newnode(_valx,_valy));
		merge(rt,rt,c);
		merge(rt,rt,b);
		rev[id]=tot;
	}
	pair<int,int>calc(int x){
		int resx=t[x].valx,resy=t[x].valy;
		while(x){
			resx=max(resx,t[x].tagx);
			resy=max(resy,t[x].tagy);
			x=t[x].par;
		}
		return make_pair(resx,resy);
	}
}

void solve(int m,int l,int r){
	if(!m||l>r)return;
	Treap::tot=0;
	rt=0;
	for(int i=1;i<=m;i++){
		ord[i]=make_pair(x[i],i);
		del[i]=false;
	}
	sort(ord+1,ord+1+m);
	Segtree::build(1,1,m);
	for(int i=l;i<=r;i++){
		if(qt[i]==4)continue;
		if(qt[i]==1&&!now[qx[i]])continue;
		if(qt[i]==1)
			ans[i]=del[now[qx[i]]]?Treap::calc(rev[now[qx[i]]]):make_pair(x[now[qx[i]]],y[now[qx[i]]]);
		else{
			if(qt[i]==2){
				int a,b;
				Treap::split_y(rt,a,b,qx[i]);
				if(b)Treap::t[b].apply(n-qx[i],0);
				Treap::merge(rt,a,b);
				ver.clear();
				int pos=lower_bound(ord+1,ord+1+m,make_pair(n-qx[i]+1,0))-ord-1;
				Segtree::query(1,1,m,1,pos,qx[i],ver);
				for(int j=0;j<int(ver.size());j++){
					int cx=n-qx[i],cy=y[ver[j]];
					Treap::insert(ver[j],cx,cy);
				}
			}
			else{
				int a,b;
				Treap::split_x(rt,a,b,qx[i]);
				if(a)Treap::t[a].apply(0,n-qx[i]);
				Treap::merge(rt,a,b);
				ver.clear();
				int pos=lower_bound(ord+1,ord+1+m,make_pair(qx[i]+1,0))-ord-1;
				Segtree::query(1,1,m,1,pos,n-qx[i],ver);
				for(int j=0;j<int(ver.size());j++){
					int cx=x[ver[j]],cy=n-qx[i];
					Treap::insert(ver[j],cx,cy);
				}
			}
		}
	}
	for(int i=1;i<=m;i++)if(del[i]){
		pair<int,int>cur=Treap::calc(rev[i]);
		x[i]=cur.first;y[i]=cur.second;
	}
}

void work(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	work(l,mid);
	work(mid+1,r);
	m=0;
	for(int i=l;i<=mid;i++)if(qt[i]==4){
		m++;
		now[qc[i]]=m;
		x[m]=qx[i];
		y[m]=qy[i];
	}
	solve(m,mid+1,r);
	for(int i=l;i<=mid;i++)if(qt[i]==4){
		qx[i]=x[now[qc[i]]];
		qy[i]=y[now[qc[i]]];
		now[qc[i]]=0;
	}
}

int main(){
	freopen("sweeping.in","r",stdin);
	freopen("sweeping.out","w",stdout);
	io::qread(n);io::qread(m);io::qread(q);
	for(int i=1;i<=m;i++){
		io::qread(x[i]);io::qread(y[i]);
		now[i]=i;
	}
	cnt=m;
	for(int i=1;i<=q;i++){
		io::qread(qt[i]);
		io::qread(qx[i]);
		if(qt[i]==4){
			io::qread(qy[i]);
			qc[i]=++cnt; 
		}
	}
	solve(m,1,q);
	for(int i=1;i<=m;i++)now[i]=0; 
	work(1,q);
	for(int i=1;i<=q;i++)if(qt[i]==1){
		io::qwrite(ans[i].first);
		io::putc(' ');
		io::qwrite(ans[i].second);
		io::putc('\n');
	}
	return 0;
}
