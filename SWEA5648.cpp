//
//  main.cpp
//  SWEA5648
//
//  Created by Hwayeon on 2021/10/21.
//

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int N;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int visit[4001][4001] = {0, };

struct Atom{
    bool gone = false;
    int x = -1;
    int y = -1;
    int d = -1;
    int K = 0;
};
vector<Atom> atoms;
int energy = 0;

void move_atom(){
    while(true){
        bool check = true;
        for(int i=0; i<atoms.size(); i++){
            if(!atoms[i].gone){
                check = false;
                break;
            }
        }
        if(check) break;
        
        for(int i=0; i<atoms.size(); i++){
            int nx = atoms[i].x + dx[atoms[i].d];
            int ny = atoms[i].y + dy[atoms[i].d];
            if(nx < 0 || nx > 4000 || ny < 0 || ny > 4000)
                atoms[i].gone = true;
            else if(!atoms[i].gone){
                visit[ny][nx] ++;
                atoms[i].x = nx;
                atoms[i].y = ny;
            }
        }
        
        for(int i=0; i<atoms.size(); i++){
            if(visit[atoms[i].y][atoms[i].x] > 1) {
                for(int j=0; j<atoms.size(); j++){
                    if(!atoms[j].gone && atoms[i].x == atoms[j].x && atoms[i].y == atoms[j].y){
                        energy += atoms[j].K;
                        atoms[j].gone = true;
                    }
                }
            }
            visit[atoms[i].y][atoms[i].x] = 0;
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        energy = 0;
        atoms.clear();
        cin >> N;
        for(int i=0; i<N; i++){
            Atom atom;
            cin >> atom.x >> atom.y >> atom.d >> atom.K;
            atom.x = 2*(atom.x+1000);
            atom.y = 2*(atom.y+1000);
            atom.gone = false;
            atoms.push_back(atom);
        }
        move_atom();
        
        cout << "#" << test_case << " " << energy << endl;
    }
    return 0;
}
