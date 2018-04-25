#include<iostream>
#include<queue>
#include<fstream>
#include<map>
#include<set>
#include<string>

using namespace std;

set< string > ID; // <ID of object>
map< string, string > ID_To_Name;// <mapping from id to name>
map< string, set <string> > Object_Priority;
map< string, int > Degree; // degree- of object;
//===================================
void Read_Data(char* file_name){
    ifstream f(file_name);
    string u,v;
    while(1){
        f >> u;
        if (u == "-1") break;
        f >> v;
        ID_To_Name[u] = v;
        ID.insert(u);
    }
    while(1){
        f >> u;
        if (u == "-1") break;
        f >> v;
        Object_Priority[u].insert(v);
    }
}
//===================================
//<use TOPO sort algorithm>
void ToPo_Algorithm(){
    for (set<string>::iterator it = ID.begin(); it != ID.end(); it ++){
        string u = *it;
        Degree[u] = 0;
    }
    for (set<string>::iterator it = ID.begin(); it != ID.end(); it ++){
            string u = *it;
        for ( set<string>:: iterator it_1 = Object_Priority[u].begin(); it_1 != Object_Priority[u].end(); it_1++){
            string v = *it_1;
            Degree[v]++;
        }
    }
    queue<string> Q;
    for (set<string>::iterator it = ID.begin(); it != ID.end(); it ++){
            string u = *it;
        if (Degree[u] == 0){
            Q.push(u);
        }
    }
    cout << "-----------------RESULT------------------" << endl;
    while(!Q.empty()){
        string u = Q.front(); Q.pop();
        cout << ID_To_Name[u] << endl;
        for (set<string>::iterator it = Object_Priority[u].begin(); it != Object_Priority[u].end(); it++){
            string v = *it;
            Degree[v]--;
            Object_Priority[u].erase(it);
            if ( Degree[v] == 0){
                Q.push(v);
            }
        }
    }
}
//===================================
int main(){
    Read_Data("object.txt");
    ToPo_Algorithm();
}
