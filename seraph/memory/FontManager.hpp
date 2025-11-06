#pragma once

#include <filesystem>
#include <memory>

#include <SFML/Graphics.hpp>

#include <seraph/memory/ResourceManager.hpp>

class FontManager : public ResourceManager<sf::Font> {

public:

    static FontManager &instance() noexcept {
        static auto instance = FontManager();
        return instance;
    }

    virtual inline std::shared_ptr<sf::Font> make(const std::filesystem::path &path) override {
        return std::make_shared<sf::Font>(path);
    }

private:

    FontManager() noexcept = default;
};
