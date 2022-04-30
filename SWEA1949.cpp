#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int N, K;
int map[8][8] = { 0, };
int visit[8][8] = { 0, };
vector<pair<int, int> > highest;

int dr[4] = { 0, -1, 0, 1 };
int dc[4] = { -1, 0, 1, 0 };
int answer = 0;

void init() {
	cin >> N >> K;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
	answer = 0;
}

void get_highest() {
	highest.clear();
	int max_high = -5;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (max_high < map[r][c]) {
				max_high = map[r][c];
				highest.clear();
				highest.push_back({ r, c });
			}
			else if (max_high == map[r][c]) {
				highest.push_back({ r, c });
			}
		}
	}
}

void get_long_road(int r, int c, int cnt, int high) {
	if (answer < cnt) answer = cnt;

	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d];
		int nc = c + dc[d];
		if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
		if (visit[nr][nc]) continue;
		if (map[nr][nc] >= high) continue;
		visit[nr][nc] = 1;
		get_long_road(nr, nc, cnt + 1, map[nr][nc]);
		visit[nr][nc] = 0;
	}
}

void cut_road() {
	for (int k = 0; k <= K; k++) {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				map[r][c] -= k;
				for (int i = 0; i < highest.size(); i++) {
					visit[highest[i].first][highest[i].second] = 1;
					get_long_road(highest[i].first, highest[i].second, 1, map[highest[i].first][highest[i].second]);
					visit[highest[i].first][highest[i].second] = 0;
				}
				
				map[r][c] += k;
			}
		}
	}


}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		init();
		get_highest();
		cut_road();

		cout << "#" << test_case << " " << answer << "\n";
	}
	return 0;
}
