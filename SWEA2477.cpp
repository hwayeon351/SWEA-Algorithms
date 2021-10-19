//
//  main.cpp
//  SWEA2477_1
//
//  Created by Hwayeon on 2021/10/19.
//

#include <iostream>
#include <queue>
using namespace std;

int N, M;
int K;
int A, B;

struct Customer{
    int num;
    int recept_center;
    int repair_center;
    int recept_arrival_time;
    int repair_arrival_time;
};
struct Center{
    int time;
    int timer;
    Customer customer;
    bool check = false;
};
Customer customer;
struct recept_cmp{
    bool operator()(Customer c1, Customer c2){
        if(c1.recept_arrival_time == c2.recept_arrival_time)
            return c1.num > c2.num;
        return c1.recept_arrival_time > c2.recept_arrival_time;
    }
};
struct repair_cmp{
    bool operator()(Customer c1, Customer c2){
        if(c1.repair_arrival_time == c2.repair_arrival_time){
            return c1.recept_center > c2.recept_center;
        }
        return c1.repair_arrival_time > c2.repair_arrival_time;
    }
};
Center receptions[10];
Center repairs[10];

priority_queue<Customer, vector<Customer>, recept_cmp> recept_waitings;
priority_queue<Customer, vector<Customer>, repair_cmp> repair_waitings;

int answer = 0;

void operate_car_center(){
    int sec = 0;
    int done = 0;
    while(true){
        //1. 접수 처리
        for(int i=1; i<=N; i++){
            if(receptions[i].check){
                receptions[i].timer--;
                //접수 처리 종료
                if(receptions[i].timer == 0){
                    customer = receptions[i].customer;
                    customer.repair_arrival_time = sec;
                    repair_waitings.push(customer);
                    receptions[i].check = false;
                }
            }
        }
        //2. 정비 처리
        for(int j=1; j<=M; j++){
            if(repairs[j].check){
                repairs[j].timer--;
                //정비 처리 종료
                if(repairs[j].timer == 0){
                    customer = repairs[j].customer;
                    repairs[j].check = false;
                    done++;
                    if(customer.recept_center == A && customer.repair_center == B){
                        answer += customer.num;
                    }
                    if(done == K) return;
                }
            }
        }
        //2. 빈 접수 창구에 고객 배치
        for(int i=1; i<=N; i++){
            if(!receptions[i].check){
                if(recept_waitings.empty()) break;
                customer = recept_waitings.top();
                if(customer.recept_arrival_time > sec) break;
                recept_waitings.pop();
                customer.recept_center = i;
                receptions[i].check = true;
                receptions[i].customer = customer;
                receptions[i].timer = receptions[i].time;
            }
        }
        //3. 빈 정비 창구에 고객 배치
        for(int j=1; j<=M; j++){
            if(!repairs[j].check){
                if(repair_waitings.empty()) break;
                customer = repair_waitings.top();
                repair_waitings.pop();
                customer.repair_center = j;
                repairs[j].check = true;
                repairs[j].customer = customer;
                repairs[j].timer = repairs[j].time;
            }
        }
        sec++;
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        answer = 0;
        cin >> N >> M >> K >> A >> B;
        for(int i=1; i<=N; i++){
            cin >> receptions[i].time;
        }
        for(int j=1; j<=M; j++){
            cin >> repairs[j].time;
        }
        for(int k=1; k<=K; k++){
            customer.num = k;
            cin >> customer.recept_arrival_time;
            recept_waitings.push(customer);
        }
        operate_car_center();
        if(answer == 0) cout << "#" << test_case << " " << -1 << endl;
        else cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
