#include <time.h>

#include "tetramino.h"
#include "drawingsystem.h"

Tetramino* instantiateTetramino(GameField&, DrawingSystem&);

int main()
{
    // Object, that actually is main window of our application
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");

    GameField *gameField = new GameField(10, 20);
    DrawingSystem ds;

    srand(time(0));

    Tetramino *tetramino = instantiateTetramino(*gameField, ds);

    // timer and delaying variables
    float timer = 0.f, delay = 0.3f;

    // clock
    sf::Clock clock;

    // Main app loop. Run while the window is open
    while(window.isOpen())
    {
        // get time, passed from countdown beginning, and convert it to seconds
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Work out the queue of events in the loop
        sf::Event event;
        while(window.pollEvent(event))
        {
            // User wants to close the window?
            if (event.type == sf::Event::Closed)
                // then close it
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    tetramino->rotate(gameField);
                else if (event.key.code == sf::Keyboard::Left)
                    tetramino->moveH(-1);
                else if (event.key.code == sf::Keyboard::Right)
                    tetramino->moveH(1);
            }
        }

        // moving tetramino down (timer thick)
        if (timer > delay)
        {
            bool reachedBottom = !tetramino->moveV(1);
            timer = 0.f;

            if (reachedBottom)
            {
                tetramino->parcelling();
                delete tetramino;
                tetramino = instantiateTetramino(*gameField, ds);
                gameField->checkRowsFilling(ds);

                std::cout << "Highest tile level: " << gameField->getHighestLevel() << std::endl;
            }
        }

        // set window background color
        window.clear(sf::Color::White);

        //for (int tileIndex = 0; tileIndex < Tetramino::TILES_COUNT; tileIndex++)
        //    window.draw(tetramino->getTileSprite(tileIndex));

        //std::cout << "Fooo\n";
        for (const Tile* drawObject : ds.drawable)
        {
            if (drawObject == nullptr)
                std::cout << "Tile not exist\n";
            window.draw(drawObject->getSprite());
        }
        window.draw(gameField->getBorderShape());
        //std::cout << "Bar\n";

        window.display();
    }

    delete gameField;
    delete tetramino;

    return 0;
}

Tetramino* instantiateTetramino(GameField &gameField, DrawingSystem &ds)
{
    const sf::Color *tileColor = &Tile::COLORS[rand() % Tile::COLORS_COUNT];
    int tileFigure = rand() % Tetramino::FIGURES_COUNT;

    Tetramino *instance = new Tetramino(gameField, tileFigure, *tileColor);
    for (int tileIndex = 0; tileIndex < Tetramino::TILES_COUNT; tileIndex++)
    {
        ds.drawable.push_front(&instance->getTile(tileIndex));
    }
    return instance;
}
