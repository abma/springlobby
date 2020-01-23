/* This file is part of the Springlobby (GPL v2 or later), see COPYING */
#ifndef SPRINGLOBBY_HEADERGUARD_CONNECTWINDOW_H
#define SPRINGLOBBY_HEADERGUARD_CONNECTWINDOW_H

#include "generated/ConnectWindowBase.h"

//! @brief wxFrame with a connection dialog used to specify username, password, and server. It can also register a new acount.
class ConnectWindow : public ConnectWindowBase
{
public:
	ConnectWindow(wxWindow* parent);

	void OnServerChange(wxCommandEvent& event);
	void ReloadServerList();

	void OnLoginDenied(const wxString& reason);
	void OnRegistrationAccepted(const wxString& user, const wxString& pass);
	void OnRegistrationDenied(const wxString& reason);

private:
	void OnCancel(wxCommandEvent& event);
	void OnOk(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& data);

	void CleanHide();

	void EnterRegistrationMode();
	void EnterLoginMode();
	void OnChangeMode(wxCommandEvent& event);
	bool in_login_mode; // true if in login mode, false if in register.
};

#endif // SPRINGLOBBY_HEADERGUARD_CONNECTWINDOW_H
