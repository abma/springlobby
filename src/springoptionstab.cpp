
/* Copyright (C) 2007 The SpringLobby Team. All rights reserved. */
//
// Class: SpringOptionsTab
//

#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/intl.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/file.h>

#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif

#include "nonportable.h"
#include "springoptionstab.h"
#include "ui.h"
#include "iunitsync.h"
#include "utils.h"
#include "settings.h"
#include "spring.h"
#include "mainwindow.h"

#include "settings++/custom_dialogs.h"

BEGIN_EVENT_TABLE(SpringOptionsTab, wxPanel)

    EVT_BUTTON ( SPRING_DIRBROWSE, SpringOptionsTab::OnBrowseDir )
    EVT_BUTTON ( SPRING_EXECBROWSE, SpringOptionsTab::OnBrowseExec )
    EVT_BUTTON ( SPRING_SYNCBROWSE, SpringOptionsTab::OnBrowseSync )
    EVT_BUTTON ( SPRING_WEBBROWSE, SpringOptionsTab::OnBrowseWeb )
    EVT_BUTTON ( SPRING_AUTOCONF, SpringOptionsTab::OnAutoConf )
    EVT_BUTTON ( SPRING_DIRFIND, SpringOptionsTab::OnFindDir )
    EVT_BUTTON ( SPRING_EXECFIND, SpringOptionsTab::OnFindExec )
    EVT_BUTTON ( SPRING_SYNCFIND, SpringOptionsTab::OnFindSync )
    EVT_RADIOBUTTON( SPRING_DEFEXE, SpringOptionsTab::OnDefaultExe )
    EVT_RADIOBUTTON( SPRING_DEFUSYNC, SpringOptionsTab::OnDefaultUsync )
    EVT_RADIOBUTTON( SPRING_DEFWEB, SpringOptionsTab::OnDefaultWeb )

    //Chat Log
    EVT_BUTTON ( CHATLOG_FIND, SpringOptionsTab::OnFindChatLog )
    EVT_BUTTON ( CHATLOG_BROWSE, SpringOptionsTab::OnBrowseChatLog )

END_EVENT_TABLE()


    SpringOptionsTab::SpringOptionsTab( wxWindow* parent, Ui& ui ) : wxPanel( parent, -1 ),m_ui(ui)
{
  m_dir_text = new wxStaticText( this, -1, _("Spring directory") );
  m_exec_loc_text = new wxStaticText( this, -1, _("Location") );
  m_sync_loc_text = new wxStaticText( this, -1, _("Location") );
  m_web_loc_text = new wxStaticText( this, -1, _("Web Browser") );

  m_dir_browse_btn = new wxButton( this, SPRING_DIRBROWSE, _("Browse") );
  m_dir_find_btn = new wxButton( this, SPRING_DIRFIND, _("Find") );
  m_exec_browse_btn = new wxButton( this, SPRING_EXECBROWSE, _("Browse") );
  m_exec_find_btn = new wxButton( this, SPRING_EXECFIND, _("Find") );
  m_sync_browse_btn = new wxButton( this, SPRING_SYNCBROWSE, _("Browse") );
  m_sync_find_btn = new wxButton( this, SPRING_SYNCFIND, _("Find") );
  m_web_browse_btn = new wxButton( this, SPRING_WEBBROWSE, _("Browse") );

  m_auto_btn = new wxButton( this, SPRING_AUTOCONF, _("Auto Configure") );

  m_exec_def_radio = new wxRadioButton( this, SPRING_DEFEXE, _("Default location."), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
  m_exec_spec_radio = new wxRadioButton( this, SPRING_DEFEXE, _("Specify:") );
  m_sync_def_radio = new wxRadioButton( this, SPRING_DEFUSYNC, _("Default location."), wxDefaultPosition, wxDefaultSize, wxRB_GROUP  );
  m_sync_spec_radio = new wxRadioButton( this, SPRING_DEFUSYNC, _("Specify:") );
  m_web_def_radio = new wxRadioButton( this, SPRING_DEFWEB, _("Default Browser."), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
  m_web_spec_radio = new wxRadioButton( this, SPRING_DEFWEB, _("Specify:") );


  if ( sett().GetSpringUseDefLoc() ) m_exec_def_radio->SetValue( true );
  else m_exec_spec_radio->SetValue( true );
  if ( sett().GetUnitSyncUseDefLoc() ) m_sync_def_radio->SetValue( true );
  else m_sync_spec_radio->SetValue( true );
  if ( sett().GetWebBrowserPath().IsEmpty() ) m_web_def_radio->SetValue( true );
  else m_web_spec_radio->SetValue( true );


  m_dir_edit = new wxTextCtrl( this, -1, WX_STRING(sett().GetSpringDir()) );
  m_exec_edit = new wxTextCtrl( this, -1, WX_STRING(sett().GetSpringLoc()) );
  m_sync_edit = new wxTextCtrl( this, -1, WX_STRING(sett().GetUnitSyncLoc()) );
  m_web_edit = new wxTextCtrl( this, -1, sett().GetWebBrowserPath() );

  m_exec_box = new wxStaticBox( this, -1, _("Spring executable") );
  m_sync_box = new wxStaticBox( this, -1, _("UnitSync library") );
  m_web_box = new wxStaticBox( this , -1, _("Web Browser") );

  //Chat Log:
  m_chatlog_loc_text = new wxStaticText( this, -1, _("Location") );
  m_chatlog_browse_btn = new wxButton( this, CHATLOG_BROWSE, _("Browse") );
  m_chatlog_find_btn = new wxButton( this, CHATLOG_FIND, _("Find") );
  m_chatlog_enable_chk = new wxCheckBox( this, CHATLOG_ENABLE, _ ("Enable logging Chat."), wxDefaultPosition, wxDefaultSize,0);
  m_chatlog_enable_chk->SetValue( sett().GetChatLogEnable() );
  m_chatlog_edit = new wxTextCtrl( this, -1, WX_STRING(sett().GetChatLogLoc()) );

  m_main_sizer = new wxBoxSizer( wxVERTICAL );
  m_dir_sizer = new wxBoxSizer( wxHORIZONTAL );
  m_aconf_sizer = new wxBoxSizer( wxVERTICAL );
  m_exec_loc_sizer = new wxBoxSizer( wxHORIZONTAL );
  m_sync_loc_sizer = new wxBoxSizer( wxHORIZONTAL );
  m_web_loc_sizer = new wxBoxSizer( wxHORIZONTAL );

  m_dir_sizer->Add( m_dir_text, 0, wxALL, 2 );
  m_dir_sizer->Add( m_dir_edit, 1, wxEXPAND );
  m_dir_sizer->Add( m_dir_browse_btn );
  m_dir_sizer->Add( m_dir_find_btn );

  m_exec_loc_sizer->Add( m_exec_loc_text, 0, wxALL, 2 );
  m_exec_loc_sizer->Add( m_exec_edit, 1, wxEXPAND );
  m_exec_loc_sizer->Add( m_exec_browse_btn );
  m_exec_loc_sizer->Add( m_exec_find_btn );

  m_sync_loc_sizer->Add( m_sync_loc_text, 0, wxALL, 2 );
  m_sync_loc_sizer->Add( m_sync_edit, 1, wxEXPAND );
  m_sync_loc_sizer->Add( m_sync_browse_btn );
  m_sync_loc_sizer->Add( m_sync_find_btn );

  m_web_loc_sizer->Add( m_web_loc_text, 0, wxALL, 2 );
  m_web_loc_sizer->Add( m_web_edit, 1, wxEXPAND );
  m_web_loc_sizer->Add( m_web_browse_btn );

  m_exec_box_sizer = new wxStaticBoxSizer( m_exec_box, wxVERTICAL );
  m_sync_box_sizer = new wxStaticBoxSizer( m_sync_box, wxVERTICAL );
  m_web_box_sizer = new wxStaticBoxSizer( m_web_box, wxVERTICAL );

  m_exec_box_sizer->Add( m_exec_def_radio, 0, wxALL, 2 );
  m_exec_box_sizer->Add( m_exec_spec_radio, 0, wxALL, 2 );
  m_exec_box_sizer->Add( m_exec_loc_sizer, 0, wxEXPAND | wxALL, 2 );

  m_sync_box_sizer->Add( m_sync_def_radio, 0, wxALL, 2 );
  m_sync_box_sizer->Add( m_sync_spec_radio, 0, wxALL, 2 );
  m_sync_box_sizer->Add( m_sync_loc_sizer, 0, wxEXPAND | wxALL, 2 );

  m_web_box_sizer->Add( m_web_def_radio, 0, wxALL, 2 );
  m_web_box_sizer->Add( m_web_spec_radio, 0, wxALL, 2 );
  m_web_box_sizer->Add( m_web_loc_sizer, 0, wxEXPAND | wxALL, 2 );

  m_aconf_sizer->AddStretchSpacer();
  m_aconf_sizer->Add( m_auto_btn );

  m_main_sizer->Add( m_dir_sizer, 0, wxEXPAND | wxALL, 2 );
  m_main_sizer->Add( m_exec_box_sizer, 0, wxEXPAND | wxALL, 2 );
  m_main_sizer->Add( m_sync_box_sizer, 0, wxEXPAND | wxALL, 2 );
  m_main_sizer->Add( m_web_box_sizer, 0, wxEXPAND | wxALL, 2 );
  //Chat Log
        m_chatlog_box = new wxStaticBox( this, -1, _("Log Chat") );
        m_chatlog_loc_sizer = new wxBoxSizer( wxHORIZONTAL );
        m_chatlog_loc_sizer->Add( m_chatlog_loc_text, 0, wxALL, 2 );
        m_chatlog_loc_sizer->Add( m_chatlog_edit, 1, wxEXPAND );
        m_chatlog_loc_sizer->Add( m_chatlog_browse_btn );
        m_chatlog_loc_sizer->Add( m_chatlog_find_btn );
        m_chatlog_box_sizer = new wxStaticBoxSizer( m_chatlog_box, wxVERTICAL );
        m_chatlog_box_sizer->Add( m_chatlog_enable_chk, 0, wxALL, 2 );
        m_chatlog_box_sizer->Add( m_chatlog_loc_sizer, 0, wxEXPAND | wxALL, 2 );
        m_main_sizer->Add( m_chatlog_box_sizer, 0, wxEXPAND | wxALL, 2 );
  //END
  m_main_sizer->Add( m_aconf_sizer, 0, wxEXPAND | wxALL, 2 );
  m_main_sizer->AddStretchSpacer();

  SetSizer( m_main_sizer );
  Layout();

  DoRestore();

  if ( sett().IsFirstRun() ) {
    wxCommandEvent event;
    OnAutoConf( event );
    OnApply( event );
  }
}


SpringOptionsTab::~SpringOptionsTab()
{

}


void SpringOptionsTab::DoRestore()
{
  m_dir_edit->SetValue( WX_STRING(sett().GetSpringDir()) );
  m_sync_edit->SetValue( WX_STRING(sett().GetUnitSyncLoc()) );
  m_exec_edit->SetValue( WX_STRING(sett().GetSpringLoc()) );
  m_exec_def_radio->SetValue( sett().GetSpringUseDefLoc() );
  m_sync_def_radio->SetValue( sett().GetUnitSyncUseDefLoc() );
  m_exec_spec_radio->SetValue( !sett().GetSpringUseDefLoc() );
  m_sync_spec_radio->SetValue( !sett().GetUnitSyncUseDefLoc() );
  HandleExeloc( sett().GetSpringUseDefLoc() );
  HandleUsyncloc( sett().GetUnitSyncUseDefLoc() );

  //Chat Log
  m_chatlog_enable_chk->SetValue(  sett().GetChatLogEnable() );
  m_chatlog_edit->SetValue(  WX_STRING(sett().GetChatLogLoc()) );
}


void SpringOptionsTab::HandleExeloc( bool defloc )
{
  m_exec_def_radio->SetValue( defloc );
  m_exec_spec_radio->SetValue( !defloc );
  if ( defloc ) {
    m_exec_edit->Enable( false );
    m_exec_browse_btn->Enable( false );
    //m_exec_find_btn->Enable( false );
    m_exec_edit->SetValue( WX_STRING(sett().GetSpringUsedLoc( true, true )) );
  } else {
    m_exec_edit->Enable( true );
    m_exec_browse_btn->Enable( true );
    //m_exec_find_btn->Enable( true );
    m_exec_edit->SetValue( WX_STRING(sett().GetSpringLoc()) );
  }
}


void SpringOptionsTab::HandleUsyncloc( bool defloc )
{
  m_sync_def_radio->SetValue( defloc );
  m_sync_spec_radio->SetValue( !defloc );
  if ( defloc ) {
    m_sync_edit->Enable( false );
    m_sync_browse_btn->Enable( false );
    //m_sync_find_btn->Enable( false );
    m_sync_edit->SetValue( WX_STRING(sett().GetUnitSyncUsedLoc( true, true )) );
  } else {
    m_sync_edit->Enable( true );
    m_sync_browse_btn->Enable( true );
    //m_sync_find_btn->Enable( true );
    m_sync_edit->SetValue( WX_STRING(sett().GetUnitSyncLoc()) );
  }
}


void SpringOptionsTab::HandleWebloc( bool defloc )
{
  m_web_def_radio->SetValue( defloc );
  m_web_spec_radio->SetValue( !defloc );
  if ( defloc ) {
    m_web_edit->Enable( false );
    m_web_browse_btn->Enable( false );
    //m_sync_find_btn->Enable( false );
    m_web_edit->SetValue( _T("") );
  } else {
    m_web_edit->Enable( true );
    m_web_browse_btn->Enable( true );
    //m_sync_find_btn->Enable( true );
    m_web_edit->SetValue( sett().GetWebBrowserPath() );
  }
}


bool SpringOptionsTab::IsDataDir( const wxString& dir )
{
  if ( wxDir::Exists( dir + wxFileName::GetPathSeparator() + _T("maps") ) ) return true;
  return false;
}


bool SpringOptionsTab::IsSpringExe( const wxString& exe )
{
  if ( !wxFile::Exists( exe ) ) return false;
#ifdef HAVE_WX28
  if ( !wxFileName::IsFileExecutable( exe ) ) return false;
#endif
  return true;
}


bool SpringOptionsTab::IsUnitSyncLib( const wxString& lib )
{
  if ( !wxFile::Exists( lib ) ) return false;
  return true;
}


wxString SpringOptionsTab::AutoFindSpringDir( const wxString& def )
{
  wxPathList pl;
  wxStandardPathsBase& sp = wxStandardPathsBase::Get();

  pl.Add( wxFileName::GetCwd() );
#ifdef HAVE_WX28
  pl.Add( sp.GetExecutablePath() );
#endif
  pl.Add( wxFileName::GetHomeDir() );
#ifdef __WXMSW__
  wxRegKey programreg( _T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion") );
  wxString tmp;
  if ( programreg.QueryValue( _T("ProgramFilesDir"), tmp ) ) pl.Add( tmp );

  pl.Add( _T("C:\\Program") );
  pl.Add( _T("C:\\Program Files") );
#endif
  pl.Add( sp.GetUserDataDir().BeforeLast( wxFileName::GetPathSeparator() ) );
  pl.Add( sp.GetDataDir().BeforeLast( wxFileName::GetPathSeparator() ) );
#ifdef HAVE_WX28
  pl.Add( sp.GetResourcesDir().BeforeLast( wxFileName::GetPathSeparator() ) );
#endif

  for ( size_t i = 0; i < pl.GetCount(); i++ ) {
    wxString path = pl[i] + wxFileName::GetPathSeparator();
    if ( IsDataDir( path ) ) return path;
    if ( IsDataDir( path + _T("Spring") ) ) return path + _T("Spring");
    if ( IsDataDir( path + _T("spring") ) ) return path + _T("spring");
    if ( IsDataDir( path + _T("spring_data") ) ) return path + _T("spring_data");
    if ( IsDataDir( path + _T(".spring") ) ) return path + _T(".spring");
    if ( IsDataDir( path + _T(".spring_data") ) ) return path + _T(".spring_data");
  }

  return def;
}


wxString SpringOptionsTab::AutoFindSpringExe( const wxString& def )
{
  wxPathList pl;
  wxStandardPathsBase& sp = wxStandardPathsBase::Get();

#ifdef __WXMSW__
  wxRegKey programreg( _T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion") );
  wxString tmp;
  if ( programreg.QueryValue( _T("ProgramFilesDir"), tmp ) ) pl.Add( tmp );

  pl.Add( _T("C:\\Program") );
  pl.Add( _T("C:\\Program Files") );
#else
  pl.Add( _T("/usr/local/games") );
  pl.Add( _T("/usr/local/games/bin") );
  pl.Add( _T("/usr/local/bin") );
  pl.Add( _T("/usr/games") );
  pl.Add( _T("/usr/games/bin") );
  pl.Add( _T("/usr/bin") );
#endif

  pl.Add( m_dir_edit->GetValue() );
  pl.Add( wxFileName::GetCwd() );

#ifdef HAVE_WX28
  pl.Add( sp.GetExecutablePath() );
#endif

  pl.Add( wxFileName::GetHomeDir() );
  pl.Add( sp.GetUserDataDir().BeforeLast( wxFileName::GetPathSeparator() ) );
  pl.Add( sp.GetDataDir().BeforeLast( wxFileName::GetPathSeparator() ) );

#ifdef HAVE_WX28
  pl.Add( sp.GetResourcesDir().BeforeLast( wxFileName::GetPathSeparator() ) );
#endif

  pl.Add( m_dir_edit->GetValue() );

  for ( size_t i = 0; i < pl.GetCount(); i++ ) {
    wxString path = pl[i];
    if ( path.Last() != wxFileName::GetPathSeparator() ) path += wxFileName::GetPathSeparator();
    if ( IsSpringExe( path + SPRING_BIN ) ) return path + SPRING_BIN;
    if ( IsSpringExe( path + _T("Spring") + wxFileName::GetPathSeparator() + SPRING_BIN ) ) return path + _T("Spring") + wxFileName::GetPathSeparator() + SPRING_BIN;
    if ( IsSpringExe( path + _T("spring") + wxFileName::GetPathSeparator() + SPRING_BIN ) ) return path + _T("spring") + wxFileName::GetPathSeparator() + SPRING_BIN;
  }

  return def;
}


wxString SpringOptionsTab::AutoFindUnitSyncLib( const wxString& def )
{
  wxPathList pl;
  wxStandardPathsBase& sp = wxStandardPathsBase::Get();

#ifdef __WXMSW__
  wxRegKey programreg( _T("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion") );
  wxString tmp;
  if ( programreg.QueryValue( _T("ProgramFilesDir"), tmp ) ) pl.Add( tmp );

  pl.Add( wxGetOSDirectory() );
  pl.Add( _T("C:\\Program") );
  pl.Add( _T("C:\\Program Files") );
#else
  pl.Add( _T("/usr/local/lib64") );
  pl.Add( _T("/usr/local/games") );
  pl.Add( _T("/usr/local/games/lib") );
  pl.Add( _T("/usr/local/lib") );
  pl.Add( _T("/usr/lib64") );
  pl.Add( _T("/usr/lib") );
  pl.Add( _T("/usr/games") );
  pl.Add( _T("/usr/games/lib64") );
  pl.Add( _T("/usr/games/lib") );
#endif

  pl.Add( m_dir_edit->GetValue() );
  pl.Add( wxFileName::GetCwd() );

#ifdef HAVE_WX28
  pl.Add( sp.GetExecutablePath() );
#endif

  pl.Add( wxFileName::GetCwd() );

#ifdef HAVE_WX28
  pl.Add( sp.GetExecutablePath() );
#endif

  pl.Add( wxFileName::GetHomeDir() );
  pl.Add( sp.GetUserDataDir().BeforeLast( wxFileName::GetPathSeparator() ) );
  pl.Add( sp.GetDataDir().BeforeLast( wxFileName::GetPathSeparator() ) );

#ifdef HAVE_WX28
  pl.Add( sp.GetResourcesDir().BeforeLast( wxFileName::GetPathSeparator() ) );
#endif

  pl.Add( m_dir_edit->GetValue() );

  for ( size_t i = 0; i < pl.GetCount(); i++ ) {
    wxString path = pl[i];
    if ( path.Last() != wxFileName::GetPathSeparator() ) path += wxFileName::GetPathSeparator();
    if ( IsUnitSyncLib( path + UNITSYNC_BIN ) ) return path + UNITSYNC_BIN;
    if ( IsUnitSyncLib( path + _T("Spring") + wxFileName::GetPathSeparator() + UNITSYNC_BIN ) ) return path + _T("Spring") + wxFileName::GetPathSeparator() + UNITSYNC_BIN;
    if ( IsUnitSyncLib( path + _T("spring") + wxFileName::GetPathSeparator() + UNITSYNC_BIN ) ) return path + _T("spring") + wxFileName::GetPathSeparator() + UNITSYNC_BIN;
  }

  return def;
}


void SpringOptionsTab::OnAutoConf( wxCommandEvent& event )
{
  OnFindDir( event );
  OnFindExec( event );
  OnFindSync( event );
  //Chat Log
  m_chatlog_enable_chk->SetValue(false);
  m_chatlog_edit->SetValue( AutoFindChatLogDir() );
}


void SpringOptionsTab::OnFindDir( wxCommandEvent& event )
{
  m_dir_edit->SetValue( AutoFindSpringDir( m_dir_edit->GetValue() ) );
}


void SpringOptionsTab::OnFindExec( wxCommandEvent& event )
{
  wxString found = AutoFindSpringExe( m_exec_edit->GetValue() );
  HandleExeloc( false );
  m_exec_edit->SetValue( found );
}


void SpringOptionsTab::OnFindSync( wxCommandEvent& event )
{
  wxString found = AutoFindUnitSyncLib( m_sync_edit->GetValue() );
  HandleUsyncloc( false );
  m_sync_edit->SetValue( found );
}


void SpringOptionsTab::OnBrowseDir( wxCommandEvent& event )
{
  wxDirDialog dirpic( this, _("Choose a directory"), WX_STRING(sett().GetSpringDir()), wxDD_DEFAULT_STYLE );
  if ( dirpic.ShowModal() == wxID_OK ) m_dir_edit->SetValue( dirpic.GetPath() );
}


void SpringOptionsTab::OnBrowseExec( wxCommandEvent& event )
{
  wxFileDialog pic( this, _("Choose a Spring executable"), WX_STRING(sett().GetSpringDir()), wxString(SPRING_BIN), CHOOSE_EXE );
  if ( pic.ShowModal() == wxID_OK ) m_exec_edit->SetValue( pic.GetPath() );
}

void SpringOptionsTab::OnBrowseSync( wxCommandEvent& event )
{
  wxFileDialog pic( this, _("Choose a unitsync library"), WX_STRING(sett().GetSpringDir()), wxString(UNITSYNC_BIN), CHOOSE_DLL );
  if ( pic.ShowModal() == wxID_OK ) m_sync_edit->SetValue( pic.GetPath() );
}


void SpringOptionsTab::OnBrowseWeb( wxCommandEvent& event )
{
  wxFileDialog pic( this, _("Choose a web browser executable"), WX_STRING(sett().GetSpringDir()), _T("*"), CHOOSE_EXE );
  if ( pic.ShowModal() == wxID_OK ) m_web_edit->SetValue( pic.GetPath() );
}


void SpringOptionsTab::OnApply( wxCommandEvent& event )
{
  sett().SetSpringDir( STD_STRING(m_dir_edit->GetValue()) );
  if ( !m_sync_def_radio->GetValue() ) sett().SetUnitSyncLoc( STD_STRING( m_sync_edit->GetValue() ) );
  if ( !m_exec_def_radio->GetValue() ) sett().SetSpringLoc( STD_STRING( m_exec_edit->GetValue() ) );
  if ( !m_web_def_radio->GetValue() ) sett().SetWebBrowserPath( m_web_edit->GetValue() );
  sett().SetSpringUseDefLoc( m_exec_def_radio->GetValue() );
  sett().SetUnitSyncUseDefLoc( m_sync_def_radio->GetValue() );

  if ( sett().IsFirstRun() ) return;

  usync()->FreeUnitSyncLib();
  if ( !usync()->LoadUnitSyncLib( WX_STRING(sett().GetSpringDir()), WX_STRING(sett().GetUnitSyncUsedLoc()) ) ) {
    wxLogWarning( _T("can't load unitsync") );
    customMessageBox( SL_MAIN_ICON, _("SpringLobby is unable to load you unitsync library.\n\nYou might want to take another look at your unitsync setting."), _("Spring error"), wxOK );
  } else {
    // If LoadUnitSyncLib() fails this will too.
    if ( !Spring::TestSpringBinary() ) {
      wxLogWarning( _T("can't load unitsync") );
      customMessageBox( SL_MAIN_ICON, _("SpringLobby is unable to detect your spring version from the unitsync library.\n\nYou might want to take another look at your settings."), _("Spring error"), wxOK );
    }
  }
  m_ui.mw().OnUnitSyncReloaded();

  //Chat Log
  sett().SetChatLogEnable( m_chatlog_enable_chk->GetValue());
  sett().SetChatLogLoc( m_chatlog_edit->GetValue() );
}


void SpringOptionsTab::OnRestore( wxCommandEvent& event )
{
  DoRestore();
}


void SpringOptionsTab::OnDefaultExe( wxCommandEvent& event )
{
  HandleExeloc( m_exec_def_radio->GetValue() );
}


void SpringOptionsTab::OnDefaultUsync( wxCommandEvent& event )
{
  HandleUsyncloc( m_sync_def_radio->GetValue() );
}

void SpringOptionsTab::OnDefaultWeb( wxCommandEvent& event )
{
  HandleWebloc( m_web_def_radio->GetValue() );
}

//Chat Log
void SpringOptionsTab::OnFindChatLog( wxCommandEvent& event )
{
  m_chatlog_edit->SetValue( AutoFindChatLogDir( m_chatlog_edit->GetValue() ) );
}

void SpringOptionsTab::OnBrowseChatLog( wxCommandEvent& event )
{
  wxDirDialog dirpic( this, _("Choose a directory"), WX_STRING(sett().GetSpringDir()), wxDD_DEFAULT_STYLE );
  if ( dirpic.ShowModal() == wxID_OK ) m_chatlog_edit->SetValue( dirpic.GetPath() );
}

wxString SpringOptionsTab::AutoFindChatLogDir( const wxString& def )
{
  return  AutoFindSpringDir( m_chatlog_edit->GetValue() )+_("logs");
}
