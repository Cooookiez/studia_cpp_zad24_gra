# studia c++ zad_24 - gra sfml

![kosmogierka.gif](./space.gif)

## Zasady gry
* Gracz posiada 3 rodzaje (kolory) broni na 3 rodzaje (kolory) przeciwników
  * Jeśli broń trafiony nią przeciwnik mają ten sam kolor, przeciwnikowi dodaje się hp
  * Jeśli kolor broni się rózni hp się odejmuje
  * jeśli przeciwnik najedzie na postać, przeciwnik znika, a hp postaci odejmuje się o 0.5 serca

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