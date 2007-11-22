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

#ifndef QUAKEWARS_INCLUDED
#define QUAKEWARS_INCLUDED

#include "stdinc.h"
#include "Protocol.h"
#include "utils.h"

class QuakeWars : public Protocol
{
	public:
		enum QueryType
		{
			QUERY_STATUS,
			QUERY_INFO
		};
		
		QuakeWars(std::string ip, int port);
		QuakeWars(Glib::ustring ip, int port);
		virtual ~QuakeWars();
	
		virtual void parse();
		virtual void get_server_info();
		virtual void get_server_info(QueryType query);
	
	protected:
		virtual void parse_info();
		virtual void parse_status();
		virtual void parse_keys();
		virtual void parse_players();
};

#endif
