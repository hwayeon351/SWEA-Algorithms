#include <iostream>
#include <cstring>
using namespace std;

int N;
int desert[20][20] = { 0, };
int visit[101] = { 0, };
int dr[4] = { 1, 1, -1, -1 };
int dc[4] = { -1, 1, 1, -1 };

int answer = -1;

void init() {
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> desert[r][c];
		}
	}
	answer = -1;
}

void go_cafe() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			for (int d1 = 1; d1 <= N - 2; d1++) {
				for (int d2 = 1; d2 <= N - 2; d2++) {
					memset(visit, 0, sizeof(visit));
					int nr = r;
					int nc = c;
					int cnt = 1;
					visit[desert[nr][nc]] = 1;
					bool check = true;

					for (int d = 0; d < d1; d++) {
						nr += dr[0];
						nc += dc[0];
						if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[desert[nr][nc]]) {
							check = false;
							break;
						}
						cnt++;
						visit[desert[nr][nc]] = 1;
					}
					if (!check) continue;

					for (int d = 0; d < d2; d++) {
						nr += dr[1];
						nc += dc[1];
						if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[desert[nr][nc]]) {
							check = false;
							break;
						}
						cnt++;
						visit[desert[nr][nc]] = 1;
					}
					if (!check) continue;

					for (int d = 0; d < d1; d++) {
						nr += dr[2];
						nc += dc[2];
						if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[desert[nr][nc]]) {
							check = false;
							break;
						}
						cnt++;
						visit[desert[nr][nc]] = 1;
					}
					if (!check) continue;

					for (int d = 0; d < d2-1; d++) {
						nr += dr[3];
						nc += dc[3];
						if (nr < 0 || nr >= N || nc < 0 || nc >= N || visit[desert[nr][nc]]) {
							check = false;
							break;
						}
						cnt++;
						visit[desert[nr][nc]] = 1;
					}
					if (!check) continue;

					if (answer == -1 || answer < cnt) answer = cnt;
				}
			}
		}
	}
}

int main()
{
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++) {
		init();
		go_cafe();

		cout << "#" << test_case << " " << answer << "\n";
	}

	return 0;
}
