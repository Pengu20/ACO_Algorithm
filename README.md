# ACO_Algorithm
Algoritme der gør brug af "Ant Colony Optimization" metoden  til at lave en racerbils rute. Gør brug af SFML som dens grafiske pakke.

Programmet fungerer således: (NOTE: klassen point er en samling af x og y coordinaterne)
Klassen myre har metoderne til at kunne vælge hvilken punkt den vil flytte sig til, fra dens givent start punkt.

vector<point> Ant::chooseRoute(point start, vector<point> endpos, vector<float> feromone, int likeFactor)

Den vil vælge tilfældigt. Men sandsynligheden for at den vælger en bestemt baseret på hvor kort ruten er og feromonstyrken på ruten. Værdien for rutens korthed, er den inverse værdi af rutens længde opløftet i en "likefactor" .Feromonens styrke baseres på den inverse værdi af ruten opløftet i en faktor. Feromoner bliver lagt på ruten af tidligere myrer, denne logik håndteres i klassen Colony Mapping. 
  
Klassen ColonyMapping gør brug af et antal af disse myrer valgt ud fra variablen "antNumber" som lægger inde i RunACO metoden. for at holde styr på feromonerne er der lavet en klasse kaldt PheromoneTrail. Den har til opgave at holde på alt feromon information. For hver feromon styrke er der 2 punkter (start og slut punkt). ColonyMapping får 10 myrer til at gå rundt mellem punkterne sekventielt. For hver myre vil feromon vejen opdateres. Efter alle 10 myrer er gået igennem vil ColonyMapping vælge den myre som har gået den korteste rute og returnere dette som en vector af punkter. Der er ingen garanti på at dette er den korteste rute, men dens succesrate er markant høj.

til sidst er der klassen route. Den har til opgave at gøre brug af ColonyMappings RunACO til at få lavet den indre og ydre bane ud fra et string input. For at øge succesraten. Vil route klassen for både den indre og ydre bane bruge RunACO metoden fra ColonyMapping klassen 20 gange. antallet er bestemt fra variablen "cycles" i metoden createShortestTour i klassen Route. Der vil så vælges den korteste rute af de 20 tilfælde for både den indre og ydre bane, hvorefter disse vil være resultatet af algoritmen.
  
