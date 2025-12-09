/**
 * @file pagamenti.c
 * @brief Implementazione delle funzionalità relative alla gestione dei pagamenti.
 *
 * Questo modulo consente di inizializzare e gestire i pagamenti associati agli allievi.
 * Ogni allievo ha 3 rate principali e una voce "extra".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pagamenti.h"
#include "allievi.h"  // Per trovaIDAllievo, ordinaAllieviAlfabetico, getter
#include "guida.h"    // Per getOreExtra, calcolaCostoOreExtra
#include "util.h"

//DEFINIZIONI STRUTTURE (PRIVATE)
#define MAX_PAGAMENTI 100

/**
 * @struct Pagamento
 * @brief Rappresenta i dati di pagamento di un allievo.
 */
struct Pagamento {
    int id_allievo;
    float prima_rata;
    float seconda_rata;
    float terza_rata;
    float extra;
};

/**
 * @struct ListaPagamenti
 * @brief Collezione statica di pagamenti registrati.
 */
struct ListaPagamenti {
    Pagamento elenco_pagamenti[MAX_PAGAMENTI];
    int n_pagamenti;
};

//FUNZIONI DI CREAZIONE/DISTRUZIONE

ListaPagamenti* creaListaPagamenti(void) {
    ListaPagamenti* lista = (ListaPagamenti*)malloc(sizeof(ListaPagamenti));
    if (lista != NULL) {
        lista->n_pagamenti = 0;
    }
    return lista;
}

void distruggiListaPagamenti(ListaPagamenti** lista) {
    if (lista != NULL && *lista != NULL) {
        free(*lista);
        *lista = NULL;
    }
}

void inizializzaListaPagamenti(ListaPagamenti* listaP) {
    if (listaP == NULL) return;
    listaP->n_pagamenti = 0;
}

//FUNZIONI DI ACCESSO (GETTER)

int getNumeroPagamenti(const ListaPagamenti* lista) {
    return (lista != NULL) ? lista->n_pagamenti : -1;
}

Pagamento* cercaPagamentoPerID(const ListaPagamenti* lista, int id_allievo) {
    if (lista == NULL || id_allievo <= 0) return NULL;

    for (int i = 0; i < lista->n_pagamenti; i++) {
        if (lista->elenco_pagamenti[i].id_allievo == id_allievo) {
            return &lista->elenco_pagamenti[i];
        }
    }
    return NULL;
}

const Pagamento* getPagamentoAtIndex(const ListaPagamenti* lista, int index) {
    if (lista == NULL || index < 0 || index >= lista->n_pagamenti) {
        return NULL;
    }
    return &lista->elenco_pagamenti[index];
}

int getPagamentoIDAllievo(const Pagamento* pagamento) {
    return (pagamento != NULL) ? pagamento->id_allievo : -1;
}

float calcolaTotalePagato(const Pagamento* pagamento) {
    if (pagamento == NULL) return 0.0;
    return pagamento->prima_rata + pagamento->seconda_rata +
           pagamento->terza_rata + pagamento->extra;
}

float getPrimaRata(const Pagamento* pagamento) {
    return (pagamento != NULL) ? pagamento->prima_rata : 0.0;
}

float getSecondaRata(const Pagamento* pagamento) {
    return (pagamento != NULL) ? pagamento->seconda_rata : 0.0;
}

float getTerzaRata(const Pagamento* pagamento) {
    return (pagamento != NULL) ? pagamento->terza_rata : 0.0;
}

float getExtra(const Pagamento* pagamento) {
    return (pagamento != NULL) ? pagamento->extra : 0.0;
}

//FUNZIONI DI MODIFICA (SETTER)

bool azzeraPagamento(Pagamento* pagamento) {
    if (pagamento == NULL) return false;

    pagamento->prima_rata = 0.0;
    pagamento->seconda_rata = 0.0;
    pagamento->terza_rata = 0.0;
    pagamento->extra = 0.0;
    return true;
}

bool setRata(Pagamento* pagamento, int tipo_rata, float importo) {
    if (pagamento == NULL || importo < 0) return false;

    switch (tipo_rata) {
        case 1:
            pagamento->prima_rata = importo;
            return true;
        case 2:
            pagamento->seconda_rata = importo;
            return true;
        case 3:
            pagamento->terza_rata = importo;
            return true;
        case 4:
            pagamento->extra = importo;
            return true;
        default:
            return false;
    }
}

//FUNZIONALITÀ DI DOMINIO

bool inizializzaPagamento(ListaPagamenti* listaP, int id_allievo) {
    if (listaP == NULL || id_allievo <= 0) return false;

    if (listaP->n_pagamenti >= MAX_PAGAMENTI) {
        printf("Errore: numero massimo di pagamenti raggiunto.\n");
        return false;
    }

    Pagamento nuovo;
    nuovo.id_allievo = id_allievo;
    nuovo.prima_rata = 250.0;
    nuovo.seconda_rata = 0.0;
    nuovo.terza_rata = 0.0;
    nuovo.extra = 0.0;

    listaP->elenco_pagamenti[listaP->n_pagamenti++] = nuovo;
    return true;
}

bool aggiungiRata(ListaPagamenti* lista, int id_allievo, int tipo_rata, float importo) {
    if (lista == NULL || id_allievo <= 0 || importo < 0) return false;

    Pagamento* p = cercaPagamentoPerID(lista, id_allievo);
    if (p == NULL) return false;

    return setRata(p, tipo_rata, importo);
}

void inserisciPagamento(ListaPagamenti* listaP, const void* listaA) {
    if (listaP == NULL || listaA == NULL) {
        printf("Errore: liste non valide.\n");
        return;
    }

    const ListaAllievi* allievi = (const ListaAllievi*)listaA;

    char nome[30], cognome[30];
    printf("Nome allievo: ");
    inputString(nome, 30);
    printf("Cognome allievo: ");
    inputString(cognome, 30);

    int id = trovaIDAllievo(allievi, nome, cognome);
    if (id == -1) {
        printf("Allievo non trovato.\n");
        return;
    }

    Pagamento* p = cercaPagamentoPerID(listaP, id);
    if (p == NULL) {
        printf("Nessun pagamento registrato per questo allievo.\n");
        return;
    }

    int scelta = inputInt("\n1. Seconda rata\n2. Terza rata\n3. Extra\nScelta: ");
    float importo = inputFloat("Inserisci importo: ");

    //Mappa la scelta al tipo_rata corretto
    int tipo_rata;
    switch(scelta){
        case 1 : tipo_rata = 2; break; //seconda rata
        case 2: tipo_rata = 3; break; //terza rata
        case 3: tipo_rata = 4; break; //quarta rata
        default:
            printf("Errore: scelta non valida.\n");
            return;
    }

    if (setRata(p, tipo_rata, importo)) {
        printf("Pagamento registrato correttamente.\n");
    } else {
        printf("Errore: scelta non valida.\n");
    }
}

void stampaStatoPagamento(const ListaPagamenti* listaP, const void* listaA) {
    if (listaP == NULL || listaA == NULL) {
        printf("Errore: liste non valide.\n");
        return;
    }

    const ListaAllievi* allievi = (const ListaAllievi*)listaA;

    char nome[30], cognome[30];
    printf("Inserisci il nome dell'allievo: ");
    inputString(nome, 30);
    printf("Inserisci il cognome dell'allievo: ");
    inputString(cognome, 30);

    int id = trovaIDAllievo(allievi, nome, cognome);
    if (id == -1) {
        printf("Allievo non trovato.\n");
        return;
    }

    Pagamento* p = cercaPagamentoPerID(listaP, id);
    if (p == NULL) {
        printf("Nessun pagamento registrato per questo allievo.\n");
        return;
    }

    float totale = p->prima_rata + p->seconda_rata + p->terza_rata;
    float complessivo = totale + p->extra;

    printf("\n--- PAGAMENTI DI %s %s ---\n", nome, cognome);
    printf("Prima rata:   %.2f\n", p->prima_rata);
    printf("Seconda rata: %.2f\n", p->seconda_rata);
    printf("Terza rata:   %.2f\n", p->terza_rata);
    printf("Extra:        %.2f\n", p->extra);
    printf("Totale pagato: %.2f €\n", complessivo);

    if (totale >= 750.0)
        printf("Pagamento completo.\n");
    else
        printf("Mancano %.2f € sulle rate principali.\n", 750.0 - totale);
}

void stampaPagamento(const Pagamento* pagamento) {
    if (pagamento == NULL) {
        printf("Pagamento non valido.\n");
        return;
    }

    float totale = calcolaTotalePagato(pagamento);
    printf("ID Allievo: %d | Prima: %.2f | Seconda: %.2f | Terza: %.2f | Extra: %.2f | Totale: %.2f\n",
           pagamento->id_allievo, pagamento->prima_rata, pagamento->seconda_rata,
           pagamento->terza_rata, pagamento->extra, totale);
}

void stampaTuttiPagamenti(const ListaPagamenti* lista) {
    if (lista == NULL) {
        printf("Lista non valida.\n");
        return;
    }

    printf("\n--- Elenco Pagamenti ---\n");
    for (int i = 0; i < lista->n_pagamenti; i++) {
        stampaPagamento(&lista->elenco_pagamenti[i]);
    }
}

void riepilogoPagamenti(const ListaPagamenti* listaP, const void* listaA, const void* listaG) {
    if (listaP == NULL || listaA == NULL) {
        printf("Errore: liste non valide.\n");
        return;
    }

    // Cast dei puntatori void
    ListaAllievi* allievi = (ListaAllievi*)listaA;
    const ListaGuide* guide = (const ListaGuide*)listaG;

    // Crea copia ordinata degli allievi
    ListaAllievi* ordinata = creaListaAllievi();
    if (ordinata == NULL) return;

    // Copia i dati (assumendo che esista un modo per copiare o iterare)
    int n_allievi = getNumeroAllievi(allievi);

    printf("\n----- RIEPILOGO PAGAMENTI TUTTI GLI ALLIEVI -----\n");
    printf("ID  | Nome            | Cognome         | Totale Rate | Extra   | Totale Pagato | Stato\n");
    printf("----|-----------------|-----------------|-------------|---------|----------------|--------\n");

    // Itera sugli allievi usando l'interfaccia pubblica
    for (int i = 0; i < n_allievi; i++) {
        const Allievo* allievo = getAllievoAtIndex(allievi, i);
        if (allievo == NULL) continue;

        int id = getAllievoID(allievo);
        const char* nome = getAllievoNome(allievo);
        const char* cognome = getAllievoCognome(allievo);

        Pagamento* p = cercaPagamentoPerID(listaP, id);
        if (p == NULL) continue;

        float rate = p->prima_rata + p->seconda_rata + p->terza_rata;
        float extra_base = p->extra;

        // Calcola costo ore extra usando getter pubblici
        float costo_ore_extra = 0.0;
        if (guide != NULL) {
            Guida* g = cercaGuidaPerID(guide, id);
            if (g != NULL) {
                costo_ore_extra = calcolaCostoOreExtra(g, 15.0);
            }
        }

        float totale = rate + extra_base + costo_ore_extra;

        printf("%-4d| %-16s| %-16s| %-11.2f| %-7.2f| %-14.2f| %s\n",
               id, nome, cognome, rate, extra_base + costo_ore_extra, totale,
               (totale >= 750.0) ? "Completo" : "Incompleto");
    }

    distruggiListaAllievi(&ordinata);
}

//FUNZIONI I/O FILE

bool salvaPagamenti(const ListaPagamenti* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Errore: impossibile aprire il file %s per la scrittura.\n", filename);
        return false;
    }

    // Salva numero pagamenti
    fwrite(&lista->n_pagamenti, sizeof(int), 1, file);

    // Salva array pagamenti
    fwrite(lista->elenco_pagamenti, sizeof(Pagamento), lista->n_pagamenti, file);

    fclose(file);
    return true;
}

bool caricaPagamenti(ListaPagamenti* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return false; // File non esiste, non è un errore
    }

    // Carica numero pagamenti
    fread(&lista->n_pagamenti, sizeof(int), 1, file);

    // Carica array pagamenti
    fread(lista->elenco_pagamenti, sizeof(Pagamento), lista->n_pagamenti, file);

    fclose(file);
    return true;
}
