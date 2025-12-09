/**
 * @file guida.h
 * @brief Gestione delle ore di guida (ADT Guida).
 *
 * Fornisce funzionalità per:
 * - Registrare ore di guida svolte
 * - Calcolare ore extra (oltre le 6 obbligatorie)
 * - Verificare prerequisiti per esame pratico
 * - Calcolare costi aggiuntivi
 *
 * La rappresentazione interna è nascosta (tipo opaco).
 */
#ifndef GUIDA_H
#define GUIDA_H

#include <stdbool.h>

//COSTANTI PUBBLICHE
#define ORE_GUIDA_OBBLIGATORIE 6

//TIPI OPACHI
/**
 * @brief Tipo opaco per una singola guida.
 * La definizione completa è in guida.c
 */
typedef struct Guida Guida;

/**
 * @brief Tipo opaco per la lista delle guide.
 * La definizione completa è in guida.c
 */
typedef struct ListaGuide ListaGuide;

//FUNZIONI DI CREAZIONE/DISTRUZIONE
/**
 * @brief Crea e inizializza una nuova lista di guide.
 * @return Puntatore alla lista creata, NULL in caso di errore.
 */
ListaGuide* creaListaGuide(void);

/**
 * @brief Distrugge una lista di guide e libera la memoria.
 * @param lista Puntatore al puntatore della lista.
 */
void distruggiListaGuide(ListaGuide** lista);

/**
 * @brief Inizializza la lista delle guide (retrocompatibilità).
 * @param lista Puntatore alla lista da inizializzare.
 */
void inizializzaListaGuide(ListaGuide* lista);

//FUNZIONI DI ACCESSO (GETTER)
/**
 * @brief Restituisce il numero di guide registrate.
 * @param lista Puntatore alla lista.
 * @return Numero di guide, -1 se lista è NULL.
 */
int getNumeroGuide(const ListaGuide* lista);

/**
 * @brief Cerca la guida associata a un ID allievo.
 * @param lista Lista delle guide.
 * @param id_allievo ID da cercare.
 * @return Puntatore alla guida se trovata, NULL altrimenti.
 */
Guida* cercaGuidaPerID(const ListaGuide* lista, int id_allievo);

/**
 * @brief Ottiene un puntatore alla guida in posizione index.
 * @param lista Lista delle guide.
 * @param index Indice della guida (0-based).
 * @return Puntatore alla guida, NULL se index non valido.
 */
const Guida* getGuidaAtIndex(const ListaGuide* lista, int index);

/**
 * @brief Ottiene l'ID allievo associato a una guida.
 * @param guida Puntatore alla guida.
 * @return ID allievo, -1 se guida è NULL.
 */
int getGuidaIDAllievo(const Guida* guida);

/**
 * @brief Restituisce le ore totali svolte da un allievo.
 * @param guida Puntatore alla guida.
 * @return Numero di ore svolte, -1 se guida è NULL.
 */
int getOreSvolte(const Guida* guida);

/**
 * @brief Restituisce le ore extra (oltre le 6 obbligatorie).
 * @param guida Puntatore alla guida.
 * @return Numero di ore extra, 0 se <= 6 ore totali o guida è NULL.
 */
int getOreExtra(const Guida* guida);

/**
 * @brief Verifica se un allievo ha completato le ore obbligatorie.
 * @param guida Puntatore alla guida.
 * @return true se ore >= 6, false altrimenti.
 */
bool haCompletateOreObbligatorie(const Guida* guida);

/**
 * @brief Calcola il costo totale delle ore extra.
 * @param guida Puntatore alla guida.
 * @param costo_orario Costo per ora extra.
 * @return Costo totale ore extra, 0.0 se nessuna ora extra o guida è NULL.
 */
float calcolaCostoOreExtra(const Guida* guida, float costo_orario);

//FUNZIONALITÀ DI DOMINIO
/**
 * @brief Inizializza una nuova guida per un allievo.
 * @param lista Puntatore alla lista delle guide.
 * @param id_allievo ID dell'allievo.
 * @return true se creata con successo, false altrimenti.
 */
bool inizializzaGuida(ListaGuide* lista, int id_allievo);

/**
 * @brief Registra ore di guida per un allievo.
 *
 * Se l'allievo ha già una guida registrata, le ore vengono sommate.
 * Le ore extra (oltre le 6) vengono calcolate automaticamente.
 *
 * @param lista Puntatore alla lista delle guide.
 * @param id_allievo ID dell'allievo.
 * @param ore_da_aggiungere Numero di ore da registrare (> 0).
 * @return true se registrazione riuscita, false altrimenti.
 */
bool registraOreGuida(ListaGuide* lista, int id_allievo, int ore_da_aggiungere);

/**
 * @brief Registra una nuova sessione di guida per un allievo.
 *
 * Se l'allievo ha già una guida registrata, le ore vengono sommate.
 * Le ore extra (oltre le 6) vengono conteggiate separatamente per eventuali costi.
 * Interagisce con l'utente da tastiera.
 *
 * @param lista Puntatore alla lista delle guide.
 * @param listaA Puntatore opaco alla lista degli allievi (per verifica nome e cognome).
 */
void registraGuida(ListaGuide* lista, const void* listaA);

/**
 * @brief Stampa i dettagli di una guida (ore totali, ore extra).
 * @param guida Puntatore alla guida da visualizzare.
 */
void stampaGuida(const Guida* guida);

/**
 * @brief Stampa tutte le guide registrate.
 * @param lista Lista delle guide.
 */
void stampaTutteGuide(const ListaGuide* lista);

/**
 * @brief Stampa l'elenco delle guide svolte per ciascun allievo.
 *
 * Include ore totali e ore extra, con visualizzazione del nome e cognome.
 *
 * @param lista Puntatore alla lista delle guide.
 * @param listaA Puntatore opaco alla lista degli allievi (per associare nomi agli ID).
 */
void stampaGuide(const ListaGuide* lista, const void* listaA);

//FUNZIONI I/O FILE
/**
 * @brief Salva la lista delle guide su file binario.
 * @param lista Lista da salvare.
 * @param filename Nome del file (es. "guide.dat").
 * @return true se successo, false altrimenti.
 */
bool salvaGuide(const ListaGuide* lista, const char* filename);

/**
 * @brief Carica la lista delle guide da file binario.
 * @param lista Lista in cui caricare (deve essere già inizializzata).
 * @param filename Nome del file (es. "guide.dat").
 * @return true se successo, false se file non esiste o errore.
 */
bool caricaGuide(ListaGuide* lista, const char* filename);

#endif // GUIDA_H
