//
//  main.cpp
//  SWEA2115
//
//  Created by Hwayeon on 2021/01/13.
//
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
 
int N, M, C;
int map[10][10] = {0,};
bool visit[10][10] = {false,};
int worker_earn[2] = {0,};
int max_earn = 0;
bool wh[2][5] = {false,};
vector<vector<pair<int, int> > > worker;
 
void choice_honey(int w, int cnt, int earn){
    if(cnt == M){
        int total = 0;
        for(int i=0; i<M; i++){
            if(wh[w][i] == true){
                total += pow(map[worker[w][i].first][worker[w][i].second], 2);
            }
        }
        if(total > worker_earn[w]) worker_earn[w] = total;
        return;
    }
    for(int i=0; i<M; i++){
        if(wh[w][i] == true) continue;
        if(map[worker[w][i].first][worker[w][i].second] + earn <= C){
            wh[w][i] = true;
            choice_honey(w, cnt+1, map[worker[w][i].first][worker[w][i].second] + earn);
            wh[w][i] = false;
        }
        else choice_honey(w, cnt+1, earn);
    }
}
 
void get_max_earn(){
    for(int i=0; i<2; i++){
        worker_earn[i] = 0;
        choice_honey(i, 0, 0);
    }
    if(worker_earn[0]+worker_earn[1] > max_earn) max_earn = worker_earn[0]+worker_earn[1];
}
 
void pick_honey(int cnt){
    vector<pair<int, int> > v;
    v.clear();
    if(cnt==2) {
        get_max_earn();
        return;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<=N-M; j++){
            bool check = true;
            for(int m=j; m<j+M; m++){
                if(visit[i][m]==true){
                    check = false;
                    break;
                }
            }
            if(check == false) continue;
            else{
                for(int m=j; m<j+M; m++){
                    visit[i][m] = true;
                    v.push_back(make_pair(i, m));
                }
                worker.push_back(v);
                pick_honey(cnt+1);
                for(int m=j; m<j+M; m++){
                    visit[i][m] = false;
                }
                worker.pop_back();
                v.clear();
            }
        }
    }
}
 
int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin>>T;
 
    for(test_case = 1; test_case <= T; ++test_case)
    {
        max_earn = 0;
        cin >> N >> M >> C;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin >> map[i][j];
            }
        }
        pick_honey(0);
        cout << "#" << test_case << " " << max_earn << endl;
    }
    return 0;
}
