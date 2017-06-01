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

#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

struct IRCChannelConfig
{
	bool is_passive = false;
	bool all_commands_allowed = true;
	std::vector<std::string> allowed_commands = {};
	std::string gitlab_project_name = "";
	std::string gitlab_project_namespace = "";
	std::vector<std::string> gitlab_writers = {};
};

typedef std::unordered_map<std::string, IRCChannelConfig*> IRCChannelConfigs;

class Config {
public:
	Config() {};
	~Config();

	bool load_configuration();

	bool is_httpd_enabled() const
	{
		return m_httpd_enabled;
	}

	void set_httpd_enabled(bool m_httpd_enabled)
	{
		Config::m_httpd_enabled = m_httpd_enabled;
	}

	uint16_t getM_httpd_port() const
	{
		return m_httpd_port;
	}

	void set_httpd_port(uint16_t m_httpd_port)
	{
		Config::m_httpd_port = m_httpd_port;
	}

	const std::string &getM_irc_name() const
	{
		return m_irc_name;
	}

	void set_irc_name(const std::string &m_irc_name)
	{
		Config::m_irc_name = m_irc_name;
	}

	const std::string &getM_irc_password() const
	{
		return m_irc_password;
	}

	void set_irc_password(const std::string &m_irc_password)
	{
		Config::m_irc_password = m_irc_password;
	}

	const std::string &getM_irc_server() const
	{
		return m_irc_server;
	}

	void set_irc_server(const std::string &m_irc_server)
	{
		Config::m_irc_server = m_irc_server;
	}

	bool isM_irc_enabled() const
	{
		return m_irc_enabled;
	}

	void set_irc_enabled(bool m_irc_enabled)
	{
		Config::m_irc_enabled = m_irc_enabled;
	}

	uint16_t getM_irc_port() const
	{
		return m_irc_port;
	}

	void set_irc_port(uint16_t m_irc_port)
	{
		Config::m_irc_port = m_irc_port;
	}

	const IRCChannelConfigs &getM_irc_channel_configs() const
	{
		return m_irc_channel_configs;
	}

	void set_irc_channel_configs(const IRCChannelConfigs &m_irc_channel_configs)
	{
		Config::m_irc_channel_configs = m_irc_channel_configs;
	}

	uint32_t getM_max_http_response_size() const
	{
		return m_max_http_response_size;
	}

	void set_max_http_response_size(uint32_t m_max_http_response_size)
	{
		Config::m_max_http_response_size = m_max_http_response_size;
	}

	const std::string &getM_openweathermap_api_key() const
	{
		return m_openweathermap_api_key;
	}

	void set_openweathermap_api_key(const std::string &m_openweathermap_api_key)
	{
		Config::m_openweathermap_api_key = m_openweathermap_api_key;
	}

	const std::string &getM_gitlab_api_key() const
	{
		return m_gitlab_api_key;
	}

	void set_gitlab_api_key(const std::string &m_gitlab_api_key)
	{
		Config::m_gitlab_api_key = m_gitlab_api_key;
	}

	const std::string &getM_gitlab_uri() const
	{
		return m_gitlab_uri;
	}

	void set_gitlab_uri(const std::string &m_gitlab_uri)
	{
		Config::m_gitlab_uri = m_gitlab_uri;
	}

	const std::string &getTwitter_consumer_key() const
	{
		return twitter_consumer_key;
	}

	void setTwitter_consumer_key(const std::string &twitter_consumer_key)
	{
		Config::twitter_consumer_key = twitter_consumer_key;
	}

	const std::string &getTwitter_consumer_secret() const
	{
		return twitter_consumer_secret;
	}

	void setTwitter_consumer_secret(const std::string &twitter_consumer_secret)
	{
		Config::twitter_consumer_secret = twitter_consumer_secret;
	}

	const std::string &getTwitter_access_token() const
	{
		return twitter_access_token;
	}

	void setTwitter_access_token(const std::string &twitter_access_token)
	{
		Config::twitter_access_token = twitter_access_token;
	}

	const std::string &getTwitter_access_token_secret() const
	{
		return twitter_access_token_secret;
	}

	void setTwitter_access_token_secret(const std::string &twitter_access_token_secret)
	{
		Config::twitter_access_token_secret = twitter_access_token_secret;
	}

private:
	bool m_httpd_enabled = true;
	uint16_t m_httpd_port = 8080;
	std::string m_irc_name = "mybot_name";
	std::string m_irc_password = "";
	std::string m_irc_server = "chat.freenode.net";
	bool m_irc_enabled = true;
	uint16_t m_irc_port = 6697;
	IRCChannelConfigs m_irc_channel_configs = {};
	uint32_t m_max_http_response_size = 100 * 1024;
	std::string m_openweathermap_api_key = "";
	std::string m_gitlab_api_key = "";
	std::string m_gitlab_uri = "";
	/*
	std::string m_redis_host = "localhost";
	uint16_t m_redis_port = 6379;
	 */

	std::string twitter_consumer_key = "";
	std::string twitter_consumer_secret = "";
	std::string twitter_access_token = "";
	std::string twitter_access_token_secret = "";


	const std::vector<std::string> get_irc_channels() const;
	const std::string get_channel_gitlab_project_name(const std::string &channel) const;
	const std::string get_channel_gitlab_project_namespace(const std::string &channel) const;

};
