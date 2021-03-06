#line 2 "CheckerExpansion.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

ll xl[41], yl[41];

bool check(ll x, ll y, int f) {
	// check overflow
	if(x < 0 || y < 0 || y > x) return false;
	if(!f) return true;
	// left triangle
	if(x + y <= xl[f - 1]) return check(x, y, f - 1);
	// upper triangle
	else if(y > yl[f - 1]) return check(x - (xl[f - 1] / 2 + 1), y - (yl[f - 1] + 1), f - 1);
	// right triangle
	else if(x > xl[f - 1] + 1 && x - y >= xl[f - 1] + 2) return check(x - (xl[f - 1] + 2), y, f - 1);
	else return false;
}

class CheckerExpansion {  
public:  
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h) {
		// precalc the size of triangle in each level
		xl[0] = 0, yl[0] = 0;
		for(int i = 1; i <= 40; ++i) xl[i] = xl[i - 1] * 2 + 2, yl[i] = yl[i - 1] * 2 + 1;
		vector<string> ret;
		// check each vectex
		for(int i = 0; i < h; ++i) {
			string s;
			for(int j = 0; j < w; ++j) {
				ll x = x0 + j, y = y0 + h - i - 1;
				if(x + y <= 2 * (t - 1)) {// check if in range
					if(check(x, y, 40)) {// check if covered
						// decide the color through mod 2
						if((x + y) / 2 % 2) s += 'B';
						else s += 'A';
					}
					else s += '.';
				}
				else s += '.';
			}
			ret.pb(s);
		}
		return ret;
	}  
};  
