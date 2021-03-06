#include <cstdio>
#include <deque>
int l, r;
int n, m;
int young[2][2] = { {0,1},{0,-1} };
char map[1001][1001];
const int SIZE = (1 << 20);
char buf[SIZE];
int p = SIZE;
inline char getcha() {
	if (p == SIZE) {
		fread(buf, 1, SIZE, stdin);
		p = 0;
	}
	return buf[p++];
}
inline void readint(int& x) {
	x = 0;
	int temp = getcha();
	while (temp<'0' || temp>'9') {
		temp = getcha();
	}
	while (temp >= '0' && temp <= '9') {
		x = x * 10 + (temp - '0');
		temp = getcha();
	}
}
inline void readoneint(char& x) {
	int temp = getcha();
	while (temp<'0' || temp>'9') {
		temp = getcha();
	}
	x = temp - '0';
}

struct state {
	int x, y;
	int l, r;
};
std::deque<state> q;
int bfs(int y, int x) {
	if (y == -1) {
		return 0;
	}
	map[y][x] = 3;
	q.push_back({ x,y,l,r });
	int ret = 1;
	while (!q.empty()) {
		auto p = q.front();
		q.pop_front();
		int nx, ny;
		for (int i = 0; i < 2; i++) {
			nx = p.x + young[i][0];
			ny = p.y + young[i][1];
			if (!(nx < 0 || ny < 0 || nx >= m || ny >= n)) {
				if (map[ny][nx] == 0) {
					map[ny][nx] = 3;
					ret++;
					q.push_front({ nx,ny,p.l,p.r });
				}
			}
		}
		if (p.l) {
			nx = p.x - 1;
			ny = p.y;
			if (!(nx < 0 || ny < 0 || nx >= m || ny >= n)) {
				if (map[ny][nx] == 0) {
					map[ny][nx] = 3;
					ret++;
					q.push_back({ nx,ny,p.l - 1,p.r });
				}
			}
		}
		if (p.r) {
			nx = p.x + 1;
			ny = p.y;
			if (!(nx < 0 || ny < 0 || nx >= m || ny >= n)) {
				if (map[ny][nx] == 0) {
					map[ny][nx] = 3;
					ret++;
					q.push_back({ nx,ny,p.l,p.r - 1 });
				}
			}
		}
	}
	return ret;
}

int main() {
	readint(n);
	readint(m);
	readint(l);
	readint(r);
	int pos[2] = { -1,-1 };
	for (register int i = 0; i < n; i++) {
		for (register int j = 0; j < m; j++) {
			readoneint(map[i][j]);
			if (map[i][j] == 2) {
				pos[0] = i;
				pos[1] = j;
			}
		}
	}
	printf("%d", bfs(pos[0], pos[1]));
	return 0;
}