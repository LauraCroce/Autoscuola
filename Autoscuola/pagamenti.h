/**
 * @file pagamenti.h
 * @brief Gestione dei pagamenti degli allievi (ADT Pagamento).
 *
 * Questo modulo fornisce funzionalità per registrare e monitorare
 * i pagamenti (tre rate + extra) senza esporre la rappresentazione interna.
 *
 * Le funzioni permettono:
 * - Inizializzazione e creazione pagamenti
 * - Registrazione delle rate
 * - Calcolo del totale pagato
 * - Visualizzazione stato pagamenti
 */
#ifndef PAGAMENTI_H
#define PAGAMENTI_H

#include <stdbool.h>

//TIPI OPACHI
/**
 * @brief Tipo opaco per un singolo pagamento.
 * La definizione completa è in pagamenti.c
 */
typedef struct Pagamento Pagamento;

/**
 * @brief Tipo opaco per la lista dei pagamenti.
 * La definizione completa è in pagamenti.c
 */
typedef struct ListaPagamenti ListaPagamenti;

//FUNZIONI DI CREAZIONE/DISTRUZIONE
/**
 * @brief Crea e inizializza una nuova lista di pagamenti.
 * @return Puntatore alla lista creata, NULL in caso di errore.
 */
ListaPagamenti* creaListaPagamenti(void);

/**
 * @brief Distrugge una lista di pagamenti e libera la memoria.
 * @param lista Puntatore al puntatore della lista.
 */
void distruggiListaPagamenti(ListaPagamenti** lista);

/**
 * @brief Inizializza la lista dei pagamenti impostando il conteggio a zero (retrocompatibilità).
 * @param listaP Puntatore alla lista da inizializzare.
 */
void inizializzaListaPagamenti(ListaPagamenti* listaP);

//FUNZIONI DI ACCESSO (GETTER)
/**
 * @brief Restituisce il numero di pagamenti registrati.
 * @param lista Puntatore alla lista.
 * @return Numero di pagamenti, -1 se lista è NULL.
 */
int getNumeroPagamenti(const ListaPagamenti* lista);

/**
 * @brief Cerca il pagamento associato a un ID allievo.
 * @param lista Lista dei pagamenti.
 * @param id_allievo ID da cercare.
 * @return Puntatore al pagamento se trovato, NULL altrimenti.
 */
Pagamento* cercaPagamentoPerID(const ListaPagamenti* lista, int id_allievo);

/**
 * @brief Ottiene un puntatore al pagamento in posizione index.
 * @param lista Lista dei pagamenti.
 * @param index Indice del pagamento (0-based).
 * @return Puntatore al pagamento, NULL se index non valido.
 */
const Pagamento* getPagamentoAtIndex(const ListaPagamenti* lista, int index);

/**
 * @brief Ottiene l'ID allievo associato a un pagamento.
 * @param pagamento Puntatore al pagamento.
 * @return ID allievo, -1 se pagamento è NULL.
 */
int getPagamentoIDAllievo(const Pagamento* pagamento);

/**
 * @brief Calcola il totale pagato da un allievo (somma di tutte le rate + extra).
 * @param pagamento Puntatore al pagamento.
 * @return Totale pagato, 0.0 se pagamento è NULL.
 */
float calcolaTotalePagato(const Pagamento* pagamento);

/**
 * @brief Ottiene l'importo della prima rata.
 * @param pagamento Puntatore al pagamento.
 * @return Importo della prima rata, 0.0 se NULL.
 */
float getPrimaRata(const Pagamento* pagamento);

/**
 * @brief Ottiene l'importo della seconda rata.
 * @param pagamento Puntatore al pagamento.
 * @return Importo della seconda rata, 0.0 se NULL.
 */
float getSecondaRata(const Pagamento* pagamento);

/**
 * @brief Ottiene l'importo della terza rata.
 * @param pagamento Puntatore al pagamento.
 * @return Importo della terza rata, 0.0 se NULL.
 */
float getTerzaRata(const Pagamento* pagamento);

/**
 * @brief Ottiene l'importo extra.
 * @param pagamento Puntatore al pagamento.
 * @return Importo extra, 0.0 se NULL.
 */
float getExtra(const Pagamento* pagamento);

//FUNZIONI DI MODIFICA (SETTER)
/**
 * @brief Azzera tutti i pagamenti di un allievo.
 * @param pagamento Puntatore al pagamento da azzerare.
 * @return true se operazione riuscita, false altrimenti.
 */
bool azzeraPagamento(Pagamento* pagamento);

/**
 * @brief Imposta una rata specifica.
 * @param pagamento Puntatore al pagamento.
 * @param tipo_rata 1=prima, 2=seconda, 3=terza, 4=extra.
 * @param importo Importo da impostare.
 * @return true se operazione riuscita, false altrimenti.
 */
bool setRata(Pagamento* pagamento, int tipo_rata, float importo);

//FUNZIONALITÀ DI DOMINIO
/**
 * @brief Registra un nuovo pagamento iniziale per un allievo appena iscritto.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param id_allievo ID dell'allievo a cui associare il pagamento.
 * @return true se il pagamento è stato creato, false altrimenti.
 */
bool inizializzaPagamento(ListaPagamenti* listaP, int id_allievo);

/**
 * @brief Aggiunge un importo a una specifica rata di un allievo.
 * @param lista Puntatore alla lista dei pagamenti.
 * @param id_allievo ID dell'allievo.
 * @param tipo_rata Tipo di rata: 1=prima, 2=seconda, 3=terza, 4=extra.
 * @param importo Importo da registrare.
 * @return true se l'operazione è riuscita, false altrimenti.
 */
bool aggiungiRata(ListaPagamenti* lista, int id_allievo, int tipo_rata, float importo);

/**
 * @brief Consente l'inserimento di una nuova rata (seconda, terza o extra) per un allievo.
 * Interagisce con l'utente da tastiera.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaA Puntatore opaco alla lista degli allievi per la ricerca dell'ID.
 */
void inserisciPagamento(ListaPagamenti* listaP, const void* listaA);

/**
 * @brief Visualizza lo stato di pagamento per un singolo allievo.
 * @param listaP Lista dei pagamenti.
 * @param listaA Puntatore opaco alla lista degli allievi (per ricerca nome/cognome).
 */
void stampaStatoPagamento(const ListaPagamenti* listaP, const void* listaA);

/**
 * @brief Stampa i dettagli di un pagamento.
 * @param pagamento Puntatore al pagamento da visualizzare.
 */
void stampaPagamento(const Pagamento* pagamento);

/**
 * @brief Stampa tutti i pagamenti registrati.
 * @param lista Lista dei pagamenti.
 */
void stampaTuttiPagamenti(const ListaPagamenti* lista);

/**
 * @brief Stampa il riepilogo di tutti i pagamenti degli allievi, includendo i costi extra per ore guida aggiuntive.
 * @param listaP Lista dei pagamenti.
 * @param listaA Puntatore opaco alla lista degli allievi (per ordinamento e associazione).
 * @param listaG Puntatore opaco alla lista delle guide per il calcolo dei costi extra.
 */
void riepilogoPagamenti(const ListaPagamenti* listaP, const void* listaA, const void* listaG);

//FUNZIONI I/O FILE
/**
 * @brief Salva la lista dei pagamenti su file binario.
 * @param lista Lista da salvare.
 * @param filename Nome del file (es. "pagamenti.dat").
 * @return true se successo, false altrimenti.
 */
bool salvaPagamenti(const ListaPagamenti* lista, const char* filename);

/**
 * @brief Carica la lista dei pagamenti da file binario.
 * @param lista Lista in cui caricare (deve essere già inizializzata).
 * @param filename Nome del file (es. "pagamenti.dat").
 * @return true se successo, false se file non esiste o errore.
 */
bool caricaPagamenti(ListaPagamenti* lista, const char* filename);

#endif // PAGAMENTI_H
