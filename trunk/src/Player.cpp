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

#include "Player.h"

using std::string;
using std::map;

Player::Player(string name)
{
	this -> name = name;
}

Player::Player(string name, int score)
{
	this -> name = name;
	this -> score = score;
}

void Player::add_param(string key, string value)
{
	this -> params[key] = value;
}

void Player::set_ping(short ping)
{
	this -> ping = ping;
}

void Player::set_bot(bool is_bot)
{
	this -> bot = is_bot;
}

map<string, string> Player::get_params()
{
	return this -> params;
}

Player::~Player()
{
}
