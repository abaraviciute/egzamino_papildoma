# Egzamino užduotis  

## Žodžių skaičiuoklė  

Programa suskaičiuoja, kiek kartų kiekvienas žodis pasikartoja tekste, į failą rezultatai.txt išveda tik tuos žodžius, kurie pasikartoja daugiau nei vieną kartą ir parašo pasikartojimų skaičių. Taip pat išvedami numeriai eilučių, kuriose žodis pasikartoja.  

## URL adresų paieška  

Programa taip pat vykdo ilgų (pvz., https://www.vu.lt/, http://www.vu.lt) ir sutrumpintų (pvz.,  www.vu.lt, vu.lt, saitas.xyz) URL adresų paiešką. Visus atrastus adresus išveda į failą rezultatai_url.txt.  


## Programa  

Failai:  

- EgzaminoUzd.cpp - pagrindinis vykdomasis taškas;  
- Funkcijos.cpp - funkcijos;  
- Funkcijos.h - funkcijų deklaracijos;  
- Lib.h - naudojamos bibliotekos.  

Funkcijos:  

- isvalytiZodi() - nuima kablelius, taškus, klaustukus ir kitus ženklus nuo žodžių. URL adresus palieka nekeistus;
- toLower() - žodį perrašo mažosiomis raidėmis;
- skaitytiFaila() - nuskaito duotą failą (priima ir lietuviškus specialiuosius simbolius);
- rasytiFaila() - įrašo rezultatus iš žodžių skaičiuoklės į failą (išvedama dažnio skaičiuoklė ir eilutės, kuriose žodis pasikartoja);
- surastiURL() - ieško tekste esančių URL adresų, atitinkančių RegEx koduotę ir saugo juos vektoriuje;
- rasytiURLFaila() - į atskirą failą surašo visus rastus URL adresus.  