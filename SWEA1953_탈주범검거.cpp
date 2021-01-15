//
//  main.cpp
//  SWEA1953
//
//  Created by Hwayeon on 2021/01/15.
//
#include<iostream>
#include<vector>
#include<cmath>
#include<queue>

using namespace std;

int N, M, L, R, C;
int map[50][50] = {0, };
int num_loc = 0;
int dx[5] = {0, -1, 0, 1, 0};
int dy[5] = {0, 0, -1, 0, 1};
vector< vector<int> > ternal = {{0}, {1, 2, 3, 4}, {2, 4}, {1, 3}, {2, 3}, {3, 4}, {1, 4}, {1, 2}};

void find_loc(){
    bool visit[50][50] = {false, };
    queue<queue<pair<int, int>>> time_q;
    queue<pair<int, int>> hole;
    hole.push(make_pair(R, C));
    time_q.push(hole);
    int time = 1;
    visit[R][C] = true;
    while(time < L && time_q.empty() == false){
        queue<pair<int, int>> now_q = time_q.front();
        time_q.pop();
        queue<pair<int, int>> in_q;
        while(now_q.empty()==false){
            int x = now_q.front().second;
            int y = now_q.front().first;
            now_q.pop();
            int type = map[y][x];
            for(int i=0; i<ternal[type].size(); i++){
                int new_y = y + dy[ternal[type][i]];
                int new_x = x + dx[ternal[type][i]];
                int new_type = map[new_y][new_x];
                if(new_type == 0) continue;
                for(int j=0; j<ternal[new_type].size(); j++){
                    if(abs(ternal[new_type][j]-ternal[type][i]) == 2){
                        if(visit[new_y][new_x]==true) continue;
                        in_q.push(make_pair(new_y, new_x));
                        visit[new_y][new_x] = true;
                    }
                }
            }
        }
        time_q.push(in_q);
        time++;
    }
    for(int i=0; i<N; i++){
       for(int j=0; j<M; j++){
            if(visit[i][j] == true) num_loc++;
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
        num_loc = 0;
        cin >> N >> M >> R >> C >> L;
        
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                cin >> map[i][j];
            }
        }
        find_loc();
        cout << "#" << test_case << " " << num_loc << endl;
    }
    return 0;
}
