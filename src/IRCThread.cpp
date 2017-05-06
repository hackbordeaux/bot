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

#include <cstring>
#include <thread>
#include "IRCThread.h"

IRCThread::IRCThread(const std::string channel, const std::string nick)
{
	m_iis.channel = channel;
	m_iis.nick = nick;
}

void IRCThread::run(const char *server, unsigned short port)
{
	irc_callbacks_t callbacks = { 0 };
	irc_session_t *s;

	callbacks.event_connect = &IRCThread::event_connect;
	callbacks.event_join = &IRCThread::event_join;
	//callbacks.event_nick = dump_event;
	//callbacks.event_numeric = &IRCThread::event_numeric;

	std::thread(&IRCThread::connect);
}

void IRCThread::connect(irc_callbacks_t callbacks, const char *server, unsigned short port)
{
	std::cout << "Debut du thread connexion" << std::endl;
	while (m_run) {
		m_irc_session = irc_create_session(&callbacks);

		if (!m_irc_session) {
			std::cout << "Could not create session" << std::endl;
			return;
		}

		irc_set_ctx(m_irc_session, &m_iis);

		if (server[0] == '#' && server[1] == '#') {
			server++;

			irc_option_set(m_irc_session, LIBIRC_OPTION_SSL_NO_VERIFY);
		}

		std::cout << "Connection wait...";
		// Initiate the IRC server connection
		if (irc_connect(m_irc_session, server, port, 0, m_iis.nick.c_str(), 0, 0)) {
			std::cout << std::endl << "Could not connect " << irc_strerror(irc_errno(m_irc_session)) << std::endl;
			return;
		}

		std::cout << "..." << std::endl;

		if (irc_run(m_irc_session)) {
			std::cout << "Could not connect or I/O error: " << irc_strerror(irc_errno(m_irc_session)) << std::endl;
			return;
		}

		std::cout << "Connection done !" << std::endl;
	}
}

void IRCThread::event_connect(irc_session_t *session, const char *event, const char *origin,
			const char **params, unsigned int count)
{
	if (!irc_is_connected(session)) {
		std::cout << "Not connected to IRC" << std::endl;
	}
	std::cout << "Connected to IRC" << std::endl;
}

void IRCThread::event_join(irc_session_t *session, const char *event, const char *origin,
			const char **params, unsigned int count)
{

}

void IRCThread::event_numeric(irc_session_t *session, const char *event, const char *origin,
			const char **params, unsigned int count)
{

}