#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>

std::string trim(const std::string &str) {
    const char *whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

float getRandomY() {
    return static_cast<float>(50 + std::rand() % 400);
}

struct Word {
    std::string text;
    sf::Text displayText;
    float x, y, speed;
};

void saveGame(int score, int lives, float baseSpeed, int fontSize, const std::vector<Word> &words) {
    std::ofstream file("save.txt");
    if (!file.is_open()) return;
    file << score << " " << lives << " " << baseSpeed << " " << fontSize << "\n";
    for (const auto &word: words) {
        file << word.text << " " << word.x << " " << word.y << " " << word.speed << "\n";
    }
}

void loadGame(int &score, int &lives, float &baseSpeed, int &fontSize, std::vector<Word> &words, sf::Font &font) {
    std::ifstream file("save.txt");
    if (!file.is_open()) return;
    words.clear();
    file >> score >> lives >> baseSpeed >> fontSize;
    std::string wordText;
    float x, y, speed;
    while (file >> wordText >> x >> y >> speed) {
        Word w;
        w.text = wordText;
        w.x = x;
        w.y = y;
        w.speed = speed;
        w.displayText.setFont(font);
        w.displayText.setCharacterSize(fontSize);
        w.displayText.setString(w.text);
        w.displayText.setFillColor(sf::Color::White);
        w.displayText.setPosition(w.x, w.y);
        words.push_back(w);
    }
}


int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    //auto comic = sf::Font("C:Users/panah/CLionProjects/untitled/MonkeyTyperSFML/comic.ttf");

    sf::Font fontArial, fontComic, fontTimes;
    if (!fontArial.loadFromFile("arial.ttf") ||
    !fontComic.loadFromFile("comic.ttf") ||
    !fontTimes.loadFromFile("times.ttf")) {
        std::cerr << "Font files not found!" << std::endl;
        return 1;
    }

    sf::Font *currentFont = &fontArial;

    std::ifstream wordFile("C:/Users/panah/CLionProjects/untitled/MonkeyTyperSFML/words.txt");
    std::vector<std::string> wordList;
    std::string line;
    while (std::getline(wordFile, line)) {
        if (!line.empty()) wordList.push_back(line);
    }
    if (wordList.empty()) {
        std::cerr << "words.txt is missing or empty!" << std::endl;
        return 1;
    }

    int highScore = 0;
    std::ifstream hsFile("highscore.txt");
    if (hsFile.is_open()) {
        hsFile >> highScore;
        hsFile.close();
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Monkey Typer");
    window.setFramerateLimit(60);

    std::vector<sf::CircleShape> stars;
    for (int i = 0; i < 100; ++i) {
        sf::CircleShape star(1);
        star.setFillColor(sf::Color::White);
        star.setPosition(rand() % 800, rand() % 600);
        stars.push_back(star);
    }

    sf::Text inputText, scoreText, highScoreText, livesText;
    sf::Text labelScore, labelMissed, labelBest;

    while (window.isOpen()) {
        int score = 0;
        int lives = 3;
        int fontSize = 30;
        float baseSpeed = 1.0f;
        float spawnInterval = 2.0f;
        std::string userInput = "";
        std::vector<Word> activeWords;

        auto applySizeOnly = [&]() {
            inputText.setCharacterSize(fontSize);
            for (auto &word: activeWords) {
                word.displayText.setCharacterSize(fontSize);
            }
        };



        sf::Clock spawnClock, difficultyClock;

        inputText.setFont(*currentFont);
        inputText.setCharacterSize(28);
        inputText.setFillColor(sf::Color::Green);
        inputText.setPosition(550, 515); // moved lower to avoid collision

        scoreText.setFont(*currentFont);
        scoreText.setCharacterSize(22);
        scoreText.setFillColor(sf::Color::Yellow);
        scoreText.setPosition(20, 540);

        livesText.setFont(*currentFont);
        livesText.setCharacterSize(22);
        livesText.setFillColor(sf::Color::Red);
        livesText.setPosition(220, 540);

        highScoreText.setFont(*currentFont);
        highScoreText.setCharacterSize(22);
        highScoreText.setFillColor(sf::Color::Cyan);
        highScoreText.setPosition(420, 540);

        labelScore.setFont(*currentFont);
        labelScore.setCharacterSize(20);
        labelScore.setFillColor(sf::Color::White);
        labelScore.setString("Score:");
        labelScore.setPosition(20, 515);

        labelMissed.setFont(*currentFont);
        labelMissed.setCharacterSize(20);
        labelMissed.setFillColor(sf::Color::White);
        labelMissed.setString("Missed:");
        labelMissed.setPosition(220, 515);

        labelBest.setFont(*currentFont);
        for (auto &word: activeWords) {
            word.displayText.setFont(*currentFont);
        }
        labelBest.setCharacterSize(20);
        labelBest.setFillColor(sf::Color::White);
        labelBest.setString("Best:");
        labelBest.setPosition(420, 515);

        bool playing = true;
        while (playing) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    return 0;
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        if (!userInput.empty()) userInput.pop_back();
                    } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                        userInput += static_cast<char>(event.text.unicode);
                    }
                }

                // Increase game difficulty every 15 seconds
                if (difficultyClock.getElapsedTime().asSeconds() > 15.f) {
                    if (baseSpeed < 5.0f) baseSpeed += 0.3f;
                    if (spawnInterval > 0.5f) spawnInterval -= 0.2f;

                    std::cout << "[INFO] Difficulty increased. Speed: " << baseSpeed << ", Interval: " << spawnInterval
                            << std::endl;

                    difficultyClock.restart();
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::F1 && fontSize > 10) {
                        fontSize -= 2;
                        applySizeOnly(); // update fonts with new size
                    }
                    if (event.key.code == sf::Keyboard::F2 && fontSize < 60) {
                        fontSize += 2;
                        applySizeOnly();
                    }
                    if (event.key.code == sf::Keyboard::F3 && baseSpeed > 0.5f) {
                        baseSpeed -= 0.2f;
                        for (auto &word: activeWords) {
                            word.speed = baseSpeed; // apply speed to all existing words
                        }
                        std::cout << "[INFO] Speed decreased: " << baseSpeed << std::endl;
                    }
                    if (event.key.code == sf::Keyboard::F4 && baseSpeed < 5.0f) {
                        baseSpeed += 0.2f;
                        for (auto &word: activeWords) {
                            word.speed = baseSpeed;
                        }
                        std::cout << "[INFO] Speed increased: " << baseSpeed << std::endl;
                    }
                    if (event.key.code == sf::Keyboard::F5) {
                        saveGame(score, lives, baseSpeed, fontSize, activeWords);
                        std::cout << "[INFO] Game saved" << std::endl;
                    }
                    if (event.key.code == sf::Keyboard::F6) {
                        loadGame(score, lives, baseSpeed, fontSize, activeWords, *currentFont);
                        applySizeOnly();
                        std::cout << "[INFO] Game loaded" << std::endl;
                    }


                    if (event.key.code == sf::Keyboard::F7) {
                        currentFont = &fontComic;
                    }
                    if (event.key.code == sf::Keyboard::F8) {
                        currentFont = &fontTimes;
                    }

                    if (event.key.code == sf::Keyboard::F9) {
                        currentFont = &fontArial;
                    }
                    // apply font change
                    inputText.setFont(*currentFont);
                    scoreText.setFont(*currentFont);
                    livesText.setFont(*currentFont);
                    highScoreText.setFont(*currentFont);
                    labelScore.setFont(*currentFont);
                    labelMissed.setFont(*currentFont);
                    labelBest.setFont(*currentFont);
                    for (auto &word: activeWords) {
                        word.displayText.setFont(*currentFont);
                    }
                }
            }


            if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
                std::string wordText = wordList[rand() % wordList.size()];
                Word w;
                w.text = wordText;
                w.x = 800.f;
                w.y = getRandomY();
                w.speed = baseSpeed;
                w.displayText.setFont(*currentFont);
                w.displayText.setCharacterSize(fontSize);
                w.displayText.setString(w.text);
                w.displayText.setFillColor(sf::Color::White);
                w.displayText.setPosition(w.x, w.y);
                activeWords.push_back(w);
                spawnClock.restart();
            }

            window.clear(sf::Color::Black);
            for (auto &star: stars) window.draw(star);

            sf::RectangleShape panel(sf::Vector2f(800, 100));
            panel.setPosition(0, 500);
            panel.setFillColor(sf::Color(30, 144, 255));
            window.draw(panel);

            for (auto &word: activeWords) {
                word.x -= word.speed;
                word.displayText.setPosition(word.x, word.y);
                window.draw(word.displayText);
            }

            for (auto it = activeWords.begin(); it != activeWords.end();) {
                if (trim(userInput) == it->text) {
                    score += 10;
                    userInput = "";
                    it = activeWords.erase(it);
                } else if (it->x + it->displayText.getGlobalBounds().width < 0) {
                    lives--;
                    it = activeWords.erase(it);
                } else {
                    ++it;
                }
            }

            inputText.setString(userInput);
            scoreText.setString(std::to_string(score));
            livesText.setString(std::to_string(3 - lives));
            highScoreText.setString(std::to_string(highScore));

            window.draw(labelScore);
            window.draw(labelMissed);
            window.draw(labelBest);
            window.draw(scoreText);
            window.draw(livesText);
            window.draw(highScoreText);
            window.draw(inputText);
            window.display();

            if (lives <= 0) {
                if (score > highScore) {
                    highScore = score;
                    std::ofstream hsOut("highscore.txt");
                    if (hsOut.is_open()) {
                        hsOut << highScore;
                        hsOut.close();
                    }
                }
                std::ofstream history("scores.txt", std::ios::app);
                if (history.is_open()) {
                    std::time_t now = std::time(nullptr);
                    history << "Score: " << score << " - " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
                            << std::endl;
                    history.close();
                }

                while (true) {
                    sf::Text gameOver("GAME OVER", *currentFont, 48);
                    gameOver.setFillColor(sf::Color::Red);
                    gameOver.setPosition(220, 200);
                    sf::Text prompt("Press R to Restart or Esc to Exit", *currentFont, 24);
                    prompt.setFillColor(sf::Color::White);
                    prompt.setPosition(180, 300);
                    window.clear();
                    window.draw(gameOver);
                    window.draw(prompt);
                    window.display();

                    sf::Event e;
                    while (window.pollEvent(e)) {
                        if (e.type == sf::Event::Closed) return 0;
                        if (e.type == sf::Event::KeyPressed) {
                            if (e.key.code == sf::Keyboard::Escape) return 0;
                            if (e.key.code == sf::Keyboard::R) playing = false;
                        }
                    }
                    if (!playing) break;
                }
            }
        }
    }

    return 0;
}
