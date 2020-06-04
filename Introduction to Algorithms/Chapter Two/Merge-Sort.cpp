#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e7;
int a[MAXN];
int a1[MAXN], a2[MAXN];
void Merge(int p, int q, int r){
	int i, j;
	int n1 = q-p+1;
	int n2 = r-q;
	for(i = 0; i < n1; i++)
		a1[i] = a[p+i];
	for(i = 0; i < n2; i++)
		a2[i] = a[q+1+i];
	i = j = 0;
	for(int k = p; k <= r; k++){
		if(j == n2 || (i < n1 && a1[i] < a2[j]))
			a[k] = a1[i++];
		else
			a[k] = a2[j++];
	}
}
void Merge_Sort(int p, int r){
	if(p < r){
		int q = (p+r)>>1;
		Merge_Sort(p, q);
		Merge_Sort(q+1, r);
		Merge(p, q, r);
	}
}
int main(){
	int N;
	scanf("%d", &N);
	while(N--){
		int n;
		scanf("%d", &n);
		memset(a, 0, sizeof(a));
		for(int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		Merge_Sort(0, n-1);
		for(int i = 0; i < n; i++)
			printf("%d ", a[i]);
		puts("");
	}
	return 0;
}
