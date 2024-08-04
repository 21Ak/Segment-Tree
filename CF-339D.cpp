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

class SGTree{  
public:
   vector<ll> seg;
   SGTree(ll n){
      seg.resize(4*n+1);
   }
   void fill(ll ind, ll alt){
      if(alt==1){
         seg[ind] = seg[2*ind+1] | seg[2*ind+2];
      }
      else{
         seg[ind] = seg[2*ind+1] ^ seg[2*ind+2];
      }
   }
   void build(ll ind, ll low, ll high, ll alt, vector<ll>& arr){
      if(low==high){
         seg[ind] = arr[low];
         return;
      }
      ll mid = (low+high)/2;
      build(2*ind+1, low, mid, 1-alt, arr);
      build(2*ind+2, mid+1, high, 1-alt, arr);

      fill(ind,alt);
   }
   void update(ll ind, ll low, ll high, ll i, ll val, ll alt){
      if(low==high){
         seg[ind] = val;
         return;
      }
      ll mid = (low+high)/2;
      if(i<=mid){
         update(2*ind+1, low, mid, i, val, 1-alt);
      }
      else{
         update(2*ind+2, mid+1, high, i, val, 1-alt);
      }
      fill(ind,alt);  
   }
};

void driver(){
   ll n,m; cin>>n>>m; 
   ll sz = pow(2,n);
   vector<ll> arr(sz);
   inv(arr);

   SGTree sg1(sz);
   sg1.build(0,0,sz-1,n%2,arr);

   while(m--){
      ll i, val; cin>>i>>val;
      arr[i-1] = val;
      sg1.update(0,0,sz-1,i-1,val,n%2);
      cout<<sg1.seg[0]<<nl;
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