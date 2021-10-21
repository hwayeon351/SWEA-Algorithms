//
//  main.cpp
//  SWEA2117
//
//  Created by Hwayeon on 2021/10/21.
//

#include <iostream>
using namespace std;

int N, M;
int city[21][21] = {0, };
int house = 0;
int max_house = 0;

void service(int sx, int sy, int K){
    int cnt = 0;
    int d = 0;
    for(int y=sy; y<sy+K; y++){
        for(int dx=-d; dx<=d; dx++){
            int nx = sx+dx;
            if(nx<0 || nx>=N || y<0 || y>N) continue;
            cnt += city[y][nx];
        }
        d++;
    }
    d-=2;
    for(int y=sy+K; y<sy+2*K-1; y++){
        for(int dx=-d; dx<=d; dx++){
            int nx = sx+dx;
            if(nx<0 || nx>=N || y<0 || y>N) continue;
            cnt += city[y][nx];
        }
        d--;
    }
    if(cnt*M < K*K+(K-1)*(K-1)) return;
    if(cnt > max_house) max_house = cnt;
}

void get_service_area(){
    int K;
    if(N % 2) K = N;
    else K = N+1;
    
    for(int k=1; k<=K; k++){
        if(k*k+(k-1)*(k-1) > M*house) continue;
        for(int y=(-2*K+2); y<N; y++){
            for(int x=-K; x<N+K; x++){
                service(x, y, k);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        house = 0;
        max_house = 0;
        cin >> N >> M;
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                cin >> city[y][x];
                house += city[y][x];
            }
        }
        get_service_area();
        cout << "#" << test_case << " " << max_house << endl;
    }
    return 0;
}
