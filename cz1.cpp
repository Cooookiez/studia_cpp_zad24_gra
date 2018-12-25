#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int
    width = 1400,
    height = 900
    ;

const char*
    title = "Color switch THE GAME"
    ;

char
    cur_mian_col = 'G' // (G)reen, (B)lue, (Y)ellow
    ;

sf::Color
    G_1(0, 122, 0),
    G_2(0, 112, 0),
    B_1(0, 91, 91),
    B_2(0, 81, 81),
    Y_1(152, 140, 0),
    Y_2(142, 130, 0)
    ;

int main(int argc, const char * argv[]){

    

    sf::RenderWindow window(sf::VideoMode(width, height), title);

    // Declare and load a font
    sf::Font font;
    font.loadFromFile("fonts/Roboto-Regular.ttf");

    // Create a text
    sf::Text text("hello", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Blue);

    //tlo menu i plaszny

    sf::RectangleShape board_bg;
    board_bg.setSize(sf::Vector2f(height, height));
    board_bg.setPosition(0, 0);

    sf::RectangleShape info_bg;
    info_bg.setSize(sf::Vector2f(height-width, height));
    info_bg.setPosition(width, 0);

    while(window.isOpen()){

        //obsluga klawiszy
        sf::Event event;
        while(window.pollEvent(event)){

            //krzyzyk na oknie
            if(event.type == sf::Event::Closed){
                window.close();
                std::cout << "bla\n";
            }
            else if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        //window.close();
                        std::cout << "bla121243\n";
                        break;
                    // q, w, e - zmienia colory
                    case sf::Keyboard::Q:
                        cur_mian_col = 'G';
                        break;
                    case sf::Keyboard::W:
                        cur_mian_col = 'B';
                        break;
                    case sf::Keyboard::E:
                        cur_mian_col = 'Y';
                        break;
                    default:
                        break;
                }
            }
            
            
        }

        switch(cur_mian_col){
            case 'G':
                board_bg.setFillColor(G_1);
                info_bg.setFillColor(G_2);
                break;
            case 'B':
                board_bg.setFillColor(B_1);
                info_bg.setFillColor(B_2);
                break;
            case 'Y':
                board_bg.setFillColor(Y_1);
                info_bg.setFillColor(Y_2);
                break;
            default:
                break;
        }




        window.clear();

        window.draw(board_bg);
        window.draw(info_bg);
        window.draw(text);

        window.display();

    }

}