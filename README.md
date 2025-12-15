# HashMap Generator

In diesem Programm wird eine **hashmap** generiert, deren Länge der Nutzer bestimmen darf (mit Rücksicht auf Obergrenze). Es ist ein Konsolenprogramm.
Es werden zufällige Vor- und Nachnamen als values und Usernames als keys verwendet. Im Anschluss wird die Userliste in der Konsole ausgegeben, wonach der Nutzer einen Username benutzen kann, um den entsprechenden vollen Namen zu finden.

___

### 1. Eingabeaufforderung für die Länge der hashmap
<img width="835" height="153" alt="Screenshot 1" src="https://github.com/user-attachments/assets/f19da89c-7f0d-4fbe-8fea-606a14202097" />

* Der Nutzer kann sich für eine Zahl zwischen `1` und `150` entscheiden
* Alle Datentypen außer int und ungeeignete Zahlen werden abgelehnt und die Eingabe wiederholt

### 2. Generieren der "Nutzerdaten"
<img width="1408" height="66" alt="Screenshot 2" src="https://github.com/user-attachments/assets/5fd7b04d-146b-4587-b3ad-be201c94ba6e" />


* Aus einer beschränken Anzahl von Beispielnamen, setzen sich die vollen Namen der "Nutzer" zusammen
* Aus den vollen Namen und einer zufälligen dreistelligen Zahl setzen sich dann die usernames zusammen
* Die Obergrenze von `150` wurde festgelegt, da die Zahl von einzigartigen Namenskombinationen bei `144` liegt
* Duplikate sind nicht weiter wichtig, da jeder username *höchstwahrscheinlich* durch seine Zahlen einzigartig wird

### 3. Ausgabe der Daten und Erstellen der hashmap
<img width="431" height="400" alt="Screenshot 3" src="https://github.com/user-attachments/assets/bead04a8-3bf1-4214-b926-ec45f6d4e003" />


* Die Konsole gibt für tatsächlichen Nutzer alle Daten aus
* Im Hintergrund wurde die hashmap schon erstellt und die zwei temporären string arrays freigegeben


<img width="531" height="393" alt="Screenshot 4" src="https://github.com/user-attachments/assets/5ac7f9d7-ec95-4cf8-9fed-a6632335660b" />


### 4. Nutzereingabe und Lesen der hashmap
* Der Nutzer soll jetzt einen der zuvor angezeigten Usernames eingeben, um an die restlichen Daten dieses Eintrages zu kommen
#### Korrekte Eingabe:
<img width="709" height="324" alt="Screenshot 5" src="https://github.com/user-attachments/assets/23e891c8-7e69-4a07-bdab-5487c39e0585" />

#### Falsche Eingabe:
<img width="673" height="191" alt="Screenshot 6" src="https://github.com/user-attachments/assets/75fdf116-a50a-4795-9b54-2206aae66ff3" />

* Man kann seinen Versuch beliebig oft wiederholen
* Die hashmap wird nur bei Neustart des Programmes neu angelegt


___


#### Mögliche Fehlerquellen
* Es könnte wohl dazu kommen, dass zwei Username tatsächlich identisch sind. Hoffen wir einfach mal, dass die Wahrscheinlichkeit davon so gering ist wie ich denke

#### Sonstiges
Dieses Programm ist im Grunde nur die Demonstration einer hashmap Routine. Einen tatsächlichen Nutzen daraus hat man hier allein deshalb schon nicht, da einem die Nutzerdaten gleich zu Anfang offen präsentiert werden.
In Zukunft füge ich in `struct user` vielleicht noch einen geheimen Wert hinzu, der nur über die hashmap zugänglich ist.
Die Funktion `hash()` habe ich natürlich nicht selbst geschrieben. (Für Quelle siehe unten)

#### Quellen
[djb2 hash](https://theartincode.stanis.me/008-djb2/), 
[Idee und Anleitung](https://youtu.be/y11XNXi9dgs?si=zc7GCZ9xqLbDll1-), 
[Generelle Hilfe](https://www.geeksforgeeks.org/)
