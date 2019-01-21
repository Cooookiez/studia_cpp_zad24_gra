# studia c++ zad_24 - gra

## Zasady gry
* Gracz posiada 3 rodzaje (kolory) broni na 3 rodzaje (kolory) przeciwników
  * Jeśli broń i trafiony nią przeciwnik mają ten sam kolor, przeciwnikowi dodaje się hp
  * Jeśli kolor się rózni hp się odejmuje

## Odpalenie

Komendy pokoleji
~~~bash
g++ -c cz1.cpp
g++ cz1.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
~~~

lub w jednej lini
~~~bash
g++ -c cz1.cpp && g++ cz1.o -o sfml-app-1 -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app-1
~~~