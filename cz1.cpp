#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class Pocisk{
    private:
        int x, y, r, vx, vy;
        sf::Color color;

    public: 
        sf::CircleShape pocisk;
        char c_color;
        
        Pocisk(float x, float y, float vx, float vy, float r, sf::Color color, char c_color){
            this->x = x - r;
            this->y = y - r;
            this->r = r;
            this->vx = vx;
            this->vy = vy;
            this->pocisk.setRadius(r);
            this->pocisk.setFillColor(color);
            this->pocisk.setPosition(this->x, this->y);
            this->c_color = c_color;
        }
        void move(){
            this->x += this->vx;
            this->y += this->vy;
            this->pocisk.setPosition(this->x, this->y);
        }
        bool pozaOknem(float height, float width){
            if(
                this->x < 0 ||
                this->x + 2*this->r > height ||
                this->y < 0 ||
                this->y + 2*this->r > width
            ){
                return true;
            }
            return false;
        }
};

class Przeciwnik{
    private:
        float
            x,
            y,
            v,
            vx,
            vy,
            scale,
            width,
            height;
        // sf::Texture przeciwnik_texture;
        char c_color;
        int life = 1;
    public:
        sf::Sprite przeciwnik_sprite;

        Przeciwnik(float x, float y, float v, float scale, char c_color, sf::Sprite przeciwnik_sprite){
            this->x = x;
            this->y = y;
            this->v = v;
            this->scale = scale;
            this->c_color = c_color;
            this->przeciwnik_sprite = przeciwnik_sprite;
            switch (this->c_color){
                case 'G': this->przeciwnik_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); break;
                case 'B': this->przeciwnik_sprite.setTextureRect(sf::IntRect(16, 0, 16, 16)); break;
                case 'Y': this->przeciwnik_sprite.setTextureRect(sf::IntRect(32, 0, 16, 16)); break;
                default: break;
            }
            
            this->przeciwnik_sprite.setScale(this->scale, this->scale);
            this->height = this->przeciwnik_sprite.getLocalBounds().height*this->scale;
            this->width = this->przeciwnik_sprite.getLocalBounds().width*this->scale;
            this->przeciwnik_sprite.setPosition(this->x, this->y);
            
        }

        void move(float x, float y){
            float tmp_x = this->x;
            float tmp_y = this->y;
            float a = x - (this->x + this->width/2);
            float b = y - (this->y + this->height/2);
            float c = pow( a*a + b*b, .5 );
            this->vx = this->v*(a/c);
            this->vy = this->v*(b/c);
            this->x += this->vx;
            this->y += this->vy;
            // cout << "v("<<this->vx<<","<<this->vy<<")" << endl;
            // cout << "P("<<this->x<<","<<this->y<<")" << endl;
            this->przeciwnik_sprite.setPosition(this->x, this->y);
            // cout << x << "\t" << y << "\t" << tmp_x << "\t" << tmp_y << "\t" << vx << "\t" << vy << "\t" << this->x << "\t" << this->y << "\t" << endl;
        }

        void hit(char c_color_pociks){
            if( this->c_color == c_color_pociks ){
                this->life++;
            }else{
                this->life--;
            }
            this->rescale();
        }

        void rescale(){
            float inner_scale = this->life*.25+.75;
            // cout << inner_scale << endl;
            this->przeciwnik_sprite.setScale(this->scale*inner_scale, this->scale*inner_scale);

            float height = this->przeciwnik_sprite.getLocalBounds().height*this->scale*inner_scale;
            float width = this->przeciwnik_sprite.getLocalBounds().width*this->scale*inner_scale;

            this->x += (this->width - width)/2;
            this->y += (this->height - height)/2;

            this->width = width;
            this->height = height;

        }

        bool isALive(){
            if( this->life > 0 ) return true;
            return false;
        }

};

Przeciwnik add_przeciwnik(sf::Sprite sprite, int Height, int Width, char c_color){
   
    float tmp_x = rand()%Height;
    float tmp_y = rand()%Height;
    float tmp_v = (float)(rand()%3+2)/(float)10;

    return Przeciwnik(tmp_x, tmp_y, tmp_v, 3, c_color, sprite);
}

// void save(vector<Pocisk> pocisk, vector<Przeciwnik> przeciwnik, sf::Sprite postac, int score){
    
// }

int main(int argc, const char * argv[]){

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
        cur_mian_col = 'G', // (G)reen, (B)lue, (Y)ellow
        color
        ;

    bool inGame = true;

    int pkt = 0;

    srand(time(NULL));

    sf::Vector2f pos;
    float tmp_x, tmp_y;

    vector<Pocisk> pocisk;

    vector<Przeciwnik> przeciwnik;
    sf::Texture przeciwnik_texture;
    sf::Sprite przeciwnik_sprite;
    if( !przeciwnik_texture.loadFromFile("img/przeciwnicy.png") ) return -1;
    przeciwnik_sprite.setTexture(przeciwnik_texture);
    int ile_p_na_start = rand()%3+3;
    for( int i = 0; i < ile_p_na_start; i++ ){
        przeciwnik.push_back(add_przeciwnik(przeciwnik_sprite, Height, Width, "GBY"[rand()%3]));
    }

    // przeciwnik.push_back(Przeciwnik(20, 20, .2, 2, 'G', przeciwnik_sprite));
    // przeciwnik.push_back(Przeciwnik(60, 60, .2, 2, 'B', przeciwnik_sprite));
    // przeciwnik.push_back(Przeciwnik(100, 100, .2, 2, 'Y', przeciwnik_sprite));

    // POSTAC
        int POSTACIE_SCALE = 3;
        //kierunek ruchu
            int postac_kierunek = 8;
            float postac_v = 10;
            float _dx = .7;
            float _dy = _dx;
            float dx = 0;
            float dy = -_dx;
            /*
                kierunki jak na klawiaturze numerycznej
                |   N   |  =>  |   8   | 
                | W   E |  =>  | 4   6 |
                |   S   |  =>  |   2   |
                ale sterowane strzalkami
            */
        //grafika
            sf::Texture postac_texture;
            if( !postac_texture.loadFromFile("img/postac-2.png")) return -1;
            sf::Sprite postac;
            postac.setTexture(postac_texture);
            postac.setTextureRect(sf::IntRect(16, 0, 16, 16));
            postac.setScale(sf::Vector2f(POSTACIE_SCALE, POSTACIE_SCALE));
            int postac_height = postac.getLocalBounds().height*POSTACIE_SCALE;
            int postac_width = postac.getLocalBounds().width*POSTACIE_SCALE;

            pos = postac.getPosition();
            tmp_x = pos.x + Height/2 - postac_width/2;
            tmp_y = pos.y + Height/2 - postac_height/2;
            postac.setPosition(tmp_x, tmp_y);

    sf::Color
        G_1(0, 122, 0),
        G_2(0, 112, 0),
        B_1(0, 91, 91),
        B_2(0, 81, 81),
        Y_1(152, 140, 0),
        Y_2(142, 130, 0)
        ;

    //serca max, cur
        int num_of_hearts = 5;
        int max_live = num_of_hearts*2;
        int cur_live = max_live;
    //posytion/size
        float width;
        float h1, h2, p_;
        float heart_height, heart_width, hearts_scale=5.f;

    sf::RenderWindow window(sf::VideoMode(Width, Height), Title);

    // Declare and load a font
        sf::Font font;
        font.loadFromFile("fonts/Roboto-Regular.ttf");

    // text
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

        //* od nowa / zapisz i wyjdz
            sf::Text txt_oth_1("Esc, (x) - Wyjdz", font);
            //// sf::Text txt_oth_2("Enter - Szybki reset", font);
            sf::Text txt_oth_2("", font);

            txt_oth_1.setCharacterSize(22);
            txt_oth_2.setCharacterSize(22);

            txt_oth_1.setFillColor(sf::Color::Black);
            txt_oth_2.setFillColor(sf::Color::Black);

            pos = txt_oth_1.getPosition();  txt_oth_1.setPosition(pos.x + Height + margin, pos.y + margin*7 + h1 + sep_height*2 + h2 + p_*3);
            pos = txt_oth_2.getPosition();  txt_oth_2.setPosition(pos.x + Height + margin, pos.y + margin*8 + h1 + sep_height*2 + h2 + p_*4);

        // pkt
            string pkt_s;
            pkt_s = "Pkt: " + to_string(pkt);
            sf::Text txt_pkt(pkt_s, font);
            txt_pkt.setCharacterSize(36);
            txt_pkt.setFillColor(sf::Color::Black);
            pos = txt_pkt.getPosition();
            txt_pkt.setPosition(pos.x + Height + margin, pos.y + margin*16 + h1 + sep_height*2 + h2 + p_*5);
        
    // separatory
        sf::RectangleShape sep[2];
        
            sep[0].setSize(sf::Vector2f(Width-Height-32, sep_height));
            sep[0].setPosition(Height+16, 16 + h1 + 16);
            sep[0].setFillColor(sf::Color::Black);

            sep[1].setSize(sf::Vector2f(Width-Height-32, sep_height));
            sep[1].setPosition(Height+16, margin*8 + h1 + sep_height + h2 + p_*2);
            sep[1].setFillColor(sf::Color::Black);

    // serca
        sf::Texture hearts;
        sf::Sprite heart_half[num_of_hearts];
        sf::Sprite heart_whole[num_of_hearts];
        if( !hearts.loadFromFile("img/serca.png") ) return -1;
        for( int i = 0; i < num_of_hearts; i++){
            heart_half[i].setTexture(hearts);
            heart_whole[i].setTexture(hearts);

            heart_half[i].setTextureRect(sf::IntRect(16, 0, 16, 16));
            heart_whole[i].setTextureRect(sf::IntRect(0, 0, 16, 16));

            heart_half[i].setScale(sf::Vector2f(hearts_scale, hearts_scale));
            heart_whole[i].setScale(sf::Vector2f(hearts_scale, hearts_scale));

            heart_height = heart_whole[i].getLocalBounds().height;
            heart_width = heart_whole[i].getLocalBounds().width;

            
            float to_center = ((Width - Height) - (heart_width*hearts_scale*num_of_hearts + 8*(num_of_hearts-1)))/2; // serca sa na srodku
            
            pos = heart_half[i].getPosition(); 
            tmp_x = pos.x + Height + to_center + (heart_width*hearts_scale+8)*i;
            tmp_y = pos.y + margin*8 + h1 + sep_height*4 + h2 + p_*6;
            heart_half[i].setPosition(tmp_x, tmp_y);
            
            pos = heart_whole[i].getPosition(); 
            tmp_x = pos.x + Height + to_center + (heart_width*hearts_scale+8)*i;
            tmp_y = pos.y + margin*8 + h1 + sep_height*4 + h2 + p_*6;
            heart_whole[i].setPosition(tmp_x, tmp_y);
            
        }

    // tlo menu i plaszny
        sf::RectangleShape board_bg;
        board_bg.setSize(sf::Vector2f(Height, Height));
        board_bg.setPosition(0, 0);
        board_bg.setFillColor(sf::Color(50, 50, 50));

        sf::RectangleShape info_bg;
        info_bg.setSize(sf::Vector2f(Height-Width, Height));
        info_bg.setPosition(Width, 0);

    sf::Clock clock;
    int ile_czekac;

    // window.setFramerateLimit(1);

    while(window.isOpen() && cur_live > 0){

        sf::Time elapsed = clock.getElapsedTime();
        if( elapsed.asMilliseconds() < 1 ){
            int max = 2500;
            int min = 1000;
            ile_czekac = min+rand()%(max-min+1);
        }else if( elapsed.asMilliseconds() > ile_czekac ){
            clock.restart();
            przeciwnik.push_back(add_przeciwnik(przeciwnik_sprite, Height, Width, "GBY"[rand()%3]));
        }

        //obsluga klawiszy
        sf::Event event;
        while(window.pollEvent(event)){

            //krzyzyk na oknie
            if(event.type == sf::Event::Closed){
            cout << "pkt: " << to_string(pkt) << endl;
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        cout << "pkt: " << to_string(pkt) << endl;
                        window.close();
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
                    //kierunek lotu
                    case sf::Keyboard::Up:
                    case sf::Keyboard::Numpad8:
                        postac_kierunek = 8;
                        postac.setTextureRect(sf::IntRect(16, 0, 16, 16));
                        dx = 0;
                        dy = -_dy;
                        break;
                    case sf::Keyboard::Down:
                    case sf::Keyboard::Numpad2:
                        postac_kierunek = 2;
                        postac.setTextureRect(sf::IntRect(16, 32, 16, 16));
                        dx = 0;
                        dy = _dy;
                        break;
                    case sf::Keyboard::Left:
                    case sf::Keyboard::Numpad4:
                        postac_kierunek = 4;
                        postac.setTextureRect(sf::IntRect(0, 16, 16, 16));
                        dx = -_dx;
                        dy = 0;
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::Numpad6:
                        postac_kierunek = 6;
                        postac.setTextureRect(sf::IntRect(32, 16, 16, 16));
                        dx = _dx;
                        dy = 0;
                        break;
                    case sf::Keyboard::Space:
                        // cout << "piw paw" << endl;
                        // cout << dx << "\t" << dy << endl;
                        if( dx != 0 || dy != 0){
                            switch(cur_mian_col){
                                case 'G':
                                    pocisk.push_back(Pocisk( postac.getPosition().x + postac_width/2, postac.getPosition().y + postac_height/2, dx*3, dy*3, 10, G_2, 'G' ));
                                    break;
                                case 'B':
                                    pocisk.push_back(Pocisk( postac.getPosition().x + postac_width/2, postac.getPosition().y + postac_height/2, dx*3, dy*3, 10, B_2, 'B' ));
                                    break;
                                case 'Y':
                                    pocisk.push_back(Pocisk( postac.getPosition().x + postac_width/2, postac.getPosition().y + postac_height/2, dx*3, dy*3, 10, Y_2, 'Y' ));
                                    break;
                                default:
                                    break;
                            }
                        }
                        break;

                    default:
                        break;
                }
            }
            
            
        }

        switch(cur_mian_col){
            case 'G':
                // board_bg.setFillColor(G_1);
                info_bg.setFillColor(G_2);
                break;
            case 'B':
                // board_bg.setFillColor(B_1);
                info_bg.setFillColor(B_2);
                break;
            case 'Y':
                // board_bg.setFillColor(Y_1);
                info_bg.setFillColor(Y_2);
                break;
            default:
                break;
        }

        window.clear();

        //zawsze (bg + title + tips)
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
            window.draw(txt_pkt);

        if(inGame){
            //pociski
                for( auto i = pocisk.begin(); i < pocisk.end(); i++ ){
                    i->move();
                    if(i->pozaOknem(Height, Width)){
                        pocisk.erase(i);
                        continue;
                    }
                    window.draw(i->pocisk);
                }
            //postac
                pos = postac.getPosition();
                tmp_x = pos.x + dx;
                tmp_y = pos.y + dy;
                // cout << pos.x << "\t" << pos.y << "\t" << tmp_x << "\t" << tmp_y << "\t" << dx << "\t" << dy << endl;
                if(tmp_x < 0) tmp_x = pos.x;
                else if(tmp_x > Height - postac_width) tmp_x = pos.x;
                if(tmp_y < 0) tmp_y = pos.y;
                else if(tmp_y > Height - postac_height) tmp_y = pos.y;
                postac.setPosition(tmp_x, tmp_y);
                window.draw(postac);
            //przeciwnicy
                for( auto i = przeciwnik.begin(); i < przeciwnik.end(); i++ ){
                    i->move(postac.getPosition().x + postac_width/2, postac.getPosition().y + postac_height/2);
                    //przeciwnik dotknol postac
                    if( postac.getGlobalBounds().intersects(i->przeciwnik_sprite.getGlobalBounds()) ){
                        // cout << "przeciwnik - postac" << endl;
                        cur_live--;
                        przeciwnik.erase(i);
                        continue;
                    }else{
                        for( auto j = pocisk.begin(); j < pocisk.end(); j++ ){
                            if( i->przeciwnik_sprite.getGlobalBounds().intersects(j->pocisk.getGlobalBounds()) ){
                                // cout << "przeciwnik - pocisk" << endl;
                                i->hit(j->c_color);
                                pocisk.erase(j);
                            }
                            if( !i->isALive() ){
                                pkt++;
                                pkt_s = "Pkt: " + to_string(pkt);
                                txt_pkt.setString(pkt_s);
                                break;
                            }
                        }
                    }
                    if( !i->isALive() ){
                        przeciwnik.erase(i);
                        continue;
                    }
                    window.draw(i->przeciwnik_sprite);
                }
        }

        for(int i = 0; i < num_of_hearts; i++){
            
            if( i*2 < cur_live-1 ){
                window.draw(heart_whole[i]);
            }else if( i*2 == cur_live-1 ){
                if( cur_live%2 )
                    window.draw(heart_half[i]);
                else
                    window.draw(heart_whole[i]);
            }
        }
        // std::cout << "\n\n\n";

        window.display();

    }

}