#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;




vector<bool> sieve(int n){
    vector<bool> ps(n+1,true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 0; i <= sqrtn; ++i) {
        if(ps[i]){
            for (int j = i*i; j <= n; j+=i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

pair<ll,ll> getNums(vector<bool>& nums, ll L, ll U){
    ll i,j;
    int count;
    for(i=L; i<=U; ++i){
        if(nums[i]){
            count++;
            for(j=i+1; j<=U; ++j){
                if(nums[j]){
                    count++;
                    break;
                }
            }
            break;
        }
    }
    if(count < 2){
        return {0,0};
    }
    return {i,j};
}
void noNums(){
    cout << "There are no adjacent primes." << endl;
}

void solve(ll L, ll U){
    vector<bool> nums = sieve(U);
    pair<ll,ll> closest,farest;
    closest = farest = getNums(nums,L,U);
    if(closest.first == closest.second){
        noNums();
        return;
    }
    ll l = closest.first;
    ll r = closest.second;
    ll mini = r-l;
    ll maxi = r-l;
    for(ll i = r+1; i<=U; ++i){
        if(!nums[i]) continue;
        ll curr_r = i;
        ll curr_l = r;
        if(curr_r-curr_l > maxi){
            maxi = curr_r-curr_l;
            farest = {curr_l,curr_r};
        }
        if(curr_r-curr_l < mini){
            mini = curr_r-curr_l;
            closest = {curr_l,curr_r};
        }
        l = curr_l; r = curr_r;
    }
    cout << closest.first << "," << closest.second << " are closest, ";
    cout << farest.first << "," << farest.second << " are most distant." << endl;
}


int main() {
    int L,U;
    while(cin >> L >> U){
        solve(L,U);
    }
    return 0;
}