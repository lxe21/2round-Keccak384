//-Wl,-stack=134217728
#include<bits/stdc++.h>
#include"SHA3.h"
#include"EQU.h"
using namespace std;
int rh[384];
EQU E,E2;
int rM[1600];
int cs[320];
void scs(int flg=0)
{	for(int x=0;x<5;x++)for(int z=0;z<64;z++)
	{	int c[1678],d[1678],ld;
		memset(c,0,sizeof(c));
		for(int y=0;y<5;y++)
		{	int i=trans(x,y,z);
			for(iter it=a[i].c.begin();it!=a[i].c.end();it++)
				c[(*it).a]^=1;
		}
		for(int i=0;i<=1600;i++)if(c[i])E.add(i-1);
		if(flg==2)
		{	if(cs[x*64+z])c[0]^=1,E.add(-1);
			E.add_equ();
		}
		for(int i=1600;i>=0;i--)if(c[i])
		{	ld=0;
			for(int j=0;j<i;j++)if(c[j])d[ld++]=j;
			for(int j=0;j<1600;j++)if(a[j].c.count(Fe(i)))
			{	a[j].c.erase(Fe(i));
				for(int k=0;k<ld;k++)a[j].add(Fe(d[k]));
			}
			i=-1;
		}
	}
}
int Flg=0;
void __F_Chi()
{	for(int i=0;i<1600;i++)
	{	int x=i/64%5,y=i/320,z=i%64,u=trans((x+1)%5,y,z),v=trans((x+2)%5,y,z);
		b[i].clear();
		b[i].add(a[i]);
		b[i].add(a[v]);
		bool flg=1;
		for(iter it1=a[u].c.begin();it1!=a[u].c.end();it1++)if(flg)
			for(iter it2=a[v].c.begin();it2!=a[v].c.end();it2++)if(flg)
			{	if((*it1).a==0||(*it2).a==0)
					b[i].add((*it1)*(*it2));
				else b[i].clear(),b[i].add(a[i]),flg=0;
			}
	}
	for(int i=0;i<1600;i++)swap(a[i],b[i]);
}
void gr()
{	ull M1[1600][26];
	ull M2[1600][26];
	ull M3[1600][6];
	ull M4[1600][6];
	ull M5[1600][6];
	E.clear();
	for(int i=0;i<1600;i++)a[i].clear(),b[i].clear();
	int th[1600];
	memcpy(th,rh,sizeof(rh));
	__Iota(th,1,-1);
	__Chi(th,-1);
	int varxy[8]={0,2,3,5,7,8,10,12};
	for(int v=0;v<8;v++)
		for(int i=0;i<64;i++)
		{	int x=varxy[v]%5,y=varxy[v]/5,z=i;
			a[trans(x,y,z)].add(Fe(trans(x,y,z)+1));
		}
	for(int i=0;i<64;i++)
	{	int x=1,y=1,Y=2,z=i;
		a[trans(x,y,z)].add(Fe(0)),E.add(-1);
		E.add(trans(x,y,z)),E.add_equ();
		a[trans(x,Y,z)].add(Fe(0)),E.add(-1);
		E.add(trans(x,Y,z)),E.add_equ();
	}
	int c0xy[13]={1,13,14,15,16,17,18,19,20,21,22,23,24};
	for(int c=0;c<13;c++)
		for(int i=0;i<64;i++)
		{	int x=c0xy[c]%5,y=c0xy[c]/5,z=i;
			E.add(trans(x,y,z)),E.add_equ();
		}
	int c1xy[2]={4,9};
	for(int c=0;c<2;c++)
		for(int i=0;i<64;i++)
		{	int x=c1xy[c]%5,y=c1xy[c]/5,z=i;
			a[trans(x,y,z)].add(Fe(0)),E.add(-1);
			E.add(trans(x,y,z)),E.add_equ();
		}
	memset(cs,0,sizeof(cs));
	EQU tE;
	tE.clear();
	for(int x=0;x<5;x++)
		for(int z=0;z<64;z++)
		{	if(x==4)
			{	tE.add(trans(x,0,z));
				tE.add_equ();
				tE.add(trans((x-1+5)%5,0,z));
				tE.add(trans((x+1)%5,0,(z-1+64)%64));
				tE.add(-1);
				tE.add_equ();
			}
			else if(x==1)
			{	tE.add(trans(x,0,z));
				tE.add_equ();
				int X=x+1;
				int z1=inv_rho[inv_pi[trans(4,4,z)]]%64;
				int z2=inv_rho[inv_pi[trans(4,1,z)]]%64;
				tE.add(trans((x-1+5)%5,0,z1));
				tE.add(trans((x+1)%5,0,(z1-1+64)%64));
				tE.add(trans((X-1+5)%5,0,z2));
				tE.add(trans((X+1)%5,0,(z2-1+64)%64));
				if(th[pi[rho[trans(4,4,z)]]]^1==1)
					tE.add(-1);
				tE.add_equ();
			}
			else if(x==2)
			{	int X=x+1;
				int z1=inv_rho[inv_pi[trans(3,3,z)]]%64;
				int z2=inv_rho[inv_pi[trans(3,0,z)]]%64;
				tE.add(trans((x-1+5)%5,0,z1));
				tE.add(trans((x+1)%5,0,(z1-1+64)%64));
				tE.add(trans((X-1+5)%5,0,z2));
				tE.add(trans((X+1)%5,0,(z2-1+64)%64));
				if(th[pi[rho[trans(3,3,z)]]]^
				   th[pi[rho[trans(3,0,z)]]]==1)
					tE.add(-1);
				tE.add_equ();
			}
		}
	tE.solve(cs);
	scs(2);
	E.commit();
	F_L();
	memset(M1,0,sizeof(M1));
	for(int i=0;i<1600;i++)
		for(iter it=a[i].c.begin();it!=a[i].c.end();it++)
			if((*it).a==0)M1[i][25]^=1;
			else M1[i][((*it).a-1)/64]^=1ull<<((*it).a-1)%64;
	__F_Chi();
	F_Iota(0);
	memset(M2,0,sizeof(M2));
	for(int i=0;i<1600;i++)
		for(iter it=a[i].c.begin();it!=a[i].c.end();it++)
			if((*it).a==0)M2[i][25]^=1;
			else M2[i][((*it).a-1)/64]^=1ull<<((*it).a-1)%64;
	int sE[1600][5];
	memset(sE,0,sizeof(sE));
	for(int i=0;i<1600;i++)
		for(int j=0;j<=1600;j++)
			if(E.E[i][j/64]&(1ull<<j%64))
				sE[i][++sE[i][0]]=j;
	memset(M3,0,sizeof(M3));
	memset(M4,0,sizeof(M4));
	memset(M5,0,sizeof(M5));
	int mu[1605],me[1600],lm=0,ime[1605];
	memset(mu,0,sizeof(mu));
	memset(ime,0,sizeof(ime));
	for(int i=0;i<1600;i++)
		if(E.E[i][i/64]&(1ull<<i%64))
			mu[i]=1;
	for(int i=0;i<1600;i++)if(!mu[i])me[lm]=i,ime[i]=lm,lm++;
	ime[1600]=320;
	for(int i=0;i<1600;i++)
	{	for(int j=0;j<1600;j++)
		{	if(M1[i][j/64]&(1ull<<j%64))
			{	if(mu[j]==0)M3[i][ime[j]/64]^=1ull<<ime[j]%64;
				else for(int k=j+1;k<=1600;k++)
					if(E.E[j][k/64]&(1ull<<k%64))
						M3[i][ime[k]/64]^=1ull<<ime[k]%64;
			}
			if(M2[i][j/64]&(1ull<<j%64))
			{	if(mu[j]==0)M4[i][ime[j]/64]^=1ull<<ime[j]%64;
				else for(int k=j+1;k<=1600;k++)
					if(E.E[j][k/64]&(1ull<<k%64))
						M4[i][ime[k]/64]^=1ull<<ime[k]%64;
			}
		}
		if(M1[i][25])M3[i][5]^=1;
		if(M2[i][25])M4[i][5]^=1;
	}
	int tr=-2;
	int ttc=0,mttc=0;
	int sta[100],ls=0;memset(sta,0,sizeof(sta));
	for(ull tc=40060000;;tc++)
	{	Flg=0;
		ull E2[321][6];int le2=0;
		memset(E2,0,sizeof(E2));
		E2[320][5]=1;
		memcpy(M5,M4,sizeof(M5));
		for(int z=0;z<64;z++)if(tc&(1ull<<z))
		{	M3[trans(1,1,z)][5]^=1;
			M3[trans(1,2,z)][5]^=1;
			int z1=pi[rho[trans(1,1,z)]]%64;
			int z2=pi[rho[trans(1,2,z)]]%64;
			for(int i=0;i<=5;i++)M5[trans(0,0,z1)][i]^=M3[trans(2,0,z1)][i];
			M5[trans(1,0,z1)][5]^=1;
			for(int i=0;i<=5;i++)M5[trans(4,0,z1)][i]^=M3[trans(0,0,z1)][i];
			M5[trans(4,0,z1)][5]^=1;
			for(int i=0;i<=5;i++)M5[trans(0,3,z2)][i]^=M3[trans(1,3,z2)][i];
			M5[trans(0,3,z2)][5]^=1;
			for(int i=0;i<=5;i++)M5[trans(1,3,z2)][i]^=M3[trans(3,3,z2)][i];
			M5[trans(2,3,z2)][5]^=1;
		}
		for(int i=0;i<320;i++)
		{	int tmp=inv_rho[inv_pi[i]];
			int x=tmp/64%5,y=tmp/320,z=tmp%64;
			for(int j=0;j<=5;j++)E2[le2][j]^=M5[trans(x,y,z)][j];
			for(int j=0;j<5;j++)
				for(int k=0;k<=5;k++)
					E2[le2][k]^=M5[trans((x-1+5)%5,j,z)][k],E2[le2][k]^=M5[trans((x+1)%5,j,(z-1+64)%64)][k];
			if(th[i])E2[le2][5]^=1;
			le2++;
		}
		int fr[320],lf=0;
		for(int i=0;i<320;i++)
		{	int mxp=-1;
			for(int j=i;j<320;j++)
				if(E2[j][i/64]&(1ull<<i%64))
					mxp=j,j=320;
			if(mxp==-1)
			{	if(E2[i][5]==1)Flg=1,i=320;
				fr[lf++]=i;
				continue;
			}
			for(int j=0;j<=5;j++)swap(E2[i][j],E2[mxp][j]);
			for(int j=0;j<320;j++)if(j!=i)if(E2[j][i/64]&(1ull<<i%64))
				for(int k=0;k<=5;k++)E2[j][k]^=E2[i][k];
		}
		if(Flg){Flg=0;continue;}
		ull res[25],tmp[25];
		memset(tmp,0,sizeof(tmp));
		for(int i=0;i<320;i++)if(E2[i][5])tmp[me[i]/64]^=1ull<<me[i]%64;
		for(int i=0;i<1600;i++)if(mu[i])
		{	for(int j=2;j<=sE[i][0];j++)
				if(E2[ime[sE[i][j]]][5])
					tmp[i/64]^=1ull<<i%64;
			if((i/64==6||i/64==11)&&(tc&(1ull<<(i%64))))tmp[i/64]^=1ull<<i%64;
		}
		int mr=-2;
		ull t=0;
		int tM[1600];
		memset(tM,0,sizeof(tM));
		memset(res,0,sizeof(res));
		for(int i=0;i<25;i++)res[i]^=tmp[i];
		for(int i=0;i<1600;i++)tM[i]=(res[i/64]&(1ull<<i%64))>0;
		int c1=0;
		for(int i=0;i<2;i++)
		{	__L(res);
			__Chi(res);
			__Iota(res,i);
			if(i==0)for(int z=0;z<64;z++)if(res[24]&(1ull<<z))c1++;
		}
		int cr=0;
		for(int i=0;i<384;i++)
			if(((res[i/64]&(1ull<<i%64))>0)==rh[i])
				cr++;
		mttc=max(mttc,c1);
		ls++,sta[c1]++;
		if(cr>mr)
		{	mr=cr;
			for(int i=0;i<1600;i++)
				rM[i]=tM[i];
		}
		if(mr>tr)ttc=c1;
		tr=max(tr,mr);
		if(mr==384)return;
	}
	return;
}
void op(int*x,int k=1600)
{	for(int i=0;i<k/64;i++)
	{	for(int j=60;j>=0;j-=4)
		{	int c=0;
			for(int k=3;k>=0;k--)
				c=c*2+x[i*64+j+k];
			printf("%c",c>9?c-10+'a':c+'0');
		}
		if(i%5==4)printf("\n");
		else printf(" ");
	}
	printf("\n");
}
int main()
{   E.clear();
	memset(rh,0,sizeof(rh));
	gr();
	freopen("res.txt","w",stdout);
	op(rM);
	return 0;
}
