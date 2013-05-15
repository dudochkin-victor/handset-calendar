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

#include "threedayviewitemmodel.h"
#include "mviewmanager.h"

ThreeDayViewItemModel::ThreeDayViewItemModel(MViewManager& manager) :
viewManager(manager)
{
    date = new QDate( QDate::currentDate() );
    modelEventList = new QList<CalendarEvent*>();
    theHeaderData.append("Title");
    theHeaderData.append("Subtitle");
}

int ThreeDayViewItemModel::rowCount(const QModelIndex& /*parent*/ ) const
{
    return theData.size();
}

int ThreeDayViewItemModel::columnCount(const QModelIndex& /*parent*/ ) const
{
    return theHeaderData.size();
}

QVariant ThreeDayViewItemModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.isValid() && index.row() < theData.size()) {
            QStringList rowData = theData[index.row()];
            return QVariant(rowData);
        }
    }
    return QVariant();
}

void ThreeDayViewItemModel::updateEvents()
{
    modelEventList->clear();
    theData.clear();

    QList<CalendarEvent*>& eventList = viewManager.GetEvents();
    int cntr = eventList.count();
    QDate today = QDate::currentDate();

    for ( int i=0;i<cntr;i++ ) {
        CalendarEvent* event = eventList.at(i);
        QDateTime dt = event->StartDate();

        if ( dt.date() == *date ) {
            modelEventList->append(event);
            QString dateString;
            //Bug#7320 Author: sirisha.muppavarapu@intel.com
            //This piece of code fixes the issue with display of event
            //If today: Display time followed by event
            //Else Display Date-time followed by event
            if(today == event->StartDate().date()) {
                dateString = event->StartDate().toString ( "hh:mm AP" );
            } else {
                dateString = event->StartDate().toString ( "ddd dd hh:mm AP" );
            }

            QString alarmsString("alarmOFF");
            if ( event->Alarm() ) {
                alarmsString = "alarmON";
            }
            theData.append( QStringList() << dateString << event->Description() << alarmsString );
        }
    }
}

CalendarEvent* ThreeDayViewItemModel::selectedEvent(int index)
{
    if ( index <0 || index > modelEventList->count() )
    {
        return 0;
    }

    return modelEventList->at(index);
}

void ThreeDayViewItemModel::setDate(const QDate& newDate)
{
    delete date;
    date = new QDate( newDate );
}

const QDate& ThreeDayViewItemModel::modelDate()
{
    return *date;
}
bool ThreeDayViewItemModel::dayHasAllDayEvent()
{
    for ( int i=0; i< modelEventList->count();i++ ) {
        CalendarEvent* event = modelEventList->at(i);
        if ( event->AllDay() ) {
            return true;
        }
    }
    return false;
}

