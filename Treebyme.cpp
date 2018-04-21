#include<stdio.h>
#include<conio.h>
#include<stack>

using namespace std;

struct Node{
    int id;
    Node *leftmostchild;
    Node *rightsibling;
};

Node *root;
stack<Node*> way;
//------------------------------
Node *makenode(int x){
    Node *p = new Node;
    p->id=x;
    p->leftmostchild = NULL;
    p->rightsibling = NULL;
    return p;
}
//-------------------------------
Node *findnode(Node*r,int x){
    if(r==NULL) return NULL;
    if(r->id==x) return r;
    if(r->leftmostchild==NULL) return NULL;
    Node *p=r->leftmostchild;
    while(p!=NULL){
        Node*h=findnode(p,x);
        if(h!=NULL) return h;
        p=p->rightsibling;
    }
}
//--------------------------------
void insertchildlast(Node *p,int x){
    if(p==NULL){
        printf("\n ERRO");
        return;
    }
    if(p->leftmostchild==NULL){
        p->leftmostchild = makenode(x);
        return;
    }
    Node *q=p->leftmostchild;
    while(q->rightsibling!=NULL)
        q=q->rightsibling;
    q->rightsibling = makenode(x);
    return;
}
//-----------------------------------
void printftree(Node *r){
    if(r==NULL){
        printf("\n ERRO");
        return;
    }
    printf("%d \n",r->id);
    if(r->leftmostchild==NULL)
        return;
    Node *p=r->leftmostchild;
    while(p!=NULL){
        printftree(p);
        p=p->rightsibling;
    }
}
//------------------------------------
int countnode(Node *r){
    if(r==NULL){
        printf("\n ERRO");
        return 0;
    }
    if(r->leftmostchild==NULL) return 1;
    int c=1;
    Node *p=r->leftmostchild;
    while(p!=NULL){
        c += countnode(p);
        p=p->rightsibling;
    }
    return c;
}
//------------------------------------
int countleaves(Node *r){
    if(r==NULL){
        printf("\n ERRO");
        return 0;
    }
    if(r->leftmostchild==NULL) return 1;
    int m=0;
    Node *p=r->leftmostchild;
    while(p!=NULL){
        m += countleaves(p);
        p=p->rightsibling;
    }
    return m;
}
//------------------------------------
int heigh(Node *p){
    int m=0;
    if(p==NULL) {
        printf("\n ERRO");
        return 0;
    }
    if(p->leftmostchild==NULL) return 0;
    Node *q=p->leftmostchild;
    while(q!=NULL){
        int h = 1 + heigh(q);
        if(h>m) m=h;
        q=q->rightsibling;
    }
    return m;
}
//------------------------------------
int depth(Node *r,Node *p){
    if(p==NULL||r==NULL){
        printf("\n ERRO");
        return -1;
    }
    if(r==p) return 0;
    if(r->leftmostchild==NULL) return -1;
    Node *q=r->leftmostchild;
    while(q!=NULL){
        int d = depth(q,p);
        if(d>=0) return d+1;
        q=q->rightsibling;
    }
return d;
}
//------------------------------------
int findpath(Node*r,Node*p){
    if(r==NULL||p==NULL) return 0;
    if(p==r){
        way.push(p);
        return 1;
    }
    if(r->leftmostchild==NULL) return 0;
    Node*q=r->leftmostchild;
    while(q!=NULL){
        int tmp=findpath(q,p);
        if(tmp){
            way.push(r);
            return 1;
        }
        q=q->rightsibling;
    }
}
//------------------------------------
void printfpath(){
    while(!way.empty()){
        Node*p=way.top();
        printf("%3d",p->id);
        way.pop();
    }
}
//====================================
int main(){
    int n,m;
    root = makenode(10);
    insertchildlast(root,1);
    insertchildlast(root,2);
    insertchildlast(root,3);
    Node *p=findnode(root,1);
    insertchildlast(p,4);
    insertchildlast(p,5);
    insertchildlast(p,6);
    p=findnode(root,2);
    insertchildlast(p,7);
    insertchildlast(p,8);
    p=findnode(root,7);
    insertchildlast(p,9);
    insertchildlast(p,15);
    p=findnode(root,9);
    insertchildlast(p,11);
    p=findnode(root,11);
    insertchildlast(p,16);
    printftree(root);
    printf("\n THE NUMBER OF NODE  : %d",countnode(root));
    printf("\n THE NUMBER OF LEAVES: %d",countleaves(root));
    printf("\n WHAT IS THE NODE WHICH YOU WANT TO SEE THE HEIGH:");
    scanf("%d",&n);
    p=findnode(root,n);
    printf("\n THE HEIGH OF %d      : %d",n,heigh(p));
    //printf("\n WHAT IS THE NODE WHICH YOU WANT TO SEE THE DEPTH:");
    //scanf("%d",&m);
    p=findnode(root,11);
    //printf("\n%d",p->id);
    //printf("\n THE DEPTH OF %d      : %d",9,depth(root,p));
    findpath(root,p);
    printfpath();
}
