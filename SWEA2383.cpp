//
//  main.cpp
//  SWEA2383
//
//  Created by Hwayeon on 2021/10/20.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

int N;
int room[10][10] = {0, };

struct Person{
    int x;
    int y;
    int stair;
    int dis;
    int move;
};
struct Stairs{
    int x;
    int y;
    int K = 0;
    deque<Person> users;
    queue<Person> waitings;
};
Person person;
Stairs stair;
vector<Stairs> stairs;
vector<Stairs> copy_stairs;
vector<Person> people;
vector<Person> copy_people;

int min_time = -1;

void move_people(){
    copy_people = people;
    copy_stairs = stairs;
    int sec = 0;
    int cnt = 0;
    bool check = false;
    while(true){
        sec++;
        //1. 사람들 계단으로 이동
        for(int p=0; p<copy_people.size(); p++){
            if(copy_people[p].move > copy_people[p].dis) continue;
            copy_people[p].move ++;
            //계단 도착 -> 해당 계단 웨이팅에 들어갔다가 1초 후 계단을 내려가기 시작한다
            if(copy_people[p].move == copy_people[p].dis+1){
                person = copy_people[p];
                person.move = 0;
                copy_stairs[copy_people[p].stair].waitings.push(person);
            }
        }

        //2. 계단 이동 완료된 사람 체크
        while((!copy_stairs[0].users.empty() && copy_stairs[0].users.front().move == copy_stairs[0].K) || (!copy_stairs[1].users.empty() && copy_stairs[1].users.front().move == copy_stairs[1].K)){
            if(!copy_stairs[0].users.empty() && copy_stairs[0].users.front().move == copy_stairs[0].K){
                copy_stairs[0].users.pop_front();
                cnt++;
            }
            if(!copy_stairs[1].users.empty() && copy_stairs[1].users.front().move == copy_stairs[1].K){
                copy_stairs[1].users.pop_front();
                cnt++;
            }
            if(cnt == people.size()){
                check = true;
                break;
            }
        }
        //모든 사람이 이동 완료한 경우, while문 종료
        if(check) break;
        
        //3. 계단에 도착한 사람 추가
        while(copy_stairs[0].users.size() < 3 && copy_stairs[0].waitings.size() > 0){
            person = copy_stairs[0].waitings.front();
            copy_stairs[0].users.push_back(person);
            copy_stairs[0].waitings.pop();
        }
        while(copy_stairs[1].users.size() < 3 && copy_stairs[1].waitings.size() > 0){
            person = copy_stairs[1].waitings.front();
            copy_stairs[1].users.push_back(person);
            copy_stairs[1].waitings.pop();
        }
        
        //4. 계단에 있는 사람들 한 칸씩 내려가기
        for(int s=0; s<2; s++){
            for(int p=0; p<copy_stairs[s].users.size(); p++){
                copy_stairs[s].users[p].move++;
            }
        }
    }
    if(min_time == -1) min_time = sec;
    else if(min_time > sec) min_time = sec;
}

void decide_stairs(int p){
    if(p == people.size()){
        move_people();
        return;
    }
    for(int s=0; s<2; s++){
        people[p].stair = s;
        people[p].dis = abs(people[p].x - stairs[s].x) + abs(people[p].y - stairs[s].y);
        decide_stairs(p+1);
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    
    for(test_case=1; test_case<=T; ++test_case){
        stairs.clear();
        people.clear();
        min_time = -1;
        
        cin >> N;
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                cin >> room[y][x];
                if(room[y][x] == 1){
                    person.stair = 0;
                    person.x = x;
                    person.y = y;
                    person.dis = 0;
                    person.move = 0;
                    people.push_back(person);
                }
                else if(room[y][x] > 1){
                    stair.x = x;
                    stair.y = y;
                    stair.K = room[y][x];
                    stair.users.clear();
                    stairs.push_back(stair);
                }
            }
        }
        decide_stairs(0);
        cout << "#" << test_case << " " << min_time << endl;
    }
    return 0;
}
