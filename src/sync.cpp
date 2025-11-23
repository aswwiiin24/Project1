#include "sync.h"
#include "http_client.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Sync::upload(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in) {
        std::cout << "Local file not found: " << filePath << "\n";
        return;
    }

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();

    HttpClient hc;

    // POST to postman echo
    std::string response = hc.post(
        "https://postman-echo.com/post",
        content
    );

    std::cout << "Upload response:\n" << response << "\n";
}

void Sync::download() {
    HttpClient hc;

    // GET from postman echo
    std::string response = hc.get("https://postman-echo.com/get");

    std::cout << "Download response:\n" << response << "\n";
}
