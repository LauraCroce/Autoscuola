/**
 * @file difensiva.c
 * @brief Validazione difensiva per elementi del gestionale Autoscuola.
 *
 * Questo modulo implementa funzioni di validazione per verificare:
 * - Correttezza formale dei dati (codice fiscale, importi, ecc.)
 * - Coerenza logica dei valori
 * - Validità dei campi testuali
 *
 * Le funzioni operano su SINGOLI ELEMENTI o valori primitivi,
 * NON sulle rappresentazioni interne degli ADT.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "difensiva.h"

//VALIDAZIONE STRINGHE E FORMATI

bool validaCodiceFiscale(const char* codice_fiscale) {
    if (codice_fiscale == NULL) return false;

    size_t len = strlen(codice_fiscale);
    if (len != 16) return false;

    // Primi 6 caratteri alfabetici (cognome + nome)
    for (int i = 0; i < 6; i++) {
        if (!isalpha(codice_fiscale[i])) return false;
    }

    // Caratteri 7-8: anno (numerici)
    if (!isdigit(codice_fiscale[6]) || !isdigit(codice_fiscale[7])) return false;

    // Carattere 9: mese (alfabetico)
    if (!isalpha(codice_fiscale[8])) return false;

    // Caratteri 10-11: giorno (numerici)
    if (!isdigit(codice_fiscale[9]) || !isdigit(codice_fiscale[10])) return false;

    // Caratteri 12-15: codice comune (alfanumerici)
    for (int i = 11; i < 15; i++) {
        if (!isalnum(codice_fiscale[i])) return false;
    }

    // Carattere 16: carattere di controllo (alfabetico)
    if (!isalpha(codice_fiscale[15])) return false;

    return true;
}

bool validaStato(const char* stato) {
    if (stato == NULL || strlen(stato) == 0) return false;

    // Stati validi: "iscritto", "sospeso"
    return (strcasecmp(stato, "iscritto") == 0 ||
            strcasecmp(stato, "sospeso") == 0);
}

bool stringaNonVuota(const char* str) {
    return (str != NULL && strlen(str) > 0);
}

//VALIDAZIONE VALORI NUMERICI

bool validaImporto(float importo) {
    return (importo >= 0.0);
}

bool validaOre(int ore) {
    return (ore >= 0);
}

bool validaTentativi(int tentativi) {
    return (tentativi >= 0 && tentativi <= 2);
}

bool validaID(int id) {
    return (id > 0);
}

//VALIDAZIONE DATE

bool validaData(int giorno, int mese, int anno) {
    if (mese < 1 || mese > 12) return false;
    if (giorno < 1 || giorno > 31) return false;
    if (anno < 2000 || anno > 2100) return false;

    // Controllo giorni per mese (semplificato)
    if (mese == 2 && giorno > 29) return false;
    if ((mese == 4 || mese == 6 || mese == 9 || mese == 11) && giorno > 30) return false;

    return true;
}

bool dataMinoreDi(int g1, int m1, int a1, int g2, int m2, int a2) {
    if (a1 < a2) return true;
    if (a1 > a2) return false;

    if (m1 < m2) return true;
    if (m1 > m2) return false;

    return (g1 < g2);
}

//VALIDAZIONE LOGICA DI DOMINIO

bool verificaCoerenzaEsame(int tentativi, int superato) {
    // Se nessun tentativo, non può essere superato
    if (tentativi == 0 && superato == 1) return false;

    // Se superato, deve aver fatto almeno un tentativo
    if (superato == 1 && tentativi == 0) return false;

    // Tentativi devono essere validi
    if (tentativi < 0 || tentativi > 2) return false;

    // Superato deve essere 0 o 1
    if (superato != 0 && superato != 1) return false;

    return true;
}

bool verificaCoerenzaOreExtra(int ore_totali, int ore_extra, int soglia) {
    if (ore_totali < 0 || ore_extra < 0) return false;

    if (ore_totali <= soglia) {
        // Se ore totali <= soglia, ore extra devono essere 0
        return (ore_extra == 0);
    } else {
        // Se ore totali > soglia, ore extra devono essere (ore_totali - soglia)
        return (ore_extra == (ore_totali - soglia));
    }
}

bool verificaProgressioneRate(float prima, float seconda, float terza) {
    // Tutte le rate devono essere non negative
    if (prima < 0 || seconda < 0 || terza < 0) return false;

    // Se seconda > 0, allora prima deve essere > 0
    if (seconda > 0 && prima == 0) return false;

    // Se terza > 0, allora seconda deve essere > 0
    if (terza > 0 && seconda == 0) return false;

    return true;
}

bool verificaPrerequisitPratico(int teorico_superato, int ore_guida) {
    return (teorico_superato == 1 && ore_guida >= 6);
}

bool validaTipoRata(int tipo_rata) {
    return (tipo_rata >= 1 && tipo_rata <= 4);
}

//FUNZIONI DI REPORT

void stampaErroreValidazione(const char* campo, const char* valore_str, const char* motivo) {
    printf(" Errore validazione - Campo: %s\n", campo);
    printf("   Valore: '%s'\n", valore_str);
    printf("   Motivo: %s\n", motivo);
    printf("\n");
}

void stampaRiepilogoErrori(int n_errori) {
    printf("\n");
    printf("_______________________________________\n");
    if (n_errori == 0) {
        printf("Validazione completata: NESSUN ERRORE\n");
    } else {
        printf(" Validazione completata: %d ERRORI trovati\n", n_errori);
    }
    printf("_______________________________________\n");
}
