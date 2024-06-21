// https://cses.fi/problemset/task/1068/

#include <bits/stdc++.h>
using namespace std;
 
long long n;
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
 
	cin>>n;
 
	cout<<n<<" ";
 
	while(n!=1) {
		if(n%2==0) {
			n=n/2;
			cout<<n<<" ";
		}
		else {
			n=(n*3)+1;
			cout<<n<<" ";
		}
	}
	cout<<"\n";
}
