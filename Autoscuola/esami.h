/**
 * @file esami.h
 * @brief Gestione degli esami teorici e pratici (ADT Esame).
 *
 * Fornisce funzionalità per:
 * - Registrare tentativi d'esame
 * - Tracciare esiti e date
 * - Verificare prerequisiti
 * - Calcolare penalità
 *
 * La rappresentazione interna è nascosta (tipo opaco).
 */
#ifndef ESAMI_H
#define ESAMI_H

#include <stdbool.h>
#include "data.h"

//TIPI OPACHI
/**
 * @brief Tipo opaco per un singolo esame.
 * La definizione completa è in esami.c
 */
typedef struct Esame Esame;

/**
 * @brief Tipo opaco per la lista degli esami.
 * La definizione completa è in esami.c
 */
typedef struct ListaEsami ListaEsami;

//ENUMERAZIONI PUBBLICHE
/**
 * @brief Tipo di esame.
 */
typedef enum {
    ESAME_TEORICO = 0,
    ESAME_PRATICO = 1
} TipoEsame;

/**
 * @brief Esito di un tentativo.
 */
typedef enum {
    ESITO_NON_SUPERATO = 0,
    ESITO_SUPERATO = 1
} EsitoEsame;

/**
 * @brief Codici di ritorno per le operazioni sugli esami.
 */
typedef enum {
    ESAME_OK = 0,
    ESAME_ERRORE_GENERICO = -1,
    ESAME_TEORICO_NON_SUPERATO = -2,
    ESAME_ORE_GUIDA_INSUFFICIENTI = -3,
    ESAME_TENTATIVI_ESAURITI = -4,
    ESAME_GIA_SUPERATO = -5
} CodiceEsame;

//FUNZIONI DI CREAZIONE/DISTRUZIONE
/**
 * @brief Crea e inizializza una nuova lista di esami.
 * @return Puntatore alla lista creata, NULL in caso di errore.
 */
ListaEsami* creaListaEsami(void);

/**
 * @brief Distrugge una lista di esami e libera la memoria.
 * @param lista Puntatore al puntatore della lista.
 */
void distruggiListaEsami(ListaEsami** lista);

/**
 * @brief Inizializza la lista degli esami (retrocompatibilità).
 * @param listaE Puntatore alla lista da inizializzare.
 */
void inizializzaListaEsami(ListaEsami* listaE);

// FUNZIONI DI ACCESSO (GETTER)
/**
 * @brief Restituisce il numero di esami registrati.
 * @param lista Puntatore alla lista.
 * @return Numero di esami, -1 se lista è NULL.
 */
int getNumeroEsami(const ListaEsami* lista);

/**
 * @brief Cerca l'esame associato a un ID allievo.
 * @param lista Lista degli esami.
 * @param id_allievo ID da cercare.
 * @return Puntatore all'esame se trovato, NULL altrimenti.
 */
Esame* cercaEsamePerID(const ListaEsami* lista, int id_allievo);

/**
 * @brief Ottiene un puntatore all'esame in posizione index.
 * @param lista Lista degli esami.
 * @param index Indice dell'esame (0-based).
 * @return Puntatore all'esame, NULL se index non valido.
 */
const Esame* getEsameAtIndex(const ListaEsami* lista, int index);

/**
 * @brief Ottiene l'ID allievo associato a un esame.
 * @param esame Puntatore all'esame.
 * @return ID allievo, -1 se esame è NULL.
 */
int getEsameIDAllievo(const Esame* esame);

/**
 * @brief Restituisce il numero di tentativi teorici effettuati.
 * @param esame Puntatore all'esame.
 * @return Numero di tentativi, -1 se esame è NULL.
 */
int getTentativiTeorico(const Esame* esame);

/**
 * @brief Restituisce il numero di tentativi pratici effettuati.
 * @param esame Puntatore all'esame.
 * @return Numero di tentativi, -1 se esame è NULL.
 */
int getTentativiPratico(const Esame* esame);

/**
 * @brief Verifica se l'esame teorico è stato superato.
 * @param esame Puntatore all'esame.
 * @return true se superato, false altrimenti.
 */
bool isTeoricoSuperato(const Esame* esame);

/**
 * @brief Verifica se l'esame pratico è stato superato.
 * @param esame Puntatore all'esame.
 * @return true se superato, false altrimenti.
 */
bool isPraticoSuperato(const Esame* esame);

/**
 * @brief Verifica se l'allievo ha esaurito i tentativi per un tipo di esame.
 * @param esame Puntatore all'esame.
 * @param tipo Tipo di esame (TEORICO o PRATICO).
 * @return true se tentativi esauriti (>= 2), false altrimenti.
 */
bool tentativiEsauriti(const Esame* esame, TipoEsame tipo);

/**
 * @brief Ottiene la data di un tentativo teorico.
 * @param esame Puntatore all'esame.
 * @param tentativo Numero del tentativo (0 o 1).
 * @param data Puntatore alla struttura Data dove copiare la data.
 * @return true se il tentativo esiste, false altrimenti.
 */
bool getDataTeorico(const Esame* esame, int tentativo, Data* data);

/**
 * @brief Ottiene la data di un tentativo pratico.
 * @param esame Puntatore all'esame.
 * @param tentativo Numero del tentativo (0 o 1).
 * @param data Puntatore alla struttura Data dove copiare la data.
 * @return true se il tentativo esiste, false altrimenti.
 */
bool getDataPratico(const Esame* esame, int tentativo, Data* data);

//FUNZIONALITÀ DI DOMINIO
/**
 * @brief Inserisce un nuovo esame per l'allievo appena registrato.
 * @param listaE Puntatore alla lista esami.
 * @param id_allievo ID dell'allievo per cui inizializzare l'esame.
 * @return true se creato con successo, false altrimenti.
 */
bool inizializzaEsame(ListaEsami* listaE, int id_allievo);

/**
 * @brief Registra un tentativo di esame teorico.
 *
 * Aggiorna automaticamente il contatore tentativi e il flag superato.
 * Registra la data del tentativo.
 *
 * @param lista Lista degli esami.
 * @param id_allievo ID dell'allievo.
 * @param esito Esito del tentativo (SUPERATO o NON_SUPERATO).
 * @param data Data del tentativo.
 * @return Codice di ritorno (ESAME_OK, ESAME_TENTATIVI_ESAURITI, ecc.).
 */
CodiceEsame registraTentativoTeoricoBase(ListaEsami* lista, int id_allievo,
                                         EsitoEsame esito, Data data);

/**
 * @brief Registra un tentativo di esame pratico.
 *
 * Prerequisiti verificati internamente:
 * - Esame teorico superato
 *
 * @param lista Lista degli esami.
 * @param id_allievo ID dell'allievo.
 * @param esito Esito del tentativo.
 * @param data Data del tentativo.
 * @param ore_guida_svolte Ore di guida completate (per verifica prerequisiti).
 * @return Codice di ritorno.
 */
CodiceEsame registraTentativoPraticoBase(ListaEsami* lista, int id_allievo,
                                         EsitoEsame esito, Data data,
                                         int ore_guida_svolte);

/**
 * @brief Registra un tentativo d'esame teorico e aggiorna lo stato.
 *
 * Se il secondo tentativo fallisce, lo stato dell'allievo viene modificato
 * in "sospeso" e viene riassegnata la prima rata da pagare.
 *
 * @param listaE Lista degli esami.
 * @param id_allievo ID dell'allievo.
 * @param esito 1 se superato, 0 se fallito.
 * @param listaA Puntatore opaco alla lista allievi (per aggiornare lo stato).
 * @param listaP Puntatore opaco alla lista pagamenti (per penalità).
 */
void registraTentativoTeorico(ListaEsami* listaE, int id_allievo, int esito,
                              void* listaA, void* listaP);

/**
 * @brief Registra un tentativo d'esame pratico e aggiorna lo stato.
 *
 * Richiede il superamento del teorico e almeno 6 ore di guida svolte.
 * Se entrambi i tentativi pratici falliscono, l'allievo deve ripagare tutte le rate.
 *
 * @param listaE Lista degli esami.
 * @param id_allievo ID dell'allievo.
 * @param esito 1 se superato, 0 se fallito.
 * @param listaP Puntatore opaco alla lista pagamenti.
 * @param listaG Puntatore opaco alla lista guide.
 */
void registraTentativoPratico(ListaEsami* listaE, int id_allievo, int esito,
                              void* listaP, const void* listaG);

/**
 * @brief Stampa i dettagli di un esame (tentativi, esiti, date).
 * @param esame Puntatore all'esame da visualizzare.
 */
void stampaDettagliEsame(const Esame* esame);

/**
 * @brief Stampa tutti gli esami registrati.
 * @param lista Lista degli esami.
 */
void stampaTuttiEsami(const ListaEsami* lista);

/**
 * @brief Visualizza lo stato dettagliato degli esami (tentativi, esito, date).
 * @param listaE Lista degli esami.
 * @param listaA Puntatore opaco alla lista degli allievi (per ottenere nome e ID).
 */
void stampaEsame(const ListaEsami* listaE, const void* listaA);

//FUNZIONI I/O FILE
/**
 * @brief Salva la lista degli esami su file binario.
 * @param lista Lista da salvare.
 * @param filename Nome del file (es. "esami.dat").
 * @return true se successo, false altrimenti.
 */
bool salvaEsami(const ListaEsami* lista, const char* filename);

/**
 * @brief Carica la lista degli esami da file binario.
 * @param lista Lista in cui caricare (deve essere già inizializzata).
 * @param filename Nome del file (es. "esami.dat").
 * @return true se successo, false se file non esiste o errore.
 */
bool caricaEsami(ListaEsami* lista, const char* filename);

#endif // ESAMI_H
