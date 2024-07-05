#include <iostream>
#include <cmath>
#include <list>
#include <utility>
#include <unordered_map>
using namespace std;
// קשה מאוד דורש עץ דרגות


int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; ++i){
        int num,reqs;
        cin >> num >> reqs;
        unordered_map<int,int> movToLoc;
        unordered_map<int,int> locToMov;

        for(int j=01; j<=num; ++j){
            movToLoc[j] = j;
            locToMov[j] = j;
        }
        for(int j=0; j <reqs; ++j){
            int req;
            cin >> req;
            cout << movToLoc[req]-1 << " ";
            int pos = movToLoc[req];
            for(int k=pos; k>0; --k){
                locToMov[k] = locToMov[k-1];
                movToLoc[locToMov[k]] ++;
            }
            movToLoc[req] = 0;
            locToMov[0] = req;
        }
        cout << endl;
    }
}


//         vector<int> res;
//         for(int i=0; i<n; ++i){ // לכל שורה
//             int a = 0;
//             for(int j=0; j<n; ++j){// מעבר על אברי השורה
//                 int temp;
//                 cin >> temp;
//                 a|=temp;
//             }
//             res.push_back(a);
//         }
//         for(auto num : res){
//             cout << num << " ";
//         }
//         cout << endl;
//     }
//     return 0;
// }

// // // int main(){
// // //     int width, num, area, w_i, l_i;
// // //     while(cin >> width >> num){  
// // //         area = 0;  
// // //         for(int j=0; j<num; ++j){
// // //             cin >> w_i >> l_i;
// // //             area += w_i*l_i;
// // //         }
// // //         cout << area / width << endl;
// // //     }


// // //     return 0;
// // // }

// // int main(){
// //     int n;
    
// //     while(cin >> n){
// //         vector<int> res;
// //         for(int i=0; i<n; ++i){
// //             int a = 0;
// //             int temp;
// //             for(int j=0; j<n; ++j){
// //                 cin >> temp;
// //                 a |= temp;
// //             }
// //             res.push_back(a);
// //         }
// //         for(auto num: res)
// //             cout << num << " ";
// //     }
// //     return 0;
// // }