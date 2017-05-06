#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "json.hpp"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
bool curl_request(std::string *url);
bool request_weather(std::string args[]);
