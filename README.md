# Anleitung Schiffe Versenken


## Spiel Menü:
Nach dem Spielstart wird in der Konsole das Menü angezeigt,
dabei können verschiedene Auswahlmöglichkeiten durch die Konsole angesteuert werden,
um einen Punkt anzusteuern, muss der entsprechende Buchstabe in der eckigen Klammer eingegeben werden.
```
***********************************************
*      Willkommen bei Schiffe Versenken!      *
***********************************************
*                [m] Menue                    *
*                [f] Fortsetzen               *
*                [s] Speichern                *
*                [c] Cheaten                  *
*                [n] Neues Spiel              *
*                [l] Laden                    *
*                [e] Exit                     *
***********************************************
```
#### Menü Erklärung: 
Folgende eingaben sind im Menü möglich
```
m  : um in diese Menü zu gelangen

f  : um ein Laufendes Spiel fortzusetzen (wird nur angezeigt wenn bereist ein Spiel läuft!)

s  : um ein Laufendes Spiel zu speichern (wird nur angezeigt wenn bereist ein Spiel läuft!)

n  : um ein Neues Spiel zu Starten

l  : Ladet ein abgespeichertes Spiel (wird nur angezeigt wenn eine Speicherdatei vorhanden ist)

e  : Beendet das spiel

c  : cheat (ist nur möglich wenn bereits ein Spiel läuft!)
```

## Spiel Verlauf:
Nachdem ein neues Spiel gestartet wurde,
wird der Spieler aufgefordert seine Schiffe zu platzieren.
Dabei muss er die Start Koordinaten und die Ausrichtung des Schiffs angeben. 
```
Ausrichtungsmöglichkeiten:
v  : Vertikal
h  : Horizontal
```
Hier ein Beispiel für die Platzierung:
```
Horizontal:

Platzieren Sie Ihr Schlachtschiff (Kaestchen 5): C4h
   1  2  3  4  5  6  7  8  9  10
A  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
B  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
C  ~  ~  ~  #  #  #  #  #  ~  ~
D  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
E  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
F  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
G  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
H  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
I  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
J  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
```

```
Vertikal:

Platzieren Sie Ihr Schlachtschiff (Kaestchen 5): C4v
   1  2  3  4  5  6  7  8  9  10
A  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
B  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
C  ~  ~  ~  #  ~  ~  ~  ~  ~  ~
D  ~  ~  ~  #  ~  ~  ~  ~  ~  ~
E  ~  ~  ~  #  ~  ~  ~  ~  ~  ~
F  ~  ~  ~  #  ~  ~  ~  ~  ~  ~
G  ~  ~  ~  #  ~  ~  ~  ~  ~  ~
H  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
I  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~
J  ~  ~  ~  ~  ~  ~  ~  ~  ~  ~

```
Nachdem die Schiffe platziert wurden, wird ausgelost ob der Spieler oder der Computer Gegner anfangen darf.
Wenn der Spieler am Zug ist kann er z.b. `A1` seinen Schuss abfeuern oder mit dem Befehl `exit` oder `menue` oder `m` wieder ins Menü zurückkehren.

### Legende: 
```
~  : Meer, verdecktes Feld

#  : Schiff (nur auf dem eigenen Feld zu sehen)

O  : Schuss ins Meer, kein Treffer (Vorbei)

X  : Treffer, Schiff noch nicht versenkt

S  : Treffer, Schiff versenkt
```
## Compile:

Der Code lässt sich mit 

```
g++  .\Spiel.cpp .\Spieler.cpp .\Spielfeld.cpp .\CppRandom.cpp .\File.cpp .\Menu.cpp  .\Globals.cpp .\Main.cpp  -o schiff
```

kompilieren und über
```
./schiff
```
starten.


## Im Projekt angewandt:
```
Include-Guards
Klassendeklaration
Konstruktoren
Header (hpp)
Source (cpp)
Smart-Pointer
Zufallszahlen
typedef
Vector
nullptr
File Streams
Konversion string zu int
Access Specifiers (private und public)
Member intialiseren
Objektinhalte
Pointer auf Objekte (x->y, x.y)
Exception
```
