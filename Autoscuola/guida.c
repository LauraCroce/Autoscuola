/**
 * @file guida.c
 * @brief Implementazione della gestione delle guide pratiche per gli allievi.
 *
 * Questo modulo gestisce la registrazione e visualizzazione delle ore di guida.
 * Per ciascun allievo vengono tracciate ore totali e ore extra (oltre le 6 obbligatorie).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guida.h"
#include "allievi.h"  // Per trovaIDAllievo, getAllievoNome, getAllievoCognome
#include "util.h"

//DEFINIZIONI STRUTTURE (PRIVATE)
#define MAX_GUIDE 100

/**
 * @struct Guida
 * @brief Rappresenta il numero di ore di guida svolte da un allievo.
 */
struct Guida {
    int id_allievo;
    int ore_svolte;
    int ore_extra;
};

/**
 * @struct ListaGuide
 * @brief Rappresenta l'elenco delle guide di tutti gli allievi.
 */
struct ListaGuide {
    Guida elenco_guide[MAX_GUIDE];
    int n_guide;
};

//FUNZIONI DI CREAZIONE/DISTRUZIONE

ListaGuide* creaListaGuide(void) {
    ListaGuide* lista = (ListaGuide*)malloc(sizeof(ListaGuide));
    if (lista != NULL) {
        lista->n_guide = 0;
    }
    return lista;
}

void distruggiListaGuide(ListaGuide** lista) {
    if (lista != NULL && *lista != NULL) {
        free(*lista);
        *lista = NULL;
    }
}

void inizializzaListaGuide(ListaGuide* lista) {
    if (lista == NULL) return;
    lista->n_guide = 0;
}

//FUNZIONI DI ACCESSO (GETTER)

int getNumeroGuide(const ListaGuide* lista) {
    return (lista != NULL) ? lista->n_guide : -1;
}

Guida* cercaGuidaPerID(const ListaGuide* lista, int id_allievo) {
    if (lista == NULL || id_allievo <= 0) return NULL;

    for (int i = 0; i < lista->n_guide; i++) {
        if (lista->elenco_guide[i].id_allievo == id_allievo) {
            return &lista->elenco_guide[i];
        }
    }
    return NULL;
}

const Guida* getGuidaAtIndex(const ListaGuide* lista, int index) {
    if (lista == NULL || index < 0 || index >= lista->n_guide) {
        return NULL;
    }
    return &lista->elenco_guide[index];
}

int getGuidaIDAllievo(const Guida* guida) {
    return (guida != NULL) ? guida->id_allievo : -1;
}

int getOreSvolte(const Guida* guida) {
    return (guida != NULL) ? guida->ore_svolte : -1;
}

int getOreExtra(const Guida* guida) {
    return (guida != NULL) ? guida->ore_extra : 0;
}

bool haCompletateOreObbligatorie(const Guida* guida) {
    return (guida != NULL && guida->ore_svolte >= ORE_GUIDA_OBBLIGATORIE);
}

float calcolaCostoOreExtra(const Guida* guida, float costo_orario) {
    if (guida == NULL || costo_orario < 0) return 0.0;
    return guida->ore_extra * costo_orario;
}

//FUNZIONALITÀ DI DOMINIO

bool inizializzaGuida(ListaGuide* lista, int id_allievo) {
    if (lista == NULL || id_allievo <= 0) return false;

    if (lista->n_guide >= MAX_GUIDE) {
        printf("Errore: numero massimo di guide raggiunto.\n");
        return false;
    }

    Guida nuova;
    nuova.id_allievo = id_allievo;
    nuova.ore_svolte = 0;
    nuova.ore_extra = 0;

    lista->elenco_guide[lista->n_guide++] = nuova;
    return true;
}

bool registraOreGuida(ListaGuide* lista, int id_allievo, int ore_da_aggiungere) {
    if (lista == NULL || id_allievo <= 0 || ore_da_aggiungere <= 0) return false;

    Guida* g = cercaGuidaPerID(lista, id_allievo);
    if (g == NULL) {
        // Crea nuova guida se non esiste
        if (lista->n_guide >= MAX_GUIDE) {
            printf("Errore: numero massimo di guide raggiunto.\n");
            return false;
        }

        Guida nuova;
        nuova.id_allievo = id_allievo;
        nuova.ore_svolte = ore_da_aggiungere;
        nuova.ore_extra = (ore_da_aggiungere > ORE_GUIDA_OBBLIGATORIE) ?
                          (ore_da_aggiungere - ORE_GUIDA_OBBLIGATORIE) : 0;

        lista->elenco_guide[lista->n_guide++] = nuova;
        return true;
    }

    // Aggiorna ore esistenti
    g->ore_svolte += ore_da_aggiungere;
    g->ore_extra = (g->ore_svolte > ORE_GUIDA_OBBLIGATORIE) ?
                   (g->ore_svolte - ORE_GUIDA_OBBLIGATORIE) : 0;

    return true;
}

void registraGuida(ListaGuide* listaG, const void* listaA) {
    if (listaG == NULL || listaA == NULL) {
        printf("Errore: liste non valide.\n");
        return;
    }

    const ListaAllievi* allievi = (const ListaAllievi*)listaA;

    char nome[30], cognome[30];
    printf("Inserisci nome allievo: ");
    inputString(nome, 30);
    printf("Inserisci cognome allievo: ");
    inputString(cognome, 30);

    int id = trovaIDAllievo(allievi, nome, cognome);
    if (id == -1) {
        printf("Allievo non trovato.\n");
        return;
    }

    int ore = inputInt("Ore da registrare: ");
    if (ore <= 0) {
        printf("Numero di ore non valido.\n");
        return;
    }

    if (registraOreGuida(listaG, id, ore)) {
        Guida* g = cercaGuidaPerID(listaG, id);
        if (g != NULL) {
            printf("Ore aggiornate correttamente.\n");
            printf("Ore totali: %d | Ore extra: %d\n", g->ore_svolte, g->ore_extra);
        }
    } else {
        printf("Errore durante la registrazione delle ore.\n");
    }
}

void stampaGuida(const Guida* guida) {
    if (guida == NULL) {
        printf("Guida non valida.\n");
        return;
    }

    printf("ID Allievo: %d | Ore totali: %d | Ore extra: %d\n",
           guida->id_allievo, guida->ore_svolte, guida->ore_extra);
}

void stampaTutteGuide(const ListaGuide* lista) {
    if (lista == NULL) {
        printf("Lista non valida.\n");
        return;
    }

    printf("\n--- Elenco Guide ---\n");
    for (int i = 0; i < lista->n_guide; i++) {
        stampaGuida(&lista->elenco_guide[i]);
    }
}

void stampaGuide(const ListaGuide* listaG, const void* listaA) {
    if (listaG == NULL || listaA == NULL) {
        printf("Errore: liste non valide.\n");
        return;
    }

    const ListaAllievi* allievi = (const ListaAllievi*)listaA;

    printf("\n--- GUIDE REGISTRATE ---\n");

    if (listaG->n_guide == 0) {
        printf("Nessuna guida registrata.\n");
        return;
    }

    for (int i = 0; i < listaG->n_guide; i++) {
        const Guida* g = &listaG->elenco_guide[i];

        // Cerca l'allievo usando interfaccia pubblica
        Allievo* allievo = cercaAllievoPerID((ListaAllievi*)allievi, g->id_allievo);

        const char* nome = "???";
        const char* cognome = "???";

        if (allievo != NULL) {
            nome = getAllievoNome(allievo);
            cognome = getAllievoCognome(allievo);
        }

        printf("ID: %d | Nome: %s | Cognome: %s | Ore totali: %d | Ore extra: %d",
               g->id_allievo, nome, cognome, g->ore_svolte, g->ore_extra);

        if (g->ore_svolte >= ORE_GUIDA_OBBLIGATORIE) {
            printf(" Obbligatorie completate");
        } else {
            printf(" (Mancano %d ore)", ORE_GUIDA_OBBLIGATORIE - g->ore_svolte);
        }

        printf("\n");
    }
}

//FUNZIONI I/O FILE

bool salvaGuide(const ListaGuide* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Errore: impossibile aprire il file %s per la scrittura.\n", filename);
        return false;
    }

    // Salva numero guide
    fwrite(&lista->n_guide, sizeof(int), 1, file);

    // Salva array guide
    fwrite(lista->elenco_guide, sizeof(Guida), lista->n_guide, file);

    fclose(file);
    return true;
}

bool caricaGuide(ListaGuide* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return false; // File non esiste, non è un errore
    }

    // Carica numero guide
    fread(&lista->n_guide, sizeof(int), 1, file);

    // Carica array guide
    fread(lista->elenco_guide, sizeof(Guida), lista->n_guide, file);

    fclose(file);
    return true;
}
