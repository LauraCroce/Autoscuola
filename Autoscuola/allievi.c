/**
 * @file allievi.c
 * @brief Implementazione delle funzionalità per la gestione degli allievi nell'autoscuola.
 *
 * Questo modulo fornisce funzioni per la gestione completa degli allievi:
 * inserimento, ordinamento, ricerca, visualizzazione e filtraggio.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "allievi.h"
#include "pagamenti.h"  // Solo per inizializzaPagamento
#include "esami.h"      // Solo per inizializzaEsame
#include "util.h"

//DEFINIZIONI STRUTTURE (PRIVATE)
#define MAX_ALLIEVI 100

/**
 * @struct Allievo
 * @brief Rappresenta un allievo iscritto all'autoscuola.
 */
struct Allievo {
    int id;
    char nome[30];
    char cognome[30];
    char codice_fiscale[17];
    char categoria_patente[5];
    char stato[20];
};

/**
 * @struct ListaAllievi
 * @brief Raccoglie l'elenco degli allievi iscritti.
 */
struct ListaAllievi {
    Allievo elenco[MAX_ALLIEVI];
    int n_allievi;
    int id_corrente;
};

//FUNZIONI DI CREAZIONE/DISTRUZIONE

ListaAllievi* creaListaAllievi(void) {
    ListaAllievi* lista = (ListaAllievi*)malloc(sizeof(ListaAllievi));
    if (lista != NULL) {
        lista->n_allievi = 0;
        lista->id_corrente = 1;
    }
    return lista;
}

void distruggiListaAllievi(ListaAllievi** lista) {
    if (lista != NULL && *lista != NULL) {
        free(*lista);
        *lista = NULL;
    }
}

void inizializzaLista(ListaAllievi* lista) {
    if (lista == NULL) return;
    lista->n_allievi = 0;
    lista->id_corrente = 1;
}

//FUNZIONI DI ACCESSO (GETTER)

int getNumeroAllievi(const ListaAllievi* lista) {
    return (lista != NULL) ? lista->n_allievi : -1;
}

int getAllievoID(const Allievo* allievo) {
    return (allievo != NULL) ? allievo->id : -1;
}

const char* getAllievoNome(const Allievo* allievo) {
    return (allievo != NULL) ? allievo->nome : NULL;
}

const char* getAllievoCognome(const Allievo* allievo) {
    return (allievo != NULL) ? allievo->cognome : NULL;
}

const char* getAllievoCodiceFiscale(const Allievo* allievo) {
    return (allievo != NULL) ? allievo->codice_fiscale : NULL;
}

const char* getAllievoCategoriaPatente(const Allievo* allievo) {
    return (allievo != NULL) ? allievo->categoria_patente : NULL;
}

const char* getAllievoStato(const Allievo* allievo) {
    return (allievo != NULL) ? allievo->stato : NULL;
}

const Allievo* getAllievoAtIndex(const ListaAllievi* lista, int index) {
    if (lista == NULL || index < 0 || index >= lista->n_allievi) {
        return NULL;
    }
    return &lista->elenco[index];
}

//FUNZIONI DI MODIFICA (SETTER)

bool setAllievoStato(Allievo* allievo, const char* nuovo_stato) {
    if (allievo == NULL || nuovo_stato == NULL) return false;
    strncpy(allievo->stato, nuovo_stato, sizeof(allievo->stato) - 1);
    allievo->stato[sizeof(allievo->stato) - 1] = '\0';
    return true;
}

// FUNZIONALITÀ DI DOMINIO

void aggiornaID(ListaAllievi* lista) {
    if (lista == NULL) return;

    int max = 0;
    for (int i = 0; i < lista->n_allievi; i++) {
        if (lista->elenco[i].id > max)
            max = lista->elenco[i].id;
    }
    lista->id_corrente = max + 1;
}

int trovaIDAllievo(const ListaAllievi* lista, const char* nome, const char* cognome) {
    if (lista == NULL || nome == NULL || cognome == NULL) return -1;

    for (int i = 0; i < lista->n_allievi; i++) {
        if (equalsIgnoreCase(lista->elenco[i].nome, nome) &&
            equalsIgnoreCase(lista->elenco[i].cognome, cognome)) {
            return lista->elenco[i].id;
        }
    }
    return -1;
}

Allievo* cercaAllievoPerNome(ListaAllievi* lista, const char* nome, const char* cognome) {
    if (lista == NULL || nome == NULL || cognome == NULL) return NULL;

    for (int i = 0; i < lista->n_allievi; i++) {
        if (equalsIgnoreCase(lista->elenco[i].nome, nome) &&
            equalsIgnoreCase(lista->elenco[i].cognome, cognome)) {
            return &lista->elenco[i];
        }
    }
    return NULL;
}

Allievo* cercaAllievoPerID(ListaAllievi* lista, int id) {
    if (lista == NULL || id <= 0) return NULL;

    for (int i = 0; i < lista->n_allievi; i++) {
        if (lista->elenco[i].id == id) {
            return &lista->elenco[i];
        }
    }
    return NULL;
}

int inserisciAllievoBase(ListaAllievi* lista) {
    if (lista == NULL || lista->n_allievi >= MAX_ALLIEVI) {
        printf("Errore: lista piena o non valida.\n");
        return -1;
    }

    Allievo nuovo;
    printf("Inserisci nome: ");
    inputString(nuovo.nome, 30);
    printf("Inserisci cognome: ");
    inputString(nuovo.cognome, 30);
    printf("Inserisci codice fiscale: ");
    inputString(nuovo.codice_fiscale, 17);

    do {
        printf("Inserisci categoria patente (A, B, AM): ");
        inputString(nuovo.categoria_patente, 5);
    } while (!validaCategoria(nuovo.categoria_patente));

    // Converti in maiuscolo
    for (int i = 0; nuovo.categoria_patente[i]; i++)
        nuovo.categoria_patente[i] = toupper(nuovo.categoria_patente[i]);

    nuovo.id = lista->id_corrente++;
    strcpy(nuovo.stato, "iscritto");

    lista->elenco[lista->n_allievi++] = nuovo;

    return nuovo.id;
}

void inserisciAllievo(ListaAllievi* lista, void* listaP, void* listaE) {
    if (lista == NULL) {
        printf("Errore: lista allievi non valida.\n");
        return;
    }

    if (lista->n_allievi >= MAX_ALLIEVI) {
        printf("Numero massimo di allievi raggiunto.\n");
        return;
    }

    int nuovo_id = inserisciAllievoBase(lista);
    if (nuovo_id > 0) {
        // Cast dei puntatori void ai tipi corretti
        ListaPagamenti* pagamenti = (ListaPagamenti*)listaP;
        ListaEsami* esami = (ListaEsami*)listaE;

        if (pagamenti != NULL) {
            inizializzaPagamento(pagamenti, nuovo_id);
        }
        if (esami != NULL) {
            inizializzaEsame(esami, nuovo_id);
        }

        printf("Allievo inserito con ID: %d\n", nuovo_id);
        ordinaAllieviAlfabetico(lista);
    }
}

void ordinaAllieviAlfabetico(ListaAllievi* lista) {
    if (lista == NULL || lista->n_allievi <= 1) return;

    for (int i = 0; i < lista->n_allievi - 1; i++) {
        for (int j = i + 1; j < lista->n_allievi; j++) {
            Allievo* a = &lista->elenco[i];
            Allievo* b = &lista->elenco[j];
            if (strcasecmp(a->cognome, b->cognome) > 0 ||
               (strcasecmp(a->cognome, b->cognome) == 0 && strcasecmp(a->nome, b->nome) > 0)) {
                Allievo temp = *a;
                *a = *b;
                *b = temp;
            }
        }
    }
}

void stampaAllievi(const ListaAllievi* lista) {
    if (lista == NULL) {
        printf("Lista non valida.\n");
        return;
    }

    printf("\n--- Elenco Allievi ---\n");
    for (int i = 0; i < lista->n_allievi; i++) {
        const Allievo* a = &lista->elenco[i];
        printf("ID: %d | %s %s | CF: %s | Patente: %s | Stato: %s\n",
               a->id, a->nome, a->cognome, a->codice_fiscale, a->categoria_patente, a->stato);
    }
}

void filtraPerPatente(const ListaAllievi* lista) {
    if (lista == NULL) {
        printf("Lista non valida.\n");
        return;
    }

    char categoria[5];
    printf("Inserisci categoria patente (A, B, AM): ");
    inputString(categoria, 5);

    printf("\nAllievi con patente %s:\n", categoria);
    int trovati = 0;
    for (int i = 0; i < lista->n_allievi; i++) {
        if (equalsIgnoreCase(lista->elenco[i].categoria_patente, categoria)) {
            const Allievo* a = &lista->elenco[i];
            printf("ID: %d | %s %s | Patente: %s | Stato: %s\n",
                   a->id, a->nome, a->cognome, a->categoria_patente, a->stato);
            trovati++;
        }
    }
    if (trovati == 0) {
        printf("Nessun allievo trovato con questa categoria.\n");
    }
}

void filtraPerStato(const ListaAllievi* lista) {
    if (lista == NULL) {
        printf("Lista non valida.\n");
        return;
    }

    char stato[20];
    printf("Inserisci stato (iscritto/sospeso): ");
    inputString(stato, 20);

    printf("\nAllievi con stato '%s':\n", stato);
    int trovati = 0;
    for (int i = 0; i < lista->n_allievi; i++) {
        if (equalsIgnoreCase(lista->elenco[i].stato, stato)) {
            const Allievo* a = &lista->elenco[i];
            printf("ID: %d | %s %s | Patente: %s\n",
                   a->id, a->nome, a->cognome, a->categoria_patente);
            trovati++;
        }
    }
    if (trovati == 0) {
        printf("Nessun allievo trovato con questo stato.\n");
    }
}

void cercaAllievo(const ListaAllievi* listaA, const void* listaP, const void* listaE) {
    if (listaA == NULL) {
        printf("Lista allievi non valida.\n");
        return;
    }

    char nome[30], cognome[30];
    printf("Inserisci nome allievo: ");
    inputString(nome, 30);
    printf("Inserisci cognome allievo: ");
    inputString(cognome, 30);

    int id = trovaIDAllievo(listaA, nome, cognome);
    if (id == -1) {
        printf("Allievo non trovato.\n");
        return;
    }

    // Stampa dati allievo
    for (int i = 0; i < listaA->n_allievi; i++) {
        if (listaA->elenco[i].id == id) {
            const Allievo* a = &listaA->elenco[i];
            printf("\n--- DATI ALLIEVO ---\n");
            printf("ID: %d\nNome: %s\nCognome: %s\nCF: %s\nPatente: %s\nStato: %s\n",
                   a->id, a->nome, a->cognome, a->codice_fiscale, a->categoria_patente, a->stato);
            break;
        }
    }

    // Stampa pagamenti (usando getter pubblici)
    if (listaP != NULL) {
        const ListaPagamenti* pagamenti = (const ListaPagamenti*)listaP;
        Pagamento* p = cercaPagamentoPerID(pagamenti, id);
        if (p != NULL) {
            printf("\n--- PAGAMENTI ---\n");
            printf("Prima: %.2f\nSeconda: %.2f\nTerza: %.2f\nExtra: %.2f\n",
                   getPrimaRata(p), getSecondaRata(p), getTerzaRata(p), getExtra(p));
        }
    }

    // Stampa esami (usando getter pubblici)
    if (listaE != NULL) {
        const ListaEsami* esami = (const ListaEsami*)listaE;
        Esame* e = cercaEsamePerID(esami, id);
        if (e != NULL) {
            printf("\n--- ESAMI ---\n");
            printf("Teorico: %d (superato: %s)\nPratico: %d (superato: %s)\n",
                   getTentativiTeorico(e), isTeoricoSuperato(e) ? "Sì" : "No",
                   getTentativiPratico(e), isPraticoSuperato(e) ? "Sì" : "No");
        }
    }
}

//FUNZIONI I/O FILE

bool salvaAllievi(const ListaAllievi* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Errore: impossibile aprire il file %s per la scrittura.\n", filename);
        return false;
    }

    // Salva numero allievi e ID corrente
    fwrite(&lista->n_allievi, sizeof(int), 1, file);
    fwrite(&lista->id_corrente, sizeof(int), 1, file);

    // Salva array allievi
    fwrite(lista->elenco, sizeof(Allievo), lista->n_allievi, file);

    fclose(file);
    return true;
}

bool caricaAllievi(ListaAllievi* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return false; // File non esiste, non è un errore
    }

    // Carica numero allievi e ID corrente
    fread(&lista->n_allievi, sizeof(int), 1, file);
    fread(&lista->id_corrente, sizeof(int), 1, file);

    // Carica array allievi
    fread(lista->elenco, sizeof(Allievo), lista->n_allievi, file);

    fclose(file);
    return true;
}
