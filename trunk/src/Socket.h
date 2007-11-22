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

#ifndef SOCKET_INCLUDED
#define SOCKET_INCLUDED

#include "stdinc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

class Socket
{
	public:
		Socket();
		explicit Socket(int socktype);
		virtual ~Socket();
	
		virtual void connect(const char * hostname, int port) = 0;
		virtual void connect(Glib::ustring hostname, int port);
		virtual void connect(std::string ip, int port);
		virtual void disconnect();
	
		bool is_connected();
		
		virtual int receive(char * buffer, int length) = 0;
		virtual int receive(std::string &buffer, int length) = 0;
	
		virtual void send(const char * data, int length) = 0;
		virtual void send(const std::string &data) = 0;
	
		void set_non_blocking(const bool non_block);
	
	protected:
		/// The socket file descriptor
		int socket;
	
		/// Socket address
		sockaddr_in address;
	
		/// Socket type, Stream or Dgram
		int sock_type;
	
		/// Bool if the socket is still connected
		bool connected;
	
		virtual void init_socket();
};

class TcpClient : public Socket
{
	public:
		TcpClient();
		virtual ~TcpClient();
	
		virtual void connect(const char * hostname, int port);
		
		virtual int receive(char * buffer, int length);
		virtual int receive(std::string &buffer, int length);
	
		virtual void send(const char * data, int length);
		virtual void send(const std::string &data);
};

class UdpClient : public Socket
{
	public:
		UdpClient();
		virtual ~UdpClient();
	
		virtual void connect(const char * hostname, int port);
	
		virtual int receive(char * buffer, int length);
		virtual int receive(std::string &buffer, int length);
	
		virtual void send(const char * data, int length);
		virtual void send(const std::string &data);
};

class SocketException : public std::exception
{
	public:
		SocketException() 
		{
			this -> msg = "A Socket Exception occured";
		}
	
		explicit SocketException(std::string msg) : errnr(0)
		{
			this -> msg = msg;
		}
	
		SocketException(std::string msg, int errnr)
		{
			this -> msg = msg;
			this -> msg.append(": ");
			this -> msg.append(strerror(errnr));
			this -> errnr = errnr;
		}
	
		virtual ~SocketException() throw() { }
		virtual const char * what() const throw() 
		{ 
			return this -> msg.c_str(); 
		}
		virtual int get_errnr() { return this -> errnr; }
	protected:
		std::string msg;
		int errnr;
};

class RemoteClosedException : public SocketException
{
	public:
		RemoteClosedException() : SocketException("The remote host closed the connection.") { }
};

#endif
	
