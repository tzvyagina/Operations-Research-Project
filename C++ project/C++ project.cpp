#include <vector>
#include <iostream>
#include <iomanip>
#include "C++ project.h"
#include <algorithm>



Single_connected_component::Single_connected_component() {

}

bool Single_connected_component::If_bipartition(vector <vector <int>> Adjacency_matrix) {

    vector <char> LabelBipartition(Node_list.size(), '-');
    LabelBipartition[0] = 'X';

    bool Flag = true;

    vector <int> Vertices;
    Vertices = { Node_list[0] };
    vector <int> Neighbours;

    int step = 1;

    while (Vertices.size() > 0 and Flag == true)
    {
        for (int i = 0; i < Vertices.size(); i++)
        {
            for (int j = 0; j < Node_list.size(); j++)
            {
                if (Adjacency_matrix[Vertices[i]][Node_list[j]] == 1)
                {
                    if (step % 2 != 0 and LabelBipartition[j] == '-')
                    {
                        LabelBipartition[j] = 'Y';
                        Neighbours.push_back(Node_list[j]);
                    }
                    if (step % 2 == 0 and LabelBipartition[j] == '-')
                    {
                        LabelBipartition[j] = 'X';
                        Neighbours.push_back(Node_list[j]);
                    }
                    if (step % 2 != 0 and LabelBipartition[j] == 'X')
                        Flag = false;
                    if (step % 2 == 0 and LabelBipartition[j] == 'Y')
                        Flag = false;
                }
            }
        }
        Vertices.clear();
        Vertices = Neighbours;
        Neighbours.clear();
        step = step + 1;
    }
    if (Flag == true)
        return true;
    if (Flag == false)
        return false;
}

int Single_connected_component::Diameter(vector <vector <int>> Adjacency_matrix) {

    int Diameter = 0;
    int tempDiameter = 0;

    vector <int> LabelWave;

    for (int i = 0; i < Node_list.size(); i++)
    {
        LabelWave = Wave_Propogation(Adjacency_matrix, Node_list[i]);
        tempDiameter = *max_element(LabelWave.begin(), LabelWave.end());

        if (tempDiameter > Diameter)
            Diameter = tempDiameter;
    }
    return Diameter;
}


Connected_components::Connected_components() {

}

int Connected_components::Summa_Cardinalities() {
    int summa = 0;
    for (int i = 0; i < Node_lists.size(); i++)
        summa = summa + Node_lists[i].Node_list.size();

    return summa;
}


Graph::Graph() {

};

Graph::Graph(double Probability, int MatrixSize)
{
    vector <int> String;

    for (int i = 0; i < MatrixSize; i++)
    {
        for (int j = 0; j < MatrixSize; j++)
        {
            if (i == j)
                String.push_back(-1);
            if (j > i)
                String.push_back(TrueFalse(Probability));
            if (i > j)
                String.push_back(Adjacency_matrix[j][i]);
        }
        Adjacency_matrix.push_back(String);
        String.clear();
    }
}

void Graph::Matrix_Print(string Message)
{
    cout << Message << endl;
    for (int i = 0; i < Adjacency_matrix.size(); i++)
    {
        for (int j = 0; j < Adjacency_matrix[i].size(); j++)
        {
            if (Adjacency_matrix[i][j] == -1)
                cout << setw(3) << '-';
            else
                cout << setw(3) << Adjacency_matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Connected_components::Matrix_Print(string Message)
{
    cout << Message << endl;
    for (int i = 0; i < Node_lists.size(); i++)
    {
        for (int j = 0; j < Node_lists[i].Node_list.size(); j++)
        {
            cout << Node_lists[i].Node_list[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// to divide the graph onto connected components
Connected_components Graph::Connected_Components_Finding()
{
    Connected_components Components;
    vector <char> Label(Adjacency_matrix.size(), '-');

    while (Components.Summa_Cardinalities() != Adjacency_matrix.size())
    {
        Single_connected_component Component;

        bool flag = false;
        for (int i = 0; i < Label.size(); i++)
        {
            if (Label[i] == '-' and flag == false)
            {
                Component.Node_list.push_back(i);
                flag = true;
                Label[i] = '+';
            }
        }

        for (int i = 0; i < Component.Node_list.size(); i++)
        {
            for (int j = 0; j < Adjacency_matrix.size(); j++)
            {
                if (Adjacency_matrix[Component.Node_list[i]][j] == 1 and Label[j] == '-')
                {
                    Component.Node_list.push_back(j);
                    Label[j] = '+';
                }
            }
        }

        Components.Node_lists.push_back(Component);
    }
    return Components;
}

Analytics::Analytics() {

}

Analytics::Analytics(vector <vector <int>> Adjacency_matrix, vector <Single_connected_component> Node_lists) {

    int tempDiameter;
    MaxDiameter = 0;

    int count = 0;

    for (int i = 0; i < Node_lists.size(); i++)
    {
        tempDiameter = Node_lists[i].Diameter(Adjacency_matrix);
        if (tempDiameter > MaxDiameter)
            MaxDiameter = tempDiameter;

        if (Node_lists[i].If_bipartition(Adjacency_matrix) == true)
            count = count + 1;

    }
    AverageCardinality = double(Adjacency_matrix.size()) / double(Node_lists.size());
    if (count == Node_lists.size())
        TotalBipartition = "Yes";
    else
        TotalBipartition = "No";
}

void Analytics::Results_print()
{
    cout << "The average cardinality of the graph = " << AverageCardinality;
    cout << endl;
    cout << "The diameter of the graph = " << MaxDiameter;
    cout << endl;
    cout << "The graph is Bipartite? " << TotalBipartition;
    cout << endl;
}