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

using std::string;

TcpClient::TcpClient() : Socket(SOCK_DGRAM)
{
}

TcpClient::~TcpClient()
{
	this -> disconnect();
}

void TcpClient::connect(const char * hostname, int port)
{
	this -> init_socket();
	
	// Resolve DNS
	hostent * host = gethostbyname(hostname);
	
	if(host == 0)
	{
		throw std::runtime_error(_("Could not resolve DNS"));
	}
	
	// Copy address
	memcpy(&this -> address.sin_addr, host -> h_addr_list[0], host -> h_length);
	
	// Let's connect to the adress
	int result = ::connect(this -> socket, reinterpret_cast<sockaddr *>(&this -> address), sizeof(sockaddr));
	std::cout << this -> socket << std::endl;
	
	if(result == -1)
	{		
		throw SocketException(_("Could not connect to socket"));
	}
	else
	{
		this -> connected = true;	
	}
}

int TcpClient::receive(char * buffer, int length)
{	
	int bytes_read = recv(this -> socket, buffer, length, 0);
	
	if(bytes_read == -1)
	{
		throw SocketException(_("Problem with receiving data"));
	}
	
	if(bytes_read == 0)
	{
		this -> connected = false;
		throw RemoteClosedException();
	}
	
	return bytes_read;
}

int TcpClient::receive(string &str, int length)
{
	char buffer[length + 1];
	str = "";
	
	memset(buffer, 0, length + 1);
	
	int bytes_read = recv(this -> socket, buffer, length, 0);
	
	if(bytes_read == -1)
	{
		throw SocketException(_("Problem with receiving data"));
	}
	
	if(bytes_read == 0)
	{
		this -> connected = false;
		throw RemoteClosedException();
	}
	
	str = buffer;
	return bytes_read;
}

void TcpClient::send(const char * data, int length)
{
	int total = 0;
	int bytes_left = length;
	int bytes_sent = 0;
	
	while(total < length)
	{
		bytes_sent = ::send(this -> socket, data + total, bytes_left, 0);
		if(bytes_sent == -1)
		{
			break;
		}
		
		total += bytes_sent;
		bytes_left -= bytes_sent;
	}
	
	if(bytes_sent == -1)
	{
		throw SocketException(_("Problem with sending data"));
	}
}

void TcpClient::send(const string &str)
{
	this -> send(str.c_str(), str.size());
}
	
