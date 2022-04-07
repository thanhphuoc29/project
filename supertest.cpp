#include<bits/stdc++.h>

using namespace std;

int a[1005][1005],V,E,u,check[1005]={0},n,kt=0;
/******************Nhap ma tran*********************/
void input(){
	for(int i=1;i<=V;i++){
		for(int j=1;j<=V;j++){
			cin>>a[i][j];
		}
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
		if(d%2 != 0) point.push_back(i);
	}
}
/*********************Tim duong di giua hai dinh le****************************/
int find_way(int s,int t){
	
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
			a[d][t]=0;
			a[t][d]=0;
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
		else cout<<"Khong phai do thi euler !";
	}
	else cout<<"Do thi khong lien thong!";
}
