#include <vector>
#include <iostream>
#include "C++ project.h"
#include <random>
#include <ctime>

// to get 0 or 1 with given probability
bool TrueFalse(double Probability)
{
    int random;

    random = rand() % 1000; //0..999
    if (random < (int)(Probability * 1000))
        return true;
    else
        return false;
}

//to get list with minimum distance between 2 vertices 
vector <int> Wave_Propogation(vector <vector <int>> Adjacency_matrix, int element)
{
    vector <int> Wave(Adjacency_matrix.size(), -1);

    int number = 0;
    Wave[element] = number;

    vector <int> Vertices;
    Vertices = { element };

    vector <int> Neighbours;

    while (Vertices.size() > 0)
    {
        number = number + 1;
        for (int i = 0; i < Vertices.size(); i++)
        {
            for (int j = 0; j < Adjacency_matrix.size(); j++)
            {
                if (Adjacency_matrix[Vertices[i]][j] == 1 and Wave[j] == -1)
                {
                    Neighbours.push_back(j);
                    Wave[j] = number;
                }
            }
        }
        Vertices.clear();
        Vertices = Neighbours;
        Neighbours.clear();
    }

    return Wave;
}

int main()
{
    srand(time(NULL));

    Graph G;
    G = Graph(0.2, 15);
    G.Matrix_Print("Adjacency matrix");

    Connected_components C;
    C = G.Connected_Components_Finding();
    C.Matrix_Print("Nodes of Connected Components");

    Analytics Res;
    Res = Analytics(G.Adjacency_matrix, C.Node_lists);
    Res.Results_print();

    system("pause");
    return 0;
}