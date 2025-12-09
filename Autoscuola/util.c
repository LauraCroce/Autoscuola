/**
 * @file util.c
 * @brief Implementazione di funzioni di utilità generiche per input/output e validazioni.
 *
 * Questo modulo contiene funzioni comuni utilizzate in tutto il gestionale Autoscuola:
 * - Gestione sicura dell’input da tastiera (stringhe, interi, float)
 * - Pulizia del buffer e dello schermo
 * - Confronti case-insensitive tra stringhe
 * - Validazione della categoria di patente
 * - Messaggi di conferma
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "util.h"

/**
 * @brief Pulisce il buffer di input per evitare letture errate da tastiera.
 *
 * Consuma tutti i caratteri fino al newline o EOF, utile dopo un `scanf`.
 */
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Acquisisce una stringa in modo sicuro dalla tastiera.
 *
 * Utilizza `fgets` per evitare buffer overflow e rimuove il carattere `\n` finale.
 * Se la stringa è troppo lunga, svuota il buffer residuo.
 *
 * @param buffer Array in cui salvare la stringa.
 * @param maxLen Lunghezza massima del buffer.
 */
void inputString(char* buffer, int maxLen) {
    fgets(buffer, maxLen, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
    else
        clearBuffer();
}

/**
 * @brief Valida la categoria di patente inserita (A, B, AM).
 *
 * Converte in maiuscolo e confronta con le categorie ammesse.
 *
 * @param cat Stringa contenente la categoria.
 * @return 1 se valida, 0 altrimenti.
 */
int validaCategoria(const char* cat) {
    char upper[5];
    for (int i = 0; cat[i] && i < 4; i++) {
        upper[i] = toupper((unsigned char)cat[i]);
        upper[i+1] = '\0';
    }
    return strcmp(upper, "A") == 0 || strcmp(upper, "B") == 0 || strcmp(upper, "AM") == 0;
}

/**
 * @brief Mostra un messaggio di conferma e legge la risposta utente.
 *
 * Accetta risposte tipo "s" o "n" (case insensitive).
 *
 * @param messaggio Il messaggio da visualizzare.
 * @return 1 se la risposta è "s", 0 altrimenti.
 */
int conferma(const char* messaggio) {
    char risposta[4];
    printf("%s (s/n): ", messaggio);
    inputString(risposta, 4);
    return (tolower(risposta[0]) == 's');
}

/**
 * @brief Acquisisce un numero intero da tastiera con messaggio.
 *
 * Ripete l’input finché non viene inserito un valore valido.
 *
 * @param messaggio Messaggio da mostrare all’utente.
 * @return Intero inserito.
 */
int inputInt(const char* messaggio) {
    int val;
    printf("%s", messaggio);
    while (scanf("%d", &val) != 1) {
        printf("Valore non valido. Riprova: ");
        clearBuffer();
    }
    clearBuffer();
    return val;
}

/**
 * @brief Acquisisce un numero float da tastiera con messaggio.
 *
 * Ripete l’input finché non viene inserito un valore valido.
 *
 * @param messaggio Messaggio da mostrare all’utente.
 * @return Float inserito.
 */
float inputFloat(const char* messaggio) {
    float val;
    printf("%s", messaggio);
    while (scanf("%f", &val) != 1) {
        printf("Valore non valido. Riprova: ");
        clearBuffer();
    }
    clearBuffer();
    return val;
}

/**
 * @brief Pulisce lo schermo in modo portabile.
 *
 * Usa `cls` su Windows e `clear` su sistemi Unix.
 */
void pulisciSchermo() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Attende la pressione del tasto INVIO per proseguire.
 *
 * Utile per mettere in pausa tra un menu e l'altro.
 */
void attendiInvio() {
    printf("\nPremi INVIO per continuare...");
    while (getchar() != '\n');
}

/**
 * @brief Confronta due stringhe ignorando le differenze tra maiuscole e minuscole.
 *
 * @param a Prima stringa.
 * @param b Seconda stringa.
 * @return 1 se uguali (ignora case), 0 altrimenti.
 */
int equalsIgnoreCase(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++;
        b++;
    }
    return *a == *b;
}
