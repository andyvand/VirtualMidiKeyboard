/*
    MIDI Virtual Piano Keyboard 
    Copyright (C) 2008, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along 
    with this program; If not, see <http://www.gnu.org/licenses/>.
*/

#include "constants.h"
#include "vpiano.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QSTR_DOMAIN);
    QCoreApplication::setOrganizationDomain(QSTR_DOMAIN);
    QCoreApplication::setApplicationName(QSTR_APPNAME);    
    QApplication a(argc, argv);

    QString locale = QSTR_VMPKPX + QLocale::system().name();
    QTranslator translator;
    translator.load(locale, localeDirectory());
    a.installTranslator(&translator);
    
    VPiano w;
    w.show();
    return a.exec();
}