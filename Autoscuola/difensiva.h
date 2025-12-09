/**
 * @file difensiva.h
 * @brief Validazione difensiva per elementi del gestionale Autoscuola.
 *
 * Questo modulo fornisce funzioni di validazione per verificare:
 * - Correttezza formale dei dati (es. codice fiscale, importi)
 * - Coerenza logica dei valori (es. tentativi, ore)
 * - Validità dei campi testuali
 *
 * Le funzioni operano su SINGOLI ELEMENTI o valori primitivi,
 * NON sulle rappresentazioni interne degli ADT.
 *
 * Ogni funzione restituisce true se la validazione ha successo, false altrimenti.
 */
#ifndef DIFENSIVA_H
#define DIFENSIVA_H

#include <stdbool.h>

//VALIDAZIONE STRINGHE E FORMATI

/**
 * @brief Valida il formato di un codice fiscale italiano.
 *
 * Verifica:
 * - Lunghezza esatta 16 caratteri
 * - Primi 6 caratteri alfabetici
 * - Caratteri 7-8 numerici (anno)
 * - Carattere 9 alfabetico (mese)
 * - Caratteri 10-11 numerici (giorno)
 * - Caratteri 12-15 alfanumerici
 * - Carattere 16 alfabetico (check)
 *
 * @param codice_fiscale Stringa da validare (16 caratteri).
 * @return true se valido, false altrimenti.
 */
bool validaCodiceFiscale(const char* codice_fiscale);

/**
 * @brief Valida uno stato allievo.
 * @param stato Stato da validare (es. "iscritto", "sospeso").
 * @return true se valido, false altrimenti.
 */
bool validaStato(const char* stato);

/**
 * @brief Verifica che una stringa non sia vuota o NULL.
 * @param str Stringa da verificare.
 * @return true se valida (non vuota e non NULL), false altrimenti.
 */
bool stringaNonVuota(const char* str);

//VALIDAZIONE VALORI NUMERICI

/**
 * @brief Valida un importo (deve essere >= 0).
 * @param importo Importo da validare.
 * @return true se >= 0, false altrimenti.
 */
bool validaImporto(float importo);

/**
 * @brief Valida un numero di ore (deve essere >= 0).
 * @param ore Ore da validare.
 * @return true se >= 0, false altrimenti.
 */
bool validaOre(int ore);

/**
 * @brief Valida un numero di tentativi (deve essere 0, 1 o 2).
 * @param tentativi Numero da validare.
 * @return true se tra 0 e 2, false altrimenti.
 */
bool validaTentativi(int tentativi);

/**
 * @brief Valida un ID (deve essere > 0).
 * @param id ID da validare.
 * @return true se > 0, false altrimenti.
 */
bool validaID(int id);

//VALIDAZIONE DATE

/**
 * @brief Valida una data (giorno, mese, anno).
 *
 * Verifica:
 * - Mese tra 1 e 12
 * - Giorno tra 1 e 31 (controllo semplificato)
 * - Anno >= 2000 e <= 2100
 *
 * @param giorno Giorno (1-31).
 * @param mese Mese (1-12).
 * @param anno Anno (es. >= 2000).
 * @return true se data valida, false altrimenti.
 */
bool validaData(int giorno, int mese, int anno);

/**
 * @brief Verifica se una data è nel futuro rispetto a un'altra.
 * @param g1 Giorno prima data.
 * @param m1 Mese prima data.
 * @param a1 Anno prima data.
 * @param g2 Giorno seconda data.
 * @param m2 Mese seconda data.
 * @param a2 Anno seconda data.
 * @return true se data1 < data2, false altrimenti.
 */
bool dataMinoreDi(int g1, int m1, int a1, int g2, int m2, int a2);

//VALIDAZIONE LOGICA DI DOMINIO

/**
 * @brief Verifica coerenza tra tentativi ed esito esame.
 *
 * Regole:
 * - Se tentativi == 0 -> superato deve essere 0
 * - Se superato == 1 -> tentativi deve essere > 0
 * - Se tentativi >= 2 e superato == 0 -> coerente (bocciato dopo 2 tentativi)
 *
 * @param tentativi Numero di tentativi effettuati (0-2).
 * @param superato Flag di superamento (0 o 1).
 * @return true se coerente, false altrimenti.
 */
bool verificaCoerenzaEsame(int tentativi, int superato);

/**
 * @brief Verifica se le ore extra sono calcolate correttamente.
 *
 * Regole:
 * - Se ore_totali <= soglia -> ore_extra deve essere 0
 * - Se ore_totali > soglia -> ore_extra deve essere (ore_totali - soglia)
 *
 * @param ore_totali Ore totali svolte.
 * @param ore_extra Ore extra registrate.
 * @param soglia Soglia obbligatoria (es. 6).
 * @return true se coerente, false altrimenti.
 */
bool verificaCoerenzaOreExtra(int ore_totali, int ore_extra, int soglia);

/**
 * @brief Verifica se le rate sono progressive o nulle.
 *
 * Regole:
 * - Ogni rata può essere 0 (non pagata) o > 0
 * - Se seconda > 0, allora prima > 0
 * - Se terza > 0, allora seconda > 0
 *
 * @param prima Prima rata.
 * @param seconda Seconda rata.
 * @param terza Terza rata.
 * @return true se progressive, false altrimenti.
 */
bool verificaProgressioneRate(float prima, float seconda, float terza);

/**
 * @brief Verifica che un allievo possa sostenere l'esame pratico.
 *
 * Prerequisiti:
 * - Esame teorico superato
 * - Almeno 6 ore di guida svolte
 *
 * @param teorico_superato Flag teorico (1 se superato).
 * @param ore_guida Ore di guida svolte.
 * @return true se può sostenere l'esame, false altrimenti.
 */
bool verificaPrerequisitPratico(int teorico_superato, int ore_guida);

/**
 * @brief Verifica che un tipo di rata sia valido.
 * @param tipo_rata Tipo (1=prima, 2=seconda, 3=terza, 4=extra).
 * @return true se valido, false altrimenti.
 */
bool validaTipoRata(int tipo_rata);

//FUNZIONI DI REPORT

/**
 * @brief Stampa un messaggio di errore formattato.
 * @param campo Nome del campo con errore.
 * @param valore_str Valore errato (come stringa).
 * @param motivo Motivo dell'errore.
 */
void stampaErroreValidazione(const char* campo, const char* valore_str, const char* motivo);

/**
 * @brief Conta e stampa un riepilogo degli errori di validazione.
 * @param n_errori Numero totale di errori trovati.
 */
void stampaRiepilogoErrori(int n_errori);

#endif // DIFENSIVA_H
