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

#ifndef CALENGINE_H
#define CALENGINE_H

#include <extendedcalendar.h>
#include <extendedstorage.h>
#include <notebook.h>

using namespace mKCal;

class CalendarData;
class CalendarEvent;

class CalEngine
{
public:   
    /**
      CalEngine::CalEngine()
    */
    CalEngine();

    /**
      CalEngine::~CalEngine()
    */
    ~CalEngine();

    /**
      QList<CalendarData*>& getCalendars()

      @return List of calendars
    */
    QList<CalendarData*>& getCalendars();

    /**
      @param calendar
      @param startDate
      @param endDate
      @return List of calendar events
      */
    QList<CalendarEvent*>& getCalendarEvents( CalendarData *calendar );

    /**
      */
    QList<CalendarEvent*>& getCalendarEvents();

    /**
      */
    void createEvent( CalendarEvent &event );

    /**
      */
    void removeEvent( CalendarEvent &event );

    /**
      */
    void modifyEvent( CalendarEvent &event );
    /**
      */
    void parseRecurrence(CalendarEvent* calEvent, KCalCore::Event* event);
    /**
      */
    void createRecurrenceEvents(KCalCore::Event *event);
    /**
      */
    void reloadEvents();

private:
    /**
      void addItemSorted(CalendarEvent* evt, QList<CalendarEvent*>& eventList)
      */
    void addItemSorted(CalendarEvent* evt, QList<CalendarEvent*>& eventList);
    /**
      void clearEventsList
      */
    void clearEventsList();

private:
    ExtendedCalendar *calendar;
    ExtendedCalendar::Ptr calendarPtr;

    ExtendedStorage *storage;
    Notebook *notebook;

    QList<CalendarData*>* calendars;
    QList<CalendarEvent*>* events;
};

#endif // CALENGINE_H
