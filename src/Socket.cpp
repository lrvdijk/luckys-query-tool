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

#include "Socket.h"

/**
 * Constructor, initializes the socket
 */
Socket::Socket() : socket(0), sock_type(SOCK_STREAM), connected(false)
{		
	this -> address.sin_family = AF_INET;
	memset(&(this -> address.sin_zero), '\0', 8);
}

Socket::Socket(int type) : socket(0), sock_type(type), connected(false)
{
	this -> address.sin_family = AF_INET;
	memset(&(this -> address.sin_zero), '\0', 8);
}	

/**
 * Intializes our socket
 * And sets the socket option to reuse the addr
 */
void Socket::init_socket()
{	
	// Initialize socket
	this -> socket = ::socket(PF_INET, this -> sock_type, 0);
	
	if(this -> socket == -1)
	{
		throw SocketException(_("Could not create socket"), errno);
	}
	
	int yes = 1;
	if(setsockopt(this -> socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		throw SocketException(_("Could not set socket option"), errno);
	}
}

void Socket::connect(Glib::ustring hostname, int port)
{
	return this -> connect(hostname.c_str(), port);
}

void Socket::connect(std::string hostname, int port)
{
	return this -> connect(hostname.c_str(), port);
}

/**
 * Disconnects the socket
 * And emits the disconnect signal
 */
void Socket::disconnect()
{
	::shutdown(this -> socket, 2);
	this -> socket = 0;
	this -> connected = false;
}

/**
 * @return True if the socket is still connected, else false
 */
bool Socket::is_connected()
{
	return this -> connected;
}

/**
 * Sets if the socket is blocking or not
 * @param non_block True if you want the socket be non-blocking or else false
 */
void Socket::set_non_blocking(const bool non_block)
{
	int options = fcntl(this -> socket, F_GETFL);
	
	if(options < 0)
	{
		return;
	}
	
	if(non_block)
	{
		options = (options | O_NONBLOCK);
	}
	else
	{
		options = (options & ~O_NONBLOCK);
	}
	
	fcntl(this -> socket, F_SETFL, options);
}

/**
 * Destructor, closes the socket
 */
Socket::~Socket()
{	
	this -> disconnect();
}
