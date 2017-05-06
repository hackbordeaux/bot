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
#include "CommandHandler.h"
#include "IRCThread.h"

static const ChatCommand COMMANDHANDLERFINISHER = {nullptr, nullptr, nullptr, ""};

ChatCommand *CommandHandler::getCommandTable()
{
	static ChatCommand globalCommandTable[] = {
			{"weather", &CommandHandler::handle_command_weather, nullptr, "Usage: /weather <ville>"},
			{"help", &CommandHandler::handle_command_help, nullptr, ""},
			{"list", &CommandHandler::handle_command_list, nullptr, ""},
			COMMANDHANDLERFINISHER,
	};

	return globalCommandTable;
}

bool CommandHandler::handle_command(const std::string &text, std::string &msg)
{
	ChatCommand *command = nullptr;
	ChatCommand *parentCommand = nullptr;

	const char *ctext = &(text.c_str())[1];

	ChatCommandSearchResult res = find_command(getCommandTable(), ctext, command, &parentCommand);
	switch (res) {
		case CHAT_COMMAND_OK:
			return (this->*(command->Handler))(ctext, msg);
		case CHAT_COMMAND_UNKNOWN_SUBCOMMAND:
			m_irc_thread->add_text(command->help);
			return true;
		case CHAT_COMMAND_UNKNOWN:
			m_irc_thread->add_text("Unknown command.");
			return false;

	}
}

ChatCommandSearchResult CommandHandler::find_command(ChatCommand *table, const char *&text, ChatCommand *&command,
													 ChatCommand **parentCommand)
{
	std::string cmd = "";

	// Skip whitespaces
	while (*text != ' ' && *text != '\0') {
		cmd += *text;
		++text;
	}

	while (*text == ' ') {
		++text;
	}

	for (int32_t i = 0; table[i].name != nullptr; ++i) {
		size_t len = strlen(table[i].name);
		if (strncmp(table[i].name, cmd.c_str(), len + 1) != 0) {
			continue;
		}

		if (table[i].childCommand != nullptr) {
			const char *stext = text;
			ChatCommand *parentSubCommand = nullptr;
			ChatCommandSearchResult res = find_command(
					table[i].childCommand, text, command, &parentSubCommand
			);

			switch (res) {
				case CHAT_COMMAND_OK:
					if (parentCommand) {
						*parentCommand = parentSubCommand ? parentSubCommand : &table[i];
					}

					if (strlen(command->name) == 0 && !parentSubCommand) {
						text = stext;
					}
					return CHAT_COMMAND_OK;

				case CHAT_COMMAND_UNKNOWN:
					command = &table[i];
					if (parentCommand)
						*parentCommand = nullptr;

					text = stext;
					return CHAT_COMMAND_UNKNOWN_SUBCOMMAND;

				case CHAT_COMMAND_UNKNOWN_SUBCOMMAND:
				default:
					if (parentCommand)
						*parentCommand = parentSubCommand ? parentSubCommand : &table[i];

					return res;
			}
		}

		if (!table[i].Handler) {
			continue;
		}

		command = &table[i];

		if (parentCommand) {
			*parentCommand = nullptr;
		}

		return CHAT_COMMAND_OK;
	}

	command = nullptr;

	if (parentCommand)
		*parentCommand = nullptr;

	return CHAT_COMMAND_UNKNOWN;
}

bool CommandHandler::handle_command_list(const std::string &args, std::string &msg)
{
	ChatCommand *cmds = getCommandTable();
	msg += "Command list : ";

	for (int32_t i = 0; cmds[i].name != nullptr; i++) {
		msg += std::string(cmds[i].name) + ", ";
	}
	return true;
}

bool CommandHandler::handle_command_help(const std::string &args, std::string &msg)
{
	if (args.empty()) {
		msg = "/help <command> to get the help of the command \n";
		return handle_command_list(args, msg);
	}

	ChatCommand *command = nullptr;
	ChatCommand *parentCommand = nullptr;
	const char *ctext = args.c_str();
	msg = args;

	ChatCommandSearchResult res = find_command(
			getCommandTable(), ctext, command, &parentCommand
	);

	switch(res) {
		case CHAT_COMMAND_OK:
			msg = command->help;
			return true;

		case CHAT_COMMAND_UNKNOWN_SUBCOMMAND: {
			msg = command->help + "\n";
			ChatCommand *child = command->childCommand;
			for (uint16_t i = 0; child[i].name != nullptr; ++i) {
				msg += (std::string) child[i].name + "\n";
				msg += "		" + child[i].help + "\n";
			}
			return true;
		}

		case CHAT_COMMAND_UNKNOWN:
			msg = "Command not found";
			return false;
	}
}

bool CommandHandler::handle_command_weather(const std::string &args, std::string &msg)
{
	msg = "Commande en cours de developpement";
	return true;
}
