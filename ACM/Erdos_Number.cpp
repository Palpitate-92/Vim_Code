#include<bits/stdc++.h>
using namespace std;
const unsigned MAX_LEN=20;
const unsigned HASH_SCALE=4e5;
struct Node{
	char name[MAX_LEN+1];
	int dist;
	Node *next;//记录冲突结点
        list<Node*> neib;//记录合作者结点
	Node(const char _name[], Node *_next):dist(-1),next(_next){
		strcpy(name,_name);
	}
};
Node* hashTable[HASH_SCALE];
unsigned ELFhash(const char* key){
	unsigned h=0;
	while(*key != '\0'){
		h=(h<<4)+*key++;
		unsigned g=h&0xf0000000;
		if(g)
			h ^=g>>24;
		h &= ~g;
	}
	return h % HASH_SCALE;
}
Node* enhash(const char name[]){
	unsigned h = ELFhash(name);
	Node *p=hashTable[h];
	while(p != NULL && strcmp(p -> name, name) !=0)
		p = p -> next;
	return p ? p : hashTable[h] = new Node(name, hashTable[h]);
}
void get_coauthor_activities(){
	//读取数据，添加合作者
	int N;
	scanf("%d", &N);
	while(N--){
		char name1[MAX_LEN + 1],name2[MAX_LEN + 1];
		Node *q, *p;
		scanf("%s %s", name1, name2);
		p = enhash(name1);
		q = enhash(name2);
		p -> neib.push_back(q);
		q -> neib.push_back(p);
	}
}
void bfs(){
	queue<Node*> Q;
	Q.push(enhash("Erdos"));
	Q.front() -> dist = 0;
	while(!Q.empty()){
		typedef list<Node*>::iterator IP;
		int d = Q.front() -> dist;
		list<Node*>& L = Q.front() -> neib;
		Q.pop();
		for(IP p = L.begin(); p != L.end(); p++){
			if((*p) -> dist == -1){
				Q.push(*p);
				(*p) -> dist = d + 1;
			}
		}
	}
}
void do_query(){
	int M;
	scanf("%d", &M);
	while(M--){
		char name[MAX_LEN + 1];
		int d;
		scanf("%s", name);
		d = enhash(name) -> dist;
		if(d != -1)
			printf("%d\n", d);
		else
			printf("infinity\n");
	}
}
int main(){
	get_coauthor_activities();
	bfs();
	do_query();
	return 0;
}
