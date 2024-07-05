#include <iostream>
#include <vector>
using namespace std;
struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size)
    {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
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
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};
int main() {
    int n,k;
    while(cin >> n >> k){
        bool res = true;
        unionfind uf(n+1);
        int a,b;
        for(int i=0; i<k; ++i){
            cin >> a >> b;
            uf.Union(a,b);
        }
        for(int i=1; i <= n/2; ++i){
            if(uf.find(i) != uf.find(n+1-i)){
                res = false;
                break;
            }
        }
        if(res){
            cout << "Yes";
        }
        else{
            cout << "No";
        }
        cout << endl;
    }
}


