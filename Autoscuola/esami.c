/**
 * @file esami.c
 * @brief Gestione degli esami teorici e pratici degli allievi.
 *
 * Questo modulo implementa le funzionalità per:
 * - Inizializzare e registrare esami
 * - Registrare tentativi con date
 * - Validare prerequisiti
 * - Tracciare esiti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esami.h"
#include "allievi.h"    // Per trovaIDAllievo, setAllievoStato
#include "pagamenti.h"  // Per setRata, azzeraPagamento
#include "guida.h"      // Per getOreSvolte
#include "util.h"

//DEFINIZIONI STRUTTURE (PRIVATO)
#define MAX_ESAMI 100

/**
 * @struct Esame
 * @brief Rappresenta lo stato degli esami di un allievo (teorico e pratico).
 */
struct Esame {
    int id_allievo;
    int tentativiTeorico;
    int tentativiPratico;
    int superatoTeorico;
    int superatoPratico;
    Data dataTeorico[2];
    Data dataPratico[2];
};

/**
 * @struct ListaEsami
 * @brief Collezione di tutti gli esami registrati.
 */
struct ListaEsami {
    Esame elenco_esami[MAX_ESAMI];
    int n_esami;
};

//FUNZIONI DI CREAZIONE/DISTRUZIONE

ListaEsami* creaListaEsami(void) {
    ListaEsami* lista = (ListaEsami*)malloc(sizeof(ListaEsami));
    if (lista != NULL) {
        lista->n_esami = 0;
    }
    return lista;
}

void distruggiListaEsami(ListaEsami** lista) {
    if (lista != NULL && *lista != NULL) {
        free(*lista);
        *lista = NULL;
    }
}

void inizializzaListaEsami(ListaEsami* listaE) {
    if (listaE == NULL) return;
    listaE->n_esami = 0;
}

// FUNZIONI DI ACCESSO (GETTER)

int getNumeroEsami(const ListaEsami* lista) {
    return (lista != NULL) ? lista->n_esami : -1;
}

Esame* cercaEsamePerID(const ListaEsami* lista, int id_allievo) {
    if (lista == NULL || id_allievo <= 0) return NULL;

    for (int i = 0; i < lista->n_esami; i++) {
        if (lista->elenco_esami[i].id_allievo == id_allievo) {
            return &lista->elenco_esami[i];
        }
    }
    return NULL;
}

const Esame* getEsameAtIndex(const ListaEsami* lista, int index) {
    if (lista == NULL || index < 0 || index >= lista->n_esami) {
        return NULL;
    }
    return &lista->elenco_esami[index];
}

int getEsameIDAllievo(const Esame* esame) {
    return (esame != NULL) ? esame->id_allievo : -1;
}

int getTentativiTeorico(const Esame* esame) {
    return (esame != NULL) ? esame->tentativiTeorico : -1;
}

int getTentativiPratico(const Esame* esame) {
    return (esame != NULL) ? esame->tentativiPratico : -1;
}

bool isTeoricoSuperato(const Esame* esame) {
    return (esame != NULL && esame->superatoTeorico == 1);
}

bool isPraticoSuperato(const Esame* esame) {
    return (esame != NULL && esame->superatoPratico == 1);
}

bool tentativiEsauriti(const Esame* esame, TipoEsame tipo) {
    if (esame == NULL) return false;

    if (tipo == ESAME_TEORICO) {
        return esame->tentativiTeorico >= 2;
    } else {
        return esame->tentativiPratico >= 2;
    }
}

bool getDataTeorico(const Esame* esame, int tentativo, Data* data) {
    if (esame == NULL || data == NULL || tentativo < 0 || tentativo >= 2) {
        return false;
    }
    if (tentativo >= esame->tentativiTeorico) {
        return false;
    }
    *data = esame->dataTeorico[tentativo];
    return true;
}

bool getDataPratico(const Esame* esame, int tentativo, Data* data) {
    if (esame == NULL || data == NULL || tentativo < 0 || tentativo >= 2) {
        return false;
    }
    if (tentativo >= esame->tentativiPratico) {
        return false;
    }
    *data = esame->dataPratico[tentativo];
    return true;
}

//FUNZIONALITÀ DI DOMINIO

bool inizializzaEsame(ListaEsami* listaE, int id_allievo) {
    if (listaE == NULL || id_allievo <= 0) return false;

    if (listaE->n_esami >= MAX_ESAMI) {
        printf("Errore: numero massimo di esami raggiunto.\n");
        return false;
    }

    Esame nuovo;
    nuovo.id_allievo = id_allievo;
    nuovo.tentativiTeorico = 0;
    nuovo.tentativiPratico = 0;
    nuovo.superatoTeorico = 0;
    nuovo.superatoPratico = 0;

    // Inizializza tutte le date a 0
    for (int i = 0; i < 2; i++) {
        nuovo.dataTeorico[i] = (Data){0, 0, 0};
        nuovo.dataPratico[i] = (Data){0, 0, 0};
    }

    listaE->elenco_esami[listaE->n_esami++] = nuovo;
    return true;
}

CodiceEsame registraTentativoTeoricoBase(ListaEsami* lista, int id_allievo,
                                         EsitoEsame esito, Data data) {
    if (lista == NULL || id_allievo <= 0) return ESAME_ERRORE_GENERICO;

    Esame* e = cercaEsamePerID(lista, id_allievo);
    if (e == NULL) return ESAME_ERRORE_GENERICO;

    if (e->superatoTeorico) return ESAME_GIA_SUPERATO;
    if (e->tentativiTeorico >= 2) return ESAME_TENTATIVI_ESAURITI;

    int idx = e->tentativiTeorico;
    e->tentativiTeorico++;
    e->dataTeorico[idx] = data;

    if (esito == ESITO_SUPERATO) {
        e->superatoTeorico = 1;
        return ESAME_OK;
    } else {
        if (e->tentativiTeorico >= 2) {
            return ESAME_TENTATIVI_ESAURITI;
        }
        return ESAME_OK;
    }
}

CodiceEsame registraTentativoPraticoBase(ListaEsami* lista, int id_allievo,
                                         EsitoEsame esito, Data data,
                                         int ore_guida_svolte) {
    if (lista == NULL || id_allievo <= 0) return ESAME_ERRORE_GENERICO;

    Esame* e = cercaEsamePerID(lista, id_allievo);
    if (e == NULL) return ESAME_ERRORE_GENERICO;

    if (!e->superatoTeorico) return ESAME_TEORICO_NON_SUPERATO;
    if (ore_guida_svolte < 6) return ESAME_ORE_GUIDA_INSUFFICIENTI;
    if (e->superatoPratico) return ESAME_GIA_SUPERATO;
    if (e->tentativiPratico >= 2) return ESAME_TENTATIVI_ESAURITI;

    int idx = e->tentativiPratico;
    e->tentativiPratico++;
    e->dataPratico[idx] = data;

    if (esito == ESITO_SUPERATO) {
        e->superatoPratico = 1;
        return ESAME_OK;
    } else {
        if (e->tentativiPratico >= 2) {
            return ESAME_TENTATIVI_ESAURITI;
        }
        return ESAME_OK;
    }
}

void registraTentativoTeorico(ListaEsami* listaE, int id_allievo, int esito,
                              void* listaA, void* listaP) {
    if (listaE == NULL) {
        printf("Errore: lista esami non valida.\n");
        return;
    }

    Esame* e = cercaEsamePerID(listaE, id_allievo);
    if (e == NULL) {
        printf("Esame non trovato.\n");
        return;
    }

    if (e->superatoTeorico || e->tentativiTeorico >= 2) {
        printf("Esame teorico non registrabile.\n");
        return;
    }

    int idx = e->tentativiTeorico;
    e->tentativiTeorico++;

    // Chiedi la data del tentativo
    printf("Inserisci data esame teorico %d (gg mm aaaa): ", e->tentativiTeorico);
    scanf("%d %d %d",
          &e->dataTeorico[idx].giorno,
          &e->dataTeorico[idx].mese,
          &e->dataTeorico[idx].anno);

    if (esito == 1) {
        e->superatoTeorico = 1;
        printf("Esame teorico superato.\n");
    } else {
        printf("Esame teorico fallito. Tentativi: %d\n", e->tentativiTeorico);

        // Penalità: sospensione + ripagamento prima rata
        if (e->tentativiTeorico == 2 && !e->superatoTeorico) {
            // Cast dei puntatori void
            ListaAllievi* allievi = (ListaAllievi*)listaA;
            ListaPagamenti* pagamenti = (ListaPagamenti*)listaP;

            if (allievi != NULL) {
                Allievo* a = cercaAllievoPerID(allievi, id_allievo);
                if (a != NULL) {
                    setAllievoStato(a, "sospeso");
                }
            }

            if (pagamenti != NULL) {
                Pagamento* p = cercaPagamentoPerID(pagamenti, id_allievo);
                if (p != NULL) {
                    setRata(p, 1, 250.0);
                }
            }

            printf("Allievo sospeso. Deve ripagare la prima rata.\n");
        }
    }
}

void registraTentativoPratico(ListaEsami* listaE, int id_allievo, int esito,
                              void* listaP, const void* listaG) {
    if (listaE == NULL) {
        printf("Errore: lista esami non valida.\n");
        return;
    }

    Esame* e = cercaEsamePerID(listaE, id_allievo);
    if (e == NULL) {
        printf("Esame non trovato.\n");
        return;
    }

    if (!e->superatoTeorico) {
        printf("Non puoi sostenere l'esame pratico prima di superare quello teorico.\n");
        return;
    }

    // Controllo ore guida usando getter pubblici
    const ListaGuide* guide = (const ListaGuide*)listaG;
    if (guide != NULL) {
        Guida* g = cercaGuidaPerID(guide, id_allievo);
        if (g == NULL) {
            printf("Nessuna guida trovata per questo allievo.\n");
            return;
        }

        int ore = getOreSvolte(g);
        if (ore < 6) {
            printf("Impossibile sostenere l'esame pratico: meno di 6 ore di guida registrate.\n");
            return;
        }
    }

    if (e->superatoPratico || e->tentativiPratico >= 2) {
        printf("Esame pratico non registrabile.\n");
        return;
    }

    int idx = e->tentativiPratico;
    e->tentativiPratico++;

    // Chiedi la data del tentativo
    printf("Inserisci data esame pratico %d (gg mm aaaa): ", e->tentativiPratico);
    scanf("%d %d %d",
          &e->dataPratico[idx].giorno,
          &e->dataPratico[idx].mese,
          &e->dataPratico[idx].anno);

    if (esito == 1) {
        e->superatoPratico = 1;
        printf("Esame pratico superato.\n");
    } else {
        printf("Esame pratico fallito. Tentativi: %d\n", e->tentativiPratico);

        // Penalità: ripagamento tutte le rate
        if (e->tentativiPratico == 2 && !e->superatoPratico) {
            ListaPagamenti* pagamenti = (ListaPagamenti*)listaP;
            if (pagamenti != NULL) {
                Pagamento* p = cercaPagamentoPerID(pagamenti, id_allievo);
                if (p != NULL) {
                    setRata(p, 1, 250.0);
                    setRata(p, 2, 250.0);
                    setRata(p, 3, 250.0);
                }
            }
            printf("Due tentativi falliti. Deve ripagare tutte le rate.\n");
        }
    }
}

void stampaDettagliEsame(const Esame* esame) {
    if (esame == NULL) {
        printf("Esame non valido.\n");
        return;
    }

    printf("\n--- STATO ESAMI ---\n");
    printf("ID Allievo: %d\n", esame->id_allievo);
    printf("Teorico: %d tentativi - %s\n",
           esame->tentativiTeorico, esame->superatoTeorico ? "Superato" : "Non superato");

    for (int t = 0; t < esame->tentativiTeorico; t++) {
        Data dt = esame->dataTeorico[t];
        if (dt.giorno != 0)
            printf(" - Tentativo teorico %d: %02d/%02d/%04d\n", t + 1, dt.giorno, dt.mese, dt.anno);
    }

    printf("Pratico: %d tentativi - %s\n",
           esame->tentativiPratico, esame->superatoPratico ? "Superato" : "Non superato");

    for (int p = 0; p < esame->tentativiPratico; p++) {
        Data dp = esame->dataPratico[p];
        if (dp.giorno != 0)
            printf(" - Tentativo pratico %d: %02d/%02d/%04d\n", p + 1, dp.giorno, dp.mese, dp.anno);
    }
}

void stampaTuttiEsami(const ListaEsami* lista) {
    if (lista == NULL) {
        printf("Lista non valida.\n");
        return;
    }

    printf("\n--- Elenco Esami ---\n");
    for (int i = 0; i < lista->n_esami; i++) {
        stampaDettagliEsame(&lista->elenco_esami[i]);
    }
}

void stampaEsame(const ListaEsami* listaE, const void* listaA) {
    if (listaE == NULL || listaA == NULL) {
        printf("Errore: liste non valide.\n");
        return;
    }

    const ListaAllievi* allievi = (const ListaAllievi*)listaA;

    char nome[30], cognome[30];
    printf("Inserisci nome: ");
    inputString(nome, 30);
    printf("Inserisci cognome: ");
    inputString(cognome, 30);

    int id = trovaIDAllievo(allievi, nome, cognome);
    if (id == -1) {
        printf("Allievo non trovato.\n");
        return;
    }

    Esame* e = cercaEsamePerID(listaE, id);
    if (e == NULL) {
        printf("Esame non trovato per questo allievo.\n");
        return;
    }

    stampaDettagliEsame(e);
}

//FUNZIONI I/O FILE

bool salvaEsami(const ListaEsami* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Errore: impossibile aprire il file %s per la scrittura.\n", filename);
        return false;
    }

    // Salva numero esami
    fwrite(&lista->n_esami, sizeof(int), 1, file);

    // Salva array esami
    fwrite(lista->elenco_esami, sizeof(Esame), lista->n_esami, file);

    fclose(file);
    return true;
}

bool caricaEsami(ListaEsami* lista, const char* filename) {
    if (lista == NULL || filename == NULL) return false;

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return false; // File non esiste, non è un errore
    }

    // Carica numero esami
    fread(&lista->n_esami, sizeof(int), 1, file);

    // Carica array esami
    fread(lista->elenco_esami, sizeof(Esame), lista->n_esami, file);

    fclose(file);
    return true;
}
