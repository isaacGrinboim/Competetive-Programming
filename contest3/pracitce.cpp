#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double epsilon = 0.00001;


double location(double time, vector<pair<double, double>>& travel) {
    double location = 0;
    for (auto segment : travel) {
        double segmentHeight = segment.first;
        double segmentTime = segment.second;
        if (time <= segmentTime) {
            location += time * (segmentHeight / segmentTime);
            break;
        } else {
            location += segmentHeight;
            time -= segmentTime;
        }
    }
    return location;
}

int main() {
    int a, d;
    cin >> a >> d;
    vector<pair<double, double>> ascends(a);
    double totalAscendTime = 0;
    double totalDistance = 0;

    for (int i = 0; i < a; ++i) {
        double height, time;
        cin >> height >> time;
        totalAscendTime += time;
        totalDistance += height;
        ascends[i] = {height, time};
    }

    vector<pair<double, double>> descends(d);
    double totalDescendTime = 0;

    for (int i = 0; i < d; ++i) {
        double height, time;
        cin >> height >> time;
        totalDescendTime += time;
        descends[i] = {height, time};
    }

    double left = 0, right = max(totalAscendTime, totalDescendTime);
    while (abs(right - left) > epsilon) {
        double mid = (left + right) / 2;
        double ascender = location(mid, ascends);
        double descender = totalDistance - location(mid, descends);
        if (ascender >= descender) {
        right = mid;
        } else {
            left = mid;
        }
    }
    cout << left << endl;
    return 0;
}


//all subsets of n in cpp:
#include <unordered_set>
#include <iostream>
using namespace std;

#include <vector>
int main(){
    int res = 0;
    int N,M;
    cin >> N >> M;
    vector<pair<int,int>> dontMix(M);
    for(int i=0; i<M; ++i){
        int a,b;
        cin >> a >> b;
        dontMix[i] = {a-1,b-1};
    }

    for (int i = 0; i < (1 << N); i++) {// iterating all subsets
                                        // i represents a subset
        bool validSet = true;
        for(auto& pair : dontMix){
            int a = pair.first, b = pair.second;
            if((i & (1 << a)) && (i & (1 << b))){
                validSet = false;
                break;
            }
        }

        res += (validSet==true);
    } 
    cout << res << endl;
    return 0;
}


void subSets(){
    int n;
    for (int i = 0; i < (1 << n); i++) {// iterating all subsets
                                            // i represents a subset
            for (int j = 0; j < n; j++) if (i & (1 << j)) {// iterating all elements
                                                        // j represents an element in i
                cout << j << " " ;
            } 

    }
}




//knitpicking

#include <unordered_map>
#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    bool impossible = true;
    unordered_map<string, unordered_map<string, int>> count;
    for (int i = 0; i < n; ++i) {
        string type, fit;
        int num;
        cin >> type >> fit >> num;
        count[type][fit] += num;
    }
    int res = 0;
    for(auto& sock : count){
        
        int left = 0, right = 0, any = 0;
        if(sock.second.find("left") != sock.second.end()){
            left = sock.second["left"];
        }
        if(sock.second.find("right") != sock.second.end()){
            right = sock.second["right"];
        }
        if(sock.second.find("any") != sock.second.end()){
            any = sock.second["any"];
        }
        if(any == 0){
            res += max(left,right);
            if(left>0 && right > 0){impossible = false;}
        }
        else{
            if(right>0 || left>0 || any >1){impossible = false;}
            res += max(1,max(right,left));
        }
    }
    if(impossible){
        cout << "impossible" << endl;
    }
    else{
        cout << res+1 << endl;
    }
    return 0;
}




//jogs

#include <iostream>
#include <vector>

using namespace std;

const int First = 0, Second = 1, Unset = 2;

// [1, b+c]
int color[2005];
vector<int> whatCanSee[2005];
bool sumPossible[1005];

// Only call when can get this color
bool Partition(int node, int currentGroup, int &currentGroupCount, int &otherGroupCount)
{
    color[node] = currentGroup;
    ++currentGroupCount;
    
    for (int i = 0; i < whatCanSee[node].size(); ++i)
    {
        int other = whatCanSee[node][i];
        
        if (color[other] == Unset)
        {
            if (!Partition(other, 1-currentGroup, otherGroupCount, currentGroupCount))
                return false;
        }
        
        else if (color[other] == currentGroup)
            return false;
    }
    
    return true;
}

int main()
{
    int T;
    cin >> T;
    
    while (T--)
    {
        int a, c, b;
        
        cin >> b >> c >> a;
        for (int i = 1; i <= b + c; ++i)
        {
            color[i] = Unset;
            whatCanSee[i].clear();
        }
        
        int largest = max(b, c);
        
        sumPossible[0] = true;
        for (int i = 1; i <= largest; ++i)
            sumPossible[i] = false;
        
        while (a--)
        {
            int u, v;
            cin >> u >> v;
            whatCanSee[u].push_back(v);
            whatCanSee[v].push_back(u);
        }
        
        bool possible = true;
        
        for (int i = 1; i <= b + c && possible; ++i)
        {
            if (color[i] == Unset)
            {
                int first = 0, second = 0;
                possible = Partition(i, First, first, second);
                
                for (int i = largest - 1; i >= 0; --i)
                {
                    if (sumPossible[i])
                    {
                        sumPossible[i] = false;
                        
                        if (i + first <= largest)
                            sumPossible[i + first] = true;
                        if (i + second <= largest)
                            sumPossible[i + second] = true;
                    }
                }
            }
        }
        
        // The wanted sum can be made
        if (possible && sumPossible[b] && sumPossible[c])
            cout << "yes\n";
        else
            cout << "no\n";
    }
}