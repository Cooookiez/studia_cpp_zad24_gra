#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int
    Width = 1400,
    Height = 900,
    sep_height = 4,
    margin = 16
    ;

const char*
    Title = "Color switch THE GAME"
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

    

    sf::RenderWindow window(sf::VideoMode(Width, Height), Title);

    // Declare and load a font
        sf::Font font;
        font.loadFromFile("fonts/Roboto-Regular.ttf");

        sf::Vector2f pos;
        float width;
        float h1, h2, p_;
    
    //text
        //title
            sf::Text txt_title(Title, font);
            txt_title.setCharacterSize(32);
            txt_title.setStyle(sf::Text::Bold);
            txt_title.setFillColor(sf::Color::Black);
            pos = txt_title.getPosition();
            width = txt_title.getLocalBounds().width;
            h1 = txt_title.getLocalBounds().height;
            txt_title.setPosition(pos.x + Height + ((Width-Height-width)/2), pos.y + margin); // zawsze na srodku   
        //sterowanie
            sf::Text txt_ster_0("Sterowanie", font);
            sf::Text txt_ster_1("Q/W/E - zmiana koloru", font);
            sf::Text txt_ster_2("Strzalki- Poruszanie sie", font);
            sf::Text txt_ster_3("Spacja - Strzelanie", font);

            txt_ster_0.setCharacterSize(28);
            txt_ster_1.setCharacterSize(22);
            txt_ster_2.setCharacterSize(22);
            txt_ster_3.setCharacterSize(22);

            txt_ster_0.setStyle(sf::Text::Bold);

            h2 = txt_ster_0.getLocalBounds().height;
            p_ = txt_ster_1.getLocalBounds().height;

            txt_ster_0.setFillColor(sf::Color::Black);
            txt_ster_1.setFillColor(sf::Color::Black);
            txt_ster_2.setFillColor(sf::Color::Black);
            txt_ster_3.setFillColor(sf::Color::Black);

            pos = txt_ster_0.getPosition(); txt_ster_0.setPosition(pos.x + Height + margin, pos.y + margin*3 + h1 + sep_height);
            pos = txt_ster_1.getPosition(); txt_ster_1.setPosition(pos.x + Height + margin, pos.y + margin*4 + h1 + sep_height + h2);
            pos = txt_ster_2.getPosition(); txt_ster_2.setPosition(pos.x + Height + margin, pos.y + margin*5 + h1 + sep_height + h2 + p_);
            pos = txt_ster_3.getPosition(); txt_ster_3.setPosition(pos.x + Height + margin, pos.y + margin*6 + h1 + sep_height + h2 + p_*2);

        //od nowa / zapisz i wyjdz
            sf::Text txt_oth_1("Esc, (x) - Zapisz i wyjdz", font);
            sf::Text txt_oth_2("Enter - Szybki reset", font);

            txt_oth_1.setCharacterSize(22);
            txt_oth_2.setCharacterSize(22);

            txt_oth_1.setFillColor(sf::Color::Black);
            txt_oth_2.setFillColor(sf::Color::Black);

            pos = txt_oth_1.getPosition();  txt_oth_1.setPosition(pos.x + Height + margin, pos.y + margin*7 + h1 + sep_height*2 + h2 + p_*3);
            pos = txt_oth_2.getPosition();  txt_oth_2.setPosition(pos.x + Height + margin, pos.y + margin*8 + h1 + sep_height*2 + h2 + p_*4);
        
    //separatory
        sf::RectangleShape sep[2];
        
            sep[0].setSize(sf::Vector2f(Width-Height-32, sep_height));
            sep[0].setPosition(Height+16, 16 + h1 + 16);
            sep[0].setFillColor(sf::Color::Black);

            sep[1].setSize(sf::Vector2f(Width-Height-32, sep_height));
            sep[1].setPosition(Height+16, margin*8 + h1 + sep_height + h2 + p_*2);
            sep[1].setFillColor(sf::Color::Black);


    //tlo menu i plaszny
    sf::RectangleShape board_bg;
    board_bg.setSize(sf::Vector2f(Height, Height));
    board_bg.setPosition(0, 0);

    sf::RectangleShape info_bg;
    info_bg.setSize(sf::Vector2f(Height-Width, Height));
    info_bg.setPosition(Width, 0);

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
                        window.close();
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

        window.draw(txt_title);
        window.draw(sep[0]);
        window.draw(txt_ster_0);
        window.draw(txt_ster_1);
        window.draw(txt_ster_2);
        window.draw(txt_ster_3);
        window.draw(sep[1]);
        window.draw(txt_oth_1);
        window.draw(txt_oth_2);

        window.display();

    }

}