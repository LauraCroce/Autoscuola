/**
 * @file menu.c
 * @brief Implementazione del menu principale e dei sottomenu per il gestionale autoscuola.
 *
 * Questo modulo gestisce l'interfaccia testuale dell'applicazione, organizzando
 * i flussi operativi in menu tematici.
 */

#include <stdio.h>
#include "menu.h"
#include "allievi.h"
#include "pagamenti.h"
#include "esami.h"
#include "guida.h"
#include "fileio.h"
#include "difensiva.h"
#include "util.h"

/**
 * @brief Mostra il menu principale e gestisce la navigazione nei sottomenu.
 *
 * Il menu consente di:
 * - Gestire gli allievi (inserimento, visualizzazione, filtri)
 * - Gestire i pagamenti (rate ed extra)
 * - Registrare e visualizzare esami
 * - Registrare e visualizzare guide
 * - Eseguire controlli di integrità (difensiva)
 * - Esportare un resoconto completo su file `.txt`
 * - Salvare tutti i dati in file `.dat`
 *
 * @param listaA Puntatore alla lista degli allievi
 * @param listaP Puntatore alla lista dei pagamenti
 * @param listaE Puntatore alla lista degli esami
 * @param listaG Puntatore alla lista delle guide
 */
void mostraMenuPrincipale(ListaAllievi* listaA, ListaPagamenti* listaP, ListaEsami* listaE, ListaGuide* listaG) {
    int scelta;
    do {
        pulisciSchermo();
        printf("\n_____________________________________\n");
        printf("|    MENU AUTOSCUOLA - GESTIONALE    |\n");
        printf("_______________________________________\n");
        printf("\n1. Gestione Allievi");
        printf("\n2. Gestione Pagamenti");
        printf("\n3. Gestione Esami");
        printf("\n4. Gestione Guide");
        printf("\n5. Controllo integrita' dati");
        printf("\n6. Esporta resoconto completo");
        printf("\n7. Salva");
        printf("\n0. Esci e salva\n");
        scelta = inputInt("\n Scelta: ");

        switch (scelta) {
            case 1: { // MENU ALLIEVI
                int sotto;
                do {
                    pulisciSchermo();
                    printf("\n------------------------\n");
                    printf("|    MENU ALLIEVI       |\n");
                    printf("------------------------\n");
                    printf("\n1. Inserisci nuovo allievo\n");
                    printf("2. Visualizza allievi\n");
                    printf("3. Cerca allievo\n");
                    printf("4. Filtra per patente\n");
                    printf("5. Filtra per stato\n");
                    printf("0. Torna indietro\n");
                    sotto = inputInt("\n Scelta: ");

                    switch (sotto) {
                        case 1:
                            inserisciAllievo(listaA, listaP, listaE);
                            break;
                        case 2:
                            stampaAllievi(listaA);
                            break;
                        case 3:
                            cercaAllievo(listaA, listaP, listaE);
                            break;
                        case 4:
                            filtraPerPatente(listaA);
                            break;
                        case 5:
                            filtraPerStato(listaA);
                            break;
                        case 0:
                            break;
                        default:
                            printf(" Scelta non valida.\n");
                    }
                    if (sotto != 0) attendiInvio();
                } while (sotto != 0);
                break;
            }

            case 2: { // MENU PAGAMENTI
                int sotto;
                do {
                    pulisciSchermo();
                    printf("\n------------------------\n");
                    printf("|     MENU PAGAMENTI     |\n");
                    printf("------------------------\n");
                    printf("\n1. Inserisci pagamento\n");
                    printf("2. Visualizza pagamento per allievo\n");
                    printf("3. Riepilogo pagamenti di tutti gli allievi\n");
                    printf("0. Torna indietro\n");
                    sotto = inputInt("\n Scelta: ");

                    switch (sotto) {
                        case 1:
                            inserisciPagamento(listaP, listaA);
                            break;
                        case 2:
                            stampaStatoPagamento(listaP, listaA);
                            break;
                        case 3:
                            riepilogoPagamenti(listaP, listaA, listaG);
                            break;
                        case 0:
                            break;
                        default:
                            printf(" Scelta non valida.\n");
                    }
                    if (sotto != 0) attendiInvio();
                } while (sotto != 0);
                break;
            }

            case 3: { // MENU ESAMI
                int sotto;
                do {
                    pulisciSchermo();
                    printf("\n------------------------\n");
                    printf("|    MENU ESAMI         |\n");
                    printf("------------------------\n");
                    printf("\n1. Registra tentativo teorico\n");
                    printf("2. Registra tentativo pratico\n");
                    printf("3. Visualizza stato esami\n");
                    printf("0. Torna indietro\n");
                    sotto = inputInt("\n Scelta: ");

                    switch (sotto) {
                        case 1: {
                            char nome[30], cognome[30];
                            printf("Nome allievo: ");
                            inputString(nome, 30);
                            printf("Cognome allievo: ");
                            inputString(cognome, 30);

                            int id = trovaIDAllievo(listaA, nome, cognome);
                            if (id == -1) {
                                printf(" Allievo non trovato.\n");
                                break;
                            }

                            int esito = inputInt("Esito (1=superato, 0=non superato): ");
                            registraTentativoTeorico(listaE, id, esito, listaA, listaP);
                            break;
                        }
                        case 2: {
                            char nome[30], cognome[30];
                            printf("Nome allievo: ");
                            inputString(nome, 30);
                            printf("Cognome allievo: ");
                            inputString(cognome, 30);

                            int id = trovaIDAllievo(listaA, nome, cognome);
                            if (id == -1) {
                                printf(" Allievo non trovato.\n");
                                break;
                            }

                            int esito = inputInt("Esito (1=superato, 0=non superato): ");
                            registraTentativoPratico(listaE, id, esito, listaP, listaG);
                            break;
                        }
                        case 3:
                            stampaEsame(listaE, listaA);
                            break;
                        case 0:
                            break;
                        default:
                            printf(" Scelta non valida.\n");
                    }
                    if (sotto != 0) attendiInvio();
                } while (sotto != 0);
                break;
            }

            case 4: { // MENU GUIDE
                int sotto;
                do {
                    pulisciSchermo();
                    printf("\n------------------------\n");
                    printf("|    MENU GUIDE         |\n");
                    printf("------------------------\n");
                    printf("\n1. Registra guida\n");
                    printf("2. Visualizza ore guida\n");
                    printf("0. Torna indietro\n");
                    sotto = inputInt("\n Scelta: ");

                    switch (sotto) {
                        case 1:
                            registraGuida(listaG, listaA);
                            break;
                        case 2:
                            stampaGuide(listaG, listaA);
                            break;
                        case 0:
                            break;
                        default:
                            printf(" Scelta non valida.\n");
                    }
                    if (sotto != 0) attendiInvio();
                } while (sotto != 0);
                break;
            }

            case 5: { // CONTROLLO INTEGRITÀ
                pulisciSchermo();
                printf("\n------------------------------------\n");
                printf("      CONTROLLO INTEGRITA' DATI     \n");
                printf("--------------------------------------\n\n");

                printf("Esecuzione controlli di validazione...\n\n");

                int errori_totali = 0;
                int errori_modulo = 0;

                // Validazione Allievi
                printf("---- VALIDAZIONE ALLIEVI ----\n");
                int n_allievi = getNumeroAllievi(listaA);
                for (int i = 0; i < n_allievi; i++) {
                    const Allievo* a = getAllievoAtIndex(listaA, i);
                    if (a == NULL) continue;

                    if (!stringaNonVuota(getAllievoNome(a))) {
                        printf(" Allievo ID %d: nome vuoto\n", getAllievoID(a));
                        errori_modulo++;
                    }
                    if (!validaCodiceFiscale(getAllievoCodiceFiscale(a))) {
                        printf(" Allievo ID %d: codice fiscale non valido\n", getAllievoID(a));
                        errori_modulo++;
                    }
                }
                printf("Errori trovati: %d\n\n", errori_modulo);
                errori_totali += errori_modulo;
                errori_modulo = 0;

                // Validazione Pagamenti
                printf("---- VALIDAZIONE PAGAMENTI ----\n");
                int n_pagamenti = getNumeroPagamenti(listaP);
                for (int i = 0; i < n_pagamenti; i++) {
                    const Pagamento* p = getPagamentoAtIndex(listaP, i);
                    if (p == NULL) continue;

                    if (!validaImporto(getPrimaRata(p)) ||
                        !validaImporto(getSecondaRata(p)) ||
                        !validaImporto(getTerzaRata(p))) {
                        printf(" Pagamento ID allievo %d: importi negativi\n",
                               getPagamentoIDAllievo(p));
                        errori_modulo++;
                    }

                    if (!verificaProgressioneRate(getPrimaRata(p), getSecondaRata(p), getTerzaRata(p))) {
                        printf("Pagamento ID allievo %d: progressione rate non valida\n",
                               getPagamentoIDAllievo(p));
                        errori_modulo++;
                    }
                }
                printf("Errori trovati: %d\n\n", errori_modulo);
                errori_totali += errori_modulo;
                errori_modulo = 0;

                // Validazione Esami
                printf("---- VALIDAZIONE ESAMI ----\n");
                int n_esami = getNumeroEsami(listaE);
                for (int i = 0; i < n_esami; i++) {
                    const Esame* e = getEsameAtIndex(listaE, i);
                    if (e == NULL) continue;

                    if (!validaTentativi(getTentativiTeorico(e)) ||
                        !validaTentativi(getTentativiPratico(e))) {
                        printf(" Esame ID allievo %d: numero tentativi non valido\n",
                               getEsameIDAllievo(e));
                        errori_modulo++;
                    }

                    if (!verificaCoerenzaEsame(getTentativiTeorico(e), isTeoricoSuperato(e) ? 1 : 0)) {
                        printf(" Esame ID allievo %d: incoerenza teorico\n",
                               getEsameIDAllievo(e));
                        errori_modulo++;
                    }
                }
                printf("Errori trovati: %d\n\n", errori_modulo);
                errori_totali += errori_modulo;
                errori_modulo = 0;

                // Validazione Guide
                printf("---- VALIDAZIONE GUIDE ----\n");
                int n_guide = getNumeroGuide(listaG);
                for (int i = 0; i < n_guide; i++) {
                    const Guida* g = getGuidaAtIndex(listaG, i);
                    if (g == NULL) continue;

                    if (!validaOre(getOreSvolte(g)) || !validaOre(getOreExtra(g))) {
                        printf(" Guida ID allievo %d: ore negative\n",
                               getGuidaIDAllievo(g));
                        errori_modulo++;
                    }

                    if (!verificaCoerenzaOreExtra(getOreSvolte(g), getOreExtra(g), 6)) {
                        printf(" Guida ID allievo %d: incoerenza ore extra\n",
                               getGuidaIDAllievo(g));
                        errori_modulo++;
                    }
                }
                printf("Errori trovati: %d\n\n", errori_modulo);
                errori_totali += errori_modulo;

                // Riepilogo finale
                stampaRiepilogoErrori(errori_totali);

                attendiInvio();
                break;
            }

            case 6: // ESPORTA RESOCONTO
                printf("\n Esportazione resoconto in corso...\n");
                esportaResocontoCompleto(listaA, listaP, listaE, listaG);
                attendiInvio();
                break;

            case 7: // SALVA
                printf("\n Salvataggio dati in corso...\n");
                salvaDati(listaA, listaP, listaE, listaG);
                attendiInvio();
                break;

            case 0: // ESCI
                printf("\n Salvataggio finale...\n");
                salvaDati(listaA, listaP, listaE, listaG);
                printf("\n Arrivederci!\n");
                break;

            default:
                printf("\n Scelta non valida.\n");
                attendiInvio();
        }
    } while (scelta != 0);
}
