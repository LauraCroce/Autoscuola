/**
 * @file allievi.h
 * @brief Gestione degli allievi dell'autoscuola (ADT Allievo).
 *
 * Questo modulo fornisce le strutture dati e le funzioni per:
 * - Registrare nuovi allievi
 * - Consultare e filtrare gli allievi per patente o stato
 * - Cercare e visualizzare i dettagli completi di un allievo
 * - Ordinare alfabeticamente la lista
 *
 * La rappresentazione interna è nascosta tramite tipi opachi.
 * L'accesso ai dati avviene tramite funzioni getter pubbliche.
 */
#ifndef ALLIEVI_H
#define ALLIEVI_H

#include <stdbool.h>

//TIPI OPACHI
/**
 * @brief Tipo opaco per un singolo allievo.
 * La definizione completa è in allievi.c
 */
typedef struct Allievo Allievo;

/**
 * @brief Tipo opaco per la lista degli allievi.
 * La definizione completa è in allievi.c
 */
typedef struct ListaAllievi ListaAllievi;

//FUNZIONI DI CREAZIONE/DISTRUZIONE
/**
 * @brief Crea e inizializza una nuova lista di allievi.
 * @return Puntatore alla lista creata, NULL in caso di errore.
 */
ListaAllievi* creaListaAllievi(void);

/**
 * @brief Distrugge una lista di allievi e libera la memoria.
 * @param lista Puntatore al puntatore della lista.
 */
void distruggiListaAllievi(ListaAllievi** lista);

/**
 * @brief Inizializza una lista già allocata (retrocompatibilità).
 * @param lista Puntatore alla lista da inizializzare.
 */
void inizializzaLista(ListaAllievi* lista);

//FUNZIONI DI ACCESSO (GETTER)
/**
 * @brief Restituisce il numero di allievi nella lista.
 * @param lista Puntatore alla lista.
 * @return Numero di allievi, -1 se lista è NULL.
 */
int getNumeroAllievi(const ListaAllievi* lista);

/**
 * @brief Restituisce l'ID di un allievo.
 * @param allievo Puntatore all'allievo.
 * @return ID dell'allievo, -1 se allievo è NULL.
 */
int getAllievoID(const Allievo* allievo);

/**
 * @brief Restituisce il nome di un allievo.
 * @param allievo Puntatore all'allievo.
 * @return Puntatore al nome (read-only), NULL se allievo è NULL.
 */
const char* getAllievoNome(const Allievo* allievo);

/**
 * @brief Restituisce il cognome di un allievo.
 * @param allievo Puntatore all'allievo.
 * @return Puntatore al cognome (read-only), NULL se allievo è NULL.
 */
const char* getAllievoCognome(const Allievo* allievo);

/**
 * @brief Restituisce il codice fiscale di un allievo.
 * @param allievo Puntatore all'allievo.
 * @return Puntatore al codice fiscale (read-only), NULL se allievo è NULL.
 */
const char* getAllievoCodiceFiscale(const Allievo* allievo);

/**
 * @brief Restituisce la categoria patente di un allievo.
 * @param allievo Puntatore all'allievo.
 * @return Puntatore alla categoria (read-only), NULL se allievo è NULL.
 */
const char* getAllievoCategoriaPatente(const Allievo* allievo);

/**
 * @brief Restituisce lo stato di un allievo.
 * @param allievo Puntatore all'allievo.
 * @return Puntatore allo stato (read-only), NULL se allievo è NULL.
 */
const char* getAllievoStato(const Allievo* allievo);

/**
 * @brief Ottiene un puntatore all'allievo in posizione index.
 * @param lista Lista degli allievi.
 * @param index Indice dell'allievo (0-based).
 * @return Puntatore all'allievo, NULL se index non valido.
 */
const Allievo* getAllievoAtIndex(const ListaAllievi* lista, int index);

//FUNZIONI DI MODIFICA (SETTER)
/**
 * @brief Modifica lo stato di un allievo.
 * @param allievo Puntatore all'allievo (non const perché modifichiamo).
 * @param nuovo_stato Nuovo stato da impostare.
 * @return true se modificato con successo, false altrimenti.
 */
bool setAllievoStato(Allievo* allievo, const char* nuovo_stato);

//FUNZIONALITÀ DI DOMINIO
/**
 * @brief Aggiorna il prossimo ID disponibile in base agli allievi esistenti.
 * @param lista Puntatore alla lista degli allievi.
 */
void aggiornaID(ListaAllievi* lista);

/**
 * @brief Cerca l'ID di un allievo a partire da nome e cognome.
 * @param lista Lista degli allievi.
 * @param nome Nome da cercare.
 * @param cognome Cognome da cercare.
 * @return ID dell'allievo se trovato, -1 altrimenti.
 */
int trovaIDAllievo(const ListaAllievi* lista, const char* nome, const char* cognome);

/**
 * @brief Cerca un allievo per nome e cognome.
 * @param lista Lista degli allievi.
 * @param nome Nome da cercare.
 * @param cognome Cognome da cercare.
 * @return Puntatore all'allievo se trovato, NULL altrimenti.
 */
Allievo* cercaAllievoPerNome(ListaAllievi* lista, const char* nome, const char* cognome);

/**
 * @brief Cerca un allievo per ID.
 * @param lista Lista degli allievi.
 * @param id ID da cercare.
 * @return Puntatore all'allievo se trovato, NULL altrimenti.
 */
Allievo* cercaAllievoPerID(ListaAllievi* lista, int id);

/**
 * @brief Inserisce un nuovo allievo nella lista (acquisizione da tastiera).
 * Questa funzione interagisce con l'utente per inserire i dati.
 * @param lista Puntatore alla lista degli allievi.
 * @return ID del nuovo allievo, -1 in caso di errore.
 */
int inserisciAllievoBase(ListaAllievi* lista);

/**
 * @brief Inserisce un nuovo allievo e inizializza i suoi pagamenti ed esami.
 * Questa è la funzione da chiamare dal menu principale.
 * @param lista Puntatore alla lista degli allievi.
 * @param listaP Puntatore opaco alla lista dei pagamenti.
 * @param listaE Puntatore opaco alla lista degli esami.
 */
void inserisciAllievo(ListaAllievi* lista, void* listaP, void* listaE);

/**
 * @brief Ordina gli allievi alfabeticamente per cognome e nome.
 * @param lista Puntatore alla lista da ordinare.
 */
void ordinaAllieviAlfabetico(ListaAllievi* lista);

/**
 * @brief Stampa l'elenco completo degli allievi.
 * @param lista Lista da stampare.
 */
void stampaAllievi(const ListaAllievi* lista);

/**
 * @brief Filtra e stampa gli allievi per categoria di patente.
 * @param lista Lista degli allievi.
 */
void filtraPerPatente(const ListaAllievi* lista);

/**
 * @brief Filtra e stampa gli allievi per stato (iscritto/sospeso).
 * @param lista Lista degli allievi.
 */
void filtraPerStato(const ListaAllievi* lista);

/**
 * @brief Mostra i dettagli completi di un allievo (compresi pagamenti ed esami).
 * @param listaA Lista degli allievi.
 * @param listaP Puntatore opaco alla lista dei pagamenti.
 * @param listaE Puntatore opaco alla lista degli esami.
 */
void cercaAllievo(const ListaAllievi* listaA, const void* listaP, const void* listaE);

//FUNZIONI I/O FILE
/**
 * @brief Salva la lista degli allievi su file binario.
 * @param lista Lista da salvare.
 * @param filename Nome del file (es. "allievi.dat").
 * @return true se successo, false altrimenti.
 */
bool salvaAllievi(const ListaAllievi* lista, const char* filename);

/**
 * @brief Carica la lista degli allievi da file binario.
 * @param lista Lista in cui caricare (deve essere già inizializzata).
 * @param filename Nome del file (es. "allievi.dat").
 * @return true se successo, false se file non esiste o errore.
 */
bool caricaAllievi(ListaAllievi* lista, const char* filename);

#endif // ALLIEVI_H
