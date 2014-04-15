/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#include "offlinebattle.h"
#include "spring.h"

#include <lslunitsync/unitsync.h>
#include "utils/conversion.h"

OfflineBattle::OfflineBattle(const int id  ):
m_id( id ),
m_me( User("Spectator") )
{
	m_opts.founder = m_me.GetNick();
	OnUserAdded( m_me );
	UserBattleStatus& newstatus = m_me.BattleStatus();
	newstatus.spectator = true;
	newstatus.sync = true;
}

void OfflineBattle::StartSpring()
{
	spring().Run(*this);
}

OfflineBattle::OfflineBattle ( const OfflineBattle& other ):
	IBattle(),
	m_id(0)
{
    *this = other;
}

OfflineBattle& OfflineBattle::operator = ( const OfflineBattle& other )
{
    m_id = other.m_id;
    m_map_loaded = other.m_map_loaded;
    m_map_loaded = other.m_map_loaded;
    m_mod_loaded = other.m_mod_loaded;
    m_local_map = other.m_local_map;
    m_local_mod = other.m_local_mod;
    m_host_map = other.m_host_map;
    m_host_mod = other.m_host_mod;
    m_restricted_units = other.m_restricted_units;
    m_opt_wrap = other.m_opt_wrap;
    m_opts = other.m_opts;
    m_ingame = other.m_ingame;
    m_generating_script = other.m_generating_script;
    m_rects = other.m_rects;
    m_ready_up_map = other.m_ready_up_map; // player name -> time counting from join/unspect
    m_players_ready = other.m_players_ready;
    m_players_sync = other.m_players_sync;
    m_teams_sizes = other.m_teams_sizes; // controlteam -> number of people in
    m_ally_sizes = other.m_ally_sizes; // allyteam -> number of people in
    m_preset = other.m_preset;
    m_is_self_in = other.m_is_self_in;
    m_internal_bot_list = other.m_internal_bot_list;
    m_script = other.m_script;
    m_playback_file_path = other.m_playback_file_path;
    m_parsed_teams = other.m_parsed_teams;
    m_parsed_allies = other.m_parsed_allies;
    m_internal_user_list = other.m_internal_user_list;
    return *this;
}
