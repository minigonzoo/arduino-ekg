# arduino-ekg

Das hier ist ein Python Code, womit ihr mit einem Arduino/ESP32/was auch immer und einem
EKG Modul die Werte auslesen könnt. Diese werden dann anschaulich gemacht. 

Der Port muss COM6 sein!!!

Getestet habe ich das mit dem Arduino Uno und diesem Modul:
https://www.amazon.de/dp/B0D8Q85P2M?ref=ppx_yo2ov_dt_b_fed_asin_title

## <span style="color: blue; font-weight: bold;">Windows-Sicherheit</span>

Dadurch, dass ich kein Code Signing Zertifikat dafür kaufen werde, werdet ihr beim Ausführen die Mitteilung bekommen, dass euer Computer von Windows geschützt wurde.
### <span style="color: blue; font-weight: bold;">Trotzdem ausführen</span>

Beim Start kommt:
- „Der Computer wurde durch Windows geschützt“

- Klick auf „Weitere Informationen“

- Dann auf „Trotzdem ausführen“


## <span style="color: blue; font-weight: bold;">COM-Port</span>

- Der COM-Port ist im Code als COM6 deklariert. Prüfe, welcher deiner USB Schnittstellen COM6 ist (Meistens Frontplate USB Anschlüsse, das siehst du aber in Arduino oder im Geräte-Manager)

# EKG-Visualisierungsprogramm

Dieses Python-Programm visualisiert EKG-Daten, die über einen Arduino (via COM-Port) übertragen werden. Es bietet Funktionen zur Patienteneingabe, Rhythmusanalyse, akustischen/visuellen Warnungen und Speicherung von Aufnahmen als PNG-Dateien.

## <span style="color: blue; font-weight: bold;">Funktionen</span>

### <span style="color: blue; font-weight: bold;">Datenübertragung</span>
- EKG-Daten werden über einen COM-Port (`COM6`) vom Arduino an das Python-Programm übertragen.
- Die empfangenen numerischen Werte werden in ein EKG-Diagramm umgewandelt und in Echtzeit auf dem Bildschirm angezeigt.

### <span style="color: blue; font-weight: bold;">Patienteneingabe</span>
- Beim Programmstart können folgende Patientendaten eingegeben werden:
  - **Name**: Freitext für den Patientennamen.
  - **Geburtsdatum**: Format `TT.MM.JJJJ` (z. B. `10.08.2009`), berechnet das Alter (z. B. 15 Jahre am 02.05.2025).
  - **Geschlecht**: `M` (männlich), `W` (weiblich), `D` (divers), case-insensitive. Standard: `-` (keine Angabe).

### <span style="color: blue; font-weight: bold;">Herzschlag-Sound</span>
- Ein Piepton (`beep.wav`) erklingt bei jedem erkannten Herzschlag (Peak).
- Die `beep.wav`-Datei muss im Skriptverzeichnis liegen. Ersetzbar durch eine andere WAV-Datei (Dateiname muss `beep.wav` bleiben).
- **Beep-Toggle**: Button oben rechts (`Beep: ON`/`Beep: OFF`) aktiviert/deaktiviert den Piepton. Farbe: Weiß (`255, 255, 255`) bei `ON`, Grau (`100, 100, 100`) bei `OFF`.

### <span style="color: blue; font-weight: bold;">Rhythmusanalyse</span>
- Analysiert den Herzrhythmus in Echtzeit und zeigt ihn im Overlay an:
  - **Sinusrythmus**: Regelmäßiger Rhythmus (initialer Zustand).
  - **Asystolie**: Keine Peaks für >3 Sekunden.
  - **Bradycardie**: Herzfrequenz <40 BPM.
  - **Tachycardie**: Herzfrequenz >120 BPM.
- **Vorhofflimmern**: Entfernt, da 50 Hz-Wechselstromrauschen falsch als Vorhofflimmern erkannt werden kann.

### <span style="color: blue; font-weight: bold;">Warnsystem</span>
- **Visuelle Warnung**: Bei Rhythmusänderung (z. B. „WARNUNG: Asystolie“) blinkt eine rote Meldung im Overlay (Position: `(900, 50)`).
- **Akustische Warnung**: 
  - Bei Bradycardie/Tachycardie: Dreimaliger 1000-Hz-Warnton.
  - Bei Asystolie: Durchgehender 1000-Hz-Ton (60 Sekunden, stoppt bei Peak oder „Beep: OFF“).

### <span style="color: blue; font-weight: bold;">Aufnahmefunktion</span>
- **Start/Stopp**: Button „Starte Aufnahme“/„Stoppe Aufnahme“ (Position: `(10, 320)`).
- **Funktion**: Zeichnet EKG-Durchläufe (von links nach rechts) auf.
- **Speicherung**:
  - Nach drei Durchläufen wird ein PNG als `ekg_PATIENTENNAME_ANZAHL.png` (z. B. `ekg_Max_Mustermann_0.png`) im Skriptverzeichnis gespeichert.
  - Enthält: „Patient: [Name], Geschlecht: [M/W/D/-], Geb.: TT.MM.JJJJ ([Alter]), Aufnahme: TT.MM.JJJJ HH:MM:SS“.
  - Bei vorzeitigem Stopp werden die bisherigen Durchläufe ebenfalls als PNG gespeichert.
- **Patientenname**: Leerzeichen werden durch Unterstriche ersetzt (z. B. „Max Mustermann“ → `ekg_Max_Mustermann_0.png`).

## <span style="color: blue; font-weight: bold;">Voraussetzungen</span>
- Python-Pakete: `pygame`, `pyserial`, `numpy` (`pip install pygame pyserial numpy`).
- `beep.wav`-Datei im Skriptverzeichnis.
- Arduino mit passendem Code für EKG-Datenübertragung. (Mein Code ist beigelegt.)
- Der Port muss COM6 sein!!!.

## <span style="color: blue; font-weight: bold;">Hinweise</span>
- **Simulierte Daten**: Falls kein Arduino verbunden ist, generiert das Programm simulierte EKG-Daten (~80 BPM).
- **Konsolenausgaben**: Nur für Initialisierung (beep.wav, COM-Port) und Patienteneingaben (Name, Geburtsdatum, Geschlecht, Alter, Fehler). Keine Debugging-Ausgaben.
- **Performance**: Optimiert für Echtzeit (~16 ms pro Frame, 60 FPS).


Bei Fragen sehr gerne per Discord melden:: bysxmi
Bitte nach einer FA direkt eine Nachricht schicken, damit ich es zuordnen kann.
Viel Spaß damit

Sami




## <span style="color: blue; font-weight: bold;">To-Do</span>
- Com-Port Selector
- Sprache Auswählen
- Shared Config