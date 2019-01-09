#include <cstdio>
#include <cstring>
#include <algorithm>
inline int in() {
    int x=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=x*10+(c^48), c=getchar();
    return x;
}
template<typename T>
inline void out(T x) {
    int i=0;
    static char s[15];
    do s[i++]=x%10; while(x/=10);
    while(i--) putchar(s[i]^48);
    putchar('\n');
}

const int N = 205, inf = 0x3f3f3f3f;
struct edge {
    int next, to, w, c;
}e[N*N];
int cnt=1, head[N], S=0, T=201;

struct MCMF {
    int d[N], pre[N];
    inline bool spfa() {
        static int q[N];
        static bool vis[N];
        memset(d, inf, sizeof(d));
        int l=0, r=1; q[0]=S, d[S]=0;
        while(l!=r) {
            int u=q[l++]; if(l==N) l=0;
            vis[u]=false;
            for(int i=head[u];i;i=e[i].next) {
                int v=e[i].to;
                if(e[i].w&&d[u]+e[i].c<d[v]) {
                    d[v]=d[u]+e[i].c;
                    pre[v]=i;
                    if(!vis[v]) {
                        q[r++]=v, vis[v]=true;
                        if(r==N) r=0;
                    }
                }
            }
        }
        return d[T]<inf;
    }
    inline bool lpfa() {
        static int q[N];
        static bool vis[N];
        memset(d, -1, sizeof(d));
        int l=0, r=1; q[0]=S, d[S]=0;
        while(l!=r) {
            int u=q[l++]; if(l==N) l=0;
            vis[u]=false;
            for(int i=head[u];i;i=e[i].next) {
                int v=e[i].to;
                if(e[i].w&&d[u]+e[i].c>d[v]) {
                    d[v]=d[u]+e[i].c;
                    pre[v]=i;
                    if(!vis[v]) {
                        q[r++]=v, vis[v]=true;
                        if(r==N) r=0;
                    }
                }
            }
        }
        return d[T]>=0;
    }
    inline int modify() {
        int u=T, min=inf;
        while(u!=S) {
            min=std::min(min, e[pre[u]].w);
            u=e[pre[u]^1].to;
        }
        u=T;
        while(u!=S) {
            e[pre[u]].w-=min;
            e[pre[u]^1].w+=min;
            u=e[pre[u]^1].to;
        }
        return min*d[T];
    }
    inline int minc() {
        int cost=0;
        while(spfa()) cost+=modify();
        return cost;
    }
    inline int maxc() {
        int cost=0;
        while(spfa()) cost+=modify();
        return cost;
    }
}G;


inline void jb(int u, int v, int w, int c) {
    e[++cnt]=(edge){head[u], v, w, c},  head[u]=cnt;
    e[++cnt]=(edge){head[v], u, 0, -c}, head[v]=cnt;
}

int main() {
	freopen("t.in","r",stdin);

    int n=in();
    for(int i=1;i<=n;i++) {
        jb(S, i, 1, 0);
        jb(i+n, T, 1, 0);
        for(int j=1;j<=n;j++)
            jb(i, j+n, 1, in());
    }
    out(G.minc());
    for(int i=2;i<=cnt;i+=2) e[i].w+=e[i^1].w, e[i^1].w=0;
    for(int u=1;u<=n;u++)
        for(int i=head[u];i;i=e[i].next)
            e[i].c=-e[i].c, e[i^1].c=-e[i^1].c;
    out(-G.maxc());
    return 0;
}
