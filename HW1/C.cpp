#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<double, double> ii;

double pos(ii& car, double t){
    return car.first + car.second*t;
}
double f(vector<ii>& cars, double time){
    double maxi = pos(cars[0], time);
    double mini = maxi;
    for(auto& car : cars){
        double current = pos(car, time);
        maxi = max(maxi,current);
        mini = min(mini, current);
    }
    return maxi-mini;
}

int main(){
    int n;
    cin >> n;
    vector<ii> cars(n);
    for(auto& car : cars){
        cin >> car.first >> car.second;
    }
    double l = 0, r = 1e9;
    while (r - l > 1e-7){
        double m1 = (2*l + r)/3;
        double m2 = (2*r + l)/3;
        if (f(cars, m1) < f(cars, m2))
		    r = m2;
        else
		    l = m1;
    }
    cout << f(cars, (l+r)/2) << endl;
    return 0;
}