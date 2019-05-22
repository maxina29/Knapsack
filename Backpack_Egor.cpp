#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<string>
#include<set>
#include <fstream>
using namespace std;
struct Vesh{
	int P;
	int W;
	double K;
	int nomer; //P - value of items, W - weight of items, K - koefficient
};


int main()
{
	ifstream fin("./data/ks_100_0");
	int N,C,i,j,f=1,balast,N1,acost,kol,kol1,f1; //N - Number of items, C - Capasity of backpack, i,j - counter, f - flag, balast - checking for "bad" items, N1 - new N, acost - cost of the item
	fin>>N>>C;
	N1=N;
	Vesh V[N],Q;
	j=0;
	for(i=0;i<N;i++) // inserting and koefficienting
	{
		fin>>acost>>balast;
		if(balast>C)
			N1--;
		else
		{
			V[j].nomer=i;
			V[j].W=balast;
			V[j].P=acost;
			V[j].K=double(V[j].P)/double(V[j].W);
			j++;
		}
	}
	N=N1;
	vector <double> KK(N);
	for(i=0;i<N;i++)
	{
		KK[i]=V[i].P;
		//KK[i]=double(V[i].P)/double(V[i].W);
	}
	sort(KK.begin(),KK.end(),std::greater<double>()); // sorting
	int zn=0,cn=C; //z - value of the best sollution, zn - z but now, cn - capasity left, U - upper bound
	double U=0,z=0;
	bool X[N]={},XX[N]={}; // X - items taken now, XX - the best solution
	for(i=0;i<N;i++) // sorting the origin
	{
		for(j=0;j<N;j++)
		{
			if(V[j].P==KK[i] && X[i]==0)
			{
				Q=V[j];
				V[j]=V[i];
				V[i]=Q;
				X[i]=1;
				break;
			}
		}
	}
	for(i=0;i<N;i++)
	{
		X[i]=0;
		//cout<<V[i].nomer+1<<" "<<V[i].W<<" "<<V[i].P<<"\n";
	}
	i=0;
	U=0;
	while(1) // the algoritm itself
	{
		while(i!=N) // move forward
		{
			/*for(j=0;j<N;j++)
			{
				cout<<X[j];
			}
			cout<<"\n";*/
			kol=0;
			f1=0;
			for(j=i;j<N;j++)
			{
				kol=kol+V[j].W;
				if(kol>cn)
				{
					f1=1;
					kol=j;
					break;
				}
			}
			if(f1==1)
			{
				kol1=0;
			for(j=i;j<kol;j++)
			{
				kol1=kol1+V[j].P-V[j].W*V[kol].K;
			}
			kol1=kol1+cn*V[kol].K;
			}
			if(cn-V[i].W<0 || (U+kol1)<=z)
				break;
			else
			{
				X[i]=1;
				cn=cn-V[i].W;
				zn=zn+V[i].P;
				U=U+V[i].P;
			}
			i++;
		}
			if(X[13]==1 && X[12]==1 && X[7]==1 && X[5]==1 && X[2]==1)
				cout<<"FOUND IT!!!";
		if(zn>z) // checking for the best
		{
			z=0;
			for(j=0;j<N;j++)
			{
				XX[j]=X[j];
				if(X[j]==1)
				{
					z=z+V[j].P;
				}
			}
		}
		f=-1;
		for(j=0;j<i;j++) //moving backwards
		{
			if(X[j]==1)
			{
				f=j;
			}
		}
		if(f==-1)
			break;
		else
		{
			X[f]=0;
			zn=zn-V[f].P;
			cn=cn+V[f].W;
			U=U-V[f].P;
			i=f+1;
		}
	}
	// giving the result
	cout<<"COST: ";
	printf("%.0f",z);
	cout<<"\n"<<"ITEMS:"<<"\n";
	C=0;
	for(i=0;i<N;i++)
	{
		if(XX[i]==1)
		{
			C=C+V[i].W;
			cout<<V[i].nomer+1<<" "<<V[i].W<<" "<<V[i].P<<"\n";
		}
	}
	cout<<"WEIGHT OF BACKPACK: "<<C<<"\n";
}
