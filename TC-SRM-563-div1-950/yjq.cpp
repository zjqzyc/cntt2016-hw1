#include<bits/stdc++.h>
#define MOD 1000000009
using namespace std;int n,m;const int MAXN=50;int mp[MAXN][MAXN];const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};struct Info{int i,j,u,v;Info(int _i=0,int _j=0,int _u=0,int _v=0){i=_i,j=_j,u=_u,v=_v;}};bool vis[MAXN][MAXN];int col[MAXN][MAXN][MAXN][MAXN];int pw[MAXN*MAXN];int get(int x){return(pw[x]+MOD-x-1)%MOD;}bool exists=0;bool In(int i,int j){return i>=0&&i<n&&j>=0&&j<m;}int Dfs(int i,int j){if(!In(i,j)||!mp[i][j]||vis[i][j])return 0;vis[i][j]=true;int sz=1;for(int u=0;u<n;u++){for(int v=0;v<m;v++){if(col[i][j][u][v]==1)sz+=Dfs(u,v);}}return sz;}void Push(queue<Info>&que,int i,int j,int u,int v){if(col[i][j][u][v]!=2){col[i][j][u][v]=2;que.push(Info(i,j,u,v));}}void Color(int i,int j,int u,int v){queue<Info>que;Push(que,i,j,u,v);while(!que.empty()){Info cur=que.front();que.pop();i=cur.i,j=cur.j,u=cur.u,v=cur.v;for(int d=0;d<4;d++){int ni=i+dx[d],nj=j+dy[d],nu=u+dx[d],nv=v+dy[d];if(In(ni,nj)&&!mp[ni][nj]){nu=u-dx[d],nv=v-dy[d];if(In(nu,nv)&&mp[nu][nv])Push(que,i,j,nu,nv);nu=u+dx[d],nv=v+dy[d];}if(In(nu,nv)&&!mp[nu][nv]){ni=i-dx[d],nj=j-dy[d];if(In(ni,nj)&&mp[ni][nj])Push(que,ni,nj,u,v);ni=i+dx[d],nj=j+dy[d];}if(In(ni,nj)&&In(nu,nv)&&mp[ni][nj]&&mp[nu][nv])Push(que,ni,nj,nu,nv);}}}class CoinsGame{public:int ways(vector<string>board){n=board.size(),m=board[0].size();int cnt=0;for(int i=0;i<n;i++){for(int j=0;j<m;j++)cnt+=mp[i][j]=board[i][j]=='.';}pw[0]=1;for(int i=1;i<=cnt;i++)pw[i]=pw[i-1]*2%MOD;for(int i=0;i<n;i++)for(int j=0;j<m;j++)for(int u=0;u<n;u++)for(int v=0;v<m;v++)col[i][j][u][v]=mp[i][j]&&mp[u][v];for(int i=0;i<n;i++)for(int j=0;j<m;j++)for(int u=0;u<n;u++)for(int v=0;v<m;v++){bool flag=0;for(int d=0;d<4;d++){int ni=i+dx[d],nj=j+dy[d],nu=u+dx[d],nv=v+dy[d];if(In(ni,nj)^In(nu,nv))flag=1;}if(mp[i][j]&&mp[u][v]&&flag)Color(i,j,u,v);}int ans=get(cnt);for(int i=0;i<n;i++){for(int j=0;j<m;j++){if(mp[i][j]&&!vis[i][j])ans=(ans+MOD-get(Dfs(i,j)))%MOD;}}return ans;}} sol ; 
	
string x[] = {"##.#",
 ".###",
 "###.",
 "#.##"} ; 

vector<string> gx ; 


int main() {
		for (int i = 0; i < 4; i ++) gx.push_back(x[i]) ; 
		cout << sol.ways(gx) << endl ; 
}

