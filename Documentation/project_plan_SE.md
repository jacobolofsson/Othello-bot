# Projektplan Elektromekaniskt projekt 2018
5 hp projektarbete som del av civilingenjörsutbildningen i Teknisk fysik, inriktning inbyggda system.
## Deltagare
* Jacob Olofsson
* Thomas Danielsson
* Aksel Wännström

## Design
I detta projekt ska vi konstruera en robot som kan spela othello mot en mänsklig motståndare. Vi har delat upp designen i tre stycken huvuddelar:
* Spelplan med sensor
* Mjukvara / AI
* Mekanisk förflyttning av pjäser
AI:t ska kunna få information om hur spelplanen ser ut, beräkna ett drag och sedan skicka information om hur draget ska utföras till en robotarm eller annan mekanism som utför draget på den fysiska spelplanen.

### Minsta fungerade produkt (MVP)
Den minsta fungerande produkten vi har är en robot som kan läsa av spelplanen och göra ett slumpmässigt "lagligt" drag.
* Roboten matas med pjäs av rätt färg från mänsklig spelare
* AI:t spelar alltid som samma färg
* AI:t har inget minne
* AI:t utför ett drag efter extern input
* Mäsnkliga motståndaren måste vända på pjäserna som påverkas av draget
* Statuslampor visar i vilket state programmet är
* Mekanismen ska gå att nollställas efter utfört eller misslyckat drag

### Funktioner att lägga till efter MVP
Efter den minsta fungerande produkten har implementerats kommer följande funktioner läggas till:
1. Det går att välja färg på AI:t
1. Efter AI:t utfört ett drag vänder den alla pjäser som blir påverkade av draget
1. Mekanismen plockar upp nya pjäser utan mänsklig hjälp
1. AI:n gör "smarta" drag
1. Möjlighet att ställa in betänketid och/eller svårighetsgrad
1. Display som kan visa mer information om state
1. AI:t känner av när motståndaren utfört sitt drag och fortsätter automatiskt med sitt drag utan input
1. Möjlighet att ha två olika AI:n som spelar mot varandra
1. Bygga två stycken robotar som spelar mot varandra

### Designval
Följande val behöver göras för designen:

#### Spelplan med sensor
* Vilken storlek ska planen ha och hur många rutor ska det vara?
* Vilken sorts sensor ska användas för att känna av färg/position av pjäser?
  * Kamera - Beräkna ljusstyrkan i varje punkt där en pjäs kan befinna sig
  * Fotosensor under planen - Planen görs i genomskinligt material med en fotosensor under
  * Elektrisk / magnetisk krets - Konstruera pjäserna så att de sluter olika kretsar när de placeras på planen

Slutsats: Standard Othello spelas på 8x8. Varje ruta bör vara 3x3cm med en avskiljare som är max 1cm hög för att en mänsklig spelare enkelt ska kunna lyfta upp och placera pjäser. Vi väljer att sätta linjära halleffektsensorer under planen och sätta magneter i spelpjäserna. Med en halleffektsensor går det att känna av riktning på magneten eller om en ruta är tom.
#### Förflyttning av pjäser
* Hur ska pjäserna plockas upp?
  * Elktromagnet
  * Gripklo
* Hur ska "upplockaren" röra sig?
  * I en bana  (som på en 3D-skrivare)
  * En arm med leder
* Hur ska pjäserna byta färg?
  * Vända på pjäserna?
  * Byta ut pjäserna?
* Vilken sorts motor ska användas?

Slutsats: Eftersom pjäserna har en magnet är det praktiskt att använda en elektromagnet för att plocka upp pjäserna. För att ha så få frihetsgrader i systemet som möjligt används en bana likt i en 3D-skrivare. För enkelhet i en första design kommer roboten varken att vända eller byta ut pjäser, detta lämnas till människospelaren. Stegmoterer bör användas för förflyttningen i sidled och en servomotor för upplockandet av pjäser.

#### Mjukvara
* Hur ska programmet struktureras?
  * Hur ska interfacen mellan de olika programdelarna se ut?
* Vilken AI-algorithm ska användas?
  * Monte Carlo
  * Min/max

Slutsats: TBD

#### Hårdvara
Valet av processor kommer att styras i stor del av hur mjukvaran, sensorn och hur förflyttningen och spelplanen designas.
* Vad för sorts processor ska användas?
  * IC
  * Arduino
  * Raspberry Pi
  * Dator
* Ska samma processor användas för AI, sensor och förflyttning eller ska separata processorer som kommunicerar med varandra användas?
* Strömkälla

Slutsats: För enkelhet bör samma processor användas till allt då det finns lite att tjäna i att ha separat hårdvara för de olika delarna. Minst 8 analoga ingångar och 12 digitala utgångar krävs för designen och en någorlunda snabb processor. Förslagsvis en arduino Mega. Separata strömkällor bör användas till motorer och arduino för att minska störningar.

## Skiss
### Spelplan
Spelplanen är uppdelad i 8x8 rutor med en avskiljare mellan varandra för att pjäserna inte ska kunna glida över till rutan brevid. Spelplanen är kopplad till en arduinos 8 digital out, 8 Analog in för multiplex av 64 sensorer. Spelplanen har även 1 digital in för knappen samt 4 digital out för LED kopplad till arduinon för I/O.

<img src="./Drawings/spelbräde.svg">

### Anordning för att flytta armen
<img src="./Drawings/SkissEMP3StallningV4.svg" width ="400">
<img src="./Drawings/TestStällning.svg">

### Arm för att plocka upp pjäser
Vändnings armen är en servo motor kopplad till två metal armar vartpå det sitter en electromagnet. Denna mekanism är det som kommer att plocka up och lägga ner pjäserna för Othello spelet. 
<img src="./Drawings/lever.svg" width = "400">

## Tidsplan
| Vad | Tidsåtgång | Påbörjas senast | Färdigställt senast | Beroende av |
| --- | ---------- | --------------- | ------------------- | ----------- |
| Specifikation av hårdvaru/mjukvaruinterface | 1 dag | ASAP | 27/4 | Oberoende |
| Programmera AI | 7 dagar | ASAP |  27/4 | Oberoende |
| Konstruktion av spelplan | 1 dag | ASAP | 27/4 | Oberoende |
| Bygga ställning | 4 dagar | ASAP |  20/4 | Specifikation spelplan |
| Konstruktion av spelpjäser | 1 dag | ASAP | 27/4 | Oberoende |
| Koppla in stegmotorer | 2 dagar | 20/4 |  27/4 | Byggd ställning |
| Koppla elektronik i spelplanen | 2 dagar | 28/4 | 30/4 | Specifikation av hw/sw interface, Konstruktion av spelplan|
| Programmera styrprogram för elektroniken i spelplanen | 3 dagar | 30/4 | 3/5 | Specifikation av hw/sw interface | 
| Programmera stegmotorrörelse | 3 dagar | 2/5 |  7/5 | Färdigställd spelplan |
| Felsöka elektronik i spelplanen | 4 dagar | 3/5 | 7/5 | Koppling av elektronik i spelplanen, styrprogram för spelplanen |
| Testa och felsöka AI | 4 dagar | 7/5 | 11/5 | Programmera AI, felsöka elektronik i spelplanen |
| Skriv rapport | 4 dagar | 11/5 | 15/5 | Allt ovan |  
