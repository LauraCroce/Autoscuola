/**
 * @file menu.h
 * @brief Interfaccia menu principale dell'applicazione Autoscuola.
 *
 * Questo modulo espone la funzione che consente di navigare tra le funzionalità principali:
 * - Inserimento e consultazione degli allievi
 * - Gestione dei pagamenti, guide ed esami
 * - Operazioni di controllo integrità dati e salvataggio/esportazione
 *
 * La funzione `mostraMenuPrincipale` richiama in cascata i vari sottomenu.
 * L'interfaccia è interattiva e utilizza input da tastiera per la selezione delle opzioni.
 */
#ifndef MENU_H
#define MENU_H

//FORWARD DECLARATIONS (tipi opachi)
typedef struct ListaAllievi ListaAllievi;
typedef struct ListaPagamenti ListaPagamenti;
typedef struct ListaEsami ListaEsami;
typedef struct ListaGuide ListaGuide;

/**
 * @brief Avvia il menu principale dell'applicazione.
 *
 * Il menu permette la navigazione tra tutte le funzionalità:
 * - Gestione allievi (inserimento, ricerca, filtri, ordinamento)
 * - Gestione pagamenti (rate, riepiloghi)
 * - Gestione esami (registrazione tentativi e date)
 * - Gestione guide (ore svolte e extra)
 * - Controlli difensivi di integrità
 * - Salvataggio e esportazione dati
 *
 * @param listaA Puntatore alla lista degli allievi.
 * @param listaP Puntatore alla lista dei pagamenti.
 * @param listaE Puntatore alla lista degli esami.
 * @param listaG Puntatore alla lista delle guide.
 */
void mostraMenuPrincipale(ListaAllievi* listaA,
                          ListaPagamenti* listaP,
                          ListaEsami* listaE,
                          ListaGuide* listaG);

#endif // MENU_H
