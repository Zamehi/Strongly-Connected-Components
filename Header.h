#pragma once
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
    Graph gr = getTranspose();

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
            gr.DFSUtil2(vertices, visited, l, index, list_index);
            // l[index] = l2;

            index++;// initialize from zero
            //cout << endl;
        }

    }
    return l;

}