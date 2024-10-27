#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;

        if (data > root->data) root->left = r;
        else if (data < root->data) root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) {
        return;
    }
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

// Функция поиска значения в дереве
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

// Функция подсчета числа вхождений заданного элемента в дерево
int count_occurrences(struct Node* root, int key) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->data == key) {
        count++;
    }
    count += count_occurrences(root->left, key);
    count += count_occurrences(root->right, key);
    return count;
}

int main() {
    setlocale(LC_ALL, "");
    int D, start = 1;

    struct Node* root = NULL;
    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1) {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else {
            root = CreateTree(root, root, D);
        }
    }

    print_tree(root, 0);

    printf("Введите число для поиска: ");
    scanf_s("%d", &D);

    struct Node* found = search(root, D);
    if (found != NULL) {
        printf("Число %d найдено в дереве.\n", D);
    }
    else {
        printf("Число %d не найдено в дереве.\n", D);
    }

    int occurrences = count_occurrences(root, D);
    printf("Число %d встречается %d раз в дереве.\n", D, occurrences);

    return 0;
}