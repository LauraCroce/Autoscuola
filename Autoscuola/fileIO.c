/**
 * @file fileio.c
 * @brief Coordinamento operazioni I/O per la persistenza del sistema Autoscuola.
 *
 * Questo modulo coordina il salvataggio e caricamento di tutti i dati
 * chiamando le funzioni di I/O di ogni ADT e genera report testuali.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "fileio.h"
#include "allievi.h"
#include "pagamenti.h"
#include "esami.h"
#include "guida.h"

//FUNZIONI DI COORDINAMENTO I/O

bool salvaTuttiDati(const ListaAllievi* listaA,
                    const ListaPagamenti* listaP,
                    const ListaEsami* listaE,
                    const ListaGuide* listaG) {
    bool ok = true;

    printf("Salvataggio dati in corso...\n");

    ok &= salvaAllievi(listaA, "allievi.dat");
    ok &= salvaPagamenti(listaP, "pagamenti.dat");
    ok &= salvaEsami(listaE, "esami.dat");
    ok &= salvaGuide(listaG, "guide.dat");

    if (ok) {
        printf("Tutti i dati salvati con successo.\n");
    } else {
        printf("Alcuni dati non sono stati salvati correttamente.\n");
    }

    return ok;
}

bool caricaTuttiDati(ListaAllievi* listaA,
                     ListaPagamenti* listaP,
                     ListaEsami* listaE,
                     ListaGuide* listaG) {
    bool almeno_uno = false;

    printf("Caricamento dati in corso...\n");

    almeno_uno |= caricaAllievi(listaA, "allievi.dat");
    almeno_uno |= caricaPagamenti(listaP, "pagamenti.dat");
    almeno_uno |= caricaEsami(listaE, "esami.dat");
    almeno_uno |= caricaGuide(listaG, "guide.dat");

    if (almeno_uno) {
        printf("Dati caricati con successo.\n");
        // Aggiorna l'ID corrente dopo il caricamento
        aggiornaID(listaA);
    } else {
        printf("Nessun dato precedente trovato. Inizializzazione nuova sessione.\n");
    }

    return almeno_uno;
}

bool esportaResocontoCompleto(const ListaAllievi* listaA,
                              const ListaPagamenti* listaP,
                              const ListaEsami* listaE,
                              const ListaGuide* listaG) {
    if (listaA == NULL) {
        printf("Errore: lista allievi non valida.\n");
        return false;
    }

    FILE* f = fopen("resoconto_allievi.txt", "w");
    if (!f) {
        printf("Errore: impossibile creare il file resoconto_allievi.txt\n");
        return false;
    }

    int n_allievi = getNumeroAllievi(listaA);

    fprintf(f, "______________________________________________________________\n");
    fprintf(f, "|     RESOCONTO COMPLETO ALLIEVI AUTOSCUOLA                  |\n");
    fprintf(f, "______________________________________________________________\n\n");
    fprintf(f, "Totale allievi: %d\n\n", n_allievi);

    // Nota: Per ordinare alfabeticamente servirebbe una funzione nell'ADT
    // Per ora iteriamo in ordine di inserimento

    for (int i = 0; i < n_allievi; i++) {
        const Allievo* a = getAllievoAtIndex(listaA, i);
        if (a == NULL) continue;

        int id = getAllievoID(a);
        const char* nome = getAllievoNome(a);
        const char* cognome = getAllievoCognome(a);
        const char* cf = getAllievoCodiceFiscale(a);
        const char* patente = getAllievoCategoriaPatente(a);
        const char* stato = getAllievoStato(a);

        fprintf(f, "___________________________________________________________\n");
        fprintf(f, "| ID: %d\n", id);
        fprintf(f, "| Nome: %s %s\n", nome, cognome);
        fprintf(f, "| Codice Fiscale: %s\n", cf);
        fprintf(f, "| Patente: %s\n", patente);
        fprintf(f, "| Stato: %s\n", stato);
        fprintf(f, "___________________________________________________________\n");

        // --- PAGAMENTI ---
        fprintf(f, "\n[PAGAMENTI]\n");
        Pagamento* p = cercaPagamentoPerID(listaP, id);
        if (p != NULL) {
            float prima = getPrimaRata(p);
            float seconda = getSecondaRata(p);
            float terza = getTerzaRata(p);
            float extra_base = getExtra(p);
            float totale_rate = prima + seconda + terza;

            // Calcola costo ore extra
            float costo_ore_extra = 0.0;
            int ore_extra = 0;
            if (listaG != NULL) {
                Guida* g = cercaGuidaPerID(listaG, id);
                if (g != NULL) {
                    ore_extra = getOreExtra(g);
                    costo_ore_extra = calcolaCostoOreExtra(g, 15.0);
                }
            }

            float totale_complessivo = totale_rate + extra_base + costo_ore_extra;

            fprintf(f, "  Prima rata:      %.2f €\n", prima);
            fprintf(f, "  Seconda rata:    %.2f €\n", seconda);
            fprintf(f, "  Terza rata:      %.2f €\n", terza);
            fprintf(f, "  Extra generici:  %.2f €\n", extra_base);
            fprintf(f, "  Extra guide (%d ore x 15€): %.2f €\n", ore_extra, costo_ore_extra);
            fprintf(f, "  ─────────────────────────\n");
            fprintf(f, "  TOTALE PAGATO:   %.2f €\n", totale_complessivo);

            if (totale_rate >= 750.0) {
                fprintf(f, "  Rate principali complete\n");
            } else {
                fprintf(f, "  Mancano %.2f € sulle rate\n", 750.0 - totale_rate);
            }
        } else {
            fprintf(f, "  Nessun pagamento registrato.\n");
        }

        // --- ESAMI ---
        fprintf(f, "\n[ESAMI]\n");
        Esame* e = cercaEsamePerID(listaE, id);
        if (e != NULL) {
            int tent_teorico = getTentativiTeorico(e);
            int tent_pratico = getTentativiPratico(e);
            bool superato_teorico = isTeoricoSuperato(e);
            bool superato_pratico = isPraticoSuperato(e);

            fprintf(f, "  Teorico: %d tentativi - %s\n",
                    tent_teorico, superato_teorico ? "Superato" : "Non superato");

            for (int t = 0; t < tent_teorico; t++) {
                Data d;
                if (getDataTeorico(e, t, &d) && d.giorno != 0) {
                    fprintf(f, "    - Tentativo %d: %02d/%02d/%04d\n",
                            t + 1, d.giorno, d.mese, d.anno);
                }
            }

            fprintf(f, "  Pratico: %d tentativi - %s\n",
                    tent_pratico, superato_pratico ? "Superato" : "Non superato");

            for (int t = 0; t < tent_pratico; t++) {
                Data d;
                if (getDataPratico(e, t, &d) && d.giorno != 0) {
                    fprintf(f, "    - Tentativo %d: %02d/%02d/%04d\n",
                            t + 1, d.giorno, d.mese, d.anno);
                }
            }
        } else {
            fprintf(f, "  Nessun esame registrato.\n");
        }

        // --- GUIDE ---
        fprintf(f, "\n[GUIDE]\n");
        Guida* g = cercaGuidaPerID(listaG, id);
        if (g != NULL) {
            int ore_svolte = getOreSvolte(g);
            int ore_extra = getOreExtra(g);

            fprintf(f, "  Ore svolte:      %d\n", ore_svolte);
            fprintf(f, "  Ore extra:       %d\n", ore_extra);

            if (haCompletateOreObbligatorie(g)) {
                fprintf(f, "  Ore obbligatorie completate\n");
            } else {
                fprintf(f, "  Mancano %d ore obbligatorie\n", 6 - ore_svolte);
            }
        } else {
            fprintf(f, "  Nessuna guida registrata.\n");
        }

        // --- IDONEITÀ FINALE ---
        fprintf(f, "\n[ESITO FINALE]\n");

        bool teorico_ok = false;
        bool pratico_ok = false;
        bool pagamenti_ok = false;
        bool guide_ok = false;

        if (e != NULL) {
            teorico_ok = isTeoricoSuperato(e);
            pratico_ok = isPraticoSuperato(e);
        }

        if (p != NULL) {
            float totale_rate = getPrimaRata(p) + getSecondaRata(p) + getTerzaRata(p);
            pagamenti_ok = (totale_rate >= 750.0);
        }

        if (g != NULL) {
            guide_ok = haCompletateOreObbligatorie(g);
        }

        bool idoneo = teorico_ok && pratico_ok && pagamenti_ok && guide_ok;

        fprintf(f, "  Esame teorico:   %s\n", teorico_ok ? "Superato" : "Non superato");
        fprintf(f, "  Esame pratico:   %s\n", pratico_ok ? "Superato" : "Non superatO");
        fprintf(f, "  Pagamenti:       %s\n", pagamenti_ok ? "Completo" : "Non completo");
        fprintf(f, "  Guide (6+ ore):  %s\n", guide_ok ? "Completo" : "Non completo");
        fprintf(f, "  ─────────────────────────\n");
        fprintf(f, "  -> %s\n", idoneo ? "IDONEO " : "NON IDONEO");

        fprintf(f, "\n___________________________________________________________\n\n");
    }

    fclose(f);
    printf("Resoconto esportato in 'resoconto_allievi.txt'\n");
    return true;
}

// WRAPPER RETROCOMPATIBILI

void salvaDati(const ListaAllievi* listaA,
               const ListaPagamenti* listaP,
               const ListaEsami* listaE,
               const ListaGuide* listaG) {
    salvaTuttiDati(listaA, listaP, listaE, listaG);
}

void caricaDati(ListaAllievi* listaA,
                ListaPagamenti* listaP,
                ListaEsami* listaE,
                ListaGuide* listaG) {
    caricaTuttiDati(listaA, listaP, listaE, listaG);
}
