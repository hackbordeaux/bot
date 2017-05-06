#include <iostream>
#include "Query.h"



/**
  * callback function to be called when the curl request is done
  * has to match a certain prototype
  * let's assume ptr contains the result of curl request_weather
  * size might contain the size of ptr
  * and so on...
  */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  //parse some things
  std::cout << "Hello World!" << std::endl;
  return 0;
}


bool curl_request(const std::string *url) {

  CURL *easyhandle = curl_easy_init();
  std::string  *dataRes;
  char errorBuffer[CURL_ERROR_SIZE];
  //curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_callback);
  //curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, dataRes);
  curl_easy_setopt(easyhandle, CURLOPT_URL, url);
  curl_easy_setopt(easyhandle, CURLOPT_ERRORBUFFER, errorBuffer);
  errorBuffer[0] = 0;
  curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L); //for debugging purposes
  CURLcode success = curl_easy_perform(easyhandle);
  if(success != CURLE_OK) {
    //handling some errors
    std::cout << "dommage essaie encore :(" << std::endl;
    size_t len = strlen(errorBuffer);
    fprintf(stderr, "\nlibcurl: %d", success);
    if(len)
      fprintf(stderr, "%s%s", errorBuffer, ((errorBuffer[len - 1] != '\n') ? "\n" : ""));
    else
      fprintf(stderr, "%s\n", curl_easy_strerror(success));
    curl_easy_cleanup(easyhandle);
    return false;
  }
  curl_easy_cleanup(easyhandle);
  return true;
}


bool request_weather(std::string args[]) {
  std::string APIKEY = "55c7136ab4700ab6c1c6a23122a9b7a";
  const std::string url = "http://google.com";
  curl_request(&url);
  return true;
}
