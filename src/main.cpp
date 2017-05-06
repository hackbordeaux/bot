#include <iostream>
#include <libircclient/libircclient.h>
#include <libircclient/libirc_rfcnumeric.h>
#include <cstring>

struct irc_info_session {
	std::string channel;
	std::string nick;
};

void event_join (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	//dump_event (session, event, origin, params, count);
	irc_cmd_user_mode (session, "+i");
	irc_cmd_msg (session, params[0], "Salut le monde !");
}


void event_connect (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)
{
	irc_info_session * iis = (irc_info_session *) irc_get_ctx (session);
	//dump_event (session, event, origin, params, count);

	irc_cmd_join (session, iis->channel.c_str(), 0);
}

int main (int argc, char **argv)
{
	irc_callbacks_t	callbacks;
	irc_info_session iis;
	irc_session_t * s;
	unsigned short port;

	if ( argc != 4 )
	{
		printf ("Usage: %s <server> <nick> <channel>\n", argv[0]);
		return 1;
	}

	memset (&callbacks, 0, sizeof(callbacks));

	callbacks.event_connect = event_connect;
	callbacks.event_join = event_join;
	//callbacks.event_nick = dump_event;

	s = irc_create_session (&callbacks);

	if (!s) {
		printf ("Could not create session\n");
		return 1;
	}

	iis.channel = argv[3];
	iis.nick = argv[2];

	irc_set_ctx(s, &iis);

	if (strchr(argv[1], ':' ) != 0 )
		port = 0;

	if (argv[1][0] == '#' && argv[1][1] == '#' ) {
		argv[1]++;

		irc_option_set( s, LIBIRC_OPTION_SSL_NO_VERIFY );
	}

	// Initiate the IRC server connection
	if (irc_connect(s, argv[1], port, 0, argv[2], 0, 0)) {
		printf ("Could not connect: %s\n", irc_strerror (irc_errno(s)));
		return 1;
	}

	if (irc_run(s)) {
		printf ("Could not connect or I/O error: %s\n", irc_strerror (irc_errno(s)));
		return 1;
	}

	return 1;
}
