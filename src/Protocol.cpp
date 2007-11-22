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

#include "Protocol.h"

using std::string;

Protocol::Protocol(string ip, int port)
{
	this -> connection = UdpClient();
	this -> connection.connect(ip.c_str(), port);
}

Protocol::Protocol(Glib::ustring ip, int port)
{
	this -> connection = UdpClient();
	this -> connection.connect(ip.c_str(), port);
}

Protocol::~Protocol()
{	
	this -> connection.disconnect();
	delete this -> packet;
}

Protocol::string_map Protocol::get_params()
{
	return this -> params;
}

Protocol::player_vector Protocol::get_players()
{
	return this -> players;
}

/**
 * Sends the given data to the server
 * @param data The data to send
 * @param count How much bytes to send (length of data)
 */
void Protocol::query(const char * data, int count)
{
	if(this -> connection.is_connected() == false)
	{
		throw std::runtime_error(_("Not connected to server"));
	}
	
	std::cout << "Sending: " << std::hex << data << std::endl;
	
	this -> connection.send(data, count);
	
	std::cout << "Done." << std::endl;
	
	char * temp = new char[BUFFER_SIZE];
	int bytes_read = this -> connection.receive(temp, BUFFER_SIZE);
	
	this -> packet = new Packet(temp, bytes_read);
	
	delete[] temp;
	
	this -> parse();
}
