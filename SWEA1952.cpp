//
//  main.cpp
//  SWEA1952_1
//
//  Created by Hwayeon on 2021/10/15.
//

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    
    int dp[13] = {0, };
    int day, month, three_month, year;
    int plan[13] = {0, };
    for(test_case=1; test_case<=T; ++test_case){
        memset(dp, 0, sizeof(dp));
        cin >> day >> month >> three_month >> year;
        for(int m=1; m<=12; m++){
            cin >> plan[m];
        }
        dp[1] = min({day*plan[1], month});
        dp[2] = min({dp[1]+day*plan[2], dp[1]+month});
        for(int m=3; m<=12; m++){
            dp[m] = min({dp[m-1]+day*plan[m], dp[m-1]+month, dp[m-3]+three_month});
        }
        if(dp[12] > year) dp[12] = year;
        cout << "#" << test_case << " " << dp[12] << endl;
    }
    return 0;
}
