#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>


using namespace std;

struct numar {
    int v; // valoarea din lista
    numar *urm; // legatura catre urmatorul element din lista
}; // structura elemente lista simplu inlantuita

struct numar2 {
    int v;
    numar2 *urm;
    numar2 *prec;
};

struct lista2 {
    numar2 *prim;
    numar2 *ultim;
};

struct monom {
    int grad;
    float coef;
    monom *urm;
};

struct caracter{
    char car;
    caracter *urm;
};


// ########################  CAOPITOLUL 1: PROBLEME DIVERSE  ########################

void ec2(float a, float b, float c) {
    float delta = b * b - 4 * a * c;
    if (delta >= 0) {
        cout << "x1 = " << (-b + sqrt(delta)) / (2 * a) << "\nx2 = " << (-b - sqrt(delta)) / (2 * a) << endl;
    }
    if (delta < 0) {
        float im = sqrt(-delta) / (2 * a);
        float re = -b / (2 * a);
        if (im < 0) {
            cout << "x1 = " << re << " -i " << -im;
            cout << "\nx2 = " << re << " +i " << -im << endl;
        } else {
            cout << "x1 = " << re << " -i " << im;
            cout << "\nx2 = " << re << " +i " << im << endl;
        }
    }
} //REZOLVAREA ECUATIEI DE GR. 2

void inmultire_matrici(int n, int m, int p, float A[10][10], float B[10][10]) {
    float rezultat[n][p];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            rezultat[i][j] = 0;
            for (int k = 0; k < m; k++) {
                rezultat[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << rezultat[i][j] << " ";
        cout << "\n";
    }
} //INMULTIREA A DOUA MATRICI

bool nrprim(int n) {
    if (n == 2 || n == 1) return true;
    if (n % 2 == 0) return false;
    for (int i = 2; i * i < n; i++) if (n % i == 0) return false;
    return true;
} //VERIFICARE NUMAR PRIM

void schimbare_baza(int n, int b) {
    if (n > 0)
        schimbare_baza(n / b, b);
    if (n != 0) cout << n % b;
    cout << endl;
} //FUNCTIE RECURSIVA PENTRU SCHIMBAREA BAZEI

// ########################  CAOPITOLUL 2: ALGORITMI DE SORTARE  ########################

void Interclasare(int s, int m, int d, float x[100]) {
    int i = s;
    int j = m + 1;
    int k = 0;
    float y[100];

    while (i <= m and j <= d) {
        if (x[i] <= x[j]) y[k++] = x[i++];
        else y[k++] = x[j++];
    }
    if (i <= m)
        for (int r = i; r <= m; r++)
            y[k++] = x[r];

    if (j <= d)
        for (int r = j; r <= d; r++)
            y[k++] = x[r];

    for (int r = 0; r < k; r++) x[s + r] = y[r];
}

int numarCifre(int x) {
    int nr_cifre = 0;

    if (x == 0)
        return 1;
    else
        while (x > 0) {
            nr_cifre++;
            x = x / 10;
        }
    return nr_cifre;
}

void BubbleSort(int n, float x[100]) {
    bool sortat; // ok este true daca sirul este ordonat crescator, este false, altfel
    cout << "\nSortare Bubble\n\n";
    do {
        sortat = true;
        for (int i = 0; i <= n - 2; i++) {
            if (x[i] > x[i + 1]) {
                sortat = false;
                float aux = x[i];
                x[i] = x[i + 1];
                x[i + 1] = aux;
            }
        }
    } while (not sortat);
}

void SelectionSort(int n, float x[100]) {
    cout << "\nSortare Selection\n\n";
    for (int j = 0; j <= n - 2; j++) {
        float minim = x[j];
        int poz = j;
        for (int k = j + 1; k <= n - 1; k++) {
            if (x[k] < minim) {
                minim = x[k];
                poz = k;
            }
        }
        if (poz != j) swap(x[poz], x[j]);
    }
}

void CountingSort(int n, float x[100]) {
    cout << "\nSortare Counting\n\n";
    int c[100] = {0};
    for (int i = 0; i <= n - 2; i++) {
        for (int j = i + 1; j <= n - 1; j++) {
            if (x[i] <= x[j]) c[j]++;
            else c[i]++;
        }
    }
    float y[n];
    copy_n(x, n, y);
    for (int j = 0; j <= n - 1; j++) x[c[j]] = y[j];
}

void MergeSort(int s, int d, float x[100]) {
    if (s < d) {
        int m = (s + d) / 2;
        MergeSort(s, m, x);
        MergeSort(m + 1, d, x);
        Interclasare(s, m, d, x);
    }
}

void QuickSort(int s, int d, float x[100]) {
    if (s < d) {
        float pivot = x[s];
        int c = 0;
        for (int i = s + 1; i <= d; i++) if (x[i] <= pivot) c++;
        swap(x[s], x[s + c]);
        int i = s;
        int j = d;
        while (i < j) {
            while (x[i] < pivot) i++;
            while (x[j] >= pivot) j--;
            if (i < j) {
                swap(x[i], x[j]);
                if (i < d) i++;
                if (j > s) j--;
            }
        }
        QuickSort(s, s + c - 1, x);
        QuickSort(s + c + 1, d, x);
    }
}

void InsertionSort(int n, float x[100]) {
    for (int i = 0; i < n; i++) {
        float aux = x[i];
        int j = i - 1;
        while (j >= 0 && aux < x[j]) {
            x[j + 1] = x[j];
            j--;
        }
        x[j + 1] = aux;
    }
}

void ShellSort(int n, float x[100]) {
    int pas = n / 2;
    while (pas >= 1) {
        int i = 0;
        while ((i + pas) <= (n - 1)) {
            int j = i;
            float aux = x[i + pas];
            while (x[j] > aux and j >= 0) {
                x[j + pas] = x[j];
                j = j - pas;
            }
            x[j + pas] = aux;
            i++;
        }
        pas = pas / 2;
    }
}

void RadixSort(int n, int x[100]) {
    int y[50];
    int max_x = 0;
    for (int i = 0; i <= n; i++)
        if (max_x < x[i]) max_x = x[i];
    int M = numarCifre(max_x);
    int C[n][M];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = 0;
    int i, k;
    for (i = 0; i <= n - 1; i++) {
        if (x[i] != 0) {
            int m = x[i];
            k = 0;
            while (m > 0) {
                C[i][M - 1 - k] = m % 10;
                k++;
                m = m / 10;
            }
        }
    }

    for (int j = M - 1; j >= 0; j--) {
        i = 0;
        for (k = 0; k <= 9; k++)
            for (int s = i; s <= n - 1; s++) {
                if (C[s][j] == k) {
                    for (int r = 0; r <= M - 1; r++)
                        y[r] = C[s][r];

                    for (int p = s - 1; p >= i; p--)
                        for (int r = 0; r <= M - 1; r++)
                            C[p + 1][r] = C[p][r];

                    for (int r = 0; r <= M - 1; r++)
                        C[i][r] = y[r];
                    i++;
                }
            }
    }
    for (int i1 = 0; i1 <= n - 1; i1++) {
        for (int j1 = 0; j1 <= M - 1; j1++)
            cout << C[i1][j1] << " ";
        cout << endl;
    }
}

void CautareSecventiala(int n, float x[100], float y) {
    int nr_aparitii = 0;
    for (int i = 0; i < n; i++) if (x[i] == y) nr_aparitii++;
    if (nr_aparitii == 0) cout << "Nu s-a gasit elementul in sir!";
    if (nr_aparitii == 1) cout << "Elementul " << y << " apare o data in sir.\n";
    if (nr_aparitii != 1) cout << "Elementul " << y << " apare de " << nr_aparitii << " ori in sir.\n";
}

void CautareBinara(int s, int d, float x[100], float y) {
    if (y < x[s] or y > x[d]) {
        cout << "Nu s-a gasit elementul in sir!\n";
        return;
    }
    if (s < d) {
        //exista minim 2 elemente in sir
        int m = (s + d) / 2;
        if (x[m] == y) {
            cout << "Elementul cautat se afla in sir pe pozitia " << m << "\n";
            return;
        }
        if (y < x[m] and s <= m - 1) CautareBinara(s, m - 1, x, y);
        if (y > x[m]) CautareBinara(m + 1, d, x, y);
    } else {
        // sirul are doar un element ( s==d )
        if (x[s] == y)
            cout << "Elementul cautat se afla in sir pe pozitia " << s << "\n";
        else
            cout << "Nu s-a gasit elementul in sir!\n";
    }
}

// ########################  CAOPITOLUL 3: Liste dinamice  ########################

// Liste simplu inlantuite

numar *creare_lista() {
    numar *cap, *u, *c;
    int x, n;
    cout << "creare lista!" << endl;
    // creare capat lista
    cout << "Valoare cap lista x = ";
    cin >> x;
    cap = new numar;
    cap->v = x;
    cap->urm = NULL;
    u = cap; // ultimul element din lista
    cout << "Numarul de elemente care se adauga in lista la cearea listei n = ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Valoare de adaugat in lista x = ";
        cin >> x;
        c = new numar;
        c->v = x;
        c->urm = NULL;
        u->urm = c; // stabileste legatura intre ultimul elemnt si noul element adaugat
        u = c; // c devine ultimul element
    }
    return cap;
}

void parcurgere_lista(numar *cap) {
    numar *c;
    if (cap == NULL)
        cout << "Lista este vida!" << endl;
    else {
        c = cap;
        while (c != NULL) {
            cout << c->v << " ";
            c = c->urm;
        }
    }
}

numar *stergere_din_lista(numar *cap) {
    int cont = 0;
    int s;

    numar *c, *p;

    do {
        if (cap == NULL)
            cout << "Lista este vida! Nu sunt valori de sters!" << endl;
        else {
            //sterge elementul cu valoarea s de cate ori apare in lista
            cout << "Valoare de sters s = ";
            cin >> s;
            int nrs = 0; // numara de cate ori am sters s din lista
            // stergem valoarea s daca se afla la inceput la lista
            while (cap->v == s) {
                cap = cap->urm;
                nrs++;
                if (cap == NULL)
                    break;
            }
            if (cap != NULL) {
                c = cap->urm;
                p = cap; // precedentul elementului curent c
                while (c != NULL) {
                    if (c->v == s) {
                        // sterge din lista pe c
                        p->urm = c->urm;
                        nrs++;
                        c = c->urm;
                    } else {
                        p = c;
                        c = c->urm;
                    }
                }
            }
            cout << "Elementul de sters " << s << " a fost sters de " << nrs << " ori" << endl;
            cout << "Lista ramasa este: ";
            parcurgere_lista(cap);
            cout << endl;
        }
        cout << "Continua stergerea [0/1]? ";
        cin >> cont;
    } while (cont);
    return cap;
}

numar *adaugare_in_lista(numar *cap, int a) {
    int opa;
    numar *p;
    do {
        cout << endl << "Tip adaugare:" << endl;
        cout << "1. Adaugare la inceput de lista:" << endl;
        cout << "2. Adaugare dupa element din interiorul listei:" << endl;
        cout << "3. Adaugare la sfarsitul listei:" << endl;
        cout << "0. Incheiere adaugare!" << endl;
        cout << "Optiune adaugare: ";
        cin >> opa;
        switch (opa) {
            case 1: // adauga la inceput
                p = new numar;
                p->v = a;
                p->urm = cap;
                cap = p;
                parcurgere_lista(cap);
                cout << endl;
                break;
            case 2: // adauga dupa elemnet cu valoare dat din lista
                // citim valoarea dupa care se adauga
                int y;
                numar *c; // c - elementul curent din lista
                cout << "Valoare dupa care se face adaugarea y = ";
                cin >> y;
                c = cap;
                while (c != NULL) {
                    if (c->v == y) {
                        // adauga valoare a dupa y
                        if (c->urm == NULL) // c este ultimul element din lista
                        {
                            p = new numar;
                            p->v = a;
                            p->urm = NULL;
                            c->urm = p;
                            c = c->urm;
                        } else // c se afla in interiorul listei
                        {
                            p = new numar;
                            p->v = a;
                            p->urm = c->urm;
                            c->urm = p;
                            c = c->urm;
                        }
                    }
                    c = c->urm;
                } // end while *c
                parcurgere_lista(cap);
                cout << endl;
                break;
            case 3: // adauga la sfarsitul la listei
                numar *u;
                u = cap;
            //urgem lista pentru a ajunge la ultimul element
                while (u->urm != NULL)
                    u = u->urm;
                p = new numar;
                p->v = a;
                p->urm = NULL;
                u->urm = p;
                parcurgere_lista(cap);
                cout << endl;
                break;
            case 0:
                cout << "incheiat adaugare!" << endl;
                break;
            default:
                cout << "Optiune invalida!" << endl;
                break;
        } // end switch
    } while (opa);
    return cap;
}

numar *modificare_in_lista(numar *cap, int y, int w) {
    numar *c;
    for (c = cap; c != NULL; c = c->urm) {
        if (c->v == y)
            c->v = w;
    }
    return cap;
}

//lista simplu inlantuita ordonata din citire
numar *creare_lista_ordonata() {
    numar *cap, *u, *c;
    int x, n;
    // creare capat lista
    cout << "Valoare cap lista x = ";
    cin >> x;
    cap = new numar;
    cap->v = x;
    cap->urm = NULL;
    u = cap; // ultimul element din lista
    cout << "Numarul de elemente care se adauga in lista la cearea listei n = ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Valoare de adaugat in lista x = ";
        cin >> x;
        c = new numar;
        c->v = x;
        c->urm = NULL;
        if (x < cap->v) {
            c->urm = cap;
            cap = c;
        } else {
            numar *p;
            p = cap;
            while (p->urm != NULL && p->urm->v < x)
                p = p->urm;
            c->urm = p->urm;
            p->urm = c;
        }
    }
    return cap;
}

numar *adaugare_in_lista_ordonat(numar *cap, int a) {
    // adaugare element in lista ordonata
    numar *p;
    if (a < cap->v) {
        p = new numar;
        p->v = a;
        p->urm = cap;
        cap = p;
    } else {
        numar *c;
        c = cap;
        while (c->urm != NULL && c->urm->v < a)
            c = c->urm;
        p = new numar;
        p->v = a;
        p->urm = c->urm;
        c->urm = p;
    }
    return cap;
}

// Liste dublu inlantuite

lista2 *creare_lista2() {
    lista2 *L;
    L = new lista2;
    L->prim = NULL;
    L->ultim = NULL;
    int x, n;
    cout << "Creare lista dublu inlantuita!" << endl;
    cout << "Numarul de elemente care se adauga in lista la cearea listei n = ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Valoare de adaugat in lista x = ";
        cin >> x;
        numar2 *c;
        c = new numar2;
        c->v = x;
        c->urm = NULL;
        c->prec = L->ultim;
        if (L->prim == NULL) {
            L->prim = c;
            L->ultim = c;
        } else {
            L->ultim->urm = c;
            L->ultim = c;
        }
    }
    return L;
}

void parcurgere_lista2_directa(lista2 *L) {
    numar2 *c;
    c = L->prim;
    if (c == NULL) {cout << "Lista este vida!";}
    else {
        while (c != NULL) {
            cout << c->v << " ";
            c = c->urm;
        }
    }
}

void parcurgere_lista2_inversa(lista2 *L) {
    numar2 *c;
    c = L->ultim;
    if (c == NULL)
        cout << "Lista este vida!";
    else {
        while (c != NULL) {
            cout << c->v << " ";
            c = c->prec;
        }
    }
}

lista2 *adaugare_in_lista2(lista2 *L, int a) {
    int opa;
    numar2 *p;
    do {
        cout << endl << "Tip adaugare:" << endl;
        cout << "1. Adaugare la inceput de lista:" << endl;
        cout << "2. Adaugare dupa element din interiorul listei:" << endl;
        cout << "3. Adaugare la sfarsitul listei:" << endl;
        cout << "0. Incheiere adaugare!" << endl;
        cout << "Optiune adaugare: ";
        cin >> opa;
        switch (opa) {
            case 1: // adauga la inceput
                p = new numar2;
                p->v = a;
                p->urm = L->prim;
                p->prec = NULL;
                L->prim->prec = p;
                L->prim = p;
                parcurgere_lista2_directa(L);
                cout << endl;
                break;
            case 2: // adauga dupa elemnet cu valoare dat din lista
                // citim valoarea dupa care se adauga
                int y;
                numar2 *c; // c - elementul curent din lista
                cout << "Valoare dupa care se face adaugarea y = ";
                cin >> y;
                c = L->prim;
                while (c != NULL) {
                    if (c->v == y) {
                        // adauga valoare a dupa y
                        if (c->urm == NULL) // c este ultimul element din lista
                        {
                            p = new numar2;
                            p->v = a;
                            p->urm = NULL;
                            p->prec = c;
                            c->urm = p;
                            c = c->urm;
                        } else // c se afla in interiorul listei
                        {
                            p = new numar2;
                            p->v = a;
                            p->urm = c->urm;
                            p->prec = c;
                            c->urm->prec = p;
                            c->urm = p;
                            c = c->urm;
                        }
                    }
                    c = c->urm;
                } // end while *c
                parcurgere_lista2_directa(L);
                cout << endl;
                break;
            case 3: // adauga la sfarsitul la listei
                numar2 *u;
                u = L->prim;
                while (u->urm != NULL)
                    u = u->urm;
                p = new numar2;
                p->v = a;
                p->urm = NULL;
                p->prec = u;
                u->urm = p;
                L->ultim = p;
                parcurgere_lista2_directa(L);
                cout << endl;
                break;
            case 0:
                cout << "incheiat adaugare!" << endl;
                break;
            default:
                cout << "Optiune invalida!" << endl;
                break;
        }
    } while (opa);
    return L;
}

lista2 *stergere_din_lista2(lista2 *L) {
    int cont = 0;
    int s;
    numar2 *c;
    do {
        if (L->prim == NULL)
            cout << "Lista este vida! Nu sunt valori de sters!" << endl;
        else {
            //sterge elementul cu valoarea s de cate ori apare in lista
            cout << "Valoare de sters s = ";
            cin >> s;
            int nrs = 0; // numara de cate ori am sters s din lista
            // stergem valoarea s daca se afla la inceput la lista
            while (L->prim->v == s) {
                L->prim = L->prim->urm;
                L->prim->prec = NULL;
                nrs++;
                if (L->prim == NULL)
                    break;
            }
            if (L->prim != NULL) {
                c = L->prim->urm;
                while (c != NULL) {
                    if (c->v == s) {
                        // sterge din lista pe c
                        c->prec->urm = c->urm;
                        if (c->urm != NULL)
                            c->urm->prec = c->prec;
                        nrs++;
                        c = c->urm;
                    } else {
                        c = c->urm;
                    }
                }
            }
            cout << "Elementul de sters " << s << " a fost sters de " << nrs << " ori" << endl;
            cout << "Lista ramasa este: ";
            parcurgere_lista2_directa(L);
            cout << endl;
        }
        cout << "Continua stergerea [0/1]? ";
        cin >> cont;
    } while (cont);
    return L;
}

lista2 *modificare_in_lista2(lista2 *L, int y, int w) {
    numar2 *c;
    for (c = L->prim; c != NULL; c = c->urm) {
        if (c->v == y)
            c->v = w;
    }
    return L;
}

// Stive

numar *creare_stiva() {
    numar *c, *d;
    int x, n;
    cout << "Creare stiva!" << endl;
    // creare capat stiva
    cout << "Introduceti primul element din stiva, x = ";
    cin >> x;
    c = new numar;
    c->v = x;
    c->urm = NULL;
    cout << "Numarul de elemente care se adauga in stiva la crearea stivei n = ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Valoare de adaugat in stiva x = ";
        cin >> x;
        d = new numar;
        d->v = x;
        d->urm = c;
        c = d;
    }
    return c;
}

void parcurgere_stiva(numar *cap) {
    numar *s;
    if (cap == NULL)
        cout << "Stiva este vida!" << endl;
    else {
        s = cap;
        while (s != NULL) {
            cout << s->v << " ";
            s = s->urm;
        }
    }
}

numar *adaugare_in_stiva(numar *c, int x) {
    numar *d;
    d = new numar;
    d->v = x;
    d->urm = c;
    return d;
}

numar *stergere_din_stiva(numar *cap) {
    numar *c = nullptr;
    if (cap == NULL){
        cout << "Stiva este vida! Nu sunt valori de sters!" << endl;
        return NULL;
    }
    c = cap->urm;
    c->v = (cap->urm)->v;
    delete cap;
    return c;
}

// ########################  CAOPITOLUL 3: Cozi  ########################

lista2 *creare_coada() {
    lista2 *L;
    L = new lista2;
    L->prim = NULL;
    L->ultim = NULL;
    int x, n;
    cout << "Creare coada!" << endl;
    cout << "Numarul de elemente care se adauga in coada: n = ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Valoare de adaugat in coada: x = ";
        cin >> x;
        numar2 *c;
        c = new numar2;
        c->v = x;
        c->urm = NULL;
        c->prec = L->ultim;
        if (L->prim == NULL) {
            L->prim = c;
            L->ultim = c;
        } else {
            L->ultim->urm = c;
            L->ultim = c;
        }
    }
    return L;
}

lista2 *adaugare_in_coada(lista2 *L, int x) {
    numar2 *c;
    c = new numar2;
    c->v = x;
    c->urm = NULL;
    c->prec = L->ultim;
    if (L->prim == NULL) {
        L->prim = c;
        L->ultim = c;
    } else {
        L->ultim->urm = c;
        L->ultim = c;
    }
    return L;
}

lista2 *stergere_din_coada(lista2 *L) {
    if (L->prim == NULL)
        cout << "Coada este vida! Nu sunt valori de sters!" << endl;
    else {
        ((L->prim)->urm)->prec = NULL;
        L->prim = (L->prim)->urm;
    }
    return L;
}

void parcurgere_coada(lista2 *L) {
    numar2 *c;
    c = L->prim;
    if (c == NULL)
        cout << "Coada este vida!";
    else {
        while (c != NULL) {
            cout << c->v << " ";
            c = c->urm;
        }
    }
}

// ########################  CAOPITOLUL 3: Interclasarea a doua liste ordonate  ########################

numar *interclasare_liste(numar *L1, numar *L2) {
    numar *L = new numar;
    numar *p1, *p2;
    if (L1->v < L2->v) {
        L->v = L1->v;
        L->urm = NULL;
        p1 = L1->urm;
        p2 = L2;
    } else {
        L->v = L2->v;
        L->urm = NULL;
        p1 = L1;
        p2 = L2->urm;
    }
    numar *u = L;
    numar *c;

    while (p1 != NULL and p2 != NULL) {
        c = new numar;
        if (p1->v < p2->v) {
            c->v = p1->v;
            c->urm = NULL;
            p1 = p1->urm;
        } else {
            c->v = p2->v;
            c->urm = NULL;
            p2 = p2->urm;
        }
        u->urm = c;
        u = c;

        if (p1!=NULL) {
            while (p1!= NULL) {
                c = new numar;
                c->v = p1->v;
                c->urm = NULL;
                u->urm = c;
                u = c;
                p1 = p1->urm;
            }
            if (p2!=NULL) {
                while (p2!= NULL) {
                    c = new numar;
                    c->v = p2->v;
                    c->urm = NULL;
                    u->urm = c;
                    u = c;
                    p2 = p2->urm;
                }
            }
        }
        return L;
    }
    return L;
}

// ########################  CAOPITOLUL 3: Adunarea si inmultirea a doua polinoame  ########################

monom *crearePolinom() {
    monom *p;
    p = new monom;
    p->coef = 0;
    p->grad = 0;
    p->urm = NULL;
    int n;
    cout << "Numarul de monoame care se adauga in polinom n = ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        monom *c;
        c = new monom;
        cout << "Introduceti coeficientul si gradul monomului: ";
        cin >> c->coef;
        cout << "x^";
        cin >> c->grad;
        c->urm = NULL;
        if (p->urm == NULL) {
            p->urm = c;
        } else {
            monom *u;
            u = p;
            while (u->urm != NULL)
                u = u->urm;
            u->urm = c;
        }
    }
    return p;
}

void adunarePolinoame(monom *p1, monom *p2) {
    monom *p3 = new monom;
    monom *c1 = p1->urm;
    monom *c2 = p2->urm;
    monom *c3 = p3;
    while (c1 != NULL and c2 != NULL) {
        if (c1->grad == c2->grad) {
            c3->coef = c1->coef + c2->coef;
            c3->grad = c1->grad;
            c1 = c1->urm;
            c2 = c2->urm;
        } else if (c1->grad > c2->grad) {
            c3->coef = c1->coef;
            c3->grad = c1->grad;
            c1 = c1->urm;
        } else {
            c3->coef = c2->coef;
            c3->grad = c2->grad;
            c2 = c2->urm;
        }
        c3->urm = new monom;
        c3 = c3->urm;
        c3->urm = NULL;
    }
    if (c1 != NULL) {
        while (c1 != NULL) {
            c3->coef = c1->coef;
            c3->grad = c1->grad;
            c1 = c1->urm;
            c3->urm = new monom;
            c3 = c3->urm;
            c3->urm = NULL;
        }
    }
    if (c2 != NULL) {
        while (c2 != NULL) {
            c3->coef = c2->coef;
            c3->grad = c2->grad;
            c2 = c2->urm;
            c3->urm = new monom;
            c3 = c3->urm;
            c3->urm = NULL;
        }
    }
    c3 = p3;
    while (c3->urm->urm != NULL) {
        cout << c3->coef << "x^" << c3->grad << " + ";
        c3 = c3->urm;
    }
    cout << c3->coef << "x^" << c3->grad << endl;
}

void sorteazaPolinom(monom *p3) {
    if (!p3 || !p3->urm) {
        return; // Lista are mai puțin de 2 noduri - deja este sortată.
    }
    bool sortat;
    do {
        sortat = true;
        monom* prev = NULL; // Pointer pentru nodul anterior.
        monom* current = p3;  // Pointer pentru nodul curent.
        while (current->urm != NULL) {
            if (current->grad < current->urm->grad) {
                // Schimbă nodurile current și current->urm.
                sortat = false;
                monom* next = current->urm;
                current->urm = next->urm;
                next->urm = current;
                if (prev == NULL) {
                    // Dacă schimbăm la începutul listei.
                    p3 = next;
                } else {
                    // Dacă schimbăm în interiorul listei.
                    prev->urm = next;
                }
                // Ajustează prev și current.
                prev = next;
            } else {
                // Trecem la următorul nod.
                prev = current;
                current = current->urm;
            }
        }
    } while (!sortat);
}

void inmulirePolinoame(monom *p1, monom *p2) {
   //Functie pentru inmultirea a doua polinoame
    monom *p3 = new monom;
    monom *c1 = p1->urm;
    monom *c2 = p2->urm;
    monom *c3 = p3;
    while (c1 != NULL) {
        while (c2 != NULL) {
            c3->coef = c1->coef * c2->coef;
            c3->grad = c1->grad + c2->grad;
            c2 = c2->urm;
            c3->urm = new monom;
            c3 = c3->urm;
            c3->urm = NULL;
        }
        c1 = c1->urm;
        c2 = p2->urm;
    }
    c3 = p3;

    //Ordonarea polinomului rezultat
    sorteazaPolinom(c3);
    while (c3->urm->urm != NULL) {
        cout << c3->coef << "x^" << c3->grad << " + ";
        c3 = c3->urm;
    }
    cout << c3->coef << "x^" << c3->grad << endl;
}

// ########################  CAOPITOLUL 3: Verificarea parantezelor intr-o expresie aritmetica  ########################

caracter *stergereDinStivaCaractere(caracter *cap) {
    if (cap == NULL){
        cout << "Stiva este vida! Nu sunt valori de sters!" << endl;
        return NULL;
    }
    caracter *c= cap->urm;
    delete cap;
    return c;
}

bool verificareParanteze(const string sir){
    caracter *paranteze = NULL;

    for (int i=0; i<sir.length();i++) {
        char c = sir[i]; // Caracterul curent
        // Dacă este o paranteză deschisă, o adăugăm în stivă
        if (c == '(' || c == '{' || c == '[') {
            caracter *d = new caracter;
            d->car = c;
            d->urm = paranteze;
            paranteze = d;
        }
        // Dacă este o paranteză închisă
        else if (c == ')' || c == '}' || c == ']') {
            // Verificăm dacă stiva este goală sau paranteza nu se potrivește
            if (paranteze == NULL) {
                return false; // Nu există o paranteză deschisă pentru aceasta
            }
            char top = paranteze->car; // Paranteza de pe vârful stivei
            paranteze = stergereDinStivaCaractere(paranteze); // Scoatem paranteza deschisă din stivă

            // Verificăm dacă paranteza închisă se potrivește cu cea de pe vârful stivei
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false; // Paranteza nu se potrivește
                }
        }
    }
    // Verificăm dacă există paranteze deschise care nu au fost închise
    return paranteze == NULL;
}

// ########################  CAOPITOLUL 4: Grafuri  ########################


int main() // PROGRAM PRINCIPAL
{
    int op, op1, op2, op3;

    do // reia meniu principal pana la exit
    {
        // meniu principal
        cout << "PROGRAME SDA\n";
        cout << "1. Probleme diverse\n";
        cout << "2. Algoritmi de sortare\n";
        cout << "3. Liste dinamica\n";
        cout << "4. Grafuri\n";
        // se vor adauga optiuni
        cout << "0. Exit program." << endl;

        cout << "Optiune : ";
        cin >> op;

        switch (op) // switch pentru optiune meniu principal
        {
            case 1: //Probleme diverse (laborator 1)
                do {
                    cout << "\nProbleme diverse\n";
                    cout << "1.1. Rezolvarea ecuatiei de gradul al doilea\n";
                    cout << "1.2. Inmultire de matrici\n";
                    cout << "1.3. Verificare numar prim\n";
                    cout << "1.4. Schimbare baza numar natural\n";
                    cout << "1.0. Exit probleme diverse!" << endl;

                    cout << "Optiune probleme diverse : ";
                    cin >> op1;

                    switch (op1) {
                        case 1: {
                            float a, b, c;
                            cout << "\nIntroduceti, in ordine, coeficientii ecuatiei de gradul al doilea: ";
                            cin >> a >> b >> c;
                            cout << "\nSolutia ecuatiei de gradul al doilea este: " << endl;
                            ec2(a, b, c);
                        } //ECUATIE DE GRADUL 2
                        break;

                        case 2: {
                            int n, m, p;
                            cout << "\nIntroduceti dimensiunile matricelor: ";
                            cin >> n >> m >> p;
                            float A[10][10], B[10][10];
                            cout << "\nIntroduceti elementele matricei A: ";
                            for (int i = 0; i < n; i++)
                                for (int j = 0; j < m; j++) {
                                    cin >> A[i][j];
                                }
                            cout << "\nIntroduceti elementele matricei B: ";
                            for (int i = 0; i < n; i++)
                                for (int j = 0; j < m; j++) {
                                    cin >> B[i][j];
                                }
                            cout << "\nRezultatul inmultirii matricelor este: " << endl;
                            inmultire_matrici(n, m, p, A, B);
                        } //INMULTIRE MATRICE
                        break;

                        case 3: {
                            int n;
                            cout << "\nn=";
                            cin >> n;
                            int ok = nrprim(n); //ok=0 nu e numar prim
                            if (ok == 0)
                                cout << "\nNumarul " << n << " nu e numar prim ";
                            else
                                cout << "\nNumarul " << n << " este numar prim " << endl;
                        } //NUMAR PRIM
                        break;

                        case 4: {
                            int n, b;
                            cout << "\nIntroduceti numarul: ";
                            cin >> n;
                            cout << "\nIn ce baza vreti sa schimbati numarul? ";
                            cin >> b;
                            cout << "\nNumarul introdus, scris in baza " << b << " este: ";
                            schimbare_baza(n, b);
                        } //SCHIMBARE BAZA
                        break;

                        case 0:
                            cout << "A terminat submeniu 1\n\n";
                            break;

                        default:
                            cout << "Optiune invalida!\n";
                            break;
                    }
                } while (op1 != 0);
                break;

            case 2: //algoritmi de sortare
            {
                int n;
                float v[100], w[100];
                // citim sirul
                cout << "n= ";
                cin >> n;
                cout << "Sirul este: ";
                for (int i = 0; i < n; i++)
                    cin >> v[i];

                do {
                    cout << "\nAlgoritmi de sortare\n";
                    cout << "2.1. Algoritm Bubble Sort \n";
                    cout << "2.2. Counting Sort \n";
                    cout << "2.3. Selection Sort \n";
                    cout << "2.4. Quicksort \n";
                    cout << "2.5. Merge Sort \n";
                    cout << "2.6. Insertion Sort \n";
                    cout << "2.7. Shell Sort \n";
                    cout << "2.8. Radix Sort \n";
                    cout << "2.9. Cautarea secventiala intr-un sir \n";
                    cout << "2.10. Cautarea binara intr-un sir \n";
                    cout << "2.0. Exit algoritmi de sortare!\n";


                    cout << "\nOptiune algoritmi de sortare: ";
                    cin >> op2;
                    switch (op2) {
                        case 1: {
                            cout << "\nVectorul initial este:\n";
                            for (int i = 0; i < n; i++)
                                cout << v[i] << " ";
                            cout << '\n';
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            BubbleSort(n, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu BubbleSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } //Bubble Sort
                        break;

                        case 2: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            CountingSort(n, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu CountingSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } // Counting Sort
                        break;

                        case 3: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            SelectionSort(n, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu SelectionSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } //Selection Sort
                        break;

                        case 4: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            QuickSort(0, n - 1, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu QuickSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } //Quick Sort
                        break;

                        case 5: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            MergeSort(0, n - 1, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu MergeSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } //Merge Sort
                        break;

                        case 6: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            InsertionSort(n, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu InsertionSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } //Insertion Sort
                        break;

                        case 7: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            ShellSort(n, w); // w este vectorul ordonat
                            cout << "Vectorul ordonat cu ShellSort este:\n";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << '\n';
                        } //Shell Sort
                        break;

                        case 8: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            cout << "Matricea ordonata cu RadixSort este:\n";
                            RadixSort(n, reinterpret_cast<int *>(w)); // w este vectorul ordonat
                        } //Radix Sort
                        break;

                        case 9: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            cout << "\nIntroduceti elementul pe care il cautati: ";
                            float y;
                            cin >> y;
                            CautareSecventiala(n, w, y);
                        }
                        break;

                        case 10: {
                            for (int i = 0; i < n; i++)
                                w[i] = v[i];
                            QuickSort(0, n - 1, w);
                            cout << "\nSirul sortat este: ";
                            for (int i = 0; i < n; i++)
                                cout << w[i] << " ";
                            cout << "\nIntroduceti elementul pe care il cautati: ";
                            float y;
                            cin >> y;
                            CautareBinara(0, n - 1, w, y);
                        } //Cautare binara
                        break;

                        case 0:
                            cout << "A terminat submeniu 2" << endl << endl;
                            break;

                        default:
                            cout << "Optiune invalida!" << endl;
                            break;
                    }
                } while (op2 != 0);
            }
            break;

            case 3: //Liste dinamice
            {
                do {
                    cout << endl << "Liste dinamice" << endl;
                    cout << "3.1. Liste simplu inlantuite " << endl;
                    cout << "3.2. Aplicatie: Lista simplu inlantuite ordonata din citire" << endl;
                    cout << "3.3. Liste dublu inlantuite " << endl;
                    cout << "3.4. Stive " << endl;
                    cout << "3.5. Cozi " << endl;
                    cout << "3.6. Aplicatia 1: Adunarea si inmultirea a doua polinoame " << endl;
                    cout << "3.7. Aplicatia 2: Interclasarea a doua liste ordonate " << endl;
                    cout << "3.8. Aplicatia 3: Verificarea parantezelor intr-o expresie aritmetica " << endl;
                    cout << "3.0. Exit liste dinamice!" << endl;

                    cout << "Optiune liste dinamice: ";
                    cin >> op3;
                    switch (op3) {
                        case 1: //liste simplu inlatuite
                        {
                            numar *lista;
                            // creare lista
                            lista = creare_lista();
                            cout << "Lista dupa creare este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                            // adaugare in lista
                            int ad;
                            cout << "citeste valoare de adaugat: ";
                            cin >> ad;
                            lista = adaugare_in_lista(lista, ad);
                            cout << "Lista dupa adaugare este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                            // stergere din lista
                            lista = stergere_din_lista(lista);
                            cout << "Lista dupa stergere este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                            // modificare element in lista
                            int y, w;
                            cout << "Modificare a elementului y = ";
                            cin >> y;
                            cout << "cu valoarea w = ";
                            cin >> w;
                            lista = modificare_in_lista(lista, y, w);
                            cout << "Lista dupa modificare este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                        }
                        break;

                        case 2:
                            // Creare lista ordonata din citire
                        {
                            numar *lista;
                            // creare lista
                            cout << "Creare lista ordonata!" << endl;
                            lista = creare_lista_ordonata();
                            cout << "Lista dupa creare este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                            // adaugare in lista
                            int ad;
                            cout << "Vrei sa adaugi elemente in lista ordonata? [0/1] ";
                            cin >> ad;
                            if (ad > 0) {
                                cout << "Citeste valoare de adaugat in lista: ";
                                cin >> ad;
                                lista = adaugare_in_lista_ordonat(lista, ad);
                                cout << "Lista dupa adaugare este: ";
                                parcurgere_lista(lista);
                                cout << endl;
                            }
                            // stergere din lista
                            lista = stergere_din_lista(lista);
                            cout << "Lista dupa stergere este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                        }
                        break;

                        case 3: // Liste dublu inlatuite
                        {
                            lista2 *lista;
                            // creare lista
                            lista = creare_lista2();
                            cout << "Lista dupa creare, parcursa direct, este: ";
                            parcurgere_lista2_directa(lista);
                            cout << endl;
                            cout << "Lista dupa creare, parcursa invers, este: ";
                            parcurgere_lista2_inversa(lista);
                            cout << endl;
                            // adaugare in lista
                            int ad;
                            cout << "citeste valoare de adaugat: ";
                            cin >> ad;
                            lista = adaugare_in_lista2(lista, ad);
                            cout << "Lista dupa adaugare este: ";
                            parcurgere_lista2_directa(lista);
                            cout << endl;
                            // stergere din lista
                            lista = stergere_din_lista2(lista);
                            cout << "Lista dupa stergere este: ";
                            parcurgere_lista2_directa(lista);
                            cout << endl;
                            // modificare element in lista
                            int y, w;
                            cout << "Modificare a elementului y = ";
                            cin >> y;
                            cout << "cu valoarea w = ";
                            cin >> w;
                            lista = modificare_in_lista2(lista, y, w);
                            cout << "Lista dupa modificare este: ";
                            parcurgere_lista2_directa(lista);
                            cout << endl;
                        }
                        break;

                        case 4: //Stive
                            {
                                numar *stiva;
                                // creare stiva
                                stiva = creare_stiva();
                                cout << "Stiva dupa creare este: ";
                                parcurgere_stiva(stiva);
                                cout << endl;
                                // adaugare in stiva
                                int ad,op;
                                cout << "Citeste valoare de adaugat: ";
                                cin >> ad;
                                stiva = adaugare_in_stiva(stiva, ad);
                                cout << "Stiva dupa adaugare este: ";
                                parcurgere_stiva(stiva);
                                cout << endl;
                                // stergere din stiva
                                cout<<"Cate elemente doresti sa stergi din stiva? n = ";
                                cin>>op;
                                for(int i=0;i<op;i++)
                                    stiva = stergere_din_stiva(stiva);
                                parcurgere_stiva(stiva);
                                cout << endl;
                        }
                        break;

                        case 5: //Cozi
                            {
                                lista2 *coada;
                                // creare coada
                                coada = creare_coada();
                                cout << "Coada dupa creare este: ";
                                parcurgere_coada(coada);
                                cout << endl;
                                // adaugare in coada
                                int ad;
                                cout << "Citeste valoare de adaugat: ";
                                cin >> ad;
                                coada = adaugare_in_coada(coada, ad);
                                cout << "Coada dupa adaugare este: ";
                                parcurgere_coada(coada);
                                cout << endl;
                                // stergere din coada
                                cout<<"Cate elemente doresti sa stergi din coada? n = ";
                                int n;
                                cin>>n;
                                for(int i=0;i<n;i++)
                                    coada = stergere_din_coada(coada);
                                cout << "Coada dupa stergere este: ";
                                parcurgere_coada(coada);
                                cout << endl;
                            }
                            break;

                        case 6: //
                            {
                            //Adunare polinoame
                            monom *p1, *p2;
                            cout << "Introduceti primul polinom: "<<endl;
                            p1 = crearePolinom();
                            cout << "Introduceti al doilea polinom: ";
                            p2 = crearePolinom();
                            cout << "Rezultatul adunarii polinoamelor este: ";
                            adunarePolinoame(p1, p2);
                            cout<<endl;
                            //Inmultire polinoame
                            cout << "Rezultatul inmultirii polinoamelor este: ";
                            inmulirePolinoame(p1, p2);

                        }
                        break;

                        case 7: //
                            {
                            numar *lista1,*lista2;
                            // creare liste
                            cout<<"Introduceti elementele primei liste! "<<endl;;
                            lista1 = creare_lista_ordonata();
                            cout << "Prima lista dupa creare este: ";
                            parcurgere_lista(lista1);
                            cout << endl;

                            cout<<"Introduceti elementele celei de-a doua liste! "<<endl;;
                            lista2 = creare_lista_ordonata();
                            parcurgere_lista(lista2);
                            cout << "A doua lista dupa creare este: ";
                            cout << endl;

                            //interclasare liste
                            numar *lista = interclasare_liste(lista1, lista2);
                            cout << "Lista interclasata este: ";
                            parcurgere_lista(lista);
                            cout << endl;
                        }
                        break;

                        case 8: //
                            {
                            string expresie;
                            cout<<"Introduceti expresia: ";
                            cin>>expresie;

                            //verificare paranteze
                            cout<<"Verificare paranteze: ";
                            if(verificareParanteze(expresie))
                                cout<<"Expresia este corecta!"<<endl;
                            else
                                cout<<"Expresia nu este corecta!"<<endl;
                        }
                        break;

                        case 0:
                            cout << "A terminat submeniu 2" << endl << endl;
                            break;

                        default:
                            cout << "Optiune invalida!" << endl;
                            break;
                    }
                } while (op3 != 0);
            }
            break;

            case 0: // end Meniu principal
                cout << "Bye! Bye!" << endl;
                break;

            default:
                cout << "Optiune invalida!" << endl;
                break;
        }
    } while (op != 0); // end meniu principal

    return 0;
}
