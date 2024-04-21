#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a node in the binary tree
struct Node {
    int value;          // Value of the node
    struct Node *left;  // Pointer to the left child
    struct Node *right; // Pointer to the right child
};

// Function to recursively explore and print the values of nodes in the binary tree
void explore(struct Node *root) {
    if (root == NULL) {
        return; // Base case: if the root is NULL, return
    } 
    else {
        printf(" %d ", root->value); // Print the value of the current node
        explore(root->left);          // Explore the left subtree
        explore(root->right);         // Explore the right subtree
    }
}

int main() {
    int i = 0, last = 0, current = 0;
    struct Node *root, *pleft, *pright, *list[2000];
    int n = 0;

    //creating the root.
    printf("root value ? ");
    scanf("%d", &n);
    root = (struct Node *) malloc(sizeof(struct Node));
    root->value = n;
    root->left = NULL;
    root->right = NULL;
    list[0] = root;
    current = 0;
    last = 0;

    // Loop to build the binary tree based on user input
    while (1) {
        if (current > last) {
            break; // If all nodes are processed, exit the loop
        }

        if (list[current]->value == -99) {
            current++;
            continue; // Skip processing if current node is a placeholder
        }

        pleft = (struct Node *) malloc(sizeof(struct Node)); // Create a new node for the left child
        pright = (struct Node *) malloc(sizeof(struct Node)); // Create a new node for the right child

        // Take input for the left child
        printf("left of %d? ", list[current]->value);
        scanf("%d", &n);
        pleft->value = n; pleft->left = NULL; pleft->right = NULL;

        // Take input for the right child
        printf("right of %d? ", list[current]->value);
        scanf("%d", &n);
        pright->value = n; pright->left = NULL; pright->right = NULL;

        // Connect the left and right children to the current node
        if (pleft->value == -99) {
            list[current]->left = NULL;
        } 
        else {
            list[current]->left = pleft;
        }
        if (pright->value == -99) {
            list[current]->right = NULL;
        } 
        else {
            list[current]->right = pright;
        }

        // Update the list of nodes with the newly created children
        list[last + 1] = pleft;
        list[last + 2] = pright;
        last = last + 2;
        current++;
    }

    // Call the explore function to print the values of nodes in the tree
    explore(root);

    return 0;
}
