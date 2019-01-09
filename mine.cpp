#include <cstdio>
#include <cstring>

inline int Min(int a, int b){return a < b? a: b;}

const int N=110;
const int INF=0x3f3f3f3f;

int n,s,t;
int a[N][N];

// edge start 
struct edge{
	int to,next,flow,val;
}e[(N*N)<<3];
int ehead[N<<2],ecnt;
inline void add_edge(int now,int to,int flow,int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].flow = flow;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end 
// spfa start 
int head,tail,head_dep,tail_dep;
int pre[(N<<2)+10], dis[(N<<2)+10], que[(N<<2)+10], cur[(N<<2)+10], flow[(N<<2)+10];
bool vis[(N<<2)+10];
inline bool spfa_Mi(){
	memset(dis, INF, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	head = tail = head_dep = tail_dep = 0;
	que[head] = s; dis[s] = 0; vis[s] = true; pre[t] = 0;flow[s] = INF;

	while((head <= tail && head_dep == tail_dep) || head_dep < tail_dep){
		for(int i = ehead[ que[head] ]; i; i = e[i].next){
			if(e[i].flow > 0 && dis[ que[head] ] + e[i].val < dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ que[head] ] + e[i].val;
				cur[ e[i].to ] = i ;
				pre[ e[i].to ] = que[head];
				flow[ e[i].to ]  = Min(e[i].flow, flow[ que[head] ]);
				if(!vis[ e[i].to ]){
					vis[ e[i].to ] = true;
					tail++;
					if(tail > (n << 2) + 5 ) tail = 1,tail_dep++;
					que[ tail ] = e[i].to;
				}
			}
		}
		vis[ que[head] ] = false; 
		head++;
		if(head > (n << 2) + 5 ) head = 1,head_dep++;
	}
	return pre[t] != 0;
}

inline bool spfa_Ma(){
	memset(dis, -INF, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	head = tail = head_dep = tail_dep = 0;
	que[head] = s; dis[s] = 0; vis[s] = true; pre[t] = 0;flow[s] = INF;

	while((head <= tail && head_dep == tail_dep) || head_dep < tail_dep){
		for(int i = ehead[ que[head] ]; i; i = e[i].next){
			if(e[i].flow > 0 && dis[ que[head] ] + e[i].val > dis[ e[i].to ]){
				dis[ e[i].to ] = dis[ que[head] ] + e[i].val;
				cur[ e[i].to ] = i;
				pre[ e[i].to ] = que[head];
				flow[ e[i].to ]  = Min(e[i].flow, flow[ que[head] ]);
				if(!vis[ e[i].to ]){
					vis[ e[i].to ] = true;
					tail++;
					if(tail > (n << 2) + 5 ) tail = 1,tail_dep++;
					que[ tail ] = e[i].to;
				}
			}
		}
		vis[ que[head] ] = false; 
		head++;
		if(head > (n << 2) + 5 ) head = 1,head_dep++;
	}
	return pre[t] != 0;
}
// spfa end
int Mincost, Maxcost;
inline void MiCMF(){
	for(int i=1;i<=n;i++){
		add_edge(s,i,1,0);
		add_edge(i,s,0,0);
		add_edge(i+n,t,1,0);
		add_edge(t,i+n,0,0);
		for(int j=1;j<=n;j++){
			add_edge(i,j+n,1,a[i][j]);
			add_edge(j+n,i,0,-a[i][j]);
		}
	}
	while( spfa_Mi() ){
		Mincost += flow[t] * dis[t];
		int now = t;
		while(now != s){
			e[ cur[now] ].flow -= flow[t];
			e[ cur[now] + ( (cur[now] & 1)? 1: -1) ].flow += flow[t];
			now = pre[now];
		}
	}
	printf("%d\n", Mincost);
}

inline void MaCMF(){
	ecnt=0;
	memset(ehead, 0, sizeof(ehead));
	for(int i=1;i<=n;i++){
		add_edge(s,i,1,0);
		add_edge(i,s,0,0);
		add_edge(i+n,t,1,0);
		add_edge(t,i+n,0,0);
		for(int j=1;j<=n;j++){
			add_edge(i,j+n,1,a[i][j]);
			add_edge(j+n,i,0,-a[i][j]);
		}
	}
	while( spfa_Ma() ){
		Maxcost += flow[t] * dis[t];
		int now = t;
		while(now != s){
			e[ cur[now] ].flow -= flow[t];
			e[ cur[now] + ( (cur[now] & 1)? 1: -1) ].flow += flow[t];
			now = pre[now];
		}
	}
	printf("%d\n", Maxcost);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("t.in","r",stdin);
	freopen("mine.out","w",stdout);
#endif
	scanf("%d",&n);
	s = (n<<1) + 2;
	t = (n<<1) + 3;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	// MiCMF
	MiCMF();
	MaCMF();
}
