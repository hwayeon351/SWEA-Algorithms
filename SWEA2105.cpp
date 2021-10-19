//
//  main.cpp
//  SWEA2105_1
//
//  Created by Hwayeon on 2021/10/19.
//

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

int N;
int desert[21][21] = {0, };
int visit[101] = {0, };
int dx[4] = {-1, 1, 1, -1};
int dy[4] = {1, 1, -1, -1};

int max_deserts = -1;

void go_tour(){
    int nx, ny, cnt;
    bool check;
    for(int d1=1; d1<=N-1; d1++){
        for(int d2=1; d2<=N-1; d2++){
            for(int y=0; y<N-1; y++){
                for(int x=1; x<N-1; x++){
                    memset(visit, 0, sizeof(visit));
                    nx = x;
                    ny = y;
                    cnt = 1;
                    check = true;
                    visit[desert[y][x]] = 1;
                    for(int i=0; i<4; i++){
                        int d;
                        if(i==0) d=d1;
                        else if(i==1) d=d2;
                        else if(i==2) d=d1;
                        else d=d2-1;
                        for(int j=0; j<d; j++){
                            nx += dx[i];
                            ny += dy[i];
                            if(nx<0 || nx>=N || ny<0 || ny>=N || visit[desert[ny][nx]]) {
                                check = false;
                                break;
                            }
                            visit[desert[ny][nx]] = 1;
                            cnt++;
                        }
                        if(!check) break;
                    }
                    if(!check) continue;
                    if(max_deserts < cnt) max_deserts = cnt;
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        max_deserts = -1;
        cin >> N;
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                cin >> desert[y][x];
            }
        }
        go_tour();
        cout << "#" << test_case << " " << max_deserts << endl;
    }
    return 0;
}
