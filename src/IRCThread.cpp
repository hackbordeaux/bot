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
#include "IRCThread.h"

IRCThread::IRCThread(const std::string channel, const std::string nick)
{
	m_iis.channel = channel;
	m_iis.nick = nick;
}

void IRCThread::run(const char *server, unsigned short port)
{
	irc_callbacks_t callbacks;
	irc_session_t *s;

	memset (&callbacks, 0, sizeof(callbacks));

	callbacks.event_connect = &IRCThread::event_connect;
	callbacks.event_join = &IRCThread::event_join;
	//callbacks.event_nick = dump_event;

	s = irc_create_session (&callbacks);

	if (!s) {
		std::cout << "Could not create session" << std::endl;
		return;
	}

	irc_set_ctx(s, &m_iis);

	if (server[0] == '#' && server[1] == '#' ) {
		server++;

		irc_option_set(s, LIBIRC_OPTION_SSL_NO_VERIFY);
	}

	// Initiate the IRC server connection
	if (irc_connect(s, server, port, 0, m_iis.nick.c_str(), 0, 0)) {
		std::cout << "Could not connect " << irc_strerror(irc_errno(s)) << std::endl;
		return;
	}

	if (irc_run(s)) {
		std::cout << "Could not connect or I/O error: " << irc_strerror(irc_errno(s)) << std::endl;
		return;
	}
}

void IRCThread::event_connect(irc_session_t *session, const char *event, const char *origin,
			const char **params, unsigned int count)
{

}

void IRCThread::event_join(irc_session_t *session, const char *event, const char *origin,
			const char **params, unsigned int count)
{

}