#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define INPUT_FILE_PATTERN "tests/test%02d.txt"
#define OUTPUT_FILE_PATTERN "results/result%02d.txt"
#define EXPECTED_FILE_PATTERN "expected/test%02d-output.txt"

// Structure de noeud pour le graphe
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

Node* graph[MAX_N];
int visited[MAX_N];
int distance_arr[MAX_N];
int queue_arr[MAX_N];
int stack_arr[MAX_N];

// Compare deux fichiers
int compareFiles(const char* fileA, const char* fileB) {
    FILE* a = fopen(fileA, "rb");
    FILE* b = fopen(fileB, "rb");
    if (a == NULL || b == NULL) {
        if (a) fclose(a);
        if (b) fclose(b);
        return 0;
    }

    int same = 1;
    while (1) {
        int ca = fgetc(a);
        while (ca == '\r') ca = fgetc(a); // ignore CR (Windows)

        int cb = fgetc(b);
        while (cb == '\r') cb = fgetc(b); // ignore CR (Windows)

        if (ca != cb) {
            same = 0;
            break;
        }
        if (ca == EOF) { // EOF atteint simultanément
            break;
        }
    }

    fclose(a);
    fclose(b);
    return same;
}

// Ajoute une arrete au graphe non orienté
void ajouterArete(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v;
    newNode->next = graph[u];
    graph[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = u;
    newNode->next = graph[v];
    graph[v] = newNode;
}

// DFS iteratif pour compter les royaumes
void dfs(int start) {
    int top = 0;
    stack_arr[top++] = start;
    visited[start] = 1;

    while (top > 0) {
        int node = stack_arr[--top];
        Node* temp = graph[node];
        while (temp != NULL) {
            int nxt = temp->dest;
            if (!visited[nxt]) {
                visited[nxt] = 1;
                stack_arr[top++] = nxt;
            }
            temp = temp->next;
        }
    }
}

// BFS pour trouver le chemin le plus court
int bfs(int start, int end, int n) {
    if (start == end) return 0;

    memset(visited, 0, sizeof(int) * (n + 1));
    memset(distance_arr, -1, sizeof(int) * (n + 1));

    int front = 0, rear = 0;
    queue_arr[rear++] = start;
    visited[start] = 1;
    distance_arr[start] = 0;

    while (front < rear) {
        int current = queue_arr[front++];

        Node* temp = graph[current];
        while (temp != NULL) {
            int voisin = temp->dest;
            if (!visited[voisin]) {
                visited[voisin] = 1;
                distance_arr[voisin] = distance_arr[current] + 1;
                queue_arr[rear++] = voisin;

                if (voisin == end) {
                    return distance_arr[voisin];
                }
            }
            temp = temp->next;
        }
    }

    return -1;
}

// Libere tout le graphe pour les sommets 1..n
void libererGraphe(int n) {
    for (int i = 1; i <= n; i++) {
        Node* temp = graph[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
        graph[i] = NULL;
    }
}

// Fonction principale
int main(void) {
    for (int testId = 1; testId <= 10; testId++) {
        char inputFile[32];
        char outputFile[32];
        char expectedFile[32];
        snprintf(inputFile, sizeof(inputFile), INPUT_FILE_PATTERN, testId);
        snprintf(outputFile, sizeof(outputFile), OUTPUT_FILE_PATTERN, testId);
        snprintf(expectedFile, sizeof(expectedFile), EXPECTED_FILE_PATTERN, testId);

        FILE* input = fopen(inputFile, "r");
        if (input == NULL) {
            printf("test%02d False (input manquant)\n", testId);
            continue;
        }
        FILE* output = fopen(outputFile, "w");
        if (output == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier de sortie %s\n", outputFile);
            fclose(input);
            continue;
        }

        int n, m, a, b;
        int ok = 1;

        if (fscanf(input, "%d %d", &n, &m) != 2) {
            fprintf(stderr, "Lecture invalide pour n et m dans %s\n", inputFile);
            ok = 0;
        }

        // Initialisation
        memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));

        // Lecture des routes
        for (int i = 0; ok && i < m; i++) {
            int u, v;
            if (fscanf(input, "%d %d", &u, &v) != 2) {
                fprintf(stderr, "Lecture invalide pour une route a la ligne %d dans %s\n", i + 1, inputFile);
                ok = 0;
                break;
            }
            ajouterArete(u, v);
        }

        if (ok && fscanf(input, "%d %d", &a, &b) != 2) {
            fprintf(stderr, "Lecture invalide pour les villes a et b dans %s\n", inputFile);
            ok = 0;
        }

        // Tache 1 : Compter les royaumes
        int nbRoyaumes = 0;
        int cheminMin = -1;
        if (ok) {
            for (int i = 1; i <= n; i++) {
                if (!visited[i]) {
                    dfs(i);
                    nbRoyaumes++;
                }
            }

            // Tache 2 : Plus court chemin par BFS
            cheminMin = bfs(a, b, n);

            fprintf(output, "%d\n", nbRoyaumes);
            fprintf(output, "%d\n", cheminMin);
        }

        fclose(input);
        fclose(output);

        // comparaison exacte caractere par caractere avec le fichier attendu
        int same = ok && compareFiles(outputFile, expectedFile);
        printf("test%02d %s\n", testId, same ? "True" : "False");

        libererGraphe(n);
    }

    return 0;
}
