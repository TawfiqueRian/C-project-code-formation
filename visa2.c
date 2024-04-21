#include <stdio.h>

// Define a structure to represent a node in the graph
struct Node {
    int nodeid;     // Unique identifier for the node
    int adjcount;   // Number of adjacent nodes
    int adjs[10];   // Array to store adjacent nodes
    int costs[10];  // Array to store costs of edges to adjacent nodes
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
        ncount++;
    }
    return ncount;
}

// Function to add an edge between two nodes in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0, index;
    // Find the index of the first node
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            // Add the second node as adjacent along with cost
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
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
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int visa[], int size) {
    int index = 0, i = 0, j = 0, k = 0;

    // Check if list contains the end node
    if (list[lcount - 1] == end) {
        // Check if the path satisfies visa requirements
        for (i = 1; i < lcount - 1; i++) {
            for (j = 0; j < size; j++) {
                if (visa[j] == list[i]) {
                    k++;
                }
            }
        }
        // If the path satisfies visa requirements, print it
        if ((lcount - 2 == k)) {
            printf("\nPath found : ");
            for (i = 0; i < lcount ; i++) {
                printf(" %d ", list[i]);
            }
            printf("\n");
            return;
        }
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
        // If the adjacent node is not already in the list, explore it
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, visa, size);
            lcount--;
        }
    }
}

int main() {
    struct Node nodes[50]; // Array to store nodes of the graph
    int nodecount = 0;     // Count of nodes in the graph
    int n1 = 0, n2 = 0, c = 0; // Variables to store input values

    // Input nodes and edges
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        // Break the loop if input indicates termination
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        // Add nodes and edges to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    int start, end; // Variables to store start and end nodes for path finding
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0; // Arrays to store path and its costs
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    int arr[100], size = 0, i = 0;
    printf("Enter the visa : ");
    // Input visa requirements
    while (1) {
        scanf("%d", &arr[i]);
        if (arr[i] == -9) {
            break;
        }
        i++;
    }

    size = i;

    // Find path from start to end
    findpath(nodes, nodecount, start, end, list, clist, lcount, arr, size);

    return 0;
}
