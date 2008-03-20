/* Copyright (C) 2007 The SpringLobby Team. All rights reserved. */

#include <wx/colour.h>
#include <wx/tokenzr.h>

#include "uiutils.h"
#include "utils.h"


wxString RefineMapname( const wxString& mapname )
{
  wxString ret = mapname;
  ret = ret.BeforeLast( '.' );
  ret.Replace(_T("_"), _T(" ") );
  ret.Replace(_T("-"), _T(" ") );
  return ret;
}


wxString RefineModname( const wxString& modname )
{
  wxString ret = modname;
  ret.Replace(_T("Absolute Annihilation"), _T("AA") );
  ret.Replace(_T("Complete Annihilation"), _T("CA") );
  ret.Replace(_T("Balanced Annihilation"), _T("BA") );
  ret.Replace(_T("Expand and Exterminate"), _T("EE") );
  ret.Replace(_T("War Evolution"), _T("WarEv") );
  ret.Replace(_T("TinyComm"), _T("TC") );
  ret.Replace(_T("BETA"), _T("b") );
  ret.Replace(_T("Public Alpha"), _T("pa") );
  ret.Replace(_T("Public Beta"), _T("pb") );
  ret.Replace(_T("Public"), _T("p") );
  ret.Replace(_T("Alpha"), _T("a") );
  ret.Replace(_T("Beta"), _T("b") );
  return ret;
}


wxString RTFtoText( const wxString& rtfinput )
{
  wxString ret = rtfinput;
  ret = ret.AfterFirst( '{' ).BeforeLast( '}' );

  ret.Replace( _T("\\pard"), _T("") ); // remove a ambiguus char

  ret.Replace( _T("\\par"), _T(" \n") ); // convert the end of lines

  wxString BeforeBrack = ret.BeforeFirst( '{' );
  wxString AfterBrack = ret.AfterLast( '}' );
  ret = BeforeBrack + AfterBrack; // remove everyhting that matches { text }

  wxString out;
  while ( ret.Find('\\') >= 0 ) //remove anything in the form \please\ignore\this
  {
    out += ret.BeforeFirst( '\\' );
    ret = ret.AfterFirst ( '\\' );
    ret = ret.AfterFirst ( ' ' );
  } ;

  return out;
}

bool AreColoursSimilar( const wxColour& col1, const wxColour& col2, int mindiff )
{
  int r,g,b;
  r = col1.Red() - col2.Red();
  g = col1.Green() - col2.Green();
  b = col1.Blue() - col2.Blue();
  r = r>0?r:-r;
  g = g>0?g:-g;
  b = b>0?b:-b;
  if ( (r <= mindiff) && (g <= mindiff) && (b <= mindiff) ) return true;
  return false;
}


void ColourDelta( int& r, int& g, int& b, const int& delta )
{
  int tmpdelta;
  if ( delta > 0 ) {
    r += delta;
    tmpdelta = delta;
    if ( r > 255 ) {
      tmpdelta += r - 255;
      r = 255;
    }
    g += tmpdelta;
    tmpdelta = delta;
    if ( g > 255 ) {
      tmpdelta += g - 255;
      g = 255;
    }
    b += tmpdelta;
    if ( b > 255 ) b = 255;
  } else {
    r += delta;
    tmpdelta = -delta;
    if ( r < 0 ) {
      tmpdelta -= r;
      r = 0;
    }
    g -= tmpdelta;
    tmpdelta = -delta;
    if ( g < 0 ) {
      tmpdelta -= g;
      g = 0;
    }
    b -= tmpdelta;
    if ( b < 0 ) b = 0;
  }
}


wxColour ColourDelta( const wxColour& colour, const int& delta )
{
  int r = colour.Red();
  int g = colour.Green();
  int b = colour.Blue();
  ColourDelta( r, g, b, delta );
  return wxColour( r, g, b );
}

wxString GetColorString( const wxColour& color )
{
  return wxString::Format( _T("%d %d %d"), color.Red(), color.Green(), color.Blue() );
}

ReplayData GetReplayInfos ( wxString& ReplayPath )
{
//TODO wut?  debug_func( STD_STRING( ReplayPath ) );
  ReplayData ret;
  wxString FileName = ReplayPath.BeforeLast( '/' ); // strips file path
  FileName = FileName.Left( FileName.Find( _T(".sdf") ) ); //strips the file extension
  wxStringTokenizer args ( FileName, _T("-")); // chunks by '-' separator
  if ( args.CountTokens() != 3 || args.CountTokens() != 4 ) // not a spring standard replay filename
  {
    ret.ReplayName = FileName;
    return ret;
  }
  wxString date = args.GetNextToken(); // date format YYMMDD
  date.Left( 2 ).ToLong( &ret.year );
  date.Mid( 3, 4 ).ToLong( &ret.month );
  date.Mid( 5, 6 ).ToLong( &ret.day );
  ret.MapName = args.GetNextToken();
  ret.SpringVersion = args.GetNextToken();
  ret.ReplayName = args.GetNextToken(); // void string if multiple replays wich share previous paramteres aren't present
  return ret;
}


wxColour GetColorFromStrng( const wxString color )
{
  wxString c = color;
  long r = 0, g = 0, b = 0;
  c.BeforeFirst( ' ' ).ToLong( &r );
  c = c.AfterFirst( ' ' );
  c.BeforeFirst( ' ' ).ToLong( &g );
  c = c.AfterFirst( ' ' );
  c.BeforeFirst( ' ' ).ToLong( &b );
  return wxColour( r%256, g%256, b%256 );
}



