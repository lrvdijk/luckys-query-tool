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

#include "QuakeWars.h"
#include "Player.h"

using std::string;
using std::ostringstream;

QuakeWars::QuakeWars(string ip, int port) : Protocol(ip, port)
{
} 

QuakeWars::QuakeWars(Glib::ustring ip, int port) : Protocol(ip, port)
{
} 

void QuakeWars::parse()
{
	string header_text = this -> packet -> read_string(2);
	
	std::cout << header_text << std::endl;
	
	if(header_text == "statusResponse")
	{
		this -> parse_status();
	}
	else if(header_text == "infoResponse")
	{
		this -> parse_info();
	}
	else
	{
		throw std::runtime_error(_("Didn't receive a valid response, sure it's a Quake wars server?"));
	}
}

void QuakeWars::get_server_info()
{
	this -> get_server_info(QuakeWars::QUERY_INFO);
}

void QuakeWars::get_server_info(QuakeWars::QueryType type)
{
	// Server status
	std::cout << "Querieng..." << std::endl;
	
	switch(type)
	{
		case QuakeWars::QUERY_STATUS:
			this -> query("\xFF\xFFgetStatus\x00", 12);
		break;
		case QuakeWars::QUERY_INFO:
			this -> query("\xFF\xFFgetInfo\x00", 11);
		break;
	}
	
	std::cout << "Done." << std::endl;
	std::cout << "Position: " << this -> packet -> get_position() << std::endl;
	
}

void QuakeWars::parse_info()
{
	this -> parse_status();
	this -> parse_players();
}

void QuakeWars::parse_status()
{	
	this -> packet -> skip(16);
	this -> parse_keys();
}

void QuakeWars::parse_keys()
{
	while(true)
	{
		string key = this -> packet -> read_string();
		string value = this -> packet -> read_string();
		
		std::cout << "Position: " << this -> packet -> get_position() << std::endl;
		
		if(key.size() == 0 && value.size() == 0)
		{
			break;
		}
		
		std::cout << key << ": " << value << std::endl;
		
		this -> params[key] = value;
	}
}

void QuakeWars::parse_players()
{
	int number = 0;
	
	std::cout << "Position: " << this -> packet -> get_position() << std::endl;
	std::cout << "Parsing Players.." << std:: endl;
	
	while((number = this -> packet -> read()) != 32)
	{
		std::cout << "Player number: " << number << std::endl;
		
		short ping = this -> packet -> read_short();
		int rate = this -> packet -> read_int();
		string name = this -> packet -> read_string();
		
		Player player = Player(name);
		player.set_ping(ping);
		
		bool clantag_prefix = this -> packet -> read() == '\x00';
		string clantag = this -> packet -> read_string();
		
		bool bot = this -> packet -> read() != '\x00';
		player.set_bot(bot);
		
		std::cout << "Player: " << ((clantag_prefix && clantag.size() > 0) ? "[" + clantag + "]" : "") << name << ", ping: " << ping << ", rate: " << rate << ", is bot: " << bot << std::endl;
		
		this -> players.push_back(player);
	}
}

QuakeWars::~QuakeWars()
{
}
		
