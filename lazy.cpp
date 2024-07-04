#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define  int long long
#define  endl '\n'
const int N =  1e5 ,oo= INT_MAX;
struct segment_tree {

private:
    /*  struct node{


          node(){};
          node(int ans ) : ans(ans) {}
      };*/
    int size  ;  vector<int >seg,lazy;
    int merge(int  l, int  r) {
        return  l+r ;
    }

  /*  void Build(int ind, int l, int r,vector<int>&arr) {
        if (l == r) {
            if(l<arr.size()) {
                seg[ind] = arr[l] ;
            }
            return;

        }
        int mid = l + (r - l) / 2;
        int lf = ind * 2 + 1;
        int rt = ind * 2 + 2;
        Build(lf, l, mid,arr);
        Build(rt, mid + 1, r,arr);
        seg[ind] = merge(seg[lf], seg[rt]);
    }*/
    void propegate(int l,int r,int node)
    {
        if(lazy[node]==0)return;
        seg[node]+=lazy[node]*(r-l+1);
        if(l!=r)
        {
            lazy[2*node+1]+=lazy[node];
            lazy[2*node+2]+=lazy[node];
        }
        lazy[node]=0;
    }
    void Update(int lq ,int rq ,int node ,int l ,int r  ) {
        propegate(l,r,node);
        if(l>rq||r<lq)
            return ;

        if(l>=lq&&r<=rq) {
            lazy[node] += 1;
            propegate(l,r,node);
            return;
        }

        int mid = l + (r - l) / 2;
        int lf = node * 2 + 1;
        int rt = node  * 2 + 2;
        Update(lq,rq,lf,l,mid);
        Update(lq,rq,rt,mid+1,r);
        seg[node] = seg[lf]+seg[rt];

    }

   /* int getAns1(int l ,int r  , int node,  int idx) {
        propegate(l,r,node);
        if(l==r)
        {
            return  seg[node];
        }

        int mid = l + (r - l) / 2;
        int lf = node * 2 + 1;
        int rt = node  * 2 + 2;
       if(idx<=mid)
           return merge(getAns1(l,mid,lf,idx),seg[node]);

        return merge(getAns1(mid+1,r,rt,idx),seg[node]);
    }*/

    int getAns(int lq ,int rq  ,  int node, int l, int r) {
        propegate(l,r,node);
        if(l>rq||r<lq)
            return  0 ;
        if(l>=lq&&r<=rq)
            return seg[node];

        int mid = l + (r - l) / 2;

        int lf = node * 2 + 1;
        int rt = node * 2 + 2;
       return  merge(getAns(lq,rq, lf, l, mid),getAns(lq,rq,rt, mid + 1, r));

    }
public:
    segment_tree(vector<int>&arr)
    {
        size = 1 ;

        while(size<arr.size())size*=2;

        seg = vector<int >(size*2,0);
        lazy=vector<int>(size*2,0);


    }
    void update(int l ,int r)
    {
        Update(l ,r ,0,0,size-1);
    }
    /*int get(int idx )
    {
        return  getAns1( 0 ,size-1, 0,idx);
    }*/
    int get2(int l ,int r )
    {
        return getAns(l,r ,0,0,size-1);
    }


};
signed  main() {
    int n ,q; cin>>n>>q;
  vector<int>v(n);
 segment_tree s (v);
    while (q--)
    {
        int qq ;cin>>qq;
        if(qq==0)
        {
            int l ,r;cin>>l>>r;
            l--;
            r--;
            s.update(l,r);

        }
        else
        {

            int l ,r; cin>>l>>r;
            l--,r--;
            cout<<s.get2(l,r)<<endl;
        }
    }

}
