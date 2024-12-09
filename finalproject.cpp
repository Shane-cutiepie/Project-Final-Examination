#include <iostream> 
#include <vector>   // Includes the vector library for dynamic array management
using namespace std; 

// Node structure for Binary Search Tree (BST)
struct Node {
    int data;        
    Node* left;      // Pointer to the left child
    Node* right;     // Pointer to the right child

    // Constructor to initialize a node with a given value
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Heap class to manage a max-heap of magical artifacts
class MagicalHeap {
private:
    vector<int> heap; // Vector to store the heap elements

    // Maintains the max-heap property by moving the element up
    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[(index - 1) / 2], heap[index]); // Swap with the parent if larger
            index = (index - 1) / 2; // Update index to the parent's position
        }
    }

    // Maintains the max-heap property by moving the element down
    void heapifyDown(int index) {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        // Compare with left child
        if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }
        // Compare with right child
        if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }
        // If largest is not the current index, swap and continue heapifying
        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Inserts a new artifact into the heap
    void insertArtifact(int value) {
        heap.push_back(value);       // Add value to the end of the heap
        heapifyUp(heap.size() - 1); // Restore heap property
        cout << "Artifact with magical power " << value << " has been added to the treasure heap!\n";
    }

    // Removes the artifact with the highest power (root of the heap)
    void deleteArtifact() {
        if (heap.empty()) {
            cout << "The treasure heap is empty!\n";
            return;
        }
        cout << "Artifact with magical power " << heap[0] << " has been removed from the treasure heap!\n";
        heap[0] = heap.back(); // Replace root with last element
        heap.pop_back();       // Remove last element
        heapifyDown(0);        // Restore heap property
    }

    // Displays all artifacts in the heap
    void displayHeap() {
        if (heap.empty()) {
            cout << "The treasure heap is empty!\n";
            return;
        }
        cout << "Current treasure heap: ";
        for (int value : heap) {
            cout << value << " ";
        }
        cout << endl;
    }
};

// BST class to manage the enchanted forest of artifacts
class MagicalTree {
private:
    Node* root; // Root of the BST

    // Recursively inserts a new node into the BST
    Node* insertNode(Node* node, int value) {
        if (node == nullptr) return new Node(value); // Create a new node if empty
        if (value < node->data)
            node->left = insertNode(node->left, value); // Insert into left subtree
        else
            node->right = insertNode(node->right, value); // Insert into right subtree
        return node;
    }

    // Recursively searches for a value in the BST
    bool searchNode(Node* node, int value) {
        if (node == nullptr) return false; // Value not found
        if (node->data == value) return true; // Value found
        if (value < node->data)
            return searchNode(node->left, value); // Search in left subtree
        else
            return searchNode(node->right, value); // Search in right subtree
    }

    // Recursively deletes a node from the BST
    Node* deleteNode(Node* node, int value) {
        if (node == nullptr) return node; // Node not found

        if (value < node->data) {
            node->left = deleteNode(node->left, value); // Search in left subtree
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value); // Search in right subtree
        } else {
            // Node with one or no children
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Node with two children: Get the in-order successor (smallest in the right subtree)
            Node* temp = findMin(node->right);
            node->data = temp->data; // Replace with successor's value
            node->right = deleteNode(node->right, temp->data); // Delete the successor
        }
        return node;
    }

    // Finds the node with the smallest value in a subtree
    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // In-order traversal (left-root-right)
    void inorderTraversal(Node* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

public:
    MagicalTree() : root(nullptr) {} // Constructor to initialize an empty tree

    // Inserts a new artifact into the tree
    void insertArtifact(int value) {
        root = insertNode(root, value);
        cout << "Artifact with magical power " << value << " has been added to the enchanted forest!\n";
    }

    // Searches for an artifact in the tree
    void searchArtifact(int value) {
        if (searchNode(root, value)) {
            cout << "Artifact with magical power " << value << " is present in the enchanted forest!\n";
        } else {
            cout << "Artifact with magical power " << value << " is not found in the enchanted forest.\n";
        }
    }

    // Deletes an artifact from the tree
    void deleteArtifact(int value) {
        if (searchNode(root, value)) {
            root = deleteNode(root, value);
            cout << "Artifact with magical power " << value << " has been removed from the enchanted forest!\n";
        } else {
            cout << "No artifact with magical power " << value << " exists in the enchanted forest.\n";
        }
    }

    // Displays all artifacts in the tree using in-order traversal
    void traverseTree() {
        cout << "Artifacts in the enchanted forest (Inorder Traversal): ";
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    MagicalTree enchantedForest; // BST for the enchanted forest
    MagicalHeap treasureHeap;    // Max-heap for the treasure heap

    int choice, value;
    cout << "=== Welcome to Magical Tree and Heap System ===\n";
    while (true) {
        // Menu options
        cout << "\nOptions:\n";
        cout << "1. Insert into Tree\n";
        cout << "2. Search Tree\n";
        cout << "3. Delete from Tree\n";
        cout << "4. Traverse Tree\n";
        cout << "5. Insert into Heap\n";
        cout << "6. Delete from Heap\n";
        cout << "7. Display Heap\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle user choice
        switch (choice) {
            case 1:
                cout << "Enter the magical power of the artifact to insert into the tree: ";
                cin >> value;
                enchantedForest.insertArtifact(value);
                break;
            case 2:
                cout << "Enter the magical power of the artifact to search in the tree: ";
                cin >> value;
                enchantedForest.searchArtifact(value);
                break;
            case 3:
                cout << "Enter the magical power of the artifact to delete from the tree: ";
                cin >> value;
                enchantedForest.deleteArtifact(value);
                break;
            case 4:
                enchantedForest.traverseTree();
                break;
            case 5:
                cout << "Enter the magical power of the artifact to insert into the heap: ";
                cin >> value;
                treasureHeap.insertArtifact(value);
                break;
            case 6:
                treasureHeap.deleteArtifact();
                break;
            case 7:
                treasureHeap.displayHeap();
                break;
            case 8:
                cout << "Thank you for using the Magical Tree and Heap System! Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
