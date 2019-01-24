# studia c++ zad_24 - gra

## Zasady gry
* Gracz posiada 3 rodzaje (kolory) broni na 3 rodzaje (kolory) przeciwników
  * Jeśli broń i trafiony nią przeciwnik mają ten sam kolor, przeciwnikowi dodaje się hp
  * Jeśli kolor się rózni hp się odejmuje

## gra zapisuje
* [ ] Ilosc serc
* [ ] Ilość pkt
* przeciwnikow
  * [ ] x
  * [ ] y
  * [ ] v
  * [ ] scale
  * [ ] c_color
* pocisk
  * [ ] x
  * [ ] y
  * [ ] vx
  * [ ] vy
  * [ ] r
  * [ ] sf::Color
  * [ ] c_color
* postac
  * [ ] x
  * [ ] y
  * [ ] dx
  * [ ] dy
  * [ ] v
  * [ ] kierunek

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