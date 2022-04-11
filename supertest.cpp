#include<bits/stdc++.h>

using namespace std;

int a[1005][1005],V,E,u,check[1005]={0},n,kt=0;
vector<int>point;//luu cac dinh le
int way[1005][1005];// ma tran luu cac doan duong di, cac duong noi dinh chan gan =1, cac dinh le gan =2
const int maxn = 100001;
vector<pair<int, int>> adj[maxn];
int a[1000][1000]={};
vector<int>dl;
vector<int>hv[maxn];
vector<int>gt_hv;

const int INF = 1e9;
int pre[maxn];
 

/******************Nhap ma tran*********************/
void partition(int s,int t)//phan hoach
{
	vector<ll> d(n + 1, INF);
	d[s] = 0;
	pre[s]=s; 
	priority_queue<pair<int, int>, vector<pair<int, int>> , greater<pair<int,int>>> Q;
	Q.push({0, s});
	while(!Q.empty())
	{
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;
		int kc = top.first;
		if(kc > d[u]) continue;
		for(auto it : adj[u])
		{
			int v = it.first;
			int w = it.second;
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				Q.push({d[v], v});
				pre[v] = u;
			}
		}
	}
	vector<int>path;
	while(1)
	{
		path.push_back(t);
		if(t==s)	break;
		t = pre[t];
	}
	reverse(begin(path),end(path));
	for(int i = 1;i < n;i++)
	{
		way[path[i]][path[i+1]]++;
		way[path[i+1]][path[i]]++;
	}
}
int find_way(int s,int t)
{
	vector<ll> d(n + 1, INF);
	d[s] = 0;
	pre[s]=s; 
	priority_queue<pair<int, int>, vector<pair<int, int>> , greater<pair<int,int>>> Q;
	Q.push({0, s});
	while(!Q.empty())
	{
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;
		int kc = top.first;
		if(kc > d[u]) continue;
		for(auto it : adj[u])
		{
			int v = it.first;
			int w = it.second;
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				Q.push({d[v], v});
				pre[v] = u;
			}
		}
	}
	return d[t];
}

void xu_ly_dinh_le()
{
	for(int i = 1;i <= n;i++)
	{
		if(adj[i].size()%2==1)	dl.push_back(i);
	}
	int k = 0,k1 = 0;
	while(next_permutation(dl.begin(),dl.end()))
	{
		k++;
		if(k%2==1)
		{
			int value = 0;
			for(int i = 0;i < dl.size();i+=2)
			{
				hv[k1].push_back(dl[i]);
				hv[k1].push_back(dl[i+1]);
				value += dijkstra(dl[i],dl[i+1]);
			}
			k1++;
			gt_hv.push_back(value);
		}
	}
	int gt = gt_hv.size();
	int a[gt];
	copy(gt_hv.begin(),gt_hv.end(),a);
	int tmp = min_element(a,a+gt)-a;
	for(int i = 0;i < hv[tmp].size();i+=2)	
	{
		dijkstra1(hv[tmp][i],hv[tmp][i+1]);
	}
}
void input()
{
	for(int i = 1;i <= V;i++)
	{
		for(int j = 1;j <= V;j++)
		{
			cin >> a[i][j];
			way[i][j]=1;
		}
	}
	for(int i = 1;i <= V;i++)
	{
		for(int j = 1;j <= V;j++)
		{
			if(a[i][j]>0)
			{
				adj[i].push_back({j, a[i][j]});
			}
		}	
	}
	xu_ly_dinh_le();
	}
}
void dfs(int u){
	check[u]=1;
	for(int i=1;i<=V;i++){
		if(a[u][i]==1 && check[i]==0){
			dfs(i);
		}
	}
}
/****************Kiem tra lien thong**************************/
bool check_connected(){
	dfs(u);
	for(int i=1;i<=V;i++){
		if(check[i]==0) return false;
	}
	return true;
}
/**********************Kiem tra euler**************************/
bool check_euler(){
	if(check_connected()){
		int d=0;
		for(int i=1;i<=V;i++){
			d=0;
			for(int j=1;j<=V;j++){
				if(a[i][j]==1) d++;
			}
			if(d%2 != 0) return false;//kien tra dinh le
		}
		return true;
	}
	return false;
}
/***************Tim dinh ke************************/
int ke(int u){
	int kt=0;
	for(int i=1;i<=V;i++){
		if(a[u][i]==1) return i;
	}
	return 0;
}
/****************************Tim dinh le*************************/
void find_odd_point(){
	int d=0;
	for(int i=1;i<=V;i++){
		d=0;
		for(int j=1;j<=V;j++){
			if(a[i][j]>0) d++;
		}
		if(d%2 != 0) point.push_back(i);//luu cac dinh le
	}
}
/*********************Tim duong di giua hai dinh le****************************/

/************************Them canh vao do thi************************/

/**************************Tim chu trinh euler******************************/
void find_euler(int u){
	stack<int>s;
	vector<int>CE;
	s.push(u);
	while(s.size() != 0){
		int d=s.top();
		if(ke(d) != 0){
			int t=ke(d);
			s.push(t);
			way[d][t]--;way[t][d]--;//xoa nhung duong da di qua
			if(odd[d][t]==0 && odd[t][d]==0){//neu khong con duong di => loai canh khoi do thi
				a[d][t]=0;
				a[t][d]=0;
			}
		}
		else{
			s.pop();
			CE.push_back(d);
		}
	}
	for(int i=CE.size()-1;i>=0;i--) cout<<CE[i]<<" ";
}
int main(){
	cout<< "---------- Chu trinh euler va bai toan nguoi dua thu ------------"<<endl;
	cout<<"Moi ban chon che do nhap: (1/2)"<<endl;
	cout<<"1.Nhap bang tay"<<endl;
	cout<<"2.Duyet tu file co san"<<endl;
	cout<<"Ban chon: ";cin>>n;
	switch(n){
		case 1:{
			cout<<"Nhap so dinh: ";cin>>V;
			cout<<"Nhap dinh bat dau: ";cin>>u;
			cout<<"Nhap ma tran:"<<endl;
			input();
			break;
		}
		case 2:{
			ifstream fpi("graph.txt");
			if(fpi==NULL) cout<<"Khong the doc file!"<<endl;
			else{
				fpi>>V>>u;
				for(int i=1;i<=V;i++){
				for(int j=1;j<=V;j++) fpi>>a[i][j];
				cout<<"Nhap file thanh cong!"<<endl;
				}
			}
			break;
		}	
	}
	if(check_connected()){
		if(check_euler()){
			cout<<"Hanh trinh toi uu cua nguoi dua thu: ";
			find_euler(u);
		}
		else{
			cout<<"Khong phai do thi euler !"<<endl;
			cout<<"Khoi tao do thi euler moi\n Hanh trinh toi uu cua nguoi dua thu la: ";
			
			partition();//phan hoach
			add_path();
			find_euler();
		}
	}
	else cout<<"Do thi khong lien thong!";
}
