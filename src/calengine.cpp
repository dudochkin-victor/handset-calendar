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

#include "calengine.h"
#include <sqlitestorage.h>
#include <kdatetime.h>
#include <QDir>

#include "calendarevent.h"
#include "calendardata.h"
#include <alarm.h>
#include <QBitArray>

CalEngine::CalEngine()
{
    calendars = new QList<CalendarData*>();
    events = new QList<CalendarEvent*>();

    calendar = new ExtendedCalendar(QLatin1String("UTC"));
    calendarPtr = ExtendedCalendar::Ptr( calendar );

    // This is the place where we configure our default backend
    QString dbFile = QDir::homePath() + QLatin1String( "/.calendardb" );
    storage = new SqliteStorage( calendarPtr, dbFile, false, true );
    storage->open();

    Notebook::List nbList = storage->notebooks();
    for ( int i=0;i<nbList.count();i++) {
        Notebook::Ptr nbPtr = nbList.at(i);
        notebook = nbPtr.data();
        break;
    }
    storage->loadNotebookIncidences(notebook->uid());
}

CalEngine::~CalEngine()
{
    for ( int i=0; i<calendars->count(); i++ ) {
       CalendarData* item = calendars->at(i);
       delete item;
    }
    delete calendars;
    calendars=0;

    calendarPtr.clear();
}

QList<CalendarData*>& CalEngine::getCalendars()
{
    if( calendars ) {
        for ( int i=0; i<calendars->count(); i++ ) {
           CalendarData* item = calendars->at(i);
           delete item;
        }
        delete calendars;
        calendars = new QList<CalendarData*>();
    }
    if ( notebook ) {
        CalendarData* cal = new CalendarData( notebook->uid(), notebook->name(), notebook->color() );
        calendars->append( cal );
    }
    return *calendars;
}

void CalEngine::reloadEvents()
{
    events = &getCalendarEvents();
}

QList<CalendarEvent*>& CalEngine::getCalendarEvents( CalendarData* /*calendar*/ )
{
    KCalCore::Event::List eventList = this->calendar->rawEvents();

    clearEventsList();

    for ( int i=0; i<eventList.count();i++ ) {
        KCalCore::Event* event = eventList.at(i).data();
        CalendarEvent* calEvent = new CalendarEvent();

        calEvent->SetCalendar( calendars->at(0) );
        calEvent->SetUid( event->uid() );
        calEvent->SetDescription( event->description() );
        calEvent->SetCalendarType(0); //currently we have only one notebook
        calEvent->SetAllDay( event->allDay() );
        calEvent->SetMultipleDays( event->isMultiDay() );
        calEvent->SetStartDate( event->dtStart().dateTime() );
        calEvent->SetEndDate( event->dtEnd().dateTime() );
        calEvent->SetRepeatId( event->recurrenceId().dateTime() );

        parseRecurrence( calEvent, event);

        calEvent->SetNotes( event->altDescription() );
        calEvent->SetCalCoreEvent(event);

        calEvent->SetAlarm( false );
        if ( event->hasEnabledAlarms() ) {
            KCalCore::Alarm::List alarmList = event->alarms();

            if ( alarmList.count() > 0 ) {
                KCalCore::Alarm::Ptr ptr = alarmList.at(0);
                KCalCore::Alarm* alarm = ptr.data();
                KDateTime altime = alarm->time();
                calEvent->SetAlarm(true);
                calEvent->SetAlarmDate( altime.dateTime() );
            } else {
                calEvent->SetAlarm( false );
            }
        }

        addItemSorted( calEvent, *events );

        if ( calEvent->Repeat() ) {
           createRecurrenceEvents(event);
        }
    }

    return *events;
}

void CalEngine::createRecurrenceEvents(KCalCore::Event *event)
{
    QDate today = QDate::currentDate();
    QDate startDate = today.addDays(-45);

    for ( int i=0; i<90; i++ )
    {
       QDate date = startDate.addDays(i);

       if ( event->recursOn( date, KDateTime::Spec(KDateTime::LocalZone)) )
        {
           bool evDate = date == event->dtStart().date();
           if ( evDate == false )
           {
               CalendarEvent* calEvent = new CalendarEvent();

               calEvent->SetCalendar( calendars->at(0) );
               calEvent->SetUid( event->uid() );
               calEvent->SetDescription( event->description() );
               calEvent->SetCalendarType(0); //currently we have only one notebook
               calEvent->SetAllDay( event->allDay() );
               calEvent->SetMultipleDays( event->isMultiDay() );
               QDateTime stDT = event->dtStart().dateTime();
               stDT.setDate(date);
               calEvent->SetStartDate( stDT );
               QDateTime endDT = event->dtEnd().dateTime();
               endDT.setDate(date);
               calEvent->SetEndDate( endDT );
               calEvent->SetRepeatId( event->recurrenceId().dateTime() );

               parseRecurrence(calEvent, event);

               calEvent->SetNotes( event->altDescription() );
               calEvent->SetCalCoreEvent(event);

               calEvent->SetAlarm( false );
               if ( event->hasEnabledAlarms() ) {
                   KCalCore::Alarm::List alarmList = event->alarms();

                   if ( alarmList.count() > 0 ) {
                       for ( int j=0; j < alarmList.count();j++ )
                       {
                           KCalCore::Alarm::Ptr ptr = alarmList.at(j);
                           KCalCore::Alarm* alarm = ptr.data();
                           KDateTime altime = alarm->time();

                           if ( altime.date() == date )
                           {
                               calEvent->SetAlarm(true);
                               calEvent->SetAlarmDate( altime.dateTime() );
                           }
                       }
                   } else {
                       calEvent->SetAlarm( false );
                   }
               }
               addItemSorted( calEvent, *events );
           }
        }
    }
}

QList<CalendarEvent*>& CalEngine::getCalendarEvents()
{
    return *events;
}

void CalEngine::clearEventsList()
{
    for ( int i=0;i<events->count();i++ )
    {
        CalendarEvent* eventFromList = events->at(i);
        delete eventFromList;
    }
    events->clear();
}

void CalEngine::addItemSorted(CalendarEvent* evt, QList<CalendarEvent*>& eventList)
{
    QDateTime newDt = evt->StartDate();
    if ( eventList.count() == 0 ) {
        eventList.append(evt);
    } else if ( eventList.count() == 1 ) {
        QDateTime oldDt = eventList.at(0)->StartDate();
        if ( newDt > oldDt ) {
            eventList.append(evt);
        } else {
            eventList.insert(0, evt);
        }
    } else {
        //Bug7316 Author: Sirisha Muppavarapu
        //Events were not added in the sorted order
        //This is a linear sort. Very horrible, but a quick fix for now
        bool inserted = false;
        for ( int j=0; j<eventList.count(); j++ )
        {
            QDateTime oldDt1 = eventList.at(j)->StartDate();
            if ( newDt <= oldDt1 ) {
                eventList.insert(j, evt);
                inserted = true;
                break;
            }
        }
        if(!inserted) {
            events->append(evt);
        }
    }
}

void CalEngine::createEvent( CalendarEvent &event )
{
    KCalCore::Event* newEvent = new KCalCore::Event();

    Notebook::List nbList = storage->notebooks();
    Notebook::Ptr nbPtr = nbList.at( event.CalendarType() );
    Notebook* nb = nbPtr.data();

    newEvent->setAllDay( event.AllDay() );

    if ( &event.Description() && event.Description().length() ) {
         newEvent->setDescription( event.Description() );
    }

    if ( &event.Notes() && event.Notes().length() ) {
        newEvent->setAltDescription( event.Notes() );
    }

    if ( event.Alarm() ) {
        KCalCore::Alarm* newAlarm = new KCalCore::Alarm( newEvent );
        newAlarm->setType( KCalCore::Alarm::Display );
        newAlarm->setText( newEvent->description() );
        newAlarm->setTime( KDateTime(event.AlarmDate(), KDateTime::Spec(KDateTime::LocalZone)) );
        newAlarm->setSnoozeTime( KCalCore::Duration( 60*15 ) );
        newAlarm->setEnabled(true);
        KCalCore::Alarm::Ptr newAlarmPtr = KCalCore::Alarm::Ptr( newAlarm );
        newEvent->addAlarm( newAlarmPtr );
    }

    KCalCore::Recurrence* newRecurrence = newEvent->recurrence();

    if( event.Repeat() )
       {
        newRecurrence->setEndDate( event.RepeatEndDate().date() );
        QBitArray *qb = new QBitArray(10);

        switch( event.RepeatType() )
           {
           case 1: //once
               newRecurrence->setDaily(1);
               newRecurrence->setDuration(2);
               break;
           case 2://daily
               newRecurrence->setDaily(1);
               break;
           case 3://mon-fri
               for(int i=0;i<5;i++)
               {
                   qb->setBit(i,true);
               }
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 4://weekly mon
               qb->setBit(0,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 5://weekly tue
               qb->setBit(1,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 6:
               qb->setBit(2,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 7:
               qb->setBit(3,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 8:
               qb->setBit(4,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 9:
               qb->setBit(5,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           case 10:
               qb->setBit(6,true);
               newRecurrence->setWeekly(1,*qb, 1);
               break;
           }
       }
       else
       {
           newRecurrence->clear();
           //newRecurrence->setNewRecurrenceType(0,0);
       }

        // if events is allday, then we set only the dates. Do not set any times.
       if ( event.AllDay() ) {
           KDateTime startDT( event.StartDate().date(), KDateTime::Spec(KDateTime::LocalZone) );
           newEvent->setDtStart( startDT );
           KDateTime endDT( event.EndDate().date(), KDateTime::Spec(KDateTime::LocalZone) );
           newEvent->setDtEnd( endDT );
           newEvent->setHasEndDate( true );
       } else {
           KDateTime startDT( event.StartDate(), KDateTime::Spec(KDateTime::LocalZone) );
           newEvent->setDtStart( startDT );
           KDateTime endDT( event.EndDate(), KDateTime::Spec(KDateTime::LocalZone) );
           newEvent->setDtEnd( endDT );
           newEvent->setHasEndDate( true );
           newEvent->setDuration( KCalCore::Duration( startDT, endDT ) );
       }

    KCalCore::Event::Ptr newEventPtr = KCalCore::Event::Ptr( newEvent );

    event.SetCalCoreEvent( newEvent );
    calendar->addEvent(newEventPtr, nb->uid() );
    storage->save();
    calendar->save();
    //storage->loadNotebookIncidences(notebook->uid());
}

void CalEngine::removeEvent( CalendarEvent &event )
{
    KCalCore::Event::Ptr ptr = KCalCore::Event::Ptr( event.GetCalCoreEvent() );
    calendar->deleteEvent( ptr );
    storage->save();
    calendar->save();
    //storage->loadNotebookIncidences(notebook->uid());
}

void CalEngine::modifyEvent( CalendarEvent &event )
{
    removeEvent( event );
    createEvent( event );
}

void CalEngine::parseRecurrence(CalendarEvent *calEvent, KCalCore::Event *event)
{
    int recurrenceType = event->recurrenceType();
    calEvent->SetRepeat( true );
    if ( recurrenceType == 3 ) { //3 == daily
        calEvent->SetRepeatType( 2 );
    } else if ( recurrenceType == 4 ) //4 == weekly
    {
        QBitArray dayBitArray = event->recurrence()->days();
        for (int j=0; j<dayBitArray.count();j++)
        {
            if ( dayBitArray.at(j) == true )
            {
                calEvent->SetRepeatType( j+3 );
                break;
            }
        }
    } else if ( recurrenceType == 0 ) //0 == none
    {
        calEvent->SetRepeatType( 0 );
        calEvent->SetRepeat( false );
    } else {
        QBitArray dayBitArray = event->recurrence()->days();
        if ( dayBitArray.count() > 0) {
            calEvent->SetRepeatType( 3 );
        } else {
          calEvent->SetRepeatType( 0 );
          calEvent->SetRepeat( false );
        }
    }
}
