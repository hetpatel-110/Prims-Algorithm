// Prims Algorithm Implementation with TC of O(N*logN) by Het B. Patel :)

#include<bits/stdc++.h>
using namespace std;

vector<int> par(100001), siz(100001);

int find(int x){
	if(x==par[x]) return x;
	return par[x]=find(par[x]);
}

void join(int a, int b){
	a=find(a);
	b=find(b);
	if(par[a]!=b){
        if(siz[b]>siz[a]) swap(a,b);
        par[b]=a;
        siz[a]+=siz[b];
	}
}

void prims(vector<vector<int>> edges, int n){
    vector<pair<int,int>> adj[n+1];
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    for(auto it : edges){
        adj[it[0]].push_back({it[1],it[2]});
        adj[it[1]].push_back({it[0],it[2]});
    }
    vector<vector<int>> ans;

    for(auto it : adj[1]){
        pq.push({it.second,1,it.first});
    }

    int tot=0;
    vector<int> mini=pq.top();
    ans.push_back(mini);
    join(mini[1],mini[2]);
    tot+=mini[0];

    while(!pq.empty()){
        pq.pop();
        int cur=mini[2];
        for(auto it : adj[cur]){
            if(find(it.first)!=find(cur)){
                pq.push({it.second,cur,it.first});
            }
        }
        if(!pq.empty()){
            mini=pq.top();
            while(!pq.empty() && find(mini[1])==find(mini[2])){
                pq.pop();
                if(!pq.empty()) mini=pq.top();
            }
            if(!pq.empty()){
                ans.push_back(mini);
                join(mini[1],mini[2]);
                tot+=mini[0];
            }
        }
    }

    cout<<"Weight of Minimum Spanning Tree : "<<tot<<"\n";
    cout<<"Edges\tWeights\n";
    for(auto it : ans){
        cout<<it[1]<<"-"<<it[2]<<"\t"<<it[0]<<"\n";
    }
}

int main(){
	int n, e, a, b, c;
	cout<<"Enter Number of Nodes in Graph : ";
	cin>>n;
	cout<<"Enter Number of Edges in Graph : ";
	cin>>e;
	cout<<"Enter Edges with Weights : \n";
	for (int i = 1; i <= n; i++)
	{
		par[i]=i;
	}
	vector<vector<int>> adj(e, vector<int>(3));
	for(int i=0 ; i<e ; i++){
		cin>>a>>b>>c;
		adj[i]={a,b,c};
	}
	prims(adj, n);

	return 0;
}
