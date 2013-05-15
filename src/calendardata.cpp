/*
 * meego-handset-calendar - Meego Handset Calendar application
 *
 * Copyright (c) 2010, Intel Corporation.
 *
 * This program is licensed under the terms and conditions of the
 * Apache License, version 2.0.  The full text of the Apache License is at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include "calendardata.h"

CalendarData::CalendarData(const QString& newUri, const QString& newName, const QColor& newColor )
    :uri(0),name(0),color(0)
{
    SetUri(newUri);
    SetName(newName);
    SetColor(newColor);

}

CalendarData::~CalendarData()
{
    delete uri;
    delete name;
    delete color;
}

QString& CalendarData::Uri()
{
    return *uri;
}
void CalendarData::SetUri( const QString& newUri )
{
    if ( uri ) {
        delete uri;
        uri=0;
    }
    uri = new QString(newUri);
}
QString& CalendarData::Name()
{
    return *name;
}
void CalendarData::SetName( const QString& newName )
{
    if ( name ) {
        delete name;
        name=0;
    }
    name = new QString(newName);
}
QColor& CalendarData::Color()
{
    return *color;
}
void CalendarData::SetColor( const QColor& newColor )
{
    if ( color ) {
        delete color;
        color=0;
    }
    color = new QColor(newColor);
}
