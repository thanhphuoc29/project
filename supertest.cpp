#include<bits/stdc++.h>
#define ll long long
using namespace std;

int a[1005][1005],V,E,u,check[1005]={0},n,kt=0;
int way[1005][1005];  				// ma tran luu cac doan duong di, cac duong noi dinh chan gan =1, cac dinh le gan =2
const int maxn = 100001;
vector<pair<int, int> > adj[maxn];		//luu cac dinh ke va trong so vd dinh 1 ke voi 2,3 => adj[1]={2,3}(danh sach ke)
vector<int>dl;					//luu cac dinh le
vector<int>hv[maxn];				//luu hoan vi
vector<int>gt_hv;				//luu trong so cua cac hoan vi

const int INF = 1e9;
int pre[maxn];					//luu dinh truoc cua s
 

/******************Nhap ma tran*********************/
void input()
{
	for(int i = 1;i <= V;i++)
	{
		for(int j = 1;j <= V;j++)
		{
			cin >> a[i][j];
			way[i][j]=1;
			if(a[i][j] >0) adj[i].push_back({j, a[i][j]}); 			//  danh sach ke
		}
	}
}
void dfs(int u)										//duyet cac dinh bang dfs
{
	check[u]=1;
	for(int i=1;i<=V;i++)
	{
		if(a[u][i]>0 && check[i]==0)	dfs(i);
	}
}
/****************Kiem tra lien thong**************************/
bool check_connected(){
	dfs(u);
	for(int i=1;i<=V;i++){
		if(check[i]==0) return false;						//neu ton tai dinh chua dc xet se tra ve false
	}
	return true;//cac dinh da dc xet
}
/**********************Kiem tra euler**************************/
bool check_euler(){
	if(check_connected()){	
		for(int i=1;i<=V;i++)
		{
		 	if(adj[i].size()%2==1)	return false;				//kiem tra dinh le
		}
		return true;
	}
	return false;
}
/***************Tim dinh ke************************/
int ke(int u){
	int kt=0;
	for(int i=1;i<=V;i++){
		if(a[u][i]>0) return i;							//tra ve dinh ke cua u
	}
	return 0;									//khong co se tra ve 0
}
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
			way[d][t]--;way[t][d]--;					//xoa nhung duong da di qua
			if(way[d][t]==0 && way[t][d]==0){				//neu khong con duong di => loai canh khoi do thi
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
void trace(int s,int t)									//truy vet + phan hoach
{
	vector<ll> d(V + 1, INF);
	d[s] = 0;//gan nhan d[s]=0
	pre[s]=s; 
	priority_queue<pair<int, int>, vector<pair<int, int> > , greater<pair<int,int> > > Q;		//dung hang doi uu tien (phan tu top se nho nhat)
	Q.push({0, s});
	while(!Q.empty())
	{
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;									//s
		int kc = top.first;									//d[s]
		if(kc > d[u]) continue;									// tránh trong stack có trường hợp (1,2),(2,2) sẽ xét cả (2,2)
		for(int i = 0;i < adj[u].size();i++)
		{
			pair<int,int>it = adj[u][i];
			int v = it.first;								// lay ra dinh ke voi u
			int w = it.second;								//lay ra trong so (khoang cach tu u->i)
			if(d[v] > d[u] + w){								//xet cach đi đến đinh v theo cách mới( neu khoang cach  3-4 > 3 -4 -2 thi đi qua 3-4-2)
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
	//them duong di toi uu vao do thi
	reverse(path.begin(),path.end());
	for(int i = 0;i < path.size()-1;i++)
	{
		way[path[i]][path[i+1]]++;								//them duong di tu u->v vao do thi
		way[path[i+1]][path[i]]++;								//them duong di tu v->u vao do thi
	}
}
int find_way(int s,int t)			//dung thuat toan dijkstra
{
	vector<ll> d(V + 1, INF);
	d[s] = 0;
	pre[s]=s; 
	priority_queue<pair<int, int>, vector<pair<int, int> > , greater<pair<int,int> > > Q;
	Q.push({0, s});
	while(!Q.empty())
	{
		pair<int, int> top = Q.top(); Q.pop();
		int u = top.second;
		int kc = top.first;
		if(kc > d[u]) continue;
		for(int i = 0;i < adj[u].size();i++)
		{
			pair<int,int>it = adj[u][i];
			int v = it.first;
			int w = it.second;
			if(d[v] > d[u] + w){
				d[v] = d[u] + w;
				Q.push({d[v], v});
				pre[v] = u;
			}
		}
	}
	return d[t];		//tra ve do dai quang duong ngan nhat tu s -> t
}

void creat_graph()
{
	for(int i = 1;i <= V;i++)
	{
		if(adj[i].size()%2==1)	dl.push_back(i);//tim cac dinh le them vao vector dl
	}
	int k = 0,k1 = 0;
	while(next_permutation(dl.begin(),dl.end()))//tim hoan vi cua tap dinh le ke tiep
	{
		k++;
		if(k%2==1)//tranh lap lai hoan vi 
		{
			int value = 0;
			for(int i = 0;i < dl.size();i+=2)
			{
				hv[k1].push_back(dl[i]);
				hv[k1].push_back(dl[i+1]);
				value += find_way(dl[i],dl[i+1]);
			}
			k1++;
			gt_hv.push_back(value);
		}
	}
	int gt = gt_hv.size();
	int a[gt];
	copy(gt_hv.begin(),gt_hv.end(),a);
	int tmp = min_element(a,a+gt)-a;//luu vi tri chua phan hoach toi uu
	for(int i = 0;i < hv[tmp].size();i+=2)	
	{
		trace(hv[tmp][i],hv[tmp][i+1]);//truy vet duong di giua hai dinh
	}
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
					for(int j=1;j<=V;j++){
						fpi>>a[i][j];
						way[i][j]=1;
						if(a[i][j] > 0) adj[i].push_back({j, a[i][j]});
					}
				}
				
				cout<<"Nhap file thanh cong!"<<endl;
			}
			break;
		}	
	}
	if(check_connected()){//kiem tra do thi lien thong
		if(check_euler()){
			cout<<"Hanh trinh toi uu cua nguoi dua thu: ";
			find_euler(u);//dua ra hanh trinh toi uu
		}
		else{
			cout<<"Khong phai do thi euler !"<<endl;
			cout<<"Khoi tao do thi euler moi...\nHanh trinh toi uu cua nguoi dua thu la: ";
			creat_graph();
			find_euler(u);
		}
	}
	else cout<<"Do thi khong lien thong!";
	cout<<endl;
	system("pause");
}
