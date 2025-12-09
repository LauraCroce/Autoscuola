/**
 * @file fileio.h
 * @brief Coordinamento operazioni I/O per la persistenza del sistema Autoscuola.
 *
 * Questo modulo coordina il salvataggio e caricamento di tutti i dati
 * senza accedere direttamente alle rappresentazioni interne degli ADT.
 * Ogni ADT gestisce il proprio formato di file tramite funzioni dedicate.
 *
 * File utilizzati:
 * - `allievi.dat` (gestito da allievi.c)
 * - `pagamenti.dat` (gestito da pagamenti.c)
 * - `esami.dat` (gestito da esami.c)
 * - `guide.dat` (gestito da guida.c)
 * - `resoconto_allievi.txt` (report testuale generato da questo modulo)
 */
#ifndef FILEIO_H
#define FILEIO_H

#include <stdbool.h>

//FORWARD DECLARATIONS (tipi opachi)
typedef struct ListaAllievi ListaAllievi;
typedef struct ListaPagamenti ListaPagamenti;
typedef struct ListaEsami ListaEsami;
typedef struct ListaGuide ListaGuide;

//FUNZIONI DI COORDINAMENTO I/O

/**
 * @brief Salva tutti i dati su file binari.
 *
 * Chiama le funzioni di salvataggio di ogni ADT:
 * - salvaAllievi() in allievi.dat
 * - salvaPagamenti() in pagamenti.dat
 * - salvaEsami() in esami.dat
 * - salvaGuide() in guide.dat
 *
 * @param listaA Puntatore alla lista degli allievi.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaE Puntatore alla lista degli esami.
 * @param listaG Puntatore alla lista delle guide.
 * @return true se tutte le operazioni riescono, false altrimenti.
 */
bool salvaTuttiDati(const ListaAllievi* listaA,
                    const ListaPagamenti* listaP,
                    const ListaEsami* listaE,
                    const ListaGuide* listaG);

/**
 * @brief Carica tutti i dati dai file binari.
 *
 * Chiama le funzioni di caricamento di ogni ADT:
 * - caricaAllievi() da allievi.dat
 * - caricaPagamenti() da pagamenti.dat
 * - caricaEsami() da esami.dat
 * - caricaGuide() da guide.dat
 *
 * In caso di file mancante, la lista corrispondente resta vuota.
 *
 * @param listaA Puntatore alla lista degli allievi.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaE Puntatore alla lista degli esami.
 * @param listaG Puntatore alla lista delle guide.
 * @return true se almeno un caricamento riesce, false se tutti falliscono.
 */
bool caricaTuttiDati(ListaAllievi* listaA,
                     ListaPagamenti* listaP,
                     ListaEsami* listaE,
                     ListaGuide* listaG);

/**
 * @brief Esporta un resoconto completo in formato testo leggibile.
 *
 * Genera il file `resoconto_allievi.txt` con tutti i dettagli:
 * - Dati anagrafici di ogni allievo
 * - Stato pagamenti (rate + ore extra)
 * - Stato esami con date dei tentativi
 * - Ore di guida svolte ed extra
 *
 * Usa le interfacce pubbliche degli ADT (getter) per ottenere i dati.
 *
 * @param listaA Puntatore alla lista degli allievi.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaE Puntatore alla lista degli esami.
 * @param listaG Puntatore alla lista delle guide.
 * @return true se l'esportazione riesce, false altrimenti.
 */
bool esportaResocontoCompleto(const ListaAllievi* listaA,
                              const ListaPagamenti* listaP,
                              const ListaEsami* listaE,
                              const ListaGuide* listaG);

/**
 * @brief Wrapper retrocompatibile per salvaTuttiDati().
 * Mantiene il nome originale della funzione per compatibilità con il codice esistente.
 * @param listaA Puntatore alla lista degli allievi.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaE Puntatore alla lista degli esami.
 * @param listaG Puntatore alla lista delle guide.
 */
void salvaDati(const ListaAllievi* listaA,
               const ListaPagamenti* listaP,
               const ListaEsami* listaE,
               const ListaGuide* listaG);

/**
 * @brief Wrapper retrocompatibile per caricaTuttiDati().
 * Mantiene il nome originale della funzione per compatibilità con il codice esistente.
 * @param listaA Puntatore alla lista degli allievi.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaE Puntatore alla lista degli esami.
 * @param listaG Puntatore alla lista delle guide.
 */
void caricaDati(ListaAllievi* listaA,
                ListaPagamenti* listaP,
                ListaEsami* listaE,
                ListaGuide* listaG);

#endif // FILEIO_H
