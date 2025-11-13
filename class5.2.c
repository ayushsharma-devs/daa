#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char ch;
    int freq;
    struct node *left, *right;
} Node;

typedef struct {
    Node **array;
    int size;
} MinHeap;

Node* newNode(char ch, int freq) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->ch = ch;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->array = (Node**)malloc(capacity * sizeof(Node*));
    return minHeap;
}

void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, Node* minHeapNode) {
    int i = minHeap->size++;
    minHeap->array[i] = minHeapNode;

    while (i && minHeap->array[i]->freq < minHeap->array[(i-1)/2]->freq) {
        swapNode(&minHeap->array[i], &minHeap->array[(i-1)/2]);
        i = (i-1)/2;
    }
}

MinHeap* buildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; i++)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;

    for (int i = (minHeap->size - 2)/2; i >= 0; i--)
        minHeapify(minHeap, i);

    return minHeap;
}

Node* buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;

    MinHeap* minHeap = buildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        if (root->ch != '$')
            printf("%c ", root->ch);
        inorder(root->right);
    }
}

int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    char *alphabets = (char*)malloc(n * sizeof(char));
    int *freq = (int*)malloc(n * sizeof(int));

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
        scanf(" %c", &alphabets[i]);

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &freq[i]);

    Node* root = buildHuffmanTree(alphabets, freq, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorder(root);
    printf("\n");

    free(alphabets);
    free(freq);
    return 0;
}
