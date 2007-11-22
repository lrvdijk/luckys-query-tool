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

#include "Packet.h"

using std::string;

Packet::Packet(char * data, unsigned int length) : data_length(length), offset(0)
{
	this -> data = new char[length];
	
	memcpy(this -> data, data, length);
}

Packet::~Packet()
{
	delete[] this -> data;
	this -> data = 0;
}

/**
 * Reads a string from the data, till the next 00 byte
 *
 * It starts searching from the current offset
 * @return a string object containing the data
 */
string Packet::read_string()
{
	string the_str;
	for(; this -> offset < this -> data_length; this -> offset++)
	{
		if(this -> data[this -> offset] == '\x00')
		{
			this -> offset++;
			break;
		}
		
		the_str.append(1, this -> data[this -> offset]);
	}
	
	return the_str;
}

/**
 * Reads a string from the data, till the next 00 byte
 *
 * It starts searching from the current offsetgiven offset
 * @param offset the offset to start reading from
 * @return a string object containing the data
 */
string Packet::read_string(unsigned int offset)
{
	if(offset > this -> data_length)
	{
		throw std::runtime_error(_("Offset out of bounds"));
	}
	
	this -> offset = offset;
	
	return this -> read_string();
}

/**
 * Reads 2 bytes from the data, and converts it to a short
 * @return The short value of the 2 bytes
 */
short Packet::read_short()
{
	short value = *reinterpret_cast<short *>(&this -> data[this -> offset]);
	
	this -> offset += 2;
	return value;
}

/**
 * Reads 2 bytes from the data, and converts it to a short
 * This function reads the 2 bytes from a given offset
 * @param offset The offset to read from
 * @return The short value of the 2 bytes
 */
short Packet::read_short(unsigned int offset)
{
	if(offset > this -> data_length)
	{
		throw std::runtime_error(_("Offset out of bounds"));
	}
	
	this -> offset = offset;
	
	return this -> read_short();
}

/**
 * Reads 4 bytes from the data, and converts it to an int
 * @return The int value of the 4 bytes
 */
int Packet::read_int()
{
	int value = *reinterpret_cast<int *>(&this -> data[this -> offset]);
	
	this -> offset += 4;
	return value;
}

/**
 * Reads 4 bytes from the data, and converts it to an int
 * This function reads the 4 bytes from the given offset
 * @param offset The offset to read from
 * @return The int value of the 4 bytes
 */
int Packet::read_int(unsigned int offset)
{
	if(offset > this -> data_length)
	{
		throw std::runtime_error(_("Offset out of bounds"));
	}
	
	this -> offset = offset;
	
	return this -> read_int();
}

char Packet::read()
{
	return this -> data[this -> offset++];
}

char Packet::read(unsigned int offset)
{
	if(offset > this -> data_length)
	{
		throw std::runtime_error(_("Offset out of bounds"));
	}
	
	this -> offset = offset;
	
	return this -> read();
}


void Packet::skip(unsigned int length)
{
	if(this -> offset + length > this -> data_length)
	{
		throw std::runtime_error(_("Offset out of bounds"));
	}
	
	this -> offset += length;
}

unsigned int Packet::get_position()
{
	return this -> offset;
}
