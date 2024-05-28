#pragma once
#include <vector>
using namespace std;

bool TrueFalse(double Probability);
vector <int> Wave_Propogation(vector <vector <int>> Adjacency_matrix, int element);

class Single_connected_component {
public:

    vector <int> Node_list;

    Single_connected_component();

    int Diameter(vector <vector <int>> Adjacency_matrix);
    bool If_bipartition(vector <vector <int>> Adjacency_matrix);

};

class Connected_components {
public:

    vector <Single_connected_component> Node_lists;

    Connected_components();

    int Summa_Cardinalities();
    void Matrix_Print(string Message);
};


class Graph {
public:

    vector <vector <int>> Adjacency_matrix;
    int Diameter;
    bool Bipartition;

    Graph();
    Graph(double Probability, int Matrix_size);

    void Matrix_Print(string Message);
    Connected_components Connected_Components_Finding();

};

class Analytics : Single_connected_component {
public:
    int MaxDiameter;
    string TotalBipartition;
    double AverageCardinality;

    Analytics();
    Analytics(vector <vector <int>> Adjacency_matrix, vector <Single_connected_component> Node_lists);

    void Results_print();

};