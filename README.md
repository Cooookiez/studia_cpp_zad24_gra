# studia c++ zad_24 - gra

## Kompilowanie

~~~bash
g++ -c cz1.cpp
g++ cz1.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
~~~

lub w jednej lini

~~~bash
g++ -c cz1.cpp && g++ cz1.o -o sfml-app-1 -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app-1
~~~