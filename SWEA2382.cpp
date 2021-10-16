//
//  main.cpp
//  SWEA2382
//
//  Created by Hwayeon on 2021/10/16.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int N, M, K;
int area[100][100] = {0, };
int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, -1, 1, 0, 0};

struct Community{
    int y;
    int x;
    int micro_num = 0;
    int dir;
};
struct cmp{
    bool operator()(Community c1, Community c2){
        if(c1.y == c2.y){
            if(c1.x == c2.x){
                return c1.micro_num < c2.micro_num;
            }
            return c1.x < c2.x;
        }
        return c1.y < c2.y;
    }
};
Community com;
priority_queue<Community, vector<Community>, cmp> communities;
int answer = 0;

int change_dir(int dir){
    int new_dir = -1;
    switch(dir){
        case 1:
            new_dir = 2;
            break;
        case 2:
            new_dir = 1;
            break;
        case 3:
            new_dir = 4;
            break;
        case 4:
            new_dir = 3;
            break;
    }
    return new_dir;
}

void move_community(){
    priority_queue<Community, vector<Community>, cmp> new_communities;
    while(!communities.empty()){
        com = communities.top();
        communities.pop();
        area[com.y][com.x]--;
        com.x += dx[com.dir];
        com.y += dy[com.dir];
        //빨간 셀에 도착한 경우,
        if(com.x == 0 || com.x == N-1 || com.y == 0 || com.y == N-1){
            com.dir = change_dir(com.dir);
            com.micro_num /= 2;
            if(com.micro_num == 0) continue;
        }
        new_communities.push(com);
        area[com.y][com.x]++;
    }
    while(!new_communities.empty()){
        com = new_communities.top();
        new_communities.pop();
        area[com.y][com.x]--;
        while(area[com.y][com.x] > 0){
            com.micro_num += new_communities.top().micro_num;
            new_communities.pop();
            area[com.y][com.x]--;
        }
        communities.push(com);
        area[com.y][com.x] = 1;
    }
}

void start_timer(){
    for(int m=0; m<M; m++){
        move_community();
    }
    while(!communities.empty()){
        com = communities.top();
        answer += com.micro_num;
        communities.pop();
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        memset(area, 0, sizeof(area));
        answer = 0;
        cin >> N >> M >> K;
        for(int i=0; i<K; i++){
            cin >> com.y >> com.x >> com.micro_num >> com.dir;
            communities.push(com);
            area[com.y][com.x]++;
        }
        start_timer();
        cout << "#" << test_case << " " << answer << endl;
    }

    return 0;
}
