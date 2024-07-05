#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct unionfind
{
    vector<pair<int,int>> parent;
    
    unionfind(int size)
    {
        parent=vector<pair<int,int>>(size);
        for(int i=0;i<size;i++)
            parent[i]={i,1};
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x].first) x=parent[x].first;
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp].first;
            parent[tmp].first=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }
        if(parent[p].second < parent[q].second) {
            parent[p] = {q,parent[p].second+parent[q].second}; parent[q].second = parent[p].second;
        }
        else {
            parent[q] = {p,parent[p].second+parent[q].second};
            parent[p].second = parent[q].second;
        }
    }
};


int main(){
    int n;
    while(cin >> n){
        unordered_map<string, int> map;
        int index = 1;
        unionfind uf(2*n+1);
        for(int i=0; i<n; ++i){
            string a,b; // (a,b)
            cin >> a >> b;
            if(map.find(a) == map.end()){map[a] = index; ++index;}// a was not yet
            if(map.find(b) == map.end()){map[b] = index; ++index;}// b was not yet
            uf.Union(map[a],map[b]);
            int tem = uf.find(map[a]);
            cout << uf.parent[tem].second;
            cout << endl;
        }
    }
    return 0;
}