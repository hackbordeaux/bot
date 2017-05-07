/**
 * Copyright (c) 2017, Vincent Glize <vincent.glize@live.fr>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "HttpServer.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <json/json.h>
/*
HttpServer::HttpServer(IRCThread *irc_thread) : m_irc_thread(irc_thread)
{}
 */

bool HttpServer::get_json(Json::Value &json_value, const std::string &url)
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_curl = curl_easy_init();

	curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, curl_writer);
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_data);

	bool success = curl_easy_perform(m_curl);
	if (success) {
		std::cerr << "curl error" << std::endl;
	}

	curl_easy_cleanup(m_curl);
	curl_global_cleanup();

	Json::Reader *reader = new Json::Reader();
	if (!reader->parse(m_data, json_value)) {
		std::cerr << "Error parse" << std::endl;
		return false;
	}

	running = false;

	return true;
}

size_t HttpServer::curl_writer(char *data, size_t size, size_t nmemb, void *read_buffer)
{
	size_t realsize = size * nmemb;
	((std::string *) read_buffer)->append((const char *) data, realsize);
	return realsize;
}