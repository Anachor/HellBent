#include <bits/stdc++.h>
using namespace std;
const int N=510;
vector<int>to[N];
int lnk[N],vis[N],tim=0;
inline void ae(int u,int v){
	to[u].push_back(v);
}
bool dfs(int x){
	if(x==0)return true;
	vis[x]=tim;
	vector<int>::iterator it=to[x].begin(),ti=to[x].end();
	random_shuffle(it,ti);
	for(int u,v;it!=ti;it++){
		u=*it,v=lnk[u];
		if(vis[v]<tim){
			lnk[x]=u,lnk[u]=x,lnk[v]=0;
			if(dfs(v))return true;
			lnk[u]=v,lnk[v]=u,lnk[x]=0;
		}
	}
	return false;
}
int main(){
	int n,e,ans=0;
	scanf("%d%d",&n,&e);
	for(int u,v;e--;scanf("%d%d",&u,&v),ae(u,v),ae(v,u));
	srand(time(0));
	memset(lnk+1,0,n<<2);
	for(int tot=5;tot--;){
		for(int i=1;i<=n;i++){
			if(!lnk[i]){
				tim++,ans+=dfs(i);
			}
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++){
		printf("%d ",lnk[i]);
	}
	putchar('\n');
	return 0;
}

