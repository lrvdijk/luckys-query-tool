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

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "stdinc.h"

class Player
{
	public:
		Player(std::string name);
		Player(std::string name, int score);
	
		void set_ping(short ping);
		void set_bot(bool is_bot);
		virtual ~Player();
		
		virtual void add_param(std::string key, std::string value);
		virtual std::map<std::string, std::string> get_params();
	
	protected:
		std::map<std::string, std::string> params;
		std::string name;
		int score;
		short ping;
		bool bot;
};

#endif
	
