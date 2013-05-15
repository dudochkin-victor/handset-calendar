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

#include "comingupviewitemmodel.h"
#include "mviewmanager.h"
#include "calendarevent.h"
#include <kdatetime.h>

ComingUpViewItemModel::ComingUpViewItemModel( MViewManager& manager, bool showOnlyNextFewEvents) :
viewManager(manager),
restrictEventCount(showOnlyNextFewEvents)
{
    modelEventList = new QList<CalendarEvent*>();
    theHeaderData.append("Title");
    theHeaderData.append("Subtitle");
    updateEvents();
}

ComingUpViewItemModel::~ComingUpViewItemModel()
{
    delete modelEventList;
}

int ComingUpViewItemModel::rowCount(const QModelIndex& /*parent*/ ) const
{
    return theData.size();
}

int ComingUpViewItemModel::columnCount(const QModelIndex& /*parent*/ ) const
{
    return theHeaderData.size();
}

QVariant ComingUpViewItemModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.isValid() && index.row() < theData.size()) {
            QStringList rowData = theData[index.row()];
            return QVariant(rowData);
        }
    }

    return QVariant();
}

void ComingUpViewItemModel::updateEvents()
{
    modelEventList->clear();
    theData.clear();

    QList<CalendarEvent*>& eventList = viewManager.GetEvents();

    //int eventsLimitedTo = 3, comingUpEventCnt=0;
    int cntr = eventList.count();
    QDate today = QDate::currentDate();
    KDateTime daysLaterDate = KDateTime(today.addDays(7));

    for ( int i=0;i<cntr;i++ ) {
        CalendarEvent* event = eventList.at(i);
        bool addEvent = false;
        //Bug#7244 Author: sirisha.muppavarapu@intel.com
        //Fixed the issue with display of "coming up" "Later" event list
        if ( restrictEventCount == true ) {
            if ( today == event->StartDate().date() )
            {
             addEvent = true;
            }
        } else {
            if(event->StartDate().date() > daysLaterDate.date()) {
                break;
            } else if ( event->StartDate().date() > today )
            {
                addEvent = true;
            }
        }

        if ( addEvent ) {
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

CalendarEvent* ComingUpViewItemModel::selectedEvent(int index)
{
    if ( index <0 || index > modelEventList->count()-1 )
    {
        return 0;
    }

    return modelEventList->at(index);
}
