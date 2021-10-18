//
//  main.cpp
//  SWEA5650
//
//  Created by Hwayeon on 2021/10/18.
//

#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

int N;
int board[101][101] = {0, };
int block[6][4] = {{0,0,0,0}, {2,3,1,0}, {1,3,0,2}, {3,2,0,1}, {2,0,3,1}, {2,3,0,1}};
int warmhole_x[11][2] = {-1, };
int warmhole_y[11][2] = {-1, };

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct Pinball{
    int sx;
    int sy;
    int x;
    int y;
    int d;
};
Pinball ball;
int max_score = 0;

bool move_ball(Pinball& ball, int& score){
    int nx = ball.x + dx[ball.d];
    int ny = ball.y + dy[ball.d];
    int nd = ball.d;

    while((nx<0 || nx>=N || ny<0 || ny>=N) || !(board[ny][nx] == -1 || (board[ny][nx] >= 6 && board[ny][nx] <= 10) || (nx == ball.sx && ny == ball.sy))){
        //벽에 부딪힌 경우,
        if(nx<0 || nx>=N || ny<0 || ny>=N){
            nx -= dx[nd];
            ny -= dy[nd];
            nd = block[5][nd];
            score++;
        }
        //블록에 부딪힌 경우, 계속 부딪힐 수 있음!!!
        else if(board[ny][nx] >= 1 && board[ny][nx] <= 5){
            nd = block[board[ny][nx]][nd];
            nx += dx[nd];
            ny += dy[nd];
            score++;
        }
        else{
            nx += dx[nd];
            ny += dy[nd];
        }
    }
    //블랙홀에 빠졌거나 시작 위치로 돌아온 경우, 게임 종료
    if(board[ny][nx] == -1 || (nx == ball.sx && ny == ball.sy)){
        if(score > max_score) max_score = score;
        return false;
    }
    //웜홀에 빠진 경우, 다른 웜홀로 핀볼 위치 변경
    for(int i=0; i<2; i++){
        if(nx == warmhole_x[board[ny][nx]][i] && ny == warmhole_y[board[ny][nx]][i]) continue;
        ball.x = warmhole_x[board[ny][nx]][i];
        ball.y = warmhole_y[board[ny][nx]][i];
        ball.d = nd;
        break;
    }
    return true;
}

void play_pinball(){
    queue<pair<Pinball, int>> q;
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            if(board[y][x] != 0) continue;
            for(int d=0; d<4; d++){
                ball.sx = x;
                ball.sy = y;
                ball.x = x;
                ball.y = y;
                ball.d = d;
                q.push({ball, 0});
            }
        }
    }
    while(!q.empty()){
        ball = q.front().first;
        int now_score = q.front().second;
        q.pop();
        if(move_ball(ball, now_score)){
            q.push({ball, now_score});
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        max_score = 0;
        memset(warmhole_x, -1, sizeof(warmhole_x));
        memset(warmhole_y, -1, sizeof(warmhole_y));
        cin >> N;
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                cin >> board[y][x];
                //웜홀인 경우,
                if(board[y][x] >=6 && board[y][x] <= 10){
                    for(int i=0; i<2; i++){
                        if(warmhole_x[board[y][x]][i] == -1){
                            warmhole_x[board[y][x]][i] = x;
                            warmhole_y[board[y][x]][i] = y;
                            break;
                        }
                    }
                }
            }
        }
        play_pinball();
        cout << "#" << test_case << " " << max_score << endl;
    }
    return 0;
}
