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

#include <string>
#include <sstream>

#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

class Utils
{
	public:
		template<class out_type, class in_value>
		static out_type convert(const in_value &var)
		{
			std::stringstream stream;
 			stream << var; // insert value to stream
 			out_type result; // store conversion’s result here
 			stream >> result; // write value to result
			return result;
		}
	
		template<class in_value>
		static std::string convert_to_string(const in_value &var)
		{
			std::ostringstream stream;
 			stream << var; // insert value to stream
			return stream.str();
		}
};

#endif
	
