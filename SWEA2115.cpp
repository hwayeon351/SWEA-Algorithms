//
//  main.cpp
//  SWEA2115
//
//  Created by Hwayeon on 2021/10/17.
//

#include <iostream>
using namespace std;

int N, M, C;
int honey[11][11] = {0, };
int answer = 0;
int w1_earn = 0;
int w2_earn = 0;

void w1_earn_money(int x, int sx, int sy, int h, int money){
    if(x > sx+M) return;
    if(h > C) return;
    if(money > w1_earn) w1_earn = money;
    for(int xx=x; xx<sx+M; xx++){
        w1_earn_money(xx+1, sx, sy, h+honey[sy][xx], money + honey[sy][xx]*honey[sy][xx]);
    }
};

void w2_earn_money(int x, int sx, int sy, int h, int money){
    if(x > sx+M) return;
    if(h > C) return;
    if(money > w2_earn) w2_earn = money;
    for(int xx=x; xx<sx+M; xx++){
        w2_earn_money(xx+1, sx, sy, h+honey[sy][xx], money + honey[sy][xx]*honey[sy][xx]);
    }
};

void get_honey(int wx, int wy){
    w1_earn = 0;
    w1_earn_money(wx, wx, wy, 0, 0);
    int ny = wy;
    int nx = wx+M;
    if(nx > N-M){
        nx = 0;
        ny ++;
    }
    for(int y=ny; y<N; y++){
        if(y > ny) nx = 0;
        for(int x=nx; x<=N-M; x++){
            w2_earn = 0;
            w2_earn_money(x, x, y, 0, 0);
            int total = w1_earn+w2_earn;
            if(answer < total) answer = total;
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        answer = 0;
        cin >> N >> M >> C;
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                cin >> honey[y][x];
            }
        }
        for(int y=0; y<N; y++){
            for(int x=0; x<=N-M; x++){
                if(y == N-1 && x > N-2*M) break;
                get_honey(x, y);
            }
        }
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
