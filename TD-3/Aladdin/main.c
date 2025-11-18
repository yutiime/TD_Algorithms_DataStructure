#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005

// Structure de nœud pour le graphe
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

Node* graph[MAX_N];
int visited[MAX_N];
int distance[MAX_N];
int queue[MAX_N];

// Ajoute une arête au graphe
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

// DFS pour compter les royaumes
void dfs(int node) {
    visited[node] = 1;
    Node* temp = graph[node];
    while (temp != NULL) {
        if (!visited[temp->dest]) {
            dfs(temp->dest);
        }
        temp = temp->next;
    }
}

// BFS pour trouver le chemin le plus court 
int bfs(int start, int end, int n) {
    if (start == end) return 0;
    
    memset(visited, 0, sizeof(int) * (n + 1));
    memset(distance, -1, sizeof(int) * (n + 1));
    
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    distance[start] = 0;
    
    while (front < rear) {
        int current = queue[front++];
        
        Node* temp = graph[current];
        while (temp != NULL) {
            int voisin = temp->dest;
            if (!visited[voisin]) {
                visited[voisin] = 1;
                distance[voisin] = distance[current] + 1;
                queue[rear++] = voisin;
                
                if (voisin == end) {
                    return distance[voisin];
                }
            }
            temp = temp->next;
        }
    }
    
    return -1; 
}

// Fonction principale 
int main() {
    int n, m, a, b;
    
    scanf("%d %d", &n, &m);
    
    // Initialisation
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    
    // Lecture des routes
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        ajouterArete(u, v);
    }
    
    scanf("%d %d", &a, &b);
    
    // Tâche 1 : Compter les royaumes
    int nbRoyaumes = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            nbRoyaumes++;
        }
    }
    
    // Tâche 2 : Plus court chemin par BFS
    int cheminMin = bfs(a, b, n);
    
    printf("%d\n", nbRoyaumes);
    printf("%d\n", cheminMin);
    
    // Libération mémoire
    for (int i = 1; i <= n; i++) {
        Node* temp = graph[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    
    return 0;
}