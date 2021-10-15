//
//  main.cpp
//  SWEA4012
//
//  Created by Hwayeon on 2021/10/15.
//

#include <iostream>
#include <string.h>
using namespace std;

int N;
int synergy[17][17] = {0, };
int visit[17] = {0, };
int answer = 20001;

void make_food(int cnt, int i){
    if(cnt == N/2){
        int A = 0;
        int B = 0;
        for(int j=1; j<=N; j++){
            for(int k=1; k<=N; k++){
                if(j == k) continue;
                if(visit[j] && visit[k]){
                    A += synergy[j][k];
                }
                else if(!visit[j] && !visit[k]){
                    B += synergy[j][k];
                }
            }
        }
        int result = abs(A-B);
        if(result < answer) answer = result;
        return;
    }
    if(i > N) return;
    for(int j=i; j<=N; j++){
        visit[j] = 1;
        make_food(cnt+1, j+1);
        visit[j] = 0;
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case = 1; test_case<=T; ++test_case){
        answer = 20001;
        cin >> N;
        for(int y=1; y<=N; y++){
            for(int x=1; x<=N; x++){
                cin >> synergy[y][x];
            }
        }
        make_food(0, 1);
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
