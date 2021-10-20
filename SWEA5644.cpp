//
//  main.cpp
//  SWEA5644
//
//  Created by Hwayeon on 2021/10/20.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int M, A;
int map[11][11][8] = {0, };
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, -1, 0, 1, 0};
struct User{
    int x;
    int y;
    int dir[100] = {0, };
};
struct BatteryCharger{
    int x;
    int y;
    int C;
    int P;
};
BatteryCharger bc;
vector<BatteryCharger> BC;
vector<User> users;
vector<int> A_choice;
vector<int> B_choice;
int total_charge = 0;

void get_BC_area(){
    for(int i=0; i<A; i++){
        bc = BC[i];
        queue<pair<pair<int, int>, int>> q;
        q.push({{bc.x, bc.y}, 0});
        map[bc.y][bc.x][i] = 1;
        while(!q.empty()){
            int x = q.front().first.first;
            int y = q.front().first.second;
            int cnt = q.front().second;
            q.pop();
            if(cnt >= bc.C) break;
            for(int d=1; d<5; d++){
                int nx = x + dx[d];
                int ny = y + dy[d];
                if(nx<1 || nx>10 || ny<1 || ny>10) continue;
                if(map[ny][nx][i]) continue;
                map[ny][nx][i] = 1;
                q.push({{nx, ny}, cnt+1});
            }
        }
    }
}

int get_choice(){
    A_choice.clear();
    B_choice.clear();
    for(int a=0; a<A; a++){
        if(map[users[0].y][users[0].x][a]){
            A_choice.push_back(a);
        }
        if(map[users[1].y][users[1].x][a]){
            B_choice.push_back(a);
        }
    }
    int now_charge = 0;
    if(A_choice.empty()){
        for(int b=0; b<B_choice.size(); b++){
            if(now_charge < BC[B_choice[b]].P) now_charge = BC[B_choice[b]].P;
        }
    }
    else if(B_choice.empty()){
        for(int a=0; a<A_choice.size(); a++){
            if(now_charge < BC[A_choice[a]].P) now_charge = BC[A_choice[a]].P;
        }
    }
    else{
        for(int a=0; a<A_choice.size(); a++){
            for(int b=0; b<B_choice.size(); b++){
                int charge = 0;
                if(A_choice[a] == B_choice[b]){
                    charge = BC[A_choice[a]].P;
                }
                else{
                    charge = BC[A_choice[a]].P + BC[B_choice[b]].P;
                }
                if(now_charge < charge) now_charge = charge;
            }
        }
    }
    return now_charge;
}

void move_users(){
    total_charge = get_choice();
    for(int i=0; i<M; i++){
        for(int j=0; j<2; j++){
            users[j].x += dx[users[j].dir[i]];
            users[j].y += dy[users[j].dir[i]];
        }
        total_charge += get_choice();
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        memset(map, 0, sizeof(map));
        total_charge = 0;
        BC.clear();
        users.clear();
        User user;
        user.x = 1;
        user.y = 1;
        users.push_back(user);
        user.x = 10;
        user.y = 10;
        users.push_back(user);
        
        cin >> M >> A;
        for(int i=0; i<2; i++){
            for(int j=0; j<M; j++){
                cin >> users[i].dir[j];
            }
        }
        for(int i=0; i<A; i++){
            cin >> bc.x >> bc.y >> bc.C >> bc.P;
            BC.push_back(bc);
        }
        get_BC_area();
        move_users();
        cout << "#" << test_case << " " << total_charge << endl;
    }
    return 0;
}
