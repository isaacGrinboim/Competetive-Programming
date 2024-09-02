#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vb = vector<bool>;
using vvb = vector<vector<bool>>;

const int INF = 1000000000;

int numStations, maxTime;
vi travelTimes;
vvb trainRightAvailable, trainLeftAvailable;
vvi minWaitTime;

int findMinWaitTime(int currentTime, int station) {
    if (currentTime == maxTime && station == numStations) return 0;
    if (currentTime >= maxTime) return INF;
    if (minWaitTime[currentTime][station] != -1) return minWaitTime[currentTime][station];

    int moveRight = INF, moveLeft = INF, wait = findMinWaitTime(currentTime + 1, station) + 1;

    if (trainRightAvailable[currentTime][station])
        moveRight = findMinWaitTime(currentTime + travelTimes[station], station + 1);
    
    if (trainLeftAvailable[currentTime][station])
        moveLeft = findMinWaitTime(currentTime + travelTimes[station - 1], station - 1);

    return minWaitTime[currentTime][station] = min({moveRight, moveLeft, wait});
}

void initializeTrainAvailability(vvb &trainAvailable, int numTrains, bool isRightDirection) {
    for (int i = 0; i < numTrains; ++i) {
        int currentTime;
        cin >> currentTime;
        if (currentTime > maxTime) continue;

        if (isRightDirection) {
            trainAvailable[currentTime][1] = true;
            for (int j = 2; j < numStations; ++j) {
                currentTime += travelTimes[j - 1];
                if (currentTime > maxTime) continue;
                trainAvailable[currentTime][j] = true;
            }
        } else {
            trainAvailable[currentTime][numStations] = true;
            for (int j = numStations - 1; j > 1; --j) {
                currentTime += travelTimes[j];
                if (currentTime > maxTime) continue;
                trainAvailable[currentTime][j] = true;
            }
        }
    }
}

void initializeMinWaitTime() {
    minWaitTime = vvi(maxTime + 1, vi(numStations + 1, -1));
}

int main() {
    int caseNumber = 1, numRightTrains, numLeftTrains;
    while (cin >> numStations >> maxTime) {
        travelTimes = vi(numStations);
        for (int i = 1; i < numStations; ++i)
            cin >> travelTimes[i];

        cin >> numRightTrains;
        trainRightAvailable = vvb(maxTime + 1, vb(numStations + 1, false));
        initializeTrainAvailability(trainRightAvailable, numRightTrains, true);

        cin >> numLeftTrains;
        trainLeftAvailable = vvb(maxTime + 1, vb(numStations + 1, false));
        initializeTrainAvailability(trainLeftAvailable, numLeftTrains, false);

        initializeMinWaitTime();

        int result = findMinWaitTime(0, 1);
        if (result >= INF) {
            cout << "Case Number " << caseNumber << ": impossible" << endl;
        } else {
            cout << "Case Number " << caseNumber << ": " << result << endl;
        }
        caseNumber++;
    }

    return 0;
}
