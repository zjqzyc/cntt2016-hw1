#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <map>
using namespace std;
const int MOD = 1000000009, MAXN = 55;
inline void get_intersect(int &le, int &ri, int x, int y)//get intersection of two intervals
{
	if(x > le)
		le = x;
	if(y < ri)
		ri = y;
}
class Mountains
{
private:
	int h[MAXN], vis[MAXN][2];//h: height. vis: the two endpoints of the interval of visible columns.
	int n, w;
	int mxh[MAXN][MAXN];//mxh[now]: "maxheight" in the solution. mxh[now][i]: max height at place i of mountains now ~ n-1.
	map <string, int> mp;
	int search(int now)//search the place of the now-th mountain
	{
		if(now < 0)//we've searched a valid placement of the n mountains
			return 1;
		memcpy(mxh[now], mxh[now + 1], sizeof(mxh[now]));
		string str(1, now);
		for(int i = 0; i < w; i++)
			str += mxh[now][i];
		if(mp.find(str) != mp.end())//memorization
			return mp[str];
		if(vis[now][0] == -1)//invisible
		{
			int cnt = 0;//count invisible places
			for(int i = 0; i < w; i++)
				if(mxh[now][i] >= h[now])
					cnt++;
			return (long long)search(now - 1) * cnt % MOD;
		}
		int le = 0, ri = w - 1;//valid places: [le, ri]
		int tmp = h[now] - (mxh[now][vis[now][0]] + 1);
		get_intersect(le, ri, vis[now][0] - tmp, vis[now][0] + tmp);//visible at vis[now][0]
		if(vis[now][0] != 0)
			le = max(le, (vis[now][0] - 1) + (h[now] - mxh[now][vis[now][0] - 1]));//not visible at vis[now][0] - 1
		tmp = h[now] - (mxh[now][vis[now][1]] + 1);
		get_intersect(le, ri, vis[now][1] - tmp, vis[now][1] + tmp);//visible at vis[now][1]
		if(vis[now][1] != w - 1)
			ri = min(ri, (vis[now][1] + 1) - (h[now] - mxh[now][vis[now][1] + 1]));//not visible at vis[now][1] + 1
		long long ret = 0;
		for(int i = le; i <= ri; i++)//place mountain #now at place i
		{
			memcpy(mxh[now], mxh[now + 1], sizeof(mxh[now]));
			for(int j = 0; j < h[now] && i - j >= 0; j++)
				mxh[now][i - j] = max(mxh[now][i - j], h[now] - j);
			for(int j = 1; j < h[now] && i + j < w; j++)
				mxh[now][i + j] = max(mxh[now][i + j], h[now] - j);
			ret += search(now - 1);
		}
		return mp[str] = (int)(ret % MOD);//memorization
	}
public:
	int countPlacements(vector<int> heights, vector<string> visibility)
	{
		memset(mxh, 0, sizeof(mxh));
		n = heights.size();
		w = visibility[0].size();
		for(int i = 0; i < n; i++)
			h[i] = heights[i];
		for(int i = 0; i < n; i++)
		{
			//------XXXXXXXXX-----
			//      ^       ^     
			//      |       |     
			//      |       |     
			// vis[i][0] vis[i][1]
			vis[i][0] = vis[i][1] = -1;
			for(int j = 0; j < w; j++)
				if(visibility[i][j] == 'X')
				{
					vis[i][0] = j;
					break;
				}
			if(vis[i][0] == -1)//invisible
				continue;
			for(int j = vis[i][0] + 1; j < w; j++)
				if(visibility[i][j] == '-')
				{
					vis[i][1] = j - 1;
					break;
				}
			if(vis[i][1] == -1)//visible at all columns
				vis[i][1] = w - 1;
		}
		return search(n - 1);
	}
};
