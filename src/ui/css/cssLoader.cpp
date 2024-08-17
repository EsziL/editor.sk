#include "cssLoader.h"
#include "../etc/error.h"
#include "gtk/gtkcssprovider.h"
#include <curl/curl.h>
#include "../../util/util.h"
#include "../../main.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <regex>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace fs = std::filesystem;

std::string get_config_path() {
    #ifdef _WIN32
        // Windows
        char* app_data_dir = getenv("APPDATA");
        if (app_data_dir == nullptr) {
            return ".config/editor.sk/default.css";
        }
        return std::string(app_data_dir) + "\\editor.sk\\default.css";
    #elif __APPLE__
        // macOS
        std::string home_dir = std::getenv("HOME");
        if (home_dir.empty()) {
            return ".config/editor.sk/default.css";
        }
        return home_dir + "/Library/Application Support/editor.sk/default.css";
    #else
        // Linux
        std::string home_dir = std::getenv("HOME");
        if (home_dir.empty()) {
            return ".config/editor.sk/default.css";
        }
        return home_dir + "/.config/editor.sk/default.css";
    #endif
}

std::string extractVersion(const std::string& input) {
    std::regex versionRegex(R"(\/\*\s*VERSION:\s*(.*?)\s*\*\/)");
    std::smatch match;

    if (std::regex_search(input, match, versionRegex) && match.size() > 1) {
        return match[1];
    }

    return "";
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* out = static_cast<std::ofstream*>(userp);
    size_t totalSize = size * nmemb;
    out->write(static_cast<const char*>(contents), totalSize);
    return totalSize;
}

bool download_css_file(const std::string& url, const std::string& local_path) {
    try {
        fs::create_directories(fs::path(local_path).parent_path());

        std::ofstream file(local_path, std::ios::binary);
        if (!file.is_open()) {
            showError("Failed to open file for writing: " + local_path);
            return false;
        }

        CURL* curl;
        CURLcode res;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Follow redirects

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                showError("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
                return false;
            }

            curl_easy_cleanup(curl);
        }

        file.close();
        return true;
    } catch (const std::exception& e) {
        showError("Error downloading CSS file: " + std::string(e.what()));
        return false;
    }
}

std::string load_css_style() {
    std::string config_path = get_config_path();
    const std::string remote_url = "https://raw.githubusercontent.com/EsziL/editor.sk/main/src/ui/css/default.css";

    if (fs::exists(config_path)) {
        std::ifstream file(config_path, std::ios::binary);
        std::string css_style((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if (extractVersion(css_style) != version) {
            showError("CSS file is outdated. Downloading new version...");
            if (download_css_file(remote_url, config_path)) {
                std::ifstream file(config_path, std::ios::binary);
                std::string css_style((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                return css_style;
            } else {
                showError("Something went wrong while downloading the CSS file. This is probably because you are offline.");
                return "";
            }
        } 
        return css_style;
    } else {
        showError("Default CSS config file not found. Downloading...");

        if (download_css_file(remote_url, config_path)) {
            std::ifstream file(config_path, std::ios::binary);
            std::string css_style((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            return css_style;
        } else {
            showError("Something went wrong while downloading the CSS file. This is probably because you are offline.");
            return "";
        }
    }
}

void initCSS() {
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(cssProvider, R"(
    .errorBox {
        background-color: #ff6b6b;
        border-radius: 10px;
        animation: swoop-in 0.3s ease-in forwards;
    }
    .errorBox label {
        color: black;
        font-weight: 500;
    }
    )");
    gtk_css_provider_load_from_string(cssProvider, load_css_style().c_str());
    std::basic_string<char> style = *std::prev(split(get_config_path(), '/').end());
    if (fs::exists(style)) {
        gtk_css_provider_load_from_path(cssProvider, style.c_str());
    }
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}
