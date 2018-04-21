#include<iostream>
#include<set>
#include<map>
#include<queue>
#include<fstream>
#include<stack>

using namespace std;

int t; //<time visit vertices of the graph>
set< int > Vertices; //< set of vertices of the graph>
map< int, set<int> > Adjacent_Vertices; //< Adjacent_Vertices[u] is the set of the adjacent vertices of v >
//===========================================
//<data sructure of dfs>
map< int, int > d; //<d[i] the time visits vertices i>
map< int, int > f; //<f[i] the time visits vertices i completely>
map< int, char > color;//<White, Black, Gray>
map< int, int > p; //<p[i] is the vertices that visits i>
//===========================================
void Read_Data(char* file_name){
    ifstream f(file_name);
    while(1){
        int u;
        f >> u;
        if( u == -1) break;
        Vertices.insert(u);
    }
    while(1){
        int u,v;
        f >> u;
        if(u == -1) break;
        f >> v;
        Adjacent_Vertices[u].insert(v);
    }
}
//===========================================
void Print_Graph(){
    for (set< int >::iterator it = Vertices.begin(); it != Vertices.end(); it ++){
        int u = *it;
        cout << "Vertices_Adjacent[" << u << "] = ";
        for (set< int >::iterator it_1 = Adjacent_Vertices[u].begin(); it_1 != Adjacent_Vertices[u].end(); it_1++){
            int v = *it_1;
            cout << v << ' ';
        }
        cout << '\n';
    }
}
//===========================================
//<initialization>
void Init(){
    for (set< int >::iterator it = Vertices.begin(); it != Vertices.end(); it++){
        int u = *it;
        color[u] = 'W';
        p[u] = -1;
    }
}
//===========================================
//< USE QUEUE>
void BFS_Visit(int u){
    Init();
    d[u] = 1;
    queue< int > Q;
    Q.push(u);
    color[u] = 'G';
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        for (set< int >::iterator it = Adjacent_Vertices[v].begin(); it != Adjacent_Vertices[v].end(); it++){
            int x = *it;
            if (color[x] == 'W'){
                color[x] = 'G';
                d[x] = d[v] + 1;
                p[x] = v;
                Q.push(x);
            }
        }
    }
}
//===========================================
//< FIND PATH FROM S TO D USE BFS>
void Find_Path(int s, int d){
    BFS_Visit(s);
    int x = d;
    if( color[d] == 'W')
        cout << " NOT FIND THE PATH" << endl;
    else{
        stack< int > Path;
        while(d != s){
            Path.push(d);
            d = p[d];
        }
        cout << "PATH FROM " << s << " TO " << x << " : " << s;
        while(!Path.empty()){
            int x = Path.top();
            Path.pop();
            cout << "->" << x;
        }
        cout << endl;
    }
}
//===========================================
int main(){
    Read_Data("graph_1.txt");
    Print_Graph();
    Find_Path(1,7);
}
