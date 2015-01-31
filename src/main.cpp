#include "UtttGame.hpp"

#include <iostream>
#include <random>
#include <ctime>
#include <array>

#include <SFML/Graphics.hpp>


#define NROUNDS 100000


std::default_random_engine rnd;


int main(void) {
    rnd.seed(time(NULL));

    std::vector<std::pair<std::vector<unsigned>, unsigned>> data;

    for (auto n=0u; n<NROUNDS; ++n) {
        UtttGame game;
        short player = 1;

        std::vector<unsigned> slots;
        slots.reserve(81);

        for (auto i=0u; i<81; ++i)
            slots.push_back(i);

        while (game.getWinner() == 0) {
            slots = game.play(player, slots[rnd() % slots.size()]);
            player = player ^ 0x03;
        }

        data.push_back(std::make_pair(game.getHistory(), game.getWinner()));

        printf("%0.2f%%\r", (float)(n*100)/NROUNDS);
    }

    connections.resize(80);

    for (auto& entry : data) {
        if (entry.second == 1) {
            for (auto i=0u; i<entry.first.size()-1; ++i)
                connections[i][entry.first[i]][entry.first[i+1]] += 1.0f;
        }
    }

    sf::Texture textures[80];
    sf::Sprite sprites[80];

    sf::Vertex vertices[6561];
    sf::RenderTexture renderTexture;
    renderTexture.create(83, 83);

    for (auto j=0u; j<80; ++j) {
        renderTexture.clear(sf::Color(255, 0, 0));
        for (auto i=0u; i<6561; ++i) {
            unsigned col = connections[j][i%81][i/81];
            vertices[i] = sf::Vertex(sf::Vector2f(1+(i%81), 2+(i/81)), sf::Color(col, col, col));
        }
        renderTexture.draw(vertices, 6561, sf::Points);
        renderTexture.display();
        textures[j] = renderTexture.getTexture();
        sprites[j].setTexture(textures[j]);
        sprites[j].setPosition((j%10)*90, (j/10)*90);
    }

    // Declare and create a new window
    sf::RenderWindow window(sf::VideoMode(900, 720), "SFML window");
    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);
    // The main loop - ends as soon as the window is closed
    while (window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
           // Request for closing the window
           if (event.type == sf::Event::Closed)
               window.close();
        }
        // Activate the window for OpenGL rendering
        window.setActive();

        for (auto i=0u; i<80; ++i)
            window.draw(sprites[i]);

        // End the current frame and display its contents on screen
        window.display();
    }

    return 0;
}
