/**
 * @file util.h
 * @brief Funzioni di utilità generali per input/output, validazione e manipolazione stringhe.
 *
 * Questo modulo fornisce funzioni ausiliarie per migliorare l'interazione
 * con l'utente e semplificare la gestione di input da tastiera,
 * validazioni di base, confronti tra stringhe, e operazioni di pulizia.
 *
 * Le funzioni qui definite sono utilizzate trasversalmente
 * in più moduli del progetto Autoscuola, in particolare per:
 * - Input numerico e testuale da tastiera
 * - Validazione delle categorie di patente
 * - Pulizia del buffer di input
 * - Pulizia del terminale
 * - Attesa tra schermate
 * - Confronto case-insensitive tra stringhe
 *
 */

#ifndef UTIL_H
#define UTIL_H

/**
 * @brief Acquisisce una stringa da tastiera con lunghezza massima specificata.
 * @param buffer Buffer di destinazione dove salvare la stringa.
 * @param maxLen Lunghezza massima accettata (incluso '\0').
 */
void inputString(char* buffer, int maxLen);

/**
 * @brief Valida la categoria di patente inserita (A, B, AM).
 * @param cat Stringa contenente la categoria da verificare.
 * @return 1 se valida, 0 altrimenti.
 */
int validaCategoria(const char* cat);

/**
 * @brief Richiede conferma all'utente con una domanda.
 * @param messaggio Messaggio da mostrare (es. "Sei sicuro?").
 * @return 1 se l'utente conferma, 0 altrimenti.
 */
int conferma(const char* messaggio);

/**
 * @brief Acquisisce un intero da tastiera con messaggio personalizzato.
 * @param messaggio Messaggio da mostrare all'utente.
 * @return Valore intero inserito dall'utente.
 */
int inputInt(const char* messaggio);

/**
 * @brief Acquisisce un numero decimale (float) da tastiera con messaggio personalizzato.
 * @param messaggio Messaggio da mostrare all'utente.
 * @return Valore float inserito dall'utente.
 */
float inputFloat(const char* messaggio);

/**
 * @brief Svuota il buffer di input per evitare letture residue.
 */
void clearBuffer();

/**
 * @brief Pulisce lo schermo del terminale in modo portabile.
 */
void pulisciSchermo();

/**
 * @brief Attende che l'utente prema INVIO prima di continuare.
 */
void attendiInvio();

/**
 * @brief Confronta due stringhe ignorando le differenze tra maiuscole e minuscole.
 * @param a Prima stringa.
 * @param b Seconda stringa.
 * @return 1 se le stringhe sono uguali (case-insensitive), 0 altrimenti.
 */
int equalsIgnoreCase(const char* a, const char* b);

#endif // UTIL_H
