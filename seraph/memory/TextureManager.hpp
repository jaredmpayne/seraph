#pragma once

#include <filesystem>
#include <memory>

#include <SFML/Graphics.hpp>

#include <seraph/memory/ResourceManager.hpp>

class TextureManager : public ResourceManager<sf::Texture> {

public:

    static TextureManager &instance() noexcept {
        static auto instance = TextureManager();
        return instance;
    }

    virtual inline std::shared_ptr<sf::Texture> make(const std::filesystem::path &path) override {
        return std::make_shared<sf::Texture>(path);
    }

private:

    TextureManager() noexcept = default;
};
