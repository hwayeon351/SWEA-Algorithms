//
//  main.cpp
//  SWEA1952
//
//  Created by Hwayeon on 2021/01/05.
//

#include<iostream>

using namespace std;

int minimum_cost;
int cost[4] = {0,};
int monthly_plan[12] = {0,};

void print_cost_monthly_plan(){
    for(int i=0; i<4; i++){
        cout << cost[i] << " ";
    }
    cout << "\n";
    for(int i=0; i<12; i++){
        cout << monthly_plan[i] << " ";
    }
    cout << "\n\n";
}

void get_minimum_cost(int month, int now_cost){
    if(month >= 12){
        if(now_cost < minimum_cost){
            minimum_cost = now_cost;
        }
        return;
    }
    
    if(monthly_plan[month] == 0){
        get_minimum_cost(month+1, now_cost);
    }
    //daily
    get_minimum_cost(month+1, (cost[0] * monthly_plan[month]) + now_cost);

    //monthly
    get_minimum_cost(month+1, cost[1] + now_cost);

    //3 monthly
    get_minimum_cost(month+3, cost[2] + now_cost);
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        for(int i=0; i<4; i++){
            cin >> cost[i];
        }
        for(int i=0; i<12; i++){
            cin >> monthly_plan[i];
        }
        minimum_cost = cost[3];
        get_minimum_cost(0, 0);
        cout << "#" << test_case << " " << minimum_cost << endl;
    }
    return 0;
}
