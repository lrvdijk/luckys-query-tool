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

#ifndef PACKET_INCLUDED
#define PACKET_INCLUDED

#include "stdinc.h"

class Packet
{
	public:
		explicit Packet(char * data, unsigned int length);
		virtual ~Packet();
	
		std::string read_string();
		std::string read_string(unsigned int offset);
	
		short read_short();
		short read_short(unsigned int offset);
	
		int read_int();
		int read_int(unsigned int offset);
	
		char read();
		char read(unsigned int offset);
	
		void skip(unsigned int count);
		unsigned int get_position();
	protected:
		char * data;
		unsigned int data_length;
		unsigned int offset;
};

#endif

