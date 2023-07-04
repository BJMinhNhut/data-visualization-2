//
// Created by MINH NHUT on 6/8/2023.
//

#include "Application.hpp"
#include "States/States.hpp"
#include "State.hpp"
#include "Constants.hpp"

#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

#ifdef SFML_DEBUG
const std::string Application::dataPrefix = "../";
#else
const std::string Application::dataPrefix = "";
#endif

Application::Application()
        : mWindow(sf::VideoMode(1600, 900), "Data Visualization 2", sf::Style::Close,
                  sf::ContextSettings(0, 0, 4)),
#ifdef SFML_DEBUG
          mStatisticsText(),
          mStatisticsUpdateTime(),
          mStatisticsNumFrames(0),
#endif
          mTextures(),
          mFonts(),
          mColors(),
          mStateStack(State::Context(mWindow, mTextures, mFonts, mColors)) {

    mFonts.load(Fonts::Main, dataPrefix + "resources/fonts/DMSans-Regular.ttf");
    mFonts.load(Fonts::Bold, dataPrefix + "resources/fonts/DMSans-Bold.ttf");
    mFonts.load(Fonts::Mono, dataPrefix + "resources/fonts/UbuntuMono-Regular.ttf");

    loadIcon();
    loadImages();
    loadColors();

#ifdef SFML_DEBUG
    mStatisticsText.setFont(mFonts.get(Fonts::Main));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setFillColor(sf::Color::Black);
    mStatisticsText.setCharacterSize(13u);
#endif

    registerStates();
    mStateStack.pushState(States::Menu);
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if (mStateStack.isEmpty())
                mWindow.close();
        }
#ifdef SFML_DEBUG
        updateStatistics(dt);
#endif
        render();
    }
}

void Application::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt) {
    mStateStack.update(dt);
}

void Application::render() {
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);

    mWindow.display();
}

#ifdef SFML_DEBUG

void Application::updateStatistics(sf::Time dt) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.f)) {
        mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.f);
        mStatisticsNumFrames = 0;
    }
}

#endif

void Application::registerStates() {
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<AboutState>(States::About);
}

void Application::loadIcon() {
    sf::Image image;
    if (!image.loadFromFile(dataPrefix + "resources/images/icon.png")) {
        throw std::runtime_error("Icon load unsucessfully!");
    }
    mWindow.setIcon(image.getSize().x, image.getSize().y,
                    image.getPixelsPtr());
}

void Application::loadImages() {
    for (int id = 0; id < Textures::NumTextures; ++id) {
        std::string imagePaths = dataPrefix + "resources/images/" + Constants::imageNames[id];
        std::cerr << "Loaded: " << imagePaths << '\n';
        mTextures.load(static_cast<Textures::ID>(id), imagePaths);
    }
}

void Application::loadColors() {
    mColors.load(Colors::Text, Constants::mBlack);
    mColors.load(Colors::UIPrimary, Constants::WhiteUI);
    mColors.load(Colors::UISecondary, Constants::WhiteDisplay);
    mColors.load(Colors::UIBorder, Constants::GrayBorder);
    mColors.load(Colors::Highlight, Constants::YellowLight);
    mColors.load(Colors::Red, Constants::RedDark);
    mColors.load(Colors::Blue, Constants::BlueDark);
}