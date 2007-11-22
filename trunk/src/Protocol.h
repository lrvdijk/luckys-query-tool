/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/**
 *                  Lucky's Query Tool
 *                ---------------------
 *       This tool can be used to view some information
 *         about a game server. Multiple protocols are
 *                       supported
 * 
 * Created by Lucas van Dijk <info@return1.net>
 * http://www.return1.net
 * 
 * You may redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * @author $Author$
 * @version $Id$
 */

#ifndef PROTOCOL_INCLUDED
#define PROTOCOL_INCLUDED
#define BUFFER_SIZE (1024 * 5)

#include <string>
#include <map>
#include <vector>
#include "Socket.h"
#include "Player.h"
#include "Packet.h"

class Protocol
{
	public:	
		typedef std::map<std::string, std::string> string_map;
		typedef std::vector<Player> player_vector;
	
		Protocol(std::string ip, int port);
		Protocol(Glib::ustring ip, int port);
		virtual ~Protocol();
		
		virtual void query(const char * data, int count);
		
		virtual void get_server_info() = 0;
		virtual void parse() = 0;
	
		string_map get_params();
		player_vector get_players();
		
	protected:
		std::string read_next_string();
		std::string read_next_string(unsigned int offset);
		
		/// Map containg all config variables of the server
		string_map params;
	
		/// Map containg all players
		player_vector players;
		
		/// Data received from the server
		Packet * packet;
	
		/// Socket to the server
		UdpClient connection;
};

#endif
