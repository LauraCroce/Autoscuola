
🚗 PROGETTO AUTOSCUOLA (C)
Laboratorio di Informatica
Prof. Loglisci
Università degli Studi di Bari


```

# 📘 Descrizione generale

Il **Progetto Autoscuola** è stato realizzato come attività d’esame per il corso di **Laboratorio di Informatica** tenuto dal **Prof. Loglisci** presso l’Università degli Studi di Bari.  
Il software, scritto in linguaggio **C**, consente la gestione completa delle attività di un’autoscuola: dalla registrazione degli allievi, alla pianificazione delle lezioni, fino alla gestione degli esami teorici e pratici.

---

# 🎯 Obiettivi del progetto

Il progetto ha come obiettivo la progettazione e realizzazione di un’applicazione modulare e documentata, che permetta di:

- Gestire gli **allievi** (iscrizioni, dati anagrafici, risultati esami);
- Organizzare gli **esami teorici e pratici**;
- Pianificare e gestire le **lezioni di guida**;
- Visualizzare **report e riepiloghi**;
- Documentare automaticamente il codice sorgente tramite **Doxygen**.

---

# 🧠 Architettura del progetto

```

717847_Autoscuola/
├── 717847_Autoscuola/
│   ├── allievi.c                    # Implementazione delle funzioni sugli allievi
│   ├── allievi.h                    # File header con dichiarazioni
│   ├── 717847_Autoscuola.cbp        # File di progetto Code::Blocks
│   ├── 717847_Autoscuola.layout     # Layout IDE
│   └── ... altri file sorgente (.c / .h)
│
└── doxygen/
├── Doxyfile                     # File di configurazione per Doxygen
├── html/                        # Documentazione HTML generata
└── latex/                       # Documentazione LaTeX/PDF

````

---

# ⚙️ Tecnologie e strumenti utilizzati

| Strumento / Tecnologia | Descrizione |
|------------------------|-------------|
| 💻 **Linguaggio** | C |
| 🧩 **Ambiente di sviluppo** | Code::Blocks |
| 📚 **Documentazione** | Doxygen |
| 🧠 **Sistema operativo di sviluppo** | macOS |
| 🌐 **Controllo di versione** | Git + GitHub |

---

# 🧩 Funzionalità principali

- Gestione e archiviazione dei dati degli allievi  
- Inserimento, modifica e ricerca informazioni  
- Gestione esami teorici e pratici  
- Struttura modulare del codice con separazione `.c` / `.h`  
- Generazione automatica della documentazione con Doxygen  

---

# 📄 Generazione della documentazione

Per rigenerare la documentazione Doxygen:

```bash
doxygen doxygen/Doxyfile
````

Doxygen genererà:

* la documentazione **HTML** in `doxygen/html/` (aprire `index.html` con un browser)
* la documentazione **LaTeX/PDF** in `doxygen/latex/`

---

# 📚 Note finali

Il progetto **Autoscuola** è stato sviluppato a scopo didattico come prova finale del corso di **Laboratorio di Informatica**.
Tutti i file inclusi (sorgenti, configurazioni e documentazione) sono destinati esclusivamente all’attività accademica.
La struttura modulare e l’uso di Doxygen mirano a favorire la chiarezza, la manutenibilità e la qualità del codice.

---

# 🏁 Fine documento

