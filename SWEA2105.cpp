//
//  main.cpp
//  SWEA2105
//
//  Created by Hwayeon on 2020/12/08.
//

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int dx[4] = {-1,1,1,-1};
int dy[4] = {1,1,-1,-1};
int max_desert;
int map[20][20];
int N;
int init_x, init_y;
vector<int> deserts;

void print_map(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << map[i][j];
        }
        cout << endl;
    }
}

void print_deserts(){
    cout << "now deserts = ";
    for(int i=0; i<deserts.size(); i++){
        cout << deserts[i] << " ";
    }
    cout << endl;
}

bool check_deserts(int dst){
    for(int i=0; i<deserts.size(); i++){
        if(deserts[i]!=dst) continue;
        return true;
    }
    return false;
}

void dfs(int dir, int x, int y, int cnt1, int cnt2){
    if(check_deserts(map[y][x]) && dir!=3){
        cout << "exist already!" << endl;
        return;
    }
    if((x<0 || x>=N) || (y<0 || y>=N)) return;
    cout << "now x=" << x << " y=" << y  << " desert=" << map[y][x] << endl;
    if(dir!=3) deserts.push_back(map[y][x]);
    int sx, sy, ox, oy;
    print_deserts();
    sx = x+dx[dir];
    sy = y+dy[dir];
    ox = x+dx[dir+1];
    oy = y+dy[dir+1];
    switch (dir) {
        case 0:
            if((sx>=0 && sx<N) && (sy>=0 && sy<N)) dfs(dir, sx, sy, cnt1+1, cnt2);
            if((ox>=0 && ox<N) && (oy>=0 && oy<N)) dfs(dir+1, ox, oy, cnt1, cnt2+1);
            break;
        case 1:
            if((sx>=0 && sx<N) && (sy>=0 && sy<N)) dfs(dir, sx, sy, cnt1, cnt2+1);
            if((ox>=0 && ox<N) && (oy>=0 && oy<N)) dfs(dir+1, ox, oy, cnt1-1, cnt2);
            break;
        case 2:
            if(cnt1>0) dfs(dir, sx, sy, cnt1-1, cnt2);
            else{
                if((ox>=0 && ox<N) && (oy>=0 && oy<N)) dfs(dir+1, ox, oy, 0, cnt2-1);
            }
        case 3:
            if(cnt2>0) dfs(dir, sx, sy, cnt1, cnt2-1);
            else{
                int num_dst = int(deserts.size());
                cout << "ok!! ";
                print_deserts();
                if((max_desert < num_dst) && (num_dst >= 4)) max_desert = num_dst;
                cout << "num_dst = " << num_dst << " max_desert = " << max_desert << endl;
            }
    }
    deserts.pop_back();
    return;
}

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        max_desert = -1;
        cin >> N;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cin >> map[i][j];
            }
        }
        print_map();
        for(int i=0; i<N-2; i++){
            for(int j=1; j<N-1; j++){
                deserts.clear();
                deserts.push_back(map[i][j]);
                print_deserts();
                //init_x = j;
                //init_y = i;
                cout << "init x=" << j << " y=" << i << endl;
                dfs(0,j+dx[0],i+dy[0],1,0);
            }
        }
        cout << "#" << test_case << " " << max_desert;
    }
    return 0;
}
