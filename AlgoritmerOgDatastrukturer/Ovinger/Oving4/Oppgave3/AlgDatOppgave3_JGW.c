#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Represents the properties of a node in the tree.
 */
typedef struct {
    int value;
    char letter;
} Property;

/**
 * Tree node.
 */
typedef struct {
    Property property;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;
TreeNode* newTreeNode(int v, char c, TreeNode* p, TreeNode* l, TreeNode* r) {
    TreeNode* res = (TreeNode*)(malloc(sizeof(TreeNode)));
    res->property.value = v;
    res->property.letter = c;
    res->left = l;
    res->right = r;
    res->parent = p;
    return res;
}

/**
 * Tree.
 */
typedef struct {
 TreeNode* root;
} Tree;
Tree* newTree() {
    Tree* res = (Tree*)(malloc(sizeof(Tree)));
    res->root = NULL;
    return res;
}
bool empty(Tree* t) {
    return!(t->root);
}

/**
 * Insertion into tree.
 */
void insertRoot(Tree* t, TreeNode* n) {
    if (!t->root) t->root = n;
    else printf("This tree already has a root node!");
}

/**
 * Add children to a node.
 * @param n
 * @param p
 */
void insertLeft(TreeNode* p, TreeNode* n) {
    if (p->left) {
        printf("This node already has a left child node!");
    }
    else if (!p->left) p->left = n;
}
void insertRight(TreeNode* p, TreeNode* n) {
    if (p->right) printf("This node already has a right child node!");
    else if (!p->right) p->right = n;
}

/**
 * Inorder traversal and printing of the tree nodes.
 * @param n
 */
void writeInIntern(TreeNode* n) {
    if (n) {
        if (n->left && n->right) {
            printf("(");
        }
        writeInIntern(n->left);
        if(n->property.value==0) printf("%c", n->property.letter);
        else printf("%i", n->property.value);
        writeInIntern(n->right);
        if (n->left && n->right) {
            printf(")");
        }
    }
}
void writeInorder(Tree* t) {
    writeInIntern(t->root);
}

/**
 * Calculate the result of a tree's arithmetic expression.
 * @param n the start (root) node of the tree.
 * @return the final value of the expression.
 */
int calculateArithmeticExpression(TreeNode* n) {
    if (n) {
        if (n->left && n->right) {
            int left = calculateArithmeticExpression(n->left);
            int right = calculateArithmeticExpression(n->right);
            switch (n->property.letter) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/':
                    if (right != 0) {
                        return left / right;
                    } else {
                        printf("\n### Attempted division by zero. Exiting... ###");
                        exit(1);
                    }
            }
        }
        else {
            // Returns the value into either left or right if it's a leaf node
            return n->property.value;
        }
    }
    printf("\n### The entered node does not exist. ###");
    return 1;
}

/**
 * Main.
 * @return
 */
int main() {

    // Construct an example tree, equal to the tree shown in the task description
    Tree* tree = newTree();
    TreeNode* root = newTreeNode(0, '/', NULL, NULL, NULL);
    insertRoot(tree, root);
    if (empty(tree)) printf("The root was not inserted into the tree correctly!");
    TreeNode* a1 = newTreeNode(0, '*', root, NULL, NULL);
    TreeNode* a2 = newTreeNode(0, '-', root, NULL, NULL);
    insertLeft(root, a1);
    insertRight(root, a2);
    TreeNode* b1 = newTreeNode(3, ' ', a1, NULL, NULL);
    TreeNode* b2 = newTreeNode(0, '+', a1, NULL, NULL);
    TreeNode* b3 = newTreeNode(7, ' ', a2, NULL, NULL);
    TreeNode* b4 = newTreeNode(0, '*', a2, NULL, NULL);
    insertLeft(a1, b1);
    insertRight(a1, b2);
    insertLeft(a2, b3);
    insertRight(a2, b4);
    TreeNode* c1 = newTreeNode(2, ' ', b2, NULL, NULL);
    TreeNode* c2 = newTreeNode(4, ' ', b2, NULL, NULL);
    TreeNode* c3 = newTreeNode(2, ' ', b4, NULL, NULL);
    TreeNode* c4 = newTreeNode(2, ' ', b4, NULL, NULL);
    insertLeft(b2, c1);
    insertRight(b2, c2);
    insertLeft(b4, c3);
    insertRight(b4, c4);

    // Print the arithmetic expression read from the tree using inorder traversal
    printf("Inorder traversal: ");
    writeInorder(tree);

    // Calculate and print the sum of the tree when
    // considering it as an arithmetic expression
    int sum = calculateArithmeticExpression(root);
    printf("\n\nSum of tree's expression: %i", sum);

    return 0;
}

