//
//  main.cpp
//  SWEA1204
//
//  Created by Hwayeon on 2020/12/16.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        int tc;
        int nums[101] = {0,};
        int max_score = 0;
        int max_cnt = 0;
        cin >> tc;
        for(int i=0; i<1000; i++){
            int now;
            cin >> now;
            nums[now]++;
        }
        for(int i=0; i<=100; i++){
            if(nums[i]>=max_cnt){
                max_score = i;
                max_cnt = nums[i];
            }
        }
        cout << "#" << test_case << " " << max_score << endl;
    }
    return 0;
}
