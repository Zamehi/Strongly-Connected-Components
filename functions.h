#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#include "graph.h"
using namespace std;

// ***********************************************************************************************
// Read from a txt file 
Graph read(string name, int* edges, Graph g)
{
    //Graph g();
    string ret, final;
    ifstream file;
    file.open(name);
    if (file.fail())
    {
        cout << "File failed to open, enter valid string." << endl;

    }
    else
    {
        while (file.eof() == 0)
        {
            int check = 0;
            getline(file, ret);
            for (int i = 0; ret[i] != '\0'; i++)
            {
                if ((ret[i] >= 48 && ret[i] <= 57) || ret[i] == 32)
                {
                    check = 1;
                }
                else
                {
                    check = 0;
                }
            }
            if (check == 1)
            {
                int pp = 0;
                string str1 = "", str2 = "";
                // call by address
                *edges = *edges + 1;  // ret has the two values


                // storing elements in the graph
                for (pp = 0; ret[pp] != 32; pp++)
                {
                    str1.push_back(ret[pp]);
                }
                while (ret[pp] != 32)
                {
                    pp++;
                }
                for (pp; ret[pp] != '\n'; pp++)
                {
                    str2.push_back(ret[pp]);
                }
                // stoi converts string into integer
              //  g.addEdge(stoi(str1), stoi(str2));


                //final.append(ret);
                //final.push_back('\n');
            }


        }
    }
    file.close();
    return g;
}



//
//class Graph
//{
//    int vertices;    // No. of vertices
//    list<int>* adjacency_list;    // An array of adjacency lists
//
//    // Fills Stack with vertices (in increasing order of finishing
//    // times). The top element of stack has the maximum finishing
//    // time
//    void fill_stack(int vertices, bool visited[], stack<int>& Stack);
//
//    // A recursive function to print DFS starting from vertices
//    void DFSUtil(int vertices, bool visited[]);
//    void DFSUtil2(int vertices, bool visited[], List** l, int index);
//public:
//    int number;
//    Graph(int vertices);
//    void addEdge(int vertices, int w);
//
//    // The main function that finds and prints strongly connected
//    // components
//    void printSCCs();
//
//    // Function that returns reverse (or transpose) of this graph
//    Graph getTranspose();
//    List* make_list(int number)
//    {
//        int index = 0;
//        List* l = new List[number];
//        // Makes Stack
//
//        stack<int> Stack;
//
//        // Mark all the vertices as not visited (For first DFS)
//        bool* visited = new bool[vertices];
//
//        for (int i = 0; i < vertices; i++)
//        {
//            visited[i] = false;
//        }
//
//
//        // Fill vertices in stack according to their finishing times
//        for (int i = 0; i < vertices; i++)
//        {
//            if (visited[i] == false)
//            {
//                fill_stack(i, visited, Stack);
//            }
//        }
//
//
//        // Create a reversed graph
//        Graph gr = getTranspose();
//
//        // Mark all the vertices as not visited (For second DFS)
//        for (int i = 0; i < vertices; i++)
//        {
//            visited[i] = false;
//        }
//
//
//        // Now process all vertices in order defined by Stack
//        while (Stack.empty() == false)
//        {
//            // Pop a vertex from stack
//            int vertices = Stack.top();
//            Stack.pop();
//
//            // Print Strongly connected component of the popped vertex
//            if (visited[vertices] == false)
//            {
//                gr.DFSUtil2(vertices, visited, &l, index);
//                index++;
//                //cout << endl;
//            }
//
//        }
//        return l;
//
//    }
//};
