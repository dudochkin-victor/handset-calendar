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

#include "calendarevent.h"
#include "calendardata.h"

CalendarEvent::CalendarEvent()
{
    //uri             = new QString("");
    uid             = new QString("");
    description     = new QString("description");
    calendarType    = 0;
    allDay          = qrand()%2;

    startDate       = new QDateTime(QDateTime::currentDateTime().addDays( -10 + qrand()%20 ).addSecs(qrand()%30*1800));
    endDate         = new QDateTime( startDate->addSecs(1800 + qrand()%3*1800 ) );

    repeat          = false;

    repeatEndDate   = new QDateTime( startDate->addYears(50) );

    alarm           = qrand()%2;
    alarmDate       = new QDateTime(startDate->addSecs(-900));

    notes           = new QString("notes");
    calendarData = NULL;

    calCoreEvent = NULL;

    repeatId = NULL;
}

CalendarEvent::CalendarEvent (const QString& newDescription,
                              int newType,
                              bool newAllDay,
                              const QDateTime& newStartDate,
                              const QDateTime& newEndDate,
                              bool newRepeat,
                              int newRepeatType,
                              const QDateTime& newRepeatEndDate,
                              bool newAlarm,
                              const QDateTime& newAlarmDate,
                              const QString& newNotes,
                              KCalCore::Event* coreEvent)
{
    uid             = new QString("");
    description     = new QString(newDescription);
    calendarType    = newType;
    allDay          = newAllDay;
    startDate       = new QDateTime(newStartDate);
    endDate         = new QDateTime(newEndDate);
    repeat          = newRepeat;
    repeatType      = newRepeatType;
    repeatEndDate   = new QDateTime(newRepeatEndDate);
    alarm           = newAlarm;
    alarmDate       = new QDateTime(newAlarmDate);
    notes           = new QString(newNotes);
    //uri             = new QString("");
    calendarData = NULL;
    calCoreEvent = coreEvent;
    repeatId = NULL;
}

CalendarEvent::~CalendarEvent()
{
    //delete uri;
    delete uid;
    delete description;
    delete startDate;
    delete endDate;
    delete alarmDate;
    delete notes;
    delete repeatId;
    delete repeatEndDate;
}

CalendarData* CalendarEvent::Calendar()
{
    return calendarData;
}

QString& CalendarEvent::Uid()
{
    return *uid;
}

QString& CalendarEvent::Description()
{
    return *description;
}

int CalendarEvent::CalendarType()
{
    return calendarType;
}

bool CalendarEvent::AllDay()
{
    return allDay;
}

bool CalendarEvent::MultipleDays()
{
    return multipleDays;
}

QDateTime& CalendarEvent::StartDate()
{
    return *startDate;
}

QDateTime& CalendarEvent::EndDate()
{
    return *endDate;
}

bool CalendarEvent::Repeat()
{
    return repeat;
}

int CalendarEvent::RepeatType()
{
    return repeatType;
}

bool CalendarEvent::Alarm()
{
    return alarm;
}

QDateTime& CalendarEvent::AlarmDate()
{
    return *alarmDate;
}

QString& CalendarEvent::Notes()
{
    return *notes;
}

void CalendarEvent::SetCalendar( CalendarData* calendar )
{
    calendarData = calendar;
}

void CalendarEvent::SetUid( const QString& newUid )
{
    if ( uid ) {
        delete uid;
    }
    uid = new QString(newUid);
}

void CalendarEvent::SetDescription( const QString& newDescription )
{
    if ( description ) {
        delete description;
    }
    description = new QString(newDescription);
}

void CalendarEvent::SetCalendarType(int newType)
{
    calendarType = newType;
}

void CalendarEvent::SetAllDay(bool newAllDay)
{
    allDay = newAllDay;
}

void CalendarEvent::SetMultipleDays(bool newMultipleDays)
{
    multipleDays = newMultipleDays;
}

void CalendarEvent::SetStartDate(const QDateTime& newStartDate)
{
    if ( startDate ) {
        delete startDate;
    }
    startDate = new QDateTime(newStartDate);
}

void CalendarEvent::SetEndDate(const QDateTime& newEndDate)
{
    if ( endDate ) {
        delete endDate;
    }
    endDate = new QDateTime(newEndDate);
}

void CalendarEvent::SetRepeat(bool newRepeat)
{
    repeat = newRepeat;
}

void CalendarEvent::SetRepeatType(int newRepeatType)
{
    repeatType = newRepeatType;
}

void CalendarEvent::SetRepeatId(const QDateTime& newRepeatId)
{
    if (repeatId) {
        delete repeatId;
    }
    repeatId = new QDateTime(newRepeatId);
}

QDateTime& CalendarEvent::RepeatId()
{
    return *repeatId;
}

void CalendarEvent::SetAlarm(bool newAlarm)
{
    alarm = newAlarm;
}

void CalendarEvent::SetAlarmDate(const QDateTime& newAlarmDate)
{
    if ( alarmDate ) {
        delete alarmDate;
    }
    alarmDate = new QDateTime(newAlarmDate);
}

void CalendarEvent::SetNotes(const QString& newNotes)
{
    if ( notes ) {
        delete notes;
    }
    notes = new QString(newNotes);
}

void CalendarEvent::SetCalCoreEvent(KCalCore::Event* coreEvent)
{
    calCoreEvent = coreEvent;
}

KCalCore::Event* CalendarEvent::GetCalCoreEvent()
{
    return calCoreEvent;
}


void CalendarEvent::SetRepeatEndDate(const QDateTime& newRepeatEndDate)
{
    if ( repeatEndDate ) {
        delete repeatEndDate;
    }
    repeatEndDate = new QDateTime(newRepeatEndDate);
}

QDateTime& CalendarEvent::RepeatEndDate()
{
    return *repeatEndDate;
}
