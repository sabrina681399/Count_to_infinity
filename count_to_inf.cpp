#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

#define SIZE 100

struct Priority_Queue
{
    int node, dis;
    bool flag;
} Q[SIZE];


struct node
{
    int n, weight;
    bool status;
};

vector<node> adj[SIZE];
int nodes, edges;
int parent[SIZE];
int dis[SIZE];
bool status[SIZE];

bool isEmpty();
int pop();
void init_graph();
void init_Priority_Queue();

void printGraph();
void printRoutingTable();
void printPathUtil(int source, int destination);

void generateRoutingTable(int source);
void removeEdge(int node1, int node2);
void Graph();


int main()
{
    int source, choice, router, firstNode, secNode;

    srand((unsigned) time(0));
    choice = 1 + (rand() % 3);
    cout << "Selected option is: " << choice << endl;

    // Reading the graph input from txt file and Printing the graph
    Graph();
    printGraph();

    cout << endl;

    // Input the source node or starting router
    cout << "Input source: ";
    cin >> source;
    cout << endl;

    init_graph();
    generateRoutingTable(source);


    // Here are the two CASES
    // cout << "Options: " << endl;
    // cout << "1. Node Down  2. Link Down"  << endl;

    // cout << endl;
    // cout << "Input choice: ";
    // cin >> choice;

    if(choice == 1)
    {
        printRoutingTable();
    }


    else if(choice == 2)
    {
        srand((unsigned) time(0));
        router = rand() % nodes;

        status[router] = false;

        cout << "Router " << router << " is down!!" << endl; // Since this router is down,
        printRoutingTable();

        generateRoutingTable(source); // the routers that depend on this Router, first they will go down, and then all the remaining routers will go down in similar fashion

    }

    else if(choice == 3)
    {
        srand((unsigned) time(0));

        do
        {
            firstNode = rand() % nodes;
            cout << "First node: "<< firstNode << endl;
            secNode = adj[firstNode].size();
            secNode = rand() % secNode;
            cout << "Second node: "<< secNode << endl;

        }while(!secNode);

        cout << "Link is: "<< firstNode << "-" << secNode << endl;

        removeEdge(firstNode, secNode);
        printGraph();

        // Now the code will find the shortest path between First Node and Second Node
        init_graph();
        generateRoutingTable(firstNode);

        cout << endl;
        cout << "The path from Router " << firstNode << " to Router " << secNode << " is: ";
        cout << firstNode;
        printPathUtil(firstNode, secNode);

        cout << endl;
    }

    else if(choice == 4)
    {
        int initial_dis[SIZE], initial_par[SIZE];
        bool initial_status[SIZE];
        int temp = dis[1];

        //Assuming Link Node[0] - Node[1] is down
        status[1] = 0;

        for(int i = 0; i < 10; i++)
        {


            dis[1] = temp;
            dis[2] = dis[parent[2]] + dis[2];
            dis[3] = dis[parent[3]] + dis[3];
            dis[1] = 20000;
            printRoutingTable();
        }


    }

    else {
        cout << "Unknown option selected!!" << endl;
    }

    cout << endl;

    return 0;
}

int pop()
{
    int min = 10000, index = -1;

    for(int i = 0; i<nodes; i++)
    {
        if(Q[i].dis < min && Q[i].flag == true)
        {
            min = Q[i].dis;

            index = i;
        }
    }

    Q[index].flag = false;

    return index;
}

bool isEmpty()
{
    for(int i = 0; i < nodes; i++)
    {
        if(Q[i].flag == true)
            return false;
    }
    return true;
}

void init_Priority_Queue()
{

    for(int i = 0; i < nodes; i++)
    {
        Q[i].node = i;
        Q[i].dis = 9999;
        Q[i].flag = true;
    }
}

void init_graph()
{
    for(int i = 0; i < nodes; i++)
    {
        dis[i] = 9999;
        status[i] = true;
        parent[i] = -1;
    }

}

void printRoutingTable()
{
    //All the costs are from source node only
    // cout << " NODE " << "     COST  " << "  DEPENDENCY  " << endl;
    // for(int i = 0; i < nodes; i++)
    //     cout << "Node[" << i << "]     " << dis[i] << "       Node["  << parent[i] << "]"<< endl;

    cout << endl;
    cout << " NODE " << "     COST  " << "  DEPENDENCY  "  << "  STATUS  "<< endl;
    for(int i = 0; i < nodes; i++) {
        string text;
        if(status[i]) text = "UP";
        else text = "DOWN";

        cout << "Node[" << i << "]     " << dis[i] << "       Node["  << parent[i] << "]       " << text << endl;
    }
    cout << endl;
}

void generateRoutingTable(int source)
{
    init_Priority_Queue();

    dis[source] = 0;
    Q[source].dis = 0;

    while(!isEmpty())
    {
        int u = pop();
        u = Q[u].node;

        for(int i = 0; i < adj[u].size(); i++)
        {
            struct node temp;

            temp = adj[u][i];
            int v = temp.n;
            int weight = temp.weight;
            //bool stat = temp.status;

            if(dis[v] > (dis[u] + weight) && status[u]) // If dependency Router is ON
            {

                dis[v] = dis[u] + weight;

                parent[v] = u;
                Q[v].dis = dis[v];
            }

            else if(!status[u]) // If dependency Router is OFF
            {
                if(status[v]) // Checking if this has been printed already or not
                {
                    cout << "Router " << v << " is down!!" << endl;
                    status[v] = false;  // The router turns itself OFF
                    temp.status = false;

                    printRoutingTable();
                }
            }
        }
    }
}


void removeEdge(int node1, int node2)
{
    vector<struct node>::iterator itr1;
    struct node temp;

    for (itr1 = adj[node1].begin(); itr1 < adj[node1].end(); itr1++)
    {
        temp = *itr1;

        if(temp.n == node2)
        {
            adj[node1].erase(itr1);
        }
    }

    for (itr1 = adj[node2].begin(); itr1 < adj[node2].end(); itr1++)
    {
        temp = *itr1;

        if(temp.n == node1)
        {
            adj[node2].erase(itr1);
        }
    }
}

void Graph()
{
    int u, v, w;
    bool status = true;

    ifstream infile;
    infile.open("router.txt");

    infile >> nodes >> edges;

    for(int i = 0; i < edges; i++)
    {
        struct node temp;

        infile >> u >> v >> w;

        temp.n = v;
        temp.weight = w;
        temp.status = status;

        adj[u].push_back(temp);

        temp.n = u;
        adj[v].push_back(temp);

    }

    infile.close();
}

void printGraph()
{
    for(int i = 0; i < nodes; i++)
    {
        cout << i;
        for(int j = 0; j < adj[i].size(); j++)
        {
            struct node temp;

            temp = adj[i][j];

            cout << "->" << temp.n;
        }

        cout << endl;
    }
}

void printPathUtil(int source, int des)
{
    if (parent[des] == -1)
        return;

    printPathUtil(source, parent[des]);

    cout << "->" << des;
}
