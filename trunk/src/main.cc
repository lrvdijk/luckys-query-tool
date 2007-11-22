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

#include "stdinc.h"
#include "MainWindow.h"

/* For testing propose use the local (not installed) glade file */
#define GLADE_FILE "luckys-query-tool.glade"
   
int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	
	// Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	try
	{
		refXml = Gnome::Glade::Xml::create(GLADE_FILE);
	}
	catch(const Gnome::Glade::XmlError& ex)
    {
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	
	MainWindow * main_win = 0;
	refXml -> get_widget_derived("main_window", main_win);
	if (main_win)
	{
		kit.run(*main_win);
		
		// Clean it up
		delete main_win;
		main_win = 0;
	}
	else
	{
		return 1;
	}
	
	return 0;
}
