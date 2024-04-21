#include <stdio.h>

// Define a structure to represent a node in the graph
struct Node {
    int nodeid;     // Unique identifier for the node
    int adjcount;   // Number of adjacent nodes
    int adjs[10];   // Array to store adjacent nodes
    int costs[10];  // Array to store costs of edges to adjacent nodes
    int visas;      // Number of visas required to enter this node
};

// Function to add a new node to the graph
int addNode(struct Node *p, int nid, int count) {
    int i = 0, ncount = count;
    // Check if the node already exists
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    // If the node doesn't exist, add it
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        p[i].visas = 0; // Initialize visas to 0 for now
        ncount++;
    }
    return ncount;
}

// Function to add an edge between two nodes in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int visas, int count) {
    int i = 0, index;
    // Find the index of the first node
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            // Add the second node as adjacent along with cost
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].visas = visas; // Set the number of visas required for this node
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already in the list
int added(int *list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Function to find a path between two nodes in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int visas) {
    int index = 0, i = 0;

    // Check if list contains the end node and if you have enough visas
    if (list[lcount - 1] == end && visas >= 0) {
        int tcost = 0;
        printf("\n");
        // Print the path and its cost
        for (i = 0; i < lcount; i++) {
            printf(" %d ", list[i]);
            tcost += clist[i];
        }
        printf(" cost = %d", tcost);
        return;
    }

    // Find the index of the starting node
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }

    // Explore adjacent nodes
    for (i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].adjs[i]);
        int new_visas = visas - p[index].visas; // Deduct the visas required for this node
        // If the adjacent node is not already in the list and visas are sufficient, explore it
        if (a == 0 && new_visas >= 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, new_visas);
            lcount--;
        }
    }
}

int main() {
    struct Node nodes[50]; // Array to store nodes of the graph
    int nodecount = 0;     // Count of nodes in the graph
    int n1 = 0, n2 = 0, c = 0, visas = 0; // Variables to store input values

    // Input nodes and edges
    while (1) {
        printf("n1, n2, cost, visas? ");
        scanf("%d %d %d %d", &n1, &n2, &c, &visas);
        // Break the loop if input indicates termination
        if (n1 == -9 || n2 == -9 || c == -9 || visas == -9) {
            break;
        }
        // Add nodes and edges to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, visas, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, visas, nodecount);
    }

    int start, end; // Variables to store start and end nodes for path finding
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0; // Arrays to store path and its costs
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Find path from start to end
    findpath(nodes, nodecount, start, end, list, clist, lcount, 0); // Start with 0 visas

    return 0;
}
