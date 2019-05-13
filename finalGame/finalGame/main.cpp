#include <SFML/Graphics.hpp>
#include<iostream>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <time.h>
#include<cstdlib>


#include<vector>
 using namespace sf;

int main(){
    srand(time(NULL));
    
    //Window that we can play the game in
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Final Game");
    window.setFramerateLimit(60);
    
    Texture background;
    background.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/finalGame/finalGame/images/a0495902854_10.jpg");
    Sprite bg(background);
    
    //dots
    CircleShape bullet;
    bullet.setFillColor(Color::Yellow);
    bullet.setRadius(5.f);
   
    RectangleShape badguy;
    badguy.setFillColor(Color::Red);
    badguy.setSize(Vector2f(50.f,50.f));
    Texture enemyTexture;
    if(!enemyTexture.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/finalGame/finalGame/images/ship.png")){
        std::cout<< "ERROR\n";
    }
    
    badguy.setTexture(&enemyTexture);
    
    
    //Player
    CircleShape player;
    player.setFillColor(Color::White);
    player.setRadius(50.f);
    player.setPosition(window.getSize().x/2 - player.getRadius(),window.getSize().y - player.getRadius()*2 - 10);
    
    Texture playerTexture;
    if(!playerTexture.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/smfl_clt/smfl_clt/images/enemy.png")){
        std::cout<< "ERROR\n";
    }
    player.setTexture(&playerTexture);
    Vector2f pointofFire;
    int shotTimer = 0;
    
    int score = 0;
    
    
     std::vector<CircleShape> bullets;
    bullets.push_back(CircleShape(bullet));
    
    std::vector<RectangleShape> baddies;
    baddies.push_back(RectangleShape(badguy));
    int enemySpawnTimer = 0;
    
    
    Font font;
    font.loadFromFile("/Users/kenneth-matthewvelarde/Desktop/testXcode/finalGame/finalGame/TronBoldInline.ttf");
    
 
    while (window.isOpen())
        
    {

        
        sf::Event event;
        //Check when the window is closed
        
        while (window.pollEvent(event))
            
        {
            //If user presses x in the top right, Windows, top left, Mac,  close the window
            if (event.type == sf::Event::Closed)
                
            {
                window.close();
                
            }
        }
        
        //update
        
        
        std::string scorestoString = std::to_string(score);
        
        Text tally;
        tally.setFont(font);
        tally.setString(scorestoString);
        
        tally.setCharacterSize(100);
        tally.setFillColor(sf::Color::Yellow);
        
        
        
        //position of player
         player.setPosition(Mouse::getPosition(window).x, player.getPosition().y);
        
        //projectiles
        //for center + player.getRadius())
        pointofFire = Vector2f(player.getPosition().x + player.getRadius(),player.getPosition().y);
        if(shotTimer < 3){
            shotTimer++;
        }
        if(Mouse::isButtonPressed(Mouse::Left) && shotTimer >= 3){
            
            bullet.setPosition((pointofFire));
            bullets.push_back(CircleShape(bullet));
            
            
            shotTimer = 0;
        }
        for(int i = 0; i < bullets.size(); i++){
            
            bullets[i].move(0.f,-1.f);
            if(bullets[i].getPosition().y < 0){
                bullets.erase(bullets.begin() + i);
            }
            
            
        }
        
        //enemies updated
        if(enemySpawnTimer < 20){
            enemySpawnTimer++;
        }
        
        if(enemySpawnTimer >=20){
            
            badguy.setPosition((rand()% int(window.getSize().x - badguy.getSize().x)),0.f);
            baddies.push_back(RectangleShape(badguy));
            enemySpawnTimer = 0;
        }
       
        for(int i = 0; i < bullets.size(); i++){
            
            bullets[i].move(0.f,-10.f);
            if(bullets[i].getPosition().y < 0){
                bullets.erase(bullets.begin() + i);
            }
            
        }
        for(int i = 0; i < baddies.size(); i++){
            baddies[i].move(0, 5.f);
            if(baddies[i].getPosition().y > window.getSize().y ||player.getGlobalBounds().intersects(baddies[i].getGlobalBounds())){
                baddies.erase(baddies.begin() + i);
                score--;
                if (score < 0) {
                    score = 0;
                }
            }
        }
        
        //collding stuff
        for(int i = 0; i < bullets.size(); i++){
            for(int k = 0; k < baddies.size(); k++){
                if(bullets[i].getGlobalBounds().intersects(baddies[k].getGlobalBounds())){
                    
                    bullets.erase(bullets.begin() + i);
                    baddies.erase(baddies.begin() + k);
                    
                    score++;
                    break;
                }
                
            }
            
        }
        
        //draw
        
        window.clear();
        //background
        window.draw(bg);
        //score
        tally.setPosition(5,-30);
        window.draw(tally);
        //player
        window.draw(player);
        
        //enemies
        for(int i = 0; i < baddies.size(); i++){
            window.draw(baddies[i]);
            
        }
        //bullets
        for(int i = 0; i < bullets.size(); i++){
            window.draw(bullets[i]);
            
        }
        
        window.display();
        
    }
    
    return 0;
    
}


