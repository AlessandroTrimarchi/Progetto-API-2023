#include <stdio.h>
#include <stdlib.h>

struct nodo_albero 
{
    int chiave;
    struct nodo_albero* padre;
};

void aggiungi_stazione(int distanza,int** autonomie);
void aggiungi_auto(int distanza, int** autonomie);
void rottama_auto(int distanza, int** autonomie);
void demolisci_stazione(int distanza, int** autonomie);
void heapSort(int arr[], int n, int idxMapping[]);
void heapify(int arr[], int idx, int size, int idxMapping[]);
void swap(int *a, int *b);
struct nodo_albero* crea_nodo(int chiave);
void pianifica_percorso_basso_alto(int pian_distanze[], int pian_autonomie[], int dim);
void pianifica_percorso_alto_basso(int pian_distanze[], int pian_autonomie[], int dim);
void reverseArray(int arr[], int size);

int main()
{
    char nome_funzione[50];
    unsigned f, i, j, k;
    int dist;
    int num_stazioni;
    int part, arr;
    int* distanze_stazioni;
    int* primo_elemento;
    int* pian_distanze;
    int* pian_autonomie;
    int** autonomie_stazioni;

    //prime inizializzazioni, dovrebbero essere complete//
    num_stazioni=0;
    distanze_stazioni=NULL;
    primo_elemento=NULL;
    autonomie_stazioni=NULL;
    pian_distanze=NULL;
    pian_autonomie=NULL;

    while(scanf("%s", nome_funzione)!=EOF)
    {
        //funzione aggiungi-stazione//
        if(nome_funzione[0]=='a' && nome_funzione[9]=='s')
        {
            if(scanf("%d", &dist)){};
            //controllo che la stazione non esista ancora//
            f=0;
            for(i=0;i<num_stazioni;i++) //verificare sia corretta cosi la condizione oppure con num_stazioni-1//
            {
                if(distanze_stazioni[i]==dist)
                {
                    f=1;
                    break;
                }
            }
            //caso in cui la stazione non esiste ancora//
            if(f==0)
            {
                num_stazioni++;
                
                distanze_stazioni=realloc(distanze_stazioni, num_stazioni*sizeof(int));
                distanze_stazioni[num_stazioni-1]=dist;
                autonomie_stazioni=realloc(autonomie_stazioni, num_stazioni*sizeof(int*));
                aggiungi_stazione(dist, &primo_elemento);
                autonomie_stazioni[num_stazioni-1]=primo_elemento;
                
            }
            //caso in cui la stazione gia esiste//
            else
                printf("non aggiunta\n");
        }

        //funzione aggiungi-auto//
        if(nome_funzione[0]=='a' && nome_funzione[9]=='a')
        {
            if(scanf("%d", &dist)){};
            //controllo che la stazione a cui voglio aggiungere l'auto esista//
            f=0;
            for(i=0;i<num_stazioni;i++)
            {
                if(distanze_stazioni[i]==dist)
                {
                    f=1;
                    break;
                }
            }
            //caso in cui la stazione esiste//
            if(f==1)
            {
                primo_elemento=autonomie_stazioni[i];
                aggiungi_auto(dist, &primo_elemento);
            }
            //caso in cui la stazione non esiste//
            else
                printf("non aggiunta\n");
        }

        //funzione rottama-auto//
        if(nome_funzione[0]=='r')
        {
            if(scanf("%d", &dist)){};
            //controllo che la stazione a cui voglio togliere l'auto esista//
            f=0;
            for(i=0;i<num_stazioni;i++)
            {
                if(distanze_stazioni[i]==dist)
                {
                    f=1;
                    break;
                }
            }
            //caso in cui la stazione esiste//
            if(f==1)
            {
                primo_elemento=autonomie_stazioni[i];
                rottama_auto(dist, &primo_elemento);
            }
            //caso in cui la stazione non esiste//
            else
                printf("non rottamata\n");
        }

        //funzione demolisci-stazione//
        if(nome_funzione[0]=='d')
        {
            if(scanf("%d", &dist)){};
            //controllo che la stazione da demolire esista//
            f=0;
            for(i=0;i<num_stazioni;i++)
            {
                if(distanze_stazioni[i]==dist)
                {
                    f=1;
                    break;
                }
            }
            //caso in cui la stazione esiste//
            if(f==1)
            {
                primo_elemento=autonomie_stazioni[i];
                demolisci_stazione(dist, &primo_elemento);
                distanze_stazioni[i]=distanze_stazioni[num_stazioni-1];
                autonomie_stazioni[i]=autonomie_stazioni[num_stazioni-1];
                num_stazioni--;
                distanze_stazioni=realloc(distanze_stazioni, num_stazioni*sizeof(int));
                autonomie_stazioni=realloc(autonomie_stazioni, num_stazioni*sizeof(int*));
                
            }
            //caso in cui la stazione non esiste//
            else
                printf("non demolita\n");
        }

        //funzione pianifica-percorso//
        if(nome_funzione[0]=='p')
        {
            if(scanf("%d", &part)){};
            if(scanf("%d", &arr)){};

            //creo gli array con le distanze e le autonomie//
            k=0;
            j=0;
            pian_distanze=malloc(num_stazioni*sizeof(int));
            pian_autonomie=malloc(num_stazioni*sizeof(int));

            if(part<arr){
            while(k<num_stazioni && j<num_stazioni)
            {
                if(distanze_stazioni[k]>=part && distanze_stazioni[k]<=arr)
                {
                    pian_distanze[j]=distanze_stazioni[k];
                    pian_autonomie[j]=autonomie_stazioni[k][2];
                    j++;
                }
                k++;
            }}
            else{
                while(k<num_stazioni && j<num_stazioni)
            {
                if(distanze_stazioni[k]<=part && distanze_stazioni[k]>=arr)
                {
                    pian_distanze[j]=distanze_stazioni[k];
                    pian_autonomie[j]=autonomie_stazioni[k][2];
                    j++;
                }
                k++;
            }

            }

            pian_distanze=realloc(pian_distanze, j*sizeof(int));
            pian_autonomie=realloc(pian_autonomie, j*sizeof(int));

            heapSort(pian_distanze, j, pian_autonomie);

            if(part<arr)
                pianifica_percorso_basso_alto(pian_distanze, pian_autonomie, j);
                
            else if(part>arr)
            {
                reverseArray(pian_distanze, j);
                reverseArray(pian_autonomie, j);
                pianifica_percorso_alto_basso(pian_distanze, pian_autonomie, j);
            }
            else
                printf("%d", part);

            free(pian_distanze);
            free(pian_autonomie);
            pian_distanze=NULL;
            pian_autonomie=NULL;
        }
    }
    return 0;
}

//funzione aggiungi-stazione//
void aggiungi_stazione(int distanza,int** autonomie)
{
    unsigned i; 
    int num_auto, max_autonomia, indice_max_autonomia;

    max_autonomia = 0;
    indice_max_autonomia=0;

    *autonomie = malloc(517*sizeof(int));

    if(scanf("%d", &num_auto)){};

    (*autonomie)[0] = distanza;
    (*autonomie)[1] = num_auto;
    for(i=4; i<num_auto+4; i++)
    {
        if(scanf("%d", &(*autonomie)[i])){};
        if((*autonomie)[i] > max_autonomia)
        {
            max_autonomia = (*autonomie)[i];
            indice_max_autonomia = i;
        }
    }
    (*autonomie)[2] = max_autonomia;
    (*autonomie)[3] = indice_max_autonomia;

    printf("aggiunta\n");
}

//funzione aggiungi-auto//
void aggiungi_auto(int distanza, int** autonomie)
{
    int nuova_autonomia;

    if(scanf("%d", &nuova_autonomia)){};

    (*autonomie)[(*autonomie)[1]+4] = nuova_autonomia;
    (*autonomie)[1]++;
    if(nuova_autonomia>(*autonomie)[2])
    {
        (*autonomie)[2] = nuova_autonomia;
        (*autonomie)[3] = (*autonomie)[1]+3;
    }
    printf("aggiunta\n");
}

//funzione rottama-auto//
void rottama_auto(int distanza, int** autonomie)
{
    int autonomia_cancellata, max_autonomia, indice_max_autonomia;
    unsigned i, f;

    if(scanf("%d", &autonomia_cancellata)){};

    //cerco l'autonomia da cancellare e la cancello, spostando l'ultima autonomia nella posizione di quella cancellata//
    f=0;
    for(i=4;i<(*autonomie)[1]+4;i++)//rivedere questa condizione assolutamente piu il pianifica percorso alto basso//ora sembra giusta
    {
        if((*autonomie)[i]==autonomia_cancellata)
        {
            (*autonomie)[i]=(*autonomie)[(*autonomie)[1]+3];//cambiato qui da 4 a tre//
            (*autonomie)[(*autonomie)[1]+3]=-1;//aggiunto in piu ma dovrebbe essere una semplice sicurezza//
            (*autonomie)[1]--;
            f=1;
            break;
        }
    }
    //caso in cui ho cancellato l'autonomia//
    if(f==1)
    {
        if(autonomia_cancellata==(*autonomie)[2])
        {
            max_autonomia=0;
	        indice_max_autonomia=0;

            for(i=4;i<(*autonomie)[1]+3; i++)
            {
                if((*autonomie)[i] > max_autonomia)
                {
                    max_autonomia = (*autonomie)[i];
                    indice_max_autonomia = i;
                }
            }
            (*autonomie)[2] = max_autonomia;
            (*autonomie)[3] = indice_max_autonomia;
        }
        printf("rottamata\n");
    }
    //caso in cui non ho cancellato l'autonomia//
    else
        printf("non rottamata\n");
}

//funzione demolisci-stazione//
void demolisci_stazione(int distanza, int** autonomie)
{
    free(*autonomie);
    *autonomie=NULL;
    printf("demolita\n");
}

// Funzione per scambiare due elementi dell'array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione per mantenere la proprietà dell'heap (heapify)
void heapify(int arr[], int idx, int size, int idxMapping[]) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != idx) {
        swap(&arr[idx], &arr[largest]);
        swap(&idxMapping[idx], &idxMapping[largest]);
        heapify(arr, largest, size, idxMapping);
    }
}

// Funzione per eseguire l'Heap Sort
void heapSort(int arr[], int n, int idxMapping[]) {
    // Costruisci l'heap (raccogli l'array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, i, n, idxMapping);

    // Estrai un elemento alla volta dall'heap
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        swap(&idxMapping[0], &idxMapping[i]);
        heapify(arr, 0, i, idxMapping);
    }
}

struct nodo_albero* crea_nodo(int chiave) 
{
    struct nodo_albero* nuovo_nodo; 
    nuovo_nodo = malloc(sizeof(struct nodo_albero));
    nuovo_nodo->chiave = chiave;
    nuovo_nodo->padre = NULL;
    return nuovo_nodo;
}

void reverseArray(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void pianifica_percorso_basso_alto(int pian_distanze[], int pian_autonomie[], int dim)
{
    int par, arr, i, j, a;
    int pian_distanze_copia[dim];
    int array_inversione[dim];

    struct nodo_albero* nodo_corrente;

    struct nodo_albero** albero_di_nodi;

    nodo_corrente=NULL;
    albero_di_nodi=NULL;

    for(i=0; i<dim; i++)
    {
        pian_distanze_copia[i]=pian_distanze[i];
    }

    par=pian_distanze[0];
    arr=pian_distanze[dim-1];

    albero_di_nodi=malloc(dim*sizeof(struct nodo_albero*));
    for(i=0;i<dim;i++)
    {
        albero_di_nodi[i]=NULL;
    }
    albero_di_nodi[0]=crea_nodo(par);
    pian_distanze_copia[0]=-1;

    i=0;
    j=1;
    a=0;
    while(i<dim)
    {
        if(pian_distanze[j]-pian_distanze[i]<=pian_autonomie[i] && pian_distanze_copia[j]!=-1 && j<dim)
        {
            if(albero_di_nodi[i]==NULL)
            {
                printf("nessun percorso\n");
                a=1;
                break;
            }
            albero_di_nodi[j]=crea_nodo(pian_distanze[j]);
            albero_di_nodi[j]->padre=albero_di_nodi[i];
            pian_distanze_copia[j]=-1;
            if(albero_di_nodi[j]->chiave==arr)
                break;
            j++;
        }
        else if(j>=dim && i==j-1)
        {
            a=1;
            printf("nessun percorso\n");
            break;
        }
        else if(pian_distanze_copia[j]==-1)
        {
            j++;
        }
        else
        {
            i++;
            j=i+1;
        }
    }

    i=0;
    j=0;

    //ho ancora dei problemi con questa parte per execution killed sul
    //verificatore, fino all'open 15 va tutto bene//
    //da qui in poi e per ordinarlo nel caso ci sia il percorso//
    if(a==0)
    {
        nodo_corrente=albero_di_nodi[dim-1];
        while(i<dim)
        {
            array_inversione[i]=nodo_corrente->chiave;
            if(nodo_corrente==albero_di_nodi[0])
                break;
            nodo_corrente=nodo_corrente->padre;
            i++;
            j++;
        }
        j++;
        while(j<=dim)
        {
            array_inversione[j]=-1;
            j++;
        }
        for(i=dim;i>=0;i--)
        {
            if(array_inversione[i]!=-1 && array_inversione[i]==arr)
                printf("%d", array_inversione[i]);
            else if(array_inversione[i]!=-1)
                printf("%d ", array_inversione[i]);
        }
        printf("\n");
    }
    for (i = 0; i < dim; i++)
    {
        if (albero_di_nodi[i] != NULL)
        {
            free(albero_di_nodi[i]);
        }
    }
    free(albero_di_nodi);
    albero_di_nodi=NULL;
}

void pianifica_percorso_alto_basso(int pian_distanze[], int pian_autonomie[], int dim)
{
    int par, arr, i, j, a, b, d;
    int pian_distanze_copia[dim];
    int array_inversione[dim];

    struct nodo_albero* nodo_corrente;
    struct nodo_albero* nodo_prova_i;
    struct nodo_albero* nodo_prova_j;

    struct nodo_albero** albero_di_nodi;

    nodo_corrente=NULL;
    albero_di_nodi=NULL;
    nodo_prova_i=NULL;
    nodo_prova_j=NULL;

    for(i=0; i<dim; i++)
    {
        pian_distanze_copia[i]=pian_distanze[i];
    }

    par=pian_distanze[0];
    arr=pian_distanze[dim-1];

    albero_di_nodi=malloc(dim*sizeof(struct nodo_albero*));
    for(i=0;i<dim;i++)
    {
        albero_di_nodi[i]=NULL;
    }
    albero_di_nodi[0]=crea_nodo(par);
    pian_distanze_copia[0]=-1;

    i=0;
    j=1;
    a=0;
    b=0;
    d=0;

    while(i<dim)
    {
        if(pian_distanze[i]-pian_distanze[j]<=pian_autonomie[i] && pian_distanze_copia[j]!=-1 && j<dim)
        {
            if(albero_di_nodi[i]==NULL)
            {
                printf("nessun percorso\n");
                a=1;
                break;
            }
            albero_di_nodi[j]=crea_nodo(pian_distanze[j]);
            albero_di_nodi[j]->padre=albero_di_nodi[i];
            pian_distanze_copia[j]=-1;
            if(albero_di_nodi[j]->chiave==arr)
            {
                b=1;
                i++;
                break;
            }
            j++;
        }
        else if(j>=dim && i==j-1)
        {
            a=1;
            printf("nessun percorso\n");
            break;
        }
        else if(pian_distanze[i]-pian_distanze[j]<=pian_autonomie[i] && pian_distanze_copia[j]==-1)
        {
            nodo_prova_i=albero_di_nodi[i];
            nodo_prova_j=albero_di_nodi[j];
            if(albero_di_nodi[j]->padre!=albero_di_nodi[0])
            {
                while((nodo_prova_i->padre!=NULL || nodo_prova_j->padre!=NULL) && albero_di_nodi[j]->padre!=albero_di_nodi[0])
                //devo verificare anche albero di nodi di i?//
                {
                    if(nodo_prova_i->padre==nodo_prova_j->padre->padre)
                    {
                        d=1;
                        break;
                    }
                    nodo_prova_i=nodo_prova_i->padre;
                    nodo_prova_j=nodo_prova_j->padre;
                    if(nodo_prova_i==albero_di_nodi[0] || nodo_prova_i==albero_di_nodi[0])
                        break;
                }
            }
            if(d==1)
            {
                albero_di_nodi[j]->padre=albero_di_nodi[i];
                j++;
                d=0;
            }
            else
                j++;
            nodo_prova_i=NULL;
            nodo_prova_j=NULL;

        }
        /*else if(pian_distanze_copia[j]==-1)
        {
            j++;
        }*/
        else
        {
            i++;
            j=i+1;
        }
    }

    if(b==1)
    {
        while(i<j)
        {
            if(pian_distanze[i]-pian_distanze[j]<=pian_autonomie[i] && pian_distanze_copia[j]==-1)
            {
                nodo_prova_i=albero_di_nodi[i];
                nodo_prova_j=albero_di_nodi[j];
                if(albero_di_nodi[j]->padre!=albero_di_nodi[0])
                {
                    while((nodo_prova_i->padre!=NULL || nodo_prova_j->padre!=NULL) && albero_di_nodi[j]->padre!=albero_di_nodi[0])
                    {
                        if(nodo_prova_i->padre==nodo_prova_j->padre->padre)
                        {
                            d=1;
                            break;
                        }
                        nodo_prova_i=nodo_prova_i->padre;
                        nodo_prova_j=nodo_prova_j->padre;
                        if(nodo_prova_i==albero_di_nodi[0] || nodo_prova_i==albero_di_nodi[0])
                            break;
                    }
                }
            if(d==1)
            {
                albero_di_nodi[j]->padre=albero_di_nodi[i];
                d=0;
            }
            else
            nodo_prova_i=NULL;
            nodo_prova_j=NULL;
            }
            i++;
        }
        
    }
    

       
    i=0;
    j=0;

    //da qui in poi e per ordinarlo nel caso ci sia il percorso//
    if(a==0)
    {
        nodo_corrente=albero_di_nodi[dim-1];
        while(i<dim)
        {
            array_inversione[i]=nodo_corrente->chiave;
            if(nodo_corrente==albero_di_nodi[0])
                break;
            nodo_corrente=nodo_corrente->padre;
            i++;
            j++;
        }
        j++;
        while(j<=dim)
        {
            array_inversione[j]=-1;
            j++;
        }
        for(i=dim;i>=0;i--)
        {
            if(array_inversione[i]!=-1 && array_inversione[i]==arr)
                printf("%d", array_inversione[i]);
            else if(array_inversione[i]!=-1)
                printf("%d ", array_inversione[i]);
        }
        printf("\n");
    }

    for (i = 0; i < dim; i++)
    {
        if (albero_di_nodi[i] != NULL)
        {
            free(albero_di_nodi[i]);
        }
    }
    free(albero_di_nodi);
    albero_di_nodi=NULL;
}
