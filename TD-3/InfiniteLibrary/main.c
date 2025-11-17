#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ---------- AVL ----------
typedef struct Noeud {
    int cle;
    struct Noeud *gauche;
    struct Noeud *droit;
    int hauteur;
} Noeud;

static int hauteur(Noeud *n) { return n ? n->hauteur : 0; }
static int max2(int a, int b) { return (a > b) ? a : b; }

static Noeud* nouveau_noeud(int cle) {
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    if (!noeud) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    noeud->cle = cle;
    noeud->gauche = NULL;
    noeud->droit = NULL;
    noeud->hauteur = 1;
    return noeud;
}

static int facteur_equilibre(Noeud *n) {
    if (!n) return 0;
    return hauteur(n->gauche) - hauteur(n->droit);
}

static Noeud* rotation_droite(Noeud* y) {
    Noeud* x = y->gauche;
    Noeud* T2 = x->droit;
    x->droit = y;
    y->gauche = T2;
    y->hauteur = 1 + max2(hauteur(y->gauche), hauteur(y->droit));
    x->hauteur = 1 + max2(hauteur(x->gauche), hauteur(x->droit));
    return x;
}

static Noeud* rotation_gauche(Noeud* x) {
    Noeud* y = x->droit;
    Noeud* T2 = y->gauche;
    y->gauche = x;
    x->droit = T2;
    x->hauteur = 1 + max2(hauteur(x->gauche), hauteur(x->droit));
    y->hauteur = 1 + max2(hauteur(y->gauche), hauteur(y->droit));
    return y;
}

static Noeud* inserer(Noeud* racine, int cle) {
    if (racine == NULL) return nouveau_noeud(cle);

    if (cle < racine->cle)       racine->gauche = inserer(racine->gauche, cle);
    else if (cle > racine->cle)  racine->droit  = inserer(racine->droit,  cle);
    else return racine; // ignore doublon

    racine->hauteur = 1 + max2(hauteur(racine->gauche), hauteur(racine->droit));

    int fe = facteur_equilibre(racine);

    // LL
    if (fe > 1 && cle < racine->gauche->cle)
        return rotation_droite(racine);
    // RR
    if (fe < -1 && cle > racine->droit->cle)
        return rotation_gauche(racine);
    // LR
    if (fe > 1 && cle > racine->gauche->cle) {
        racine->gauche = rotation_gauche(racine->gauche);
        return rotation_droite(racine);
    }
    // RL
    if (fe < -1 && cle < racine->droit->cle) {
        racine->droit = rotation_droite(racine->droit);
        return rotation_gauche(racine);
    }
    return racine;
}

static Noeud* construire_avl_depuis_tableau(const int *tab, int n) {
    Noeud *racine = NULL;
    for (int i = 0; i < n; i++) {
        racine = inserer(racine, tab[i]);
    }
    return racine;
}


static Noeud* rechercher(Noeud *racine, int cle) {
    while (racine) {
        if (cle == racine->cle) return racine;
        racine = (cle < racine->cle) ? racine->gauche : racine->droit;
    }
    return NULL;
}

static void liberer_avl(Noeud *r) {
    if (!r) return;
    liberer_avl(r->gauche);
    liberer_avl(r->droit);
    free(r);
}

// ---------- Utils comparaison fichiers ----------
static void rstrip(char *s) {
    if (!s) return;
    size_t len = strlen(s);
    while (len > 0 && (s[len-1] == ' ' || s[len-1] == '\t' || s[len-1] == '\n' || s[len-1] == '\r')) {
        s[--len] = '\0';
    }
}

// Compare ligne par ligne deux fichiers, en ignorant les espaces de fin de ligne
static int fichiers_identiques_relaxes(const char *pathA, const char *pathB) {
    FILE *fa = fopen(pathA, "r");
    FILE *fb = fopen(pathB, "r");
    if (!fa || !fb) {
        if (fa) fclose(fa);
        if (fb) fclose(fb);
        return 0;
    }

    char la[4096], lb[4096];
    int equal = 1;

    while (1) {
        char *ra = fgets(la, sizeof la, fa);
        char *rb = fgets(lb, sizeof lb, fb);

        if (!ra || !rb) {
            // fin des fichiers : identiques seulement si les deux sont finis
            equal = (ra == NULL && rb == NULL);
            break;
        }

        rstrip(la);
        rstrip(lb);

        if (strcmp(la, lb) != 0) {
            equal = 0;
            break;
        }
    }

    fclose(fa);
    fclose(fb);
    return equal;
}

// Traite un test unique d'indice idx
static int traiter_un_test(int idx) {
    char input_file[64];
    char expected_output[64];
    char result_file[64];

    snprintf(input_file, sizeof input_file, "test%02d.txt", idx);
    snprintf(expected_output, sizeof expected_output, "test%02d-output.txt", idx);
    snprintf(result_file, sizeof result_file, "result%02d.txt", idx);

    FILE *f = fopen(input_file, "r");
    if (!f) {
        fprintf(stderr, "Impossible d'ouvrir %s\n", input_file);
        return -1;
    }

    int n_books = 0;
    if (fscanf(f, "%d", &n_books) != 1 || n_books < 0) {
        fprintf(stderr, "Format invalide (n_books) dans %s\n", input_file);
        fclose(f);
        return -1;
    }

    int *id_books = (int*)malloc((size_t)n_books * sizeof(int));
    if (!id_books) {
        fprintf(stderr, "malloc id_books failed\n");
        fclose(f);
        return -1;
    }
    for (int i = 0; i < n_books; i++) {
        if (fscanf(f, "%d", &id_books[i]) != 1) {
            fprintf(stderr, "Format invalide dans id_books (%s)\n", input_file);
            free(id_books); fclose(f); return -1;
        }
    }

    int n2 = 0;
    if (fscanf(f, "%d", &n2) != 1 || n2 < 0) {
        fprintf(stderr, "Format invalide (n2) dans %s\n", input_file);
        free(id_books); fclose(f); return -1;
    }

    int *tab2 = (int*)malloc((size_t)n2 * sizeof(int));
    if (!tab2) {
        fprintf(stderr, "malloc tab2 failed\n");
        free(id_books); fclose(f); return -1;
    }
    for (int i = 0; i < n2; i++) {
        if (fscanf(f, "%d", &tab2[i]) != 1) {
            fprintf(stderr, "Format invalide dans tab2 (%s)\n", input_file);
            free(id_books); free(tab2); fclose(f); return -1;
        }
    }
    fclose(f);

    Noeud *racine = construire_avl_depuis_tableau(id_books, n_books);

    FILE *fr = fopen(result_file, "w");
    if (!fr) {
        fprintf(stderr, "Impossible de creer %s\n", result_file);
        liberer_avl(racine);
        free(id_books); free(tab2);
        return -1;
    }

    for (int i = 0; i < n2; i++) {
        int val = tab2[i];
        int present = (rechercher(racine, val) != NULL);

        if (present) {
            fprintf(fr, "YES\n");
        } else {
            fprintf(fr, "NO\n");
        }
    }
    fclose(fr);

    int same = fichiers_identiques_relaxes(result_file, expected_output);

    liberer_avl(racine);
    free(id_books);
    free(tab2);
    return same;
}

// ---------- Programme principal ----------

int main(void)
{
    int ret = 0;
    for (int idx = 1; idx <= 10; idx++) {
        printf("=== Test %02d ===\n", idx);
        int same = traiter_un_test(idx);
        if (same == -1) {
            ret = 1;
            printf("False (erreur de traitement)\n");
        } else {
            printf("%s\n", same ? "True" : "False");
            if (!same) ret = 1;
        }
    }
    return ret;
}
