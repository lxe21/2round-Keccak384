#ifndef __EQU__ 
#define __EQU__
#include"SHA3.h"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int MaxEQU=1600;
struct EQU
{	ull E[1600][26],e[26];
	int te[MaxEQU+5],lte;
	int freedom,Free[1600];
	ull r[1600][25];
	int add_equ()
	{	for(int i=0;i<25;i++)
			for(int j=0;j<64;j++)if(e[i]&(1ull<<j))
			{	if(E[i*64+j][i]&(1ull<<j))
				{	for(int k=0;k<26;k++)
						e[k]^=E[i*64+j][k];
				}
				else
				{	for(int k=0;k<26;k++)
						E[i*64+j][k]^=e[k];
					te[lte++]=i*64+j;
					assert(lte<=MaxEQU);
					memset(e,0,sizeof(e));
					return i*64+j+1;
				}
			}
		if(e[25]==0)return -1;
		memset(e,0,sizeof(e));
		return 0;
	}
	void clear()
	{	memset(E,0,sizeof(E));
		memset(e,0,sizeof(e));
		memset(te,0,sizeof(te));
		lte=0;
		freedom=0;
		memset(Free,0,sizeof(Free));
		memset(r,0,sizeof(r));
	}
	void clean()
	{	memset(e,0,sizeof(e));
	}
	void add(int x)
	{	assert(x>=-1&&x<1600);
		if(x==-1)e[25]^=1;
		else e[x/64]^=1ull<<x%64;
	}
	void add(ull*x)
	{	for(int i=0;i<26;i++)e[i]^=x[i];
	}
	void undo()
	{	for(int tt=0;tt<lte;tt++)
			memset(E[te[tt]],0,sizeof(E[te[tt]]));
		lte=0;
	}
	void commit()
	{	lte=0;
	}
	int solve(int*u,int all_zero=0)
	{	freedom=0;
		for(int i=1599;i>=0;i--)
			if(E[i][i/64]&(1ull<<i%64))
			{	u[i]=E[i][25];
				for(int j=1599;j>i;j--)
					if(E[i][j/64]&(1ull<<j%64))
						u[i]^=u[j];
			}
			else u[i]=(all_zero?0:(rand()%2)),Free[freedom++]=i;
		return freedom;
	}
	void init_sol(ull*u)
	{	for(int i=0;i<1600;i++)if(E[i][i/64]&(1ull<<i%64))
			for(int j=0;j<i;j++)if(E[j][i/64]&(1ull<<i%64))
				for(int k=0;k<26;k++)E[j][k]^=E[i][k];
		int _u[1600],inv[1600];
		freedom=solve(_u,1);
		assert(freedom<60);
		for(int i=0;i<25;i++)u[i]=0;
		for(int i=0;i<1600;i++)
			if(_u[i])u[i/64]^=1ull<<i%64;
		memset(inv,0,sizeof(inv));
		for(int i=0;i<1600;i++)
			for(int j=0;j<freedom;j++)
			{	if(E[i][Free[j]/64]&(1ull<<Free[j]%64))
					inv[i]|=1ull<<freedom-1-j;
				if(i==Free[j])
				{	inv[i]=1ull<<freedom-1-j;
					continue;
				}
			}
		memset(r,0,sizeof(r));
		for(int i=0;i<freedom;i++)
		{	for(int j=0;j<1600;j++)
				if(inv[j]&(1ull<<i))
					r[i][j/64]^=1ull<<j%64;
		}	
		for(int i=1;i<freedom;i++)
			for(int j=0;j<25;j++)
				r[i][j]^=r[i-1][j];
	}
	void next_sol(ull*u,ull k)
	{	if(k==0)return;
		int l=0;
		for(ull tmp=k&-k;tmp>1;tmp>>=1)l++;
		for(int j=0;j<25;j++)
			u[j]^=r[l][j];
	}
};
const int B=2048;
int trans(int x,int y,int z){return y*320+x*64+z;}
struct Fe
{	ull a;
	Fe(){a=0;}
	Fe(ull x){a=x;}
};
Fe operator*(Fe x,Fe y)
{	int c[19],lc=0;
	for(;x.a;x.a/=B)c[lc++]=x.a%B;
	for(;y.a;y.a/=B)c[lc++]=y.a%B;
	c[lc++]=0;
	sort(c,c+lc);
	lc=unique(c,c+lc)-c;
	assert(lc<=5);
	Fe res;
	for(int i=1;i<lc;i++)res.a=res.a*B+c[i];
	return res;
}
bool operator==(Fe x,Fe y)
{	return x.a==y.a;
}
bool operator<(Fe x,Fe y)
{	return x.a<y.a;
}
typedef set<Fe>::iterator iter;
struct F
{	set<Fe>c;
	F(){c.clear();}
	void clear()
	{	c.clear();
	}
	void add(Fe y)
	{	if(c.find(y)!=c.end())c.erase(y);
		else c.insert(y);
	}
	void add(F y,int deep=1)
	{	if(!deep)if(c.size()<y.c.size())swap(c,y.c);
		for(iter it=y.c.begin();it!=y.c.end();it++)add(*it);
	}
};
F a[1600],b[1600];
void F_Chi()
{	for(int i=0;i<1600;i++)
	{	int x=i/64%5,y=i/320,z=i%64,u=trans((x+1)%5,y,z),v=trans((x+2)%5,y,z);
		b[i].clear();
		b[i].add(a[i]);
		b[i].add(a[v]);
		for(iter it1=a[u].c.begin();it1!=a[u].c.end();it1++)
			for(iter it2=a[v].c.begin();it2!=a[v].c.end();it2++)
				b[i].add((*it1)*(*it2));
	}
	for(int i=0;i<1600;i++)swap(a[i],b[i]);
}
void F_L()
{	for(int i=0;i<1600;i++)
	{	int x=i/64%5,z=i%64;
		b[i].clear();
		b[i].add(a[i]);
		for(int y=0;y<5;y++)
		{	b[i].add(a[trans((x-1+5)%5,y,z)]);
			b[i].add(a[trans((x+1+5)%5,y,(z-1+64)%64)]);
		}
	}
	for(int i=0;i<1600;i++)swap(a[i],b[i]);
	for(int i=0;i<1600;i++)
	{	b[rho[i]].clear();
		b[rho[i]].add(a[i]);
	}
	for(int i=0;i<1600;i++)swap(a[i],b[i]);
	for(int i=0;i<1600;i++)
	{	b[pi[i]].clear();
		b[pi[i]].add(a[i]);
	}
	for(int i=0;i<1600;i++)swap(a[i],b[i]);
}
void F_Iota(int ir)
{	for(int i=0;i<64;i++)
		if(rc[ir]&(1ull<<i))
			a[i].add(Fe(0));
}
#endif
