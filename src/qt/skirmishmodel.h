/**
    This file is part of SpringLobby,
    Copyright (C) 2007-2011

    SpringLobby is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2 as published by
    the Free Software Foundation.

    SpringLobby is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SpringLobby.  If not, see <http://www.gnu.org/licenses/>.
**/


#ifndef SKIRMISHMODEL_H
#define SKIRMISHMODEL_H

#ifdef SL_QT_MODE

#include <QAbstractListModel>
#include "../mmoptionswrapper.h"
#include <qt/noguisingleplayerbattle.h>

class SkirmishModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SkirmishModel(QObject *parent = 0);
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	enum SkirmishRoles {
			 Description = Qt::UserRole + 1,
			 Name
		 };

signals:

public slots:
	void run( const int id, const int side, const int map );

private:
	OptionsWrapper m_mod_customs;

	NoGuiSinglePlayerBattle m_battle;

	typedef std::vector< std::pair<wxString, OptionsWrapper> >
		SkirmishMap;

	SkirmishMap m_skirmishes;

};

#endif //#ifdef SL_QT_MODE
#endif // SKIRMISHMODEL_H
