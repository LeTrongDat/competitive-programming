/*
  Author: Le Trong Dat
  Idea: Cumulative sum.
 */
#include <bits/stdc++.h>
using namespace std;
#define forn(i, a, b)       for(int i=a; i<=b; ++i)
#define ford(i, a, b)       for(int i=a; i>=b; ++i)
#define repn(i, a, b)       for(int i=a; i <b; ++i)
#define repd(i, a, b)       for(int i=(int)a-1; i>=b; --i)
const int N=2000;
const int mxN=1000;
const int M=5e5 +10;
#define x   first
#define y   second 
pair<int, int> coffe[M];
int rzx, rzy;
int d[2][mxN+10][mxN+10];
int dx, dy, n, q;

void update(int id, int x, int y, int v)
{
    d[id][x][y] += v;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int Case=0;
   while (cin>>dx>>dy>>n>>q)
   //while (true)
    {
        if (!dx && !dy && !n && !q) break;
        Case ++;
        cout<<"Case "<<Case<<":\n";
        forn(i, 1, n) cin>>coffe[i].x>>coffe[i].y;   
        for(int m; q; q--)
        {
            cin>>m;
            if (m>=N) { cout<<n<<" (1,1)\n"; continue; }
            memset(d, 0, sizeof d);
            forn(i, 1, n) 
            {
                int x=coffe[i].x, y=coffe[i].y;
                int ulx, uly, urx, ury;
                int blx, bly, brx, bry;
                int lux, luy, lbx, lby;
                int rux, ruy, rbx, rby;


                ulx=urx=max(1, x-m);
                uly=max(1, y-m+x-ulx);
                ury=min(dy, y+m-x+ulx);

                blx=brx=min(dx, x+m);
                bly=max(1, y-m+blx-x);
                bry=min(dy, y+m-blx+x);

                luy=lby=max(1, y-m);
                lux=max(1, x-m+y-luy);
                lbx=min(dx, x+m-y+luy);

                ruy=rby=min(dy, y+m);
                rux=max(1, x-m+ruy-y);
                rbx=min(dx, x+m-ruy+y);

                update(0, ulx, uly, 1);
                update(0, lux+1, luy-1, -1);
                if (luy==1) update(0, lbx+1, lby, -1);

                update(1, lbx+1, lby+1, 1);
                update(1, blx+1, bly+1, -1);

                update(1, urx, ury+1, -1);
                update(1, rux+1, ruy+2, 1);

                update(0, rbx+1, rby, -1);
                update(0, brx+1, bry, 1);
            }
            forn(i, 1, dx) forn(j, 1, dy) 
            {
                d[0][i][j]+=d[0][i-1][j+1];
                if (j==1 && i!=1) d[0][i][j]+=d[0][i-1][j];

                if (j!=1) d[1][i][j]+=d[1][i-1][j-1];
            }
            forn(i, 1, dx) forn(j, 1, dy) d[0][i][j]+=d[1][i][j];

            forn(i, 1, dx) forn(j, 2, dy) d[0][i][j]+=d[0][i][j-1];

            int mx=0, x=1, y=1;
            forn(j, 1, dy) forn(i, 1, dx) if (d[0][i][j]>mx)
            {
                mx=d[0][i][j];
                x=i; y=j;
            }
            cout<<mx<<' '<<"("<<x<<","<<y<<")\n";
        }
    }
}
