#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

typedef struct tree_node_st {
    void *element;
    struct tree_node_st *left;
    struct tree_node_st *right;
    struct tree_node_st *parent;
} TreeNode;
TreeNode* newTreeNode(void *e, TreeNode *parent, TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->element = e;
    node->left = left;
    node->right = right;
    node->parent = parent;
    return node;
}
typedef struct {
    TreeNode *root;
} Tree;
Tree* newTree() {
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}
bool empty(Tree *t) {
    return !(t->root);
}
void insert(Tree *t, void *e) {
    if (empty(t)) {
        t->root = newTreeNode(e, NULL, NULL, NULL);
        return;
    }
}
typedef struct {
    wchar_t* value;
    int frequency;
} CharFrequency;

CharFrequency* newCharFrequency(wchar_t* value) {
    CharFrequency *cf = (CharFrequency*)malloc(sizeof(CharFrequency));
    cf->value = value;
    cf->frequency = 0;
    return cf;
}
CharFrequency* createFrequencyTable(wchar_t input[], int str_len) {
    CharFrequency *table = (CharFrequency*) calloc(0, sizeof (CharFrequency) * 256);

    for (int i = 0; i < str_len; ++i) {
        table[input[i]].value = (wchar_t*) input[i];
        table[input[i]].frequency++;
    }

    return table;
}


void lazySort(CharFrequency *table) {
    for (int j = 0; j < 256; ++j) {
        for (int k = 0; k < 256; ++k) {
            if (table[j].frequency > table[k].frequency) {
                CharFrequency temp = table[j];
                table[j] = table[k];
                table[k] = temp;
            }
        }
    }
}





int main() {
    setlocale(LC_ALL, "");
    wchar_t str[] = L"bbbbbbbzzzzzkkkkklleaA";
    int str_len = sizeof(str)/sizeof(wchar_t)-1;

    CharFrequency *table = createFrequencyTable(str, str_len);

    lazySort(table);

    int table_length = 0;

    for (int i = 0; i < 256; ++i) {
        if (table[i].frequency > 0) {
            printf("Char: '%c', count: %d\n", table[i].value, table[i].frequency);
            table_length++;
        }
    }

    printf("LAST VALUES:\n");
    printf("Last character: %c Freq: %d\n",table[table_length-1].value, table[table_length-1].frequency);
    printf("Last character: %c Freq: %d\n",table[table_length-2].value, table[table_length-2].frequency);

    free(table);
    return 0;
}