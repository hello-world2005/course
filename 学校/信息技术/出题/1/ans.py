import queue
N,M,INF=int(5e4+10),int(5e5+10),int(1e18)
class Edge:
  def __init__(self,v,w,nxt):self.v,self.w,self.nxt = v,w,nxt
head,e,edge_cnt,d=[0 for i in range(N)],[Edge(0,0,0) for i in range(M)],1,[0 for i in range(N)]
def AddEdge(u,v,w):global edge_cnt;edge_cnt+=1;e[edge_cnt]=Edge(v,w,head[u]);head[u]=edge_cnt
def AddEdge1(u,v,l,r):AddEdge(u,v,r-l);AddEdge(v,u,0);d[u]-=l;d[v]+=l
def Bfs(s,t):
  for i in range(N):d[i] = 0
  q=queue.SimpleQueue();q.put(s);d[s]=1
  while not q.empty():
    u=q.get();i=head[u]
    while i:
      v,w=e[i].v,e[i].w;i=e[i].nxt
      if d[v] or not w:continue
      q.put(v);d[v]=d[u]+1
  return d[t]>0
def Dfs(u,f,t):
  if (u==t):return f
  q=f;i=head[u]
  while i and q:
    v,w=e[i].v,e[i].w
    if d[v]!=d[u]+1 or not w:i=e[i].nxt;continue
    now=Dfs(v,min(q,w),t)
    if (now==0):d[v]=0
    else:e[i].w-=now;e[i^1].w+=now;q-=now
    i=e[i].nxt
  return f-q
def Dinic(s,t):
  while (Bfs(s,t)):Dfs(s,INF,t)
n,m,s,t=map(int,input().split())
for i in range(m):u,v,l,r=map(int,input().split());AddEdge1(u,v,l,r)
S,T=n+1,n+2
for i in range(1,n+1):
  if (d[i]>0):AddEdge(S,i,d[i]);AddEdge(i,S,0)
  elif (d[i]<0):AddEdge(i,T,-d[i]);AddEdge(T,i,0)
Dinic(S,T);AddEdge1(t,s,0,INF);Dinic(S,T);i=head[S]
while (i):
  if (e[i].w>0):print('emm');break
  i=e[i].nxt
else:print(e[edge_cnt].w)
