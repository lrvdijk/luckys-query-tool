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

UdpClient::UdpClient() : Socket(SOCK_DGRAM)
{
}

UdpClient::~UdpClient()
{
	this -> disconnect();
}

void UdpClient::connect(const char * hostname, int port)
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
	this -> address.sin_port = htons(port);
	
	this -> connected = true;
}

int UdpClient::receive(char * buffer, int length)
{	
	socklen_t address_size = sizeof this -> address;
	int bytes_read = recvfrom(this -> socket, buffer, length, 0, reinterpret_cast<sockaddr *>(&this -> address), &address_size);
	
	if(bytes_read == -1)
	{
		throw new SocketException(_("Could not receive data from server"), errno);
	}
	else if(bytes_read == 0)
	{
		this -> connected = false;
		throw RemoteClosedException();
	}
	
	return bytes_read;
}

int UdpClient::receive(string &str, int length)
{
	char buffer[length + 1];
	str = "";
	
	memset(buffer, 0, length + 1);
	
	socklen_t address_size = sizeof this -> address;
	int bytes_read = recvfrom(this -> socket, buffer, length, 0, reinterpret_cast<sockaddr *>(&this -> address), &address_size);
	
	if(bytes_read == -1)
	{
		throw SocketException(_("Problem with receiving data"), errno);
	}
	
	if(bytes_read == 0)
	{
		this -> connected = false;
		throw RemoteClosedException();
	}
	
	str = buffer;
	return bytes_read;
}

void UdpClient::send(const char * data, int length)
{
	int total = 0;
	int bytes_left = length;
	int bytes_sent = 0;
	
	while(total < length)
	{
		bytes_sent = sendto(this -> socket, data + total, bytes_left, 0, reinterpret_cast<sockaddr *>(&this -> address), sizeof this -> address);
		if(bytes_sent == -1)
		{
			break;
		}
		
		total += bytes_sent;
		bytes_left -= bytes_sent;
	}
	
	if(bytes_sent == -1)
	{
		throw SocketException(_("Problem with sending data"), errno);
	}
}

void UdpClient::send(const string &str)
{
	this -> send(str.c_str(), str.size());
}
	
	
	
