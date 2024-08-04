/*
*  Author : Akash
*/
#include <bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(0);
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define ll long long
#define forauto(x) for(auto it: x)
#define inv(a) for(auto& it: a) cin>>it;
#define nl "\n"
const ll MOD = 1e9+7;
using namespace std;

struct Node {
   ll open, close, full;
   Node(ll _open = 0, ll _close = 0, ll _full = 0) {
      open = _open;
      close = _close;
      full = _full;
   }
};

class SGTree {
public:
   vector<Node> seg;
   SGTree(ll n) {
      seg.resize(4 * n + 1);
   }

   Node merge(Node left, Node right) {
      Node ans;
      ll matches = min(left.open, right.close);
      ans.full = left.full + right.full + matches;
      ans.open = left.open + right.open - matches;
      ans.close = left.close + right.close - matches;
      return ans;
   }

   void build(ll ind, ll low, ll high, string& s) {
      if (low == high) {
         seg[ind] = Node(s[low] == '(', s[low] == ')', 0);
         return;
      }
      ll mid = (low + high) / 2;
      build(2 * ind + 1, low, mid, s);
      build(2 * ind + 2, mid + 1, high, s);

      seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
   }

   Node query(ll ind, ll low, ll high, ll l, ll r) {
      if (high < l || r < low) {
         return Node();
      }
      if (l <= low && high <= r) {
         return seg[ind];
      }

      ll mid = (low + high) / 2;
      Node left = query(2 * ind + 1, low, mid, l, r);
      Node right = query(2 * ind + 2, mid + 1, high, l, r);

      return merge(left, right);
   }
};

void driver() {
   string s;  
   cin >> s;
   ll n = s.size();

   SGTree sg(n);
   sg.build(0, 0, n - 1, s);

   ll q; 
   cin >> q;
   while (q--) {
      ll l, r;
      cin >> l >> r;
      l--, r--;
      cout << sg.query(0, 0, n - 1, l, r).full * 2 << nl;
   }
}

int main() {
   IOS;
   cin.tie(0);

   #ifndef ONLINE_JUDGE
      freopen("Input.txt", "r", stdin);
      freopen("Output.txt", "w", stdout);
   #endif

   driver();
   return 0;
}