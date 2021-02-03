//
//  main.cpp
//  SWEA5658
//
//  Created by Hwayeon on 2021/02/02.
//

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
using namespace std;

int N, K;
vector<char> _lock;
vector<int> passwords;

void get_passwords(){
    int cnt = _lock.size()/4;
    string new_pass = "0x";
    for(int i=0; i<_lock.size(); i++){
        int idx = i % cnt;
        new_pass += _lock[i];
        if (idx == cnt-1){
            bool check = true;
            for(int j=0; j<passwords.size(); j++){
                if(stoi(new_pass, nullptr, 16) == passwords[j]){
                    check = false;
                    break;
                }
            }
            if(check) passwords.push_back(stoi(new_pass, nullptr, 16));
            new_pass = "0x";
        }
    }
}

void rotate_lock(){   
    get_passwords();
    for(int i=0; i<N/4; i++){
        char temp;
        char before = _lock[0];
        _lock[0] = _lock[_lock.size()-1];
        for(int j=1; j<_lock.size(); j++){
            temp = _lock[j];
            _lock[j] = before;
            before = temp;
        }
        get_passwords();
    }
    sort(passwords.begin(), passwords.end(), greater<int>());
}

int main(int argc, char** argv) {
    int test_case;
    int T;
    cin>>T;
    for(test_case = 1; test_case <= T; ++test_case)
    {
        passwords.clear();
        _lock.clear();
        cin >> N >> K;
        for(int i=0; i<N; i++){
            char c;
            cin >> c;
            _lock.push_back(c);
        }
        rotate_lock();
        cout  << "#" << test_case << " " << passwords[K-1] << endl;
    }
    
    return 0;
}
