
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"
#include <iostream>
#include "ResourcePath.hpp"

int main()
{
    // setup window
    sf::Vector2i screenDimensions(832, 216);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Intelligence");
    window.setFramerateLimit(60);
    
    sf::Texture cityStreetTexture;
    if(!cityStreetTexture.loadFromFile(resourcePath() + "PunisherCity.png"))
    {
        std::cout << "Failed to load background spritesheet!" << std::endl;
        return 0;
    }
    sf::Sprite backgroundSprite(cityStreetTexture);

    
    // load texture (spritesheet)
    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile(resourcePath() + "cloudyg.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }
    
    sf::Texture xemnasTexture;
    if (!xemnasTexture.loadFromFile(resourcePath() + "Xemnas.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }
    
    // set up the animations for all four directions (set spritesheet and push frames)
    Animation cloudAnimationDown;
    cloudAnimationDown.setSpriteSheet(cloudTexture);
    cloudAnimationDown.addFrame(sf::IntRect(64, 0, 64, 64));
    cloudAnimationDown.addFrame(sf::IntRect(128, 0, 64, 64));
    cloudAnimationDown.addFrame(sf::IntRect(192, 0, 64, 64));
    cloudAnimationDown.addFrame(sf::IntRect( 0, 0, 64, 64));
    
    Animation cloudAnimationLeft;
    cloudAnimationLeft.setSpriteSheet(cloudTexture);
    cloudAnimationLeft.addFrame(sf::IntRect(64, 64, 64, 64));
    cloudAnimationLeft.addFrame(sf::IntRect(128, 64, 64, 64));
    cloudAnimationLeft.addFrame(sf::IntRect(192, 64, 64, 64));
    cloudAnimationLeft.addFrame(sf::IntRect( 0, 64, 64, 64));
    
    Animation cloudAnimationRight;
    cloudAnimationRight.setSpriteSheet(cloudTexture);
    cloudAnimationRight.addFrame(sf::IntRect(64, 128, 64, 64));
    cloudAnimationRight.addFrame(sf::IntRect(128, 128, 64, 64));
    cloudAnimationRight.addFrame(sf::IntRect(192, 128, 64, 64));
    cloudAnimationRight.addFrame(sf::IntRect( 0, 128, 64, 64));
    
    Animation cloudAnimationUp;
    cloudAnimationUp.setSpriteSheet(cloudTexture);
    cloudAnimationUp.addFrame(sf::IntRect(64, 192, 64, 64));
    cloudAnimationUp.addFrame(sf::IntRect(128, 192, 64, 64));
    cloudAnimationUp.addFrame(sf::IntRect(192, 192, 64, 64));
    cloudAnimationUp.addFrame(sf::IntRect( 0, 192, 64, 64));
    
    Animation xemnasAnimationDown;
    xemnasAnimationDown.setSpriteSheet(xemnasTexture);
    xemnasAnimationDown.addFrame(sf::IntRect(64, 0, 64, 64));
    xemnasAnimationDown.addFrame(sf::IntRect(128, 0, 64, 64));
    xemnasAnimationDown.addFrame(sf::IntRect(192, 0, 64, 64));
    xemnasAnimationDown.addFrame(sf::IntRect( 0, 0, 64, 64));
    
    Animation xemnasAnimationLeft;
    xemnasAnimationLeft.setSpriteSheet(xemnasTexture);
    xemnasAnimationLeft.addFrame(sf::IntRect(64, 64, 64, 64));
    xemnasAnimationLeft.addFrame(sf::IntRect(128, 64, 64, 64));
    xemnasAnimationLeft.addFrame(sf::IntRect(192, 64, 64, 64));
    xemnasAnimationLeft.addFrame(sf::IntRect( 0, 64, 64, 64));
    
    Animation xemnasAnimationRight;
    xemnasAnimationRight.setSpriteSheet(xemnasTexture);
    xemnasAnimationRight.addFrame(sf::IntRect(64, 128, 64, 64));
    xemnasAnimationRight.addFrame(sf::IntRect(128, 128, 64, 64));
    xemnasAnimationRight.addFrame(sf::IntRect(192, 128, 64, 64));
    xemnasAnimationRight.addFrame(sf::IntRect( 0, 128, 64, 64));
    
    Animation xemnasAnimationUp;
    xemnasAnimationUp.setSpriteSheet(xemnasTexture);
    xemnasAnimationUp.addFrame(sf::IntRect(64, 192, 64, 64));
    xemnasAnimationUp.addFrame(sf::IntRect(128, 192, 64, 64));
    xemnasAnimationUp.addFrame(sf::IntRect(192, 192, 64, 64));
    xemnasAnimationUp.addFrame(sf::IntRect( 0, 192, 64, 64));
    
    Animation* currentCloudAnim = &cloudAnimationDown;
    Animation* currentXemnasAnim = &xemnasAnimationDown;
    
    // set up AnimatedSprite
    AnimatedSprite cloudSprite(sf::seconds(0.2), true, false);
    cloudSprite.setPosition(sf::Vector2f(screenDimensions / 3));
    
    AnimatedSprite xemnasSprite(sf::seconds(0.2), true, false);
    xemnasSprite.setPosition(sf::Vector2f(screenDimensions * 2 / 3));
    
    sf::Clock frameClock;
    
    float speed = 80.f;
    bool noKeyWasPressed = true;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        
        sf::Time frameTime = frameClock.restart();
        
        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            currentCloudAnim = &cloudAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            currentCloudAnim = &cloudAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            currentCloudAnim = &cloudAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            currentCloudAnim = &cloudAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
        
        
        
        cloudSprite.play(*currentCloudAnim);
        xemnasSprite.play(*currentXemnasAnim);
        cloudSprite.move(movement * frameTime.asSeconds());
        xemnasSprite.move(movement * frameTime.asSeconds());
        
        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            cloudSprite.stop();
        }
        noKeyWasPressed = true;
        
        // update AnimatedSprite
        cloudSprite.update(frameTime);
        xemnasSprite.update(frameTime);
        
        // draw
        window.clear();
        window.draw(backgroundSprite);
        window.draw(cloudSprite);
        window.draw(xemnasSprite);
        window.display();
    }
    
    return 0;
}
