#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define tn long long // тип n
#define tw long long // тип w и p

struct item {
	tw w;
	tw p;
	tn b;
	tn num;
	item(tn Num, tw W, tw P, tn B) { num = Num; w = W; p = P; b = B; }
	item(tn Num, tw W, tw P) { num = Num; w = W; p = P; b = 1; }
	item() { num = 0; w = 1; p = -1; b = 1; }
	bool operator== (const item& a) const {
		return w * a.p == a.w;// * p && w == a.p;
	}
	bool operator< (const item& a) const {
		return w * a.p < a.w * p;// || (w*a.p == a.w * p && w < a.p);
	}
	bool operator<= (const item& a) const {
		return (*this == a) || (*this < a);
	}
	bool operator!= (const item& a) const {
		return !(*this == a);
	}
	bool operator> (const item& a) const {
		return !(*this <= a);
	}
	bool operator>= (const item& a) const {
		return !(*this < a);
	}
};

using namespace std;

int main()
{
	tn N; // число предметов
	tw W; // вместимость рюкзака
	ifstream fin("C:/Users/maxik/Desktop/data/ks_100_0");
	fin >> N >> W;
	/*vector<tw> w(N); // вес предметов каждого вида
	vector<tw> p(N); // стоимость предметов каждого вида
	vector<tn> b(N); // количество предметов каждого вида*/
	vector<item> A; // (N);
	bool t = 1; // t = 0 --- по таблице; t = 1 --- good dinamika
	tn f = 1;
	if (t == 0) {
		tn nn = N;
		vector< vector<tn> > d(N + 1, vector<tn>(W + 1, 0));
		for (tn i = 0; i < N; i++) {
			tw p, w;
			tn b;
			fin >> p >> w;// >> b;
			if (w <= W && p > 0) {
				A.push_back(item(i + 1, w, p));
			}
			else {
				nn -= 1;
			}
		}
		N = nn;
		sort(A.begin(), A.end());
		for (tn i = 0; i < N; i++) {
			cout << A[i].p << " " << A[i].w << endl;
		}
		for (tn i = 1; i <= N; i++) {
			for (tn c = W; c >= 1; c--) {
				/*d[i][c] = d[i - 1][c]; // Рюкзак, где не обязательно каждой вещи ровно 1 штука
				for (tn l = min(A[i].b, c / A[i].w); l >= 1; l--) {
					d[i][c] = max(d[i][c], d[i - 1][c - l * A[i].w] + A[i].p * l);
				}*/
				if (c >= A[i-1].w) {
					d[i][c] = max(d[i - 1][c], d[i - 1][c - A[i-1].w] + A[i-1].p);
				}
				else {
					d[i][c] = d[i - 1][c];
				}
			}
		}
		/*for (tn i = 0; i <= N; i++) {
			for (tn j = 0; j <= W; j++) {
				cout << d[i][j] << " ";
			}
			cout << endl;
		}//*/

		cout << d[N][W] << endl;

		// Восстановление ответа

		nn = N;
		tn ww = W;
		while (nn > 0 && ww > 0 && d[nn][ww] > 0) {
			if (d[nn - 1][ww] == d[nn][ww]) {
				nn -= 1;
			}
			else {
				cout << A[nn-1].num << " " << A[nn-1].p << " " << A[nn-1].w << " ";
				tn l = 1;
				while (d[nn - 1][ww - l * A[nn-1].w] != d[nn][ww] - l * A[nn-1].p) {
					l += 1;
				}
				cout << l << endl;
				nn -= 1;
				ww -= l * A[nn].w;
			}
		}
	}
	else if (t == 1) {
		tn nn = N;
		for (tn i = 0; i < N; i++) {
			tw p, w;
			tn b;
			fin >> p >> w;// >> b;
			if (w <= W && p > 0) {
				A.push_back(item(i + 1, w, p));
			}
			else {
				nn -= 1;
			}
		}
		N = nn;
		sort(A.begin(), A.end());
		tn ans;
	again:
		vector<tn> D(W + 1, 0);
		tn t = -1;
		for (tn i = 0; i < N; i++) {
			tn c = W;
			if (c >= A[i].w && D[c - A[i].w] + A[i].p > D[c]) {
				D[c] = D[c - A[i].w] + A[i].p;
				t = i;
			}
			for (tn c = W - 1; c >= 1; c--) {
				/*D[c] = D[c]; // Рюкзак, где не обязательно каждой вещи ровно 1 штука
				for (tn l = min(A[i].b, c / A[i].w); l >= 1; l--) {
					D[c] = max(D[c], D[c - l * A[i].w] + A[i].p * l);
				}*/
				if (c >= A[i].w && D[c - A[i].w] + A[i].p > D[c]) {
					D[c] = D[c - A[i].w] + A[i].p;
				}
			}
		}
		if (f == 1) {
			cout << D[W] << endl;
			ans = D[W];
			f = 0;
		}
		if (t != -1) {
			if (ans != D[W]) {
				throw 1;
			}
			cout << A[t].num << " " << A[t].p << " " << A[t].w << endl;
			W -= A[t].w;
			ans -= A[t].p;
			N = t;
			goto again;
		}
	}
	return 0;
}
