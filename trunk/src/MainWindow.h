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

#ifndef MAINWINDOW_INCLUDED
#define MAINWINDOW_INCLUDED

#include "stdinc.h"

class MainWindow : public Gtk::Window
{
	public:
		
		MainWindow(GtkWindow*& window_obj, const Glib::RefPtr<Gnome::Glade::Xml>& ui_xml);	
		virtual ~MainWindow();
	
		void OnNewServerClicked();
	
	protected:
		/// Reference to our glade file, for the UI
		Glib::RefPtr<Gnome::Glade::Xml> glade_ref;
	
		/// Dialog for opening new server info tabs
		Gtk::Dialog * server_dialog;
	
		void query(Glib::ustring ip, int port);
};

#endif
