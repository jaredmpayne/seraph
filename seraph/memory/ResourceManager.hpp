#pragma once

#include <filesystem>
#include <format>
#include <memory>
#include <unordered_map>

#include <seraph/core/Exception.hpp>

template <typename T>
class ResourceManager {

public:

    std::shared_ptr<T> get(const std::filesystem::path &path) {
        if (const auto it = m_resources.find(path); it != m_resources.end()) {
            if (const auto resource = it->second.lock()) {
                return resource;
            }
        }
        try {
            const auto resource = make(path);
            m_resources[path] = resource;
            return resource;
        }
        catch (const sf::Exception &exception) {
            throw Exception(std::format("Unable to create resource from file at path {}", path.string()));
        }
    }

    virtual inline std::shared_ptr<T> make(const std::filesystem::path &path) = 0;

// private:

    std::unordered_map<std::filesystem::path, std::weak_ptr<T>> m_resources;
};
