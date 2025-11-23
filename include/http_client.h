#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <string>

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    std::string get(const std::string& url);
    std::string post(const std::string& url, const std::string& jsonBody);

private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif
