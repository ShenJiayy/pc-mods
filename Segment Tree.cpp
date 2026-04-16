#include <bits/stdc++.h>
using namespace std;
#define int long long
namespace SegTree {
	struct UpdateOne {
		int size;
		vector<int> a, s;
		void build(int id, int l, int r) {
			if (l == r) {
				s[id] = a[l];
				return ;
			}
			int mid = l + r >> 1;
			build(id * 2, l, mid);
			build(id * 2 + 1, mid + 1, r);
			update(id);
		}
		void init() {
			size = 0;
			a.clear(), s.clear();
		}
		void init(int n, int _a[]) {
			size = n;
			a.resize(size + 5, 0);
			s.resize(size * 4 + 5, 0);
			for (int i = 1; i <= n; i ++)
				a[i] = _a[i];
			build(1, 1, n);
		}
		void init(vector<int> _a) {
			size = _a.size();
			a.resize(size + 5, 0);
			for (int i = 0; i < _a.size(); i ++)
				a[i + 1] = _a[i];
			s.resize(size * 4 + 5, 0);
			build(1, 1, size);
		}
		UpdateOne() { init(); }
		UpdateOne(int n, int _a[]) { init(n, _a); }
		UpdateOne(vector<int> _a) { init(_a); }
		void resize(int _size) {
			size = _size;
			a.resize(size + 5, 0);
			s.resize(size * 4 + 5, 0);
		}
		void update(int pt) {
			s[pt] = s[pt * 2] + s[pt * 2 + 1];
		}
		void addOne(int id, int opt, int pt, int l, int r) {
			if (l == r) {
				s[pt] += opt;
				return ;
			}
			int mid = l + r >> 1;
			if (id <= mid)
				addOne(id, opt, pt * 2, l, mid);
			else
				addOne(id, opt, pt * 2 + 1, mid + 1, r);
			update(pt);
		}
		int queryBlock(int ql, int qr, int pt, int l, int r) {
			if (ql <= l && qr >= r)
				return s[pt];
			int res = 0, mid = l + r >> 1;
			if (ql <= mid)
				res += queryBlock(ql, qr, pt * 2, l, mid);
			if (qr > mid)
				res += queryBlock(ql, qr, pt * 2 + 1, mid + 1, r);
			return res;
		}
	};
	struct UpdateBlock {
		struct Node {
			int s, tag;
			Node () {
				s = tag = 0;
			}
		};
		int size;
		vector<int> a;
		vector<Node> s;
		void build(int id, int l, int r) {
			if (l == r) {
				s[id].s = a[l];
				return ;
			}
			int mid = l + r >> 1;
			build(id * 2, l, mid);
			build(id * 2 + 1, mid + 1, r);
			s[id].s = s[id * 2].s + s[id * 2 + 1].s;
			s[id].tag = 0;
		}
		void init() {
			size = 0;
			a.clear(), s.clear();
		}
		void init(int n, int _a[]) {
			size = n;
			a.resize(size + 5, 0);
			s.resize(size * 4 + 5);
			for (int i = 1; i <= n; i ++)
				a[i] = _a[i];
			build(1, 1, n);
		}
		void init(vector<int> _a) {
			size = _a.size();
			a.resize(size + 5, 0);
			for (int i = 0; i < _a.size(); i ++)
				a[i + 1] = _a[i];
			s.resize(size * 4 + 5);
			build(1, 1, size);
		}
		UpdateBlock() { init(); }
		UpdateBlock(int n, int _a[]) { init(n, _a); }
		UpdateBlock(vector<int> _a) { init(_a); }
		void resize(int _size) {
			size = _size;
			a.resize(size + 5, 0);
			s.resize(size * 4 + 5);
		}
		void pushdown(int pt, int l, int r) {
			int mid = l + r >> 1;
			s[pt * 2].s += s[pt].tag * (mid - l + 1);
			s[pt * 2].tag += s[pt].tag;
			s[pt * 2 + 1].s += s[pt].tag * (r - mid);
			s[pt * 2 + 1].tag += s[pt].tag;
			s[pt].tag = 0; 
		}
		void addBlock(int ql, int qr, int opt, int pt, int l, int r) {
			if (ql <= l && qr >= r) {
				s[pt].s += opt * (r - l + 1);
				s[pt].tag += opt;
				return ;
			}
			pushdown(pt, l, r); 
			int res = 0, mid = l + r >> 1;
			if (ql <= mid)
				addBlock(ql, qr, opt, pt * 2, l, mid);
			if (qr > mid)
				addBlock(ql, qr, opt, pt * 2 + 1, mid + 1, r);
			s[pt].s = s[pt * 2].s + s[pt * 2 + 1].s;
		}
		int queryBlock(int ql, int qr, int pt, int l, int r) {
			if (ql <= l && qr >= r)
				return s[pt].s;
			pushdown(pt, l, r); 
			int res = 0, mid = l + r >> 1;
			if (ql <= mid)
				res += queryBlock(ql, qr, pt * 2, l, mid);
			if (qr > mid)
				res += queryBlock(ql, qr, pt * 2 + 1, mid + 1, r);
			return res;
		}
	};
}
signed main() {
    SegTree::UpdateBlock x;
	int a[] = {0, 1, 2, 3, 4};
	x.init(4, a);
	cout << x.queryBlock(1, 4, 1, 1, 4);
	x.addBlock(2, 2, 3, 1, 1, 4);
	cout << x.queryBlock(1, 4, 1, 1, 4);
    return 0;
}

