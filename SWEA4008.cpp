//
//  main.cpp
//  SWEA4008
//
//  Created by Hwayeon on 2021/10/18.
//

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int N;

//0 -> +, 1 -> -, 2 -> *, 3 -> /
int op[4] = {0, };
int num[12] = {0, };
vector<int> ops;

long long max_result = -100000001;
long long min_result = 100000001;

void calculate(){
    int result = num[0];
    for(int i=1; i<N; i++){
        switch(ops[i-1]){
            // +
            case 0:
                result += num[i];
                break;
            // -
            case 1:
                result -= num[i];
                break;
            // *
            case 2:
                result *= num[i];
                break;
            // /
            case 3:
                result /= num[i];
                break;
                
        }
    }
    if(result > max_result) max_result = result;
    if(result < min_result) min_result = result;
}

void get_op_permutations(int cnt){
    if(cnt == N-1){
        calculate();
        return;
    }
    for(int i=0; i<4; i++){
        if(op[i] > 0){
            op[i]--;
            ops.push_back(i);
            get_op_permutations(cnt+1);
            ops.pop_back();
            op[i]++;
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        min_result = 100000001;
        max_result = -100000001;
        
        cin >> N;
        for(int i=0; i<4; i++){
            cin >> op[i];
        }
        for(int i=0; i<N; i++){
            cin >> num[i];
        }
        
        get_op_permutations(0);
        cout << "#" << test_case << " " << abs(max_result-min_result) << endl;
    }
    return 0;
}
