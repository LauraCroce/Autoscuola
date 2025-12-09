/**
 * @file main.c
 * @brief Punto di ingresso dell'applicazione gestionale per autoscuola.
 *
 * Questo file contiene la funzione `main()` che gestisce il flusso principale
 * del programma: inizializzazione delle strutture dati, caricamento da file,
 * ordinamento degli allievi, visualizzazione del menu principale, e salvataggio
 * dei dati prima dell'uscita.
 *
 * Il sistema consente la gestione integrata di:
 * - Allievi (iscrizione, visualizzazione, ricerca, filtri)
 * - Pagamenti (rate, extra, controllo stato)
 * - Esami (teorico e pratico, con limite tentativi e vincoli)
 * - Guide (registrazione ore, calcolo ore extra)
 * - Salvataggio/caricamento automatico da file `.dat`
 */

#include <stdio.h>
#include <stdlib.h>
#include "allievi.h"
#include "pagamenti.h"
#include "esami.h"
#include "guida.h"
#include "fileio.h"
#include "menu.h"

/**
 * @brief Funzione principale che avvia il gestionale autoscuola.
 *
 * - Crea e inizializza tutte le strutture dati (allocazione dinamica).
 * - Carica i dati da file binari salvati in precedenza.
 * - Ordina alfabeticamente gli allievi e aggiorna l'ID corrente.
 * - Avvia il menu principale per la gestione interattiva.
 * - Salva automaticamente i dati prima della chiusura.
 * - Libera la memoria allocata.
 *
 * @return 0 in caso di esecuzione corretta, 1 in caso di errore.
 */
int main() {
    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("|                                                        |\n");
    printf("|         GESTIONALE AUTOSCUOLA - Versione 2.0           |\n");
    printf("|                                                        |\n");
    printf("----------------------------------------------------------\n");
    printf("\n");
    printf("Inizializzazione in corso...\n\n");

    //CREAZIONE STRUTTURE DATI
    ListaAllievi* listaAllievi = creaListaAllievi();
    ListaPagamenti* listaPagamenti = creaListaPagamenti();
    ListaEsami* listaEsami = creaListaEsami();
    ListaGuide* listaGuide = creaListaGuide();

    // Verifica allocazione
    if (listaAllievi == NULL || listaPagamenti == NULL ||
        listaEsami == NULL || listaGuide == NULL) {
        printf("Errore critico: impossibile allocare memoria.\n");

        // Libera eventuali risorse già allocate
        if (listaAllievi != NULL) distruggiListaAllievi(&listaAllievi);
        if (listaPagamenti != NULL) distruggiListaPagamenti(&listaPagamenti);
        if (listaEsami != NULL) distruggiListaEsami(&listaEsami);
        if (listaGuide != NULL) distruggiListaGuide(&listaGuide);

        return 1;
    }

    //INIZIALIZZAZIONE LISTE
    inizializzaLista(listaAllievi);
    inizializzaListaPagamenti(listaPagamenti);
    inizializzaListaEsami(listaEsami);
    inizializzaListaGuide(listaGuide);

    printf(" Strutture dati inizializzate\n");

    //CARICAMENTO DATI DA FILE
    printf("\nCaricamento dati salvati...\n");
    caricaDati(listaAllievi, listaPagamenti, listaEsami, listaGuide);

    //ORDINAMENTO E AGGIORNAMENTO ID
    ordinaAllieviAlfabetico(listaAllievi);
    aggiornaID(listaAllievi);

    int n_allievi = getNumeroAllievi(listaAllievi);
    int n_pagamenti = getNumeroPagamenti(listaPagamenti);
    int n_esami = getNumeroEsami(listaEsami);
    int n_guide = getNumeroGuide(listaGuide);

    printf("\n   Statistiche sistema:\n");
    printf("     Allievi registrati:  %d\n", n_allievi);
    printf("     Pagamenti attivi:    %d\n", n_pagamenti);
    printf("     Esami in corso:      %d\n", n_esami);
    printf("     Guide registrate:    %d\n", n_guide);
    printf("\n Sistema pronto!\n");
    printf("\nPremi INVIO per continuare...");
    getchar();

    //MENU PRINCIPALE
    mostraMenuPrincipale(listaAllievi, listaPagamenti, listaEsami, listaGuide);

    //SALVATAGGIO FINALE
    printf("\n Salvataggio finale dei dati...\n");
    salvaDati(listaAllievi, listaPagamenti, listaEsami, listaGuide);

    //PULIZIA MEMORIA
    printf("Pulizia memoria...\n");
    distruggiListaAllievi(&listaAllievi);
    distruggiListaPagamenti(&listaPagamenti);
    distruggiListaEsami(&listaEsami);
    distruggiListaGuide(&listaGuide);

    printf("\n");
    printf("----------------------------------------------------------\n");
    printf("|                                                        |\n");
    printf("|              Grazie per aver usato il                  |\n");
    printf("|            GESTIONALE AUTOSCUOLA v2.0                  |\n");
    printf("|                                                        |\n");
    printf("|                   Arrivederci!                         |\n");
    printf("|                                                        |\n");
    printf("----------------------------------------------------------\n");
    printf("\n");

    return 0;
}
