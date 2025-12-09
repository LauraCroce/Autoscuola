/**
 * @file data.h
 * @brief Definizione della struttura Data per la gestione delle date nel progetto Autoscuola.
 *
 * Questo modulo contiene la definizione della struttura `Data`, utilizzata per rappresentare
 * una data (giorno, mese e anno). La struttura viene usata per registrare eventi associati
 * agli allievi, come i tentativi d’esame teorico e pratico.
 *
 * Non include funzioni associate: viene utilizzata come tipo ausiliario in altri moduli
 * (es. `esami.h`, `fileio.h`, ecc.).
 *
 * La struttura è compatibile con serializzazione su file binari e testuale.
 *
 */

#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

/**
 * @struct Data
 * @brief Rappresenta una data nel formato giorno/mese/anno.
 */
typedef struct {
    int giorno; /**< Giorno del mese (1–31) */
    int mese;   /**< Mese (1–12) */
    int anno;   /**< Anno completo (es. 2025) */
} Data;

#endif // DATA_H_INCLUDED
