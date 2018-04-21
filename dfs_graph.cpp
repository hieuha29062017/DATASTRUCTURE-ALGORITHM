#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<stack>

using namespace std;

int t; //<time visit vertices of the graph>
set< int > Vertices; //< set of vertices of the graph>
map< int, set<int> > Adjacent_Vertices; //< Adjacent_Vertices[u] is the set of the adjacent vertices of v >
//=========================================================================================================
//<data sructure of dfs>
map< int, int > d; //<d[i] the time visits vertices i>
map< int, int > f; //<f[i] the time visits vertices i completely>
map< int, char > color;//<White, Black, Gray>
map< int, int > p; //<p[i] is the vertices that visits i>
void Read_Data(char* name_file);
void Print_Graph();
void DFS_Visit(int u);
void DFS();
void Init();
void Find_Path(int soure, int destination);
//==================================
//<MAIN FUNCTION>

int main(){
    Read_Data("graph.txt");
    Print_Graph();
    Find_Path(1,7);
    DFS();
}


//===================================
void Read_Data(char* name_file){
    ifstream f(name_file);
    while(1){
        int v;
        f >> v;
        if(v == -1) break;
        Vertices.insert(v);
    }
    while(1){
        int u,v;
        f >> u;
        if(u == -1) break;
        f >> v;
        Adjacent_Vertices[u].insert(v);
    }
}
//====================================
void Print_Graph(){
    for(set< int >::iterator it = Vertices.begin(); it != Vertices.end(); it ++){
        int u = *it;
        cout << "Adjacent_Vertices[" << u << "] = ";
        for(set< int >::iterator it_1 = Adjacent_Vertices[u].begin(); it_1 != Adjacent_Vertices[u].end(); it_1++){
            int v = *it_1;
            cout << v << ' ';
        }
        cout << '\n';
    }
}
//====================================
void Init(){
    for(set< int >::iterator it = Vertices.begin(); it != Vertices.end(); it++){
        int u = *it;
        color[u] = 'W';
        p[u] = -1; //< specail value >
    }
}
//===================================
//< DEPTH FIRST SEARCH>
void DFS_Visit(int u){
    t++;
    d[u] = t;
    color[u] = 'G';
    for(set< int >::iterator it = Adjacent_Vertices[u].begin(); it != Adjacent_Vertices[u].end(); it++){
        int v = *it;
        if(color[v] == 'W'){
            p[v] = u;
            DFS_Visit(v);
        }
    }
    t++;
    f[u] = t;
    color[u] = 'B';
}
//===================================
//<DEPTH FIRST SEARCH ALL THE GRAPH>
void DFS(){
    t = 0;
    Init();
    for(set< int >::iterator it = Vertices.begin(); it != Vertices.end(); it++){
        int u = *it;
        if(color[u] == 'W'){
            DFS_Visit(u);
        }
    }
    for(set< int >::iterator it = Vertices.begin(); it != Vertices.end(); it++){
        int u = *it;
        cout << u << " : " << " TIME :" <<  d[u] << " FINISH TIME :" << f[u] << " PARENT :" << p[u] << " COLOR :" << color[u] << endl;
    }
}
//====================================
//<FIND PATH FROM SOURE TO DESTINATION>
//< USE STACK>
void Find_Path(int soure, int destination){
    Init();
    int temp = destination;
    DFS_Visit(soure);
    stack< int > Path;
    while(destination != soure){
        Path.push(destination);
        destination = p[destination];
    }
    cout << '\n';
    cout<< "PATH FROM " << soure << " TO " << temp << " : ";
    cout << soure;
    while(!Path.empty()){
        int v = Path.top();
        Path.pop();
        cout << "->" << v;
    }
    cout << '\n' << '\n';
}
