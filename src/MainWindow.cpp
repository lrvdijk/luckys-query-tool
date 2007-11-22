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
#include "MainWindow.h"
#include "QuakeWars.h"
#include "utils.h"

/**
 * Constructor, inits our window, automaticly called by libglademm
 * @param window_obj A C instance of the window
 * @param ui_xml a reference to the glade xml instance
 */
MainWindow::MainWindow(GtkWindow*& window_obj, const Glib::RefPtr<Gnome::Glade::Xml>& ui_xml) : Gtk::Window(window_obj), glade_ref(ui_xml), server_dialog(0)
{
	this -> glade_ref -> connect_clicked("newserverMenu", sigc::mem_fun(*this, &MainWindow::OnNewServerClicked));
	
	// Initialize server dialog
	this -> glade_ref -> get_widget("server_dialog", this -> server_dialog);
}

void MainWindow::OnNewServerClicked()
{	
	Gtk::Entry * txtEntry = 0;
	this -> glade_ref -> get_widget("txtAddress", txtEntry);		
	
	txtEntry -> set_text("");
	
	int result = this -> server_dialog -> run();
	
	if(result == Gtk::RESPONSE_OK)
	{
		std::cout << "OK Clicked" << std::endl;
		
		Glib::ustring text = txtEntry -> get_text();
		
		if(!text.empty())
		{		
			size_t pos = text.find_first_of(':');
			
			int port;
			Glib::ustring ip;
			if(pos == std::string::npos)
			{
				port = 27733;
				ip = text;
			}
			else
			{
				port = Utils::convert<int>(text.substr(pos + 1, std::string::npos));
				ip = text.substr(0, text.size() - (text.size() - pos));
			}
			
			this -> query(ip, port);
		}
	}
	
	this -> server_dialog -> hide();
}

void MainWindow::query(Glib::ustring ip, int port)
{
	try
	{		
		QuakeWars qw_query(ip, port);
		qw_query.get_server_info();
	}
	catch(std::runtime_error& e)
	{
		Gtk::MessageDialog dlg(*this, _("Could not connect to server"));
		dlg.set_secondary_text(e.what());
		
		dlg.run();
	}
	catch(SocketException& e)
	{
		Gtk::MessageDialog dlg(*this, _("Could not connect to server"));
		dlg.set_secondary_text(e.what());
		
		dlg.run();
	}
}

/**
 * Destructor, cleans our window up
 */
MainWindow::~MainWindow()
{
	delete this -> server_dialog;
}
