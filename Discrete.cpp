//#pragma warning(disable:4996)
/*   21i-0780
*    21i-0437
*    21i-0885
*/
#include <iostream>
#include <string>
#include <fstream>
#include "linked_list.h"
#include <list>
#include <stack>
#include <iterator>

using namespace std;


// ***********************************************************************************************
// OUTPUT STRING overloading
ostream& operator<<(ostream& os, string& msg)
{
    os << msg.c_str();
    return os;

}


// **********************************************************************************************
// GRAPH CLASS 
class Graph
{
    int vertices;                 // No. of vertices
    list<int>* adjacency_list;    // An array of adjacency lists


public:
    int number;


    // *******************************************************************
    //                        FILL STACK IN BUILT
    void fillStack(int var1, bool visited[], stack<int>& Stack)
    {
        // Mark the current node as visited and print it
        visited[var1] = true;

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adjacency_list[var1].begin(); i != adjacency_list[var1].end(); ++i)
            if (!visited[*i])
                fillStack(*i, visited, Stack);

        // All vertices reachable from var1 are processed by now, push var1
        Stack.push(var1);
    }



    // *************************************************************
    //                           DFS
    void DFS(int var1, bool visited[])
    {
        visited[var1] = true;
        cout << var1 << " ";

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adjacency_list[var1].begin(); i != adjacency_list[var1].end(); ++i)
            if (!visited[*i])
                DFS(*i, visited);
    }


    // *************************************************************
    //                           DFS 2
    void DFS2(int vertices, bool visited[], List*& l2, int index, int list_index)
    {

        visited[vertices] = true;
        l2[index].insert(list_index, vertices);
        list<int>::iterator i;
        for (i = adjacency_list[vertices].begin(); i != adjacency_list[vertices].end(); ++i)
        {
            if (!visited[*i])
            {
                list_index++;
                DFS2(*i, visited, l2, index, list_index);

            }
        }
    }



    // ************************** Constructor ************************
    Graph(int vertices = 0)
    {
        this->number = 0;
        this->vertices = vertices;
        adjacency_list = new list<int>[vertices];
    }


    // ************************** ADD NODE ***************************
    void add_node(int var1, int w)
    {
        adjacency_list[var1].push_back(w); 
    }



    // ************************** PRINT SCC **************************
    void Print()
    {
        stack<int> Stack;

        // Mark all the vertices as not visited (For first DFS)
        bool* visited = new bool[vertices];
        for (int i = 0; i < vertices; i++)
            visited[i] = false;

        for (int i = 0; i < vertices; i++)
            if (visited[i] == false)
                fillStack(i, visited, Stack);

        // Create a reversed graph
        Graph gr = Transpose();

       
        for (int i = 0; i < vertices; i++)
            visited[i] = false;

        while (Stack.empty() == false)
        {
            // Pop a vertex from stack
            int var1 = Stack.top();
            Stack.pop();

            // Print Strongly connected component of the popped vertex
            if (visited[var1] == false)
            {
                gr.DFS(var1, visited);
                this->number++;
                cout << endl;
            }
        }
    }


    // ****************************************************************
    //                        TRANSPOSE 
    Graph Transpose()
    {
        Graph g(vertices);
        for (int var1 = 0; var1 < vertices; var1++)
        {
            // Recur for all the vertices adjacent to this vertex
            list<int>::iterator i;
            for (i = adjacency_list[var1].begin(); i != adjacency_list[var1].end(); ++i)
            {
                g.adjacency_list[*i].push_back(var1);
            }
        }
        return g;
    }


    // ********************************************************* 
    // Make list of strongly connected components
    List* make_list(int number)
    {
        int index = 0;
        List* l = new List[number];
        // Makes Stack

        stack<int> Stack;

        // Mark all the vertices as not visited (For first DFS)
        bool* visited = new bool[vertices];

        for (int i = 0; i < vertices; i++)
        {
            visited[i] = false;
        }

        // Fill vertices in stack according to their finishing times
        for (int i = 0; i < vertices; i++)
        {
            if (visited[i] == false)
            {
                fillStack(i, visited, Stack);
            }
        }


        // Create a reversed graph
        Graph gr = Transpose();

        // Mark all the vertices as not visited (For second DFS)
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = false;
        }

        // Now process all vertices in order defined by Stack
        while (Stack.empty() == false)
        {
            // Pop a vertex from stack
            int vertices = Stack.top();
            Stack.pop();

            // Print Strongly connected component of the popped vertex
            if (visited[vertices] == false)
            {
                int list_index = 0;
                gr.DFS2(vertices, visited, l, index,  list_index);
                index++;// initialize from zero
            }
        }
        return l;

    }

};



// ***************************************************************************************************
//                                           CHECKS MAXIMUM SCC
int check_max(List *l, int number , int &vertice) 
{
   
    int index = 0;
    int max = 0;
    int unme= 0;
    for (int i = 0; i < number; i++) 
    {
        Node* temp = new Node;
        temp = l[i].head;
        while (temp->next_add != NULL) 
        {
            temp = temp->next_add;
            unme++;
        }
        unme++;
        if (unme > max) 
        {
            max = unme;
            index = i;
        }
        vertice = max;
        unme = 0;
    }
    return index;

}



// ***************************************************************************************************
//                                           MAIN FUNCTION 

int main() 
{
    //int j = 0;
    int index = 1;
    string str1 = "", str2 = "";

      

	//                                     Kosaraju's algorithm
	int edges=0;
	int nodes_g = 875713, edges_g = 5105039;
	string file_name[2] = { "C:\\Users\\Zunaira\\Documents\\3rd Semester\\Discrete Mathematics\\Discrete Project\\web-Google.txt", "C:\\Users\\Zunaira\\Documents\\3rd Semester\\Discrete Mathematics\\Discrete Project\\twitter_combined.txt" };
	Graph g(24);
    string ret, final;
    ifstream file;
    // file.open(file_name[0]);
    file.open("C:\\Users\\Zunaira\\Documents\\3rd Semester\\Discrete Mathematics\\Discrete Project\\web.txt");
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
                if ((ret[i] >= 48 && ret[i] <= 57) || ret[i] == 32|| ret[i]== 9)
                {
                    check = 1;
                }
                else
                {
                    check = 0;
                    break;
                }
            }
            int j = 0;
            if (check == 1)
            {
                // call by address
                edges = edges + 1;  // ret has the two values

                int s = 0;
                string p = ret;
                int tutui=0;
                for (j ; ret[j] != '\n'; j++)
                {  
                    if (p[s] >= 48 && p[s] <= 57)
                    {
                        str1.push_back(p[j]);
                        s++;
                    }
                    
                    else 
                    {
                        tutui = 1;
                    }
                    if (tutui == 1) 
                    {
                        goto down;
                    }
                }
            down:
                tutui = 0;
                while (ret[j] == 32 || ret[j] == 9) 
                {
                    j++;
                }

                for (j; ret[j] != '\n'; j++)
                {

                    if (ret[j] >= 48 && ret[j] <= 57)
                    {
 
                        str2.push_back(ret[j]);
                       // s++;
                    }

                    else
                    {
                        tutui = 1;
                    }
                    if (tutui == 1)
                    {
                        goto againdown;
                    }
                }

                // stoi converts string into integer
            againdown:
                cout << "The index is " << index << ": " << stoi(str1) << "    " << stoi(str2) << endl;
                g.add_node(stoi(str1), stoi(str2));
                index++;
            }
            ret = "";
            str1 = "", str2 = "";
        }
        cout << "done " << endl;
    }
    file.close();
    cout << endl;
    cout << "         _____    ______   ______                " << endl;
    cout << "         |    |   |        |                     " << endl;
    cout << "         |        |        |                     " << endl;
    cout << "         |____    |        |                     " << endl;
    cout << "              |   |        |                     " << endl;
    cout << "         |    |   |        |                     " << endl;
    cout << "         |____|   |_____   |_____                " << endl;

    g.Print();


    // --------------------------------------------------------------------------
    // Making a linked List
    int number = g.number;
    cout << "The number of SCC is " << number << endl;
    List* l = new List[number];
    l = g.make_list(number);


    // --------------------------------------------------------------------------
    // finding biggest strongly connected component
    
    int vertice;

    int max = check_max(l, number, vertice);


  
    cout << "The size of largest SCC is " << vertice << endl;
    cout << "The biggest strongly connected components is " ;
    Node* temp = new Node;
    temp = l[max].head;
    cout << l[max].get_data() << " ";
    while (temp->next_add != NULL) 
    {
        temp = temp->next_add;
        cout << temp->data << " ";
    }
    cout << endl;


    cout << "bye" << endl;
}