Textur_Readme.txt
=================
texture_with_SOIL.cpp
- verwendet die SOIL-Bibliothek  (http://www.lonesock.net/soil.html) 
- SOIL.h (dorthin, wo auch (free)glut.h  steht)
- SOIL.lib (dorthin, wo auch (free)glut.lib steht)
- TREE1.png in der Regel dorthin, wo auch stdafx.h steht 
- Falls erforderlich: soil.lib explizit zum Aufnehmen angeben:
  Projektmappen-Explorer (<CTRL><Ü>) > Konfigurationseigenschaften > 
     > Linker > Eingabe > Zusätzliche Abhängigkeiten > SOIL.lib
- wenn's nicht klappt: SOIL.lib mit den sources aus 
     http://www.lonesock.net/soil.html
  selbst erstellen.
