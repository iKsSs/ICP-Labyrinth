********************
        
Project: Labyrinth 2015

Author: Jakub Pastuszek <xpastu00@stud.fit.vutbr.cz>

Brief:
    Project for VUT FIT ICP 2014/2015.

********************

Aplikace byla vytvořena v Qt Creatoru pro verzi Qt-5.4.
Pro překlad stačí zadat make a poté pro spuštění použít make run.

Program implementuje známou deskovou hru zvanou Labyrint. Hra je pro 2 až 4 hráče a cílem je nasbírat určitý počet 
pokladů a to tak, že je možno posouvat sudé řádky/sloupce a posouvat figurkou. Hráči se v tazích střídají.

Ovládání programu je čistě pomocí myši, a to klikáním levým tlačítkem na příslušná pole.

Program se skládá z menu, kde se nejprve nastaví velikost hrací plochy (která je vždy čtvercová), počet pokladů a také
se přidají hráči reprezentováni jménem/přezdívkou. V případě úspěšného nastavení a kliknutí na tlačítko "Play!" se
spustí okno s hlavní obrazovkou hry. Na hlavní obrazovce většinu okna zabírá hrací pole, které obsahuje kameny 
s určitými cestami, na kterých může být poklad a plochy pro vložení kamene. Na kamenech se také zobrazují figurky 
hráčů. Pod tímto podoknem je vyobrazen kámen, který se bude vkládat do hrací plochy pomocí jedné z dostupných políček 
pro vkládání. Tento kámen může také obsahovat poklad. Orientace může být změněna po kliknutí na tlačítko "Rotate".
Vpravo dole je vyobrazen seznam hráčů a jejich příslušné barvy figurek. Po pravé straně od hlavní hrací plochy jsou
tlačítka pro uložení hry ("Save") a pro načtení dříve uložené hry ("Load"). Pod těmito tlačítky se nachází jméno
hráče, který je aktuálně na tahu a dále jeho karta s pokladem, který se snaží najít (sebrat). Pod touto kartou je 
tlačítko pro navrácení jednoho tahu zpět ("Undo"). Toto navrácení funguje opakovaně, až do úplného začátku hry. 
V případě výhry je pod tímto tlačítkem zobrazeno jméno hráče který hru vyhrál.

Při ukládání hry nejsou ukládány návraty ("Undo"), tudíž po nahrání hry se nelze vracet zpět (načtená pozice je nově 
startovací pozicí).

Pro hledání cesty je použit algoritmus BFS s frontou CLOSED.
Ukládání hry probíhá v CSV formátu.

Poděkování patří Martinu Pitříkovi, který mi poskytl užitečné informace a rady při tvorbě a hlavně návrhu projektu.