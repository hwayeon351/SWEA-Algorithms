//
//  main.cpp
//  SWEA4013
//
//  Created by Hwayeon on 2021/10/15.
//

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int magnet[5][8] = {0, };
int K;
vector<pair<int, int>> cmds;
int answer = 0;
int dir, num;

void rotate_magnet(int n, int d){
    int temp = -1;
    switch(d){
        case 1:
            temp = magnet[n][7];
            for(int i=7; i>=1; i--){
                magnet[n][i] = magnet[n][i-1];
            }
            magnet[n][0] = temp;
            break;
            
        case -1:
            temp = magnet[n][0];
            for(int i=0; i<=6; i++){
                magnet[n][i] = magnet[n][i+1];
            }
            magnet[n][7] = temp;
            break;
    }
}

void play_cmds(){
    for(int i=0; i<K; i++){
        num = cmds[i].first;
        dir = cmds[i].second;
        switch(num){
            case 1:
                if(magnet[1][2] != magnet[2][6]){
                    if(magnet[2][2] != magnet[3][6]){
                        if(magnet[3][2] != magnet[4][6]){
                            rotate_magnet(4, -dir);
                        }
                        rotate_magnet(3, dir);
                    }
                    rotate_magnet(2, -dir);
                }
                rotate_magnet(1, dir);
                break;
                
            case 2:
                if(magnet[2][6] != magnet[1][2]){
                    rotate_magnet(1, -dir);
                }
                if(magnet[3][6] != magnet[2][2]){
                    if(magnet[4][6] != magnet[3][2]){
                        rotate_magnet(4, dir);
                    }
                    rotate_magnet(3, -dir);
                }
                rotate_magnet(2, dir);
                break;
                
            case 3:
                if(magnet[3][2] != magnet[4][6]){
                    rotate_magnet(4, -dir);
                }
                if(magnet[3][6] != magnet[2][2]){
                    if(magnet[1][2] != magnet[2][6]){
                        rotate_magnet(1, dir);
                    }
                    rotate_magnet(2, -dir);
                }
                rotate_magnet(3, dir);
                break;
                
            case 4:
                if(magnet[4][6] != magnet[3][2]){
                    if(magnet[3][6] != magnet[2][2]){
                        if(magnet[2][6] != magnet[1][2]){
                            rotate_magnet(1, -dir);
                        }
                        rotate_magnet(2, dir);
                    }
                    rotate_magnet(3, -dir);
                }
                rotate_magnet(4, dir);
                break;
        }
    }
}

int main(int argc, const char * argv[]) {
    int test_case;
    int T, num, dir;
    cin >> T;
    for(test_case=1; test_case<=T; ++test_case){
        cmds.clear();
        answer = 0;
        cin >> K;
        for(int i=1; i<5; i++){
            for(int j=0; j<8; j++){
                cin >> magnet[i][j];
            }
        }
        for(int i=0; i<K; i++){
            cin >> num >> dir;
            cmds.push_back({num, dir});
        }
        play_cmds();
        for(int i=1; i<5; i++){
            if(magnet[i][0]) answer += pow(2, i-1);
        }
        cout << "#" << test_case << " " << answer << endl;
    }
    return 0;
}
