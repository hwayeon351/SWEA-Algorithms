//
//  main.cpp
//  SWEA1244
//
//  Created by Hwayeon on 2020/12/04.
//
#include <iostream>
#include <string>
using namespace std;

int answer;

void change_board(int cnt, string num, int idx){
    if(cnt==0){
        int val = stoi(num);
        if(val>answer) answer = val;
        return;
    }
    for(int num_1=idx; num_1<num.size()-1; num_1++){
        for(int num_2=num_1+1; num_2<num.size(); num_2++){
            char temp1 = num[num_1];
            char temp2 = num[num_2];
            num[num_1] = temp2;
            num[num_2] = temp1;
            change_board(cnt-1,num, num_1);
            num[num_1] = temp1;
            num[num_2] = temp2;
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        int change;
         string num;
        answer = 0;
        cin >> num >> change;
          if(change > num.size()) change = num.size();
        change_board(change, num, 0);
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
