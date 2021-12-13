#include "candies.h"

// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
#define f first
#define s second
const int Q=200000;

int n, q;
ll mn[4*Q], mx[4*Q];
ll lazy[4*Q];
vector<int> start[Q], en[Q];

void push(int x, int lx, int rx){
    if(rx-lx==1) return;
    lazy[2*x+1]+=lazy[x];
    lazy[2*x+2]+=lazy[x];
    mn[2*x+1]+=lazy[x];
    mx[2*x+1]+=lazy[x];
    mn[2*x+2]+=lazy[x];
    mx[2*x+2]+=lazy[x];
    lazy[x]=0;
}

void upd(int l, int r, int v, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r){
        lazy[x]+=v;
        mn[x]+=v;
        mx[x]+=v;   
        return;
    }
    if(lx>=r || rx<=l) return;
    int m=(lx+rx)/2;
    upd(l, r, v, 2*x+1, lx,m ); upd(l, r, v, 2*x+2, m, rx);
    mn[x]=min(mn[2*x+1], mn[2*x+2]);
    mx[x]=max(mx[2*x+1], mx[2*x+2]);
} 

void upd(int l, int r, int v){
    upd(l, r, v, 0, 0, q);
}

pll get_range(int l, int r, int x, int lx, int rx){
    push(x, lx, rx);
    if(lx>=l && rx<=r) return {mn[x], mx[x]};
    if(lx>=r || rx<=l) return {1e18, -1e18};
    int m=(lx+rx)/2;
    pll a=get_range(l, r, 2*x+1, lx, m);
    pll b=get_range(l, r, 2*x+2, m, rx);
    return {min(a.f, b.f), max(a.s, b.s)};
}  

pll get_range(int l, int r){
    if(l>=0) return get_range(l, r, 0, 0, q);
    pll p=get_range(0, r, 0, 0, q);
    return {min(0LL, p.f), max(0LL, p.s)};
}

ll st(int i){
    if(i==-1) return 0;
    return get_range(i, i+1).f;
}

std::vector<int> distribute_candies(std::vector<int> c, std::vector<int> l,
                                    std::vector<int> r, std::vector<int> v) {
    n = c.size();
    q=l.size();
    std::vector<int> s(n);
    for(int i=0; i<q; i++){
        start[l[i]].push_back(i);
        en[r[i]].push_back(i);
    }

    for(int i=0; i<n; i++){
        for(int t:start[i]){
            upd(t, q, v[t]);
        }
        pll p=get_range(-1, q);
        if(p.s-p.f<=c[i]){
            s[i]=(st(q-1))-p.f;
        }
        else{
            int t=-1;
            for(int k=q; k; k/=2){
                pll p;
                while(t+k<q && (p=get_range(t+k, q)).s-p.f>c[i]) t+=k;
            }
            p=get_range(t, q);
            if(st(t)==p.s){
                s[i]=st(q-1)-p.f;
            }
            else{
                s[i]=(st(q-1)-(p.s-c[i]));
            }
        }
        
        for(int t:en[i]){
            upd(t, q, -v[t]);
        }
    }
    return s;
}
// range add
// range min max

// why did I believe
// I had to dream
