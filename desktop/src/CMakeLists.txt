# Virtual MIDI Piano Keyboard
# Copyright (C) 2008-2013 Pedro Lopez-Cabanillas <plcl@users.sourceforge.net>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along 
# with this program; If not, see <http://www.gnu.org/licenses/>.

include_directories(${CMAKE_CURRENT_BINARY_DIR})
link_directories(${CMAKE_CURRENT_BINARY_DIR})

set(vmpk_forms_SRCS
    about.ui
    colordialog.ui
    extracontrols.ui
    kmapdialog.ui
    midisetup.ui
    preferences.ui
    riffimportdlg.ui
    vpiano.ui
    shortcutdialog.ui
    fluidsettingsdialog.ui
    networksettingsdialog.ui
)

QT5_WRAP_UI(vmpk_ui_SRCS ${vmpk_forms_SRCS})

set(vmpk_SRCS
    about.cpp
    about.h
    colordialog.cpp
    colordialog.h
    colorwidget.cpp
    colorwidget.h
    constants.h
    extracontrols.cpp
    extracontrols.h
    instrument.cpp
    instrument.h
    keyboardmap.cpp
    keyboardmap.h
    keylabel.cpp
    keylabel.h
    kmapdialog.cpp
    kmapdialog.h
    main.cpp
    mididefs.h
    midisetup.cpp
    midisetup.h
    pianodefs.h
    pianokeybd.cpp
    pianokeybd.h
    pianokey.cpp
    pianokey.h
    pianopalette.cpp
    pianopalette.h
    pianoscene.cpp
    pianoscene.h
    preferences.cpp
    preferences.h
    nativefilter.cpp
    nativefilter.h
    riff.cpp
    riff.h
    riffimportdlg.cpp
    riffimportdlg.h
    shortcutdialog.cpp
    shortcutdialog.h
    fluidsettingsdialog.cpp
    fluidsettingsdialog.h
    networksettingsdialog.cpp
    networksettingsdialog.h
    vpiano.cpp
    vpiano.h )

QT5_ADD_RESOURCES(vmpk_SRCS ../data/vmpk.qrc)

set(vmpk_qtobject_SRCS
    about.h
    colordialog.h
    colorwidget.h
    extracontrols.h
    kmapdialog.h
    midisetup.h
    pianokeybd.h
    pianoscene.h
    preferences.h
    riff.h
    riffimportdlg.h
    vpiano.h
    fluidsettingsdialog.h
    networksettingsdialog.h
    shortcutdialog.h)

if(ENABLE_DBUS)
    QT5_ADD_DBUS_ADAPTOR (vmpk_SRCS
                          net.sourceforge.vmpk.xml 
                          vpiano.h 
                          VPiano
                          vmpk_adaptor)
endif()

QT5_WRAP_CPP(vmpk_moc_SRCS ${vmpk_qtobject_SRCS})

if(UNIX AND NOT APPLE)
    add_executable (vmpk
                    ${vmpk_ui_SRCS}
                    ${vmpk_moc_SRCS}
                    ${vmpk_SRCS})
    install (TARGETS vmpk
             RUNTIME DESTINATION bin)
endif()

if(WIN32)
    set (vmpk_RESOURCES)
    configure_file (vmpk.rc.in ${CMAKE_CURRENT_BINARY_DIR}/vmpk.rc 
                    IMMEDIATE @ONLY)
	set (vmpk_RESOURCES ${CMAKE_CURRENT_BINARY_DIR}/vmpk.rc)
    add_executable (vmpk WIN32
                    ${vmpk_ui_SRCS}
                    ${vmpk_moc_SRCS}
                    ${vmpk_SRCS}
                    ${vmpk_RESOURCES})
    install (TARGETS vmpk
			 RUNTIME DESTINATION .)
endif()

if(APPLE)
    set(vmpk_SRCS ${vmpk_SRCS} maceventhelper.mm)
    set (MACOSX_BUNDLE_INFO_STRING "Virtual MIDI Piano Keyboard" )
    set (MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION} )
    set (MACOSX_BUNDLE_ICON_FILE "vmpk.icns" )
    set (MACOSX_BUNDLE_GUI_IDENTIFIER "net.sourceforge" )
    set (MACOSX_BUNDLE_BUNDLE_NAME "vmpk" )
    set (vmpk_RSC ../data/vmpk.icns
             ../data/help.html
             ../data/help_es.html
             ../data/txt2ins.awk
             ../data/gmgsxg.ins
             ../data/spanish.xml
             ../data/german.xml
             ../data/azerty.xml
             ../data/it-qwerty.xml
             ../data/vkeybd-default.xml
             ../data/pc102mac.xml )
    set_source_files_properties (${vmpk_RSC} PROPERTIES
                                 MACOSX_PACKAGE_LOCATION Resources)
    add_executable (vmpk MACOSX_BUNDLE
        ${vmpk_ui_SRCS}
        ${vmpk_moc_SRCS}
        ${vmpk_SRCS}
        ${vmpk_RSC}
    )
    target_link_libraries(vmpk
        "-framework Cocoa"
    )
endif()

target_link_libraries(vmpk
    Qt5::Widgets
    Qt5::Svg
    Qt5::Network
)

if(ENABLE_DBUS)
    target_link_libraries(vmpk
        Qt5::DBus
    )
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(vmpk
        Qt5::X11Extras
    )
endif()
