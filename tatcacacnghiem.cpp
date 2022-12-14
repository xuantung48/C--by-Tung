#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

vector < vector < int > > solve(int n, int k){
    // Dieu kien dung
    if (n == 1) return vector < vector < int > >(1, vector < int >(1, k)); // [[k]] (1*1)
    if (k == 0) return vector < vector < int > >(1, vector < int >(n, 0)); // [[0,0,0,0, ..]] (1*n)

    // Cong thuc de quy
    vector < vector < int > > r;
    for (int i= k; i>=0 ; i--){
        vector < vector < int > > t= solve(n-1, k-i); //(m, n-1)
        //vector: a+b
        for (int j= 0;j < t.size(); j++){
            t[j].push_back(i); // n bien 
            r.push_back(t[j]);
        }
    }
    return r;
}

int main(){
    int N, K;
    cin>>N>>K;
    vector < vector < int > > ans= solve(N,K);
    for(int i=0 ;i< ans.size(); i++){
        for (int j= N-1; j>= 0; j--)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }

    return 0;

}