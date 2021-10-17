//
//  main.cpp
//  SWEA5656
//
//  Created by Hwayeon on 2021/10/17.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int N, W, H;
int brick[16][13] = {0, };
int copy_brick[16][13] = {0, };
int visit[16][13] = {0, };
vector<int> order;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int answer = 181;

void break_bricks(int sx, int sy){
    memset(visit, 0, sizeof(visit));
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visit[sy][sx] = 1;
    while(!q.empty()){
        int now_x = q.front().first;
        int now_y = q.front().second;
        int num = copy_brick[now_y][now_x];
        copy_brick[now_y][now_x] = 0;
        q.pop();
        for(int d=0; d<4; d++){
            for(int i=1; i<num; i++){
                int nx = now_x + i*dx[d];
                int ny = now_y + i*dy[d];
                if(nx<0 || nx>=W || ny<0 || ny>=H) continue;
                if(visit[ny][nx]) continue;
                if(copy_brick[ny][nx] == 0) continue;
                q.push({nx, ny});
                visit[ny][nx] = 1;
            }
        }
    }
}

void fall_down_bricks(){
    for(int x=0; x<W; x++){
        for(int y=H-1; y>=0; y--){
            if(copy_brick[y][x] == 0){
                int yy;
                bool check = false;
                for(yy=y-1; yy>=0; yy--){
                    if(copy_brick[yy][x] > 0) {
                        check = true;
                        break;
                    }
                }
                if(!check) break;
                copy_brick[y][x] = copy_brick[yy][x];
                copy_brick[yy][x] = 0;
            }
        }
    }
}

void count_bricks(){
    int cnt = 0;
    for(int y=0; y<H; y++){
        for(int x=0; x<W; x++){
            if(copy_brick[y][x] > 0) cnt++;
        }
    }
    if(cnt < answer) answer = cnt;
}

void shoot_bead(){
    memcpy(copy_brick, brick, sizeof(brick));
    for(int i=0; i<order.size(); i++){
        int x = order[i];
        int y;
        for(y=0; y<H; y++){
            if(copy_brick[y][x] > 0) break;
        }
        if(y == H-1 && copy_brick[y][x] == 0) return;
        break_bricks(x, y);
        fall_down_bricks();
    }
    count_bricks();
}

void choose_bead(int cnt){
    if(cnt == N){
        shoot_bead();
        return;
    }
    for(int x=0; x<W; x++){
        order.push_back(x);
        choose_bead(cnt+1);
        order.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        answer = 181;
        cin >> N >> W >> H;
        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                cin >> brick[y][x];
            }
        }
        choose_bead(0);
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
