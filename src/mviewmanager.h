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

#ifndef MVIEWMANAGER_H
#define MVIEWMANAGER_H

#include <MWidget>
#include <QList>

#include "calendarevent.h"
#include "calendardata.h"
#include "calengine.h"

class MApplicationPage;
class MComboBox;
class MWidgetAction;
class MCreateNewdialog;

enum ViewIndex
{
    EComingUpView = 0,
    EMonthView,
    EThreeDayView
};

class MViewManager : public QObject
{
   Q_OBJECT

public:
    /**
      MViewManager();
      */
    MViewManager();
    /**
      ~MViewManager();
      */
    ~MViewManager();
    /**
      void changeView(int viewIndex);
      */
    void changeView(int viewIndex);

public:
    /**
      int getDateEventCount( const QDate & date ) const;
      */
    int getDateEventCount( const QDate & date ) const;
    /**
      bool isAlldayEvent( const QDate & date, QColor& color ) const;
      */
    bool isAlldayEvent( const QDate & date, QColor& color ) const;
    /**
      bool isMultipledaysEvent( const QDate & date ) const;
      */
    bool isMultipledaysEvent( const QDate & date ) const;
    /**
      float getDateEventHours( const QDate & date ) const;
      */
    float getDateEventHours( const QDate & date ) const;
    /**
      QList<CalendarEvent*> getDateEvents( const QDate & date );
      */
    QList<CalendarEvent*> getDateEvents( const QDate & date );
    /**
      QList<CalendarEvent*>& GetEvents();
      */
    QList<CalendarEvent*>& GetEvents();
    /**
      void setSelectedDate(const QDate& date);
      */
    void setSelectedDate(const QDate& date);
    /**
      const QDate& getSelectedDate();
      */
    const QDate& getSelectedDate();
    /**
      void showEventDetails(CalendarEvent* event);
      */
    void showEventDetails(CalendarEvent* event);
    /**
      void handleEditCalendarEvent( CalendarEvent* calendarEventToEdit=0 );
      */
    void handleEditCalendarEvent( CalendarEvent* calendarEventToEdit=0 );
    /**
      QList<QString*>& getCalendarNames();
      */
    QList<QString*>& getCalendarNames();
    /**
      CalendarData* GetCalendarByName( const QString& name );
      */
    CalendarData* GetCalendarByName( const QString& name );
    /**
      void addNewCalendarEvent( CalendarEvent* newCalendarEvent );
      */
    void addNewCalendarEvent( CalendarEvent* newCalendarEvent );
    /**
      void deleteEvent(CalendarEvent* calendarEventToRemove);
      */
    void deleteEvent(CalendarEvent* calendarEventToRemove);
    /**
      void changeCalendarEvent(CalendarEvent* editEvent);
      */
    void changeCalendarEvent(CalendarEvent* editEvent);

public:
   /**
      void writeSettings();
      */
    void writeSettings();
private:
    /**
      void setupCalendarEngine();
      */
    void setupCalendarEngine();
    /**
      void readSettings();
      */
    void readSettings();
    /**
      bool isSameDate( const QDate & date1, const QDate & date2 ) const;
      */
    bool isSameDate( const QDate & date1, const QDate & date2 ) const;
    /**
      bool setCalendarByFilter( const QString& filter, bool disableUpdate );
      */
    bool setCalendarByFilter( const QString& filter, bool disableUpdate );
    /**
      void addItemSorted(CalendarEvent* evt);
      */
    void addItemSorted(CalendarEvent* evt);
public:
    /**
      void updateEvents();
      */
    void updateEvents();

public Q_SLOTS:
    /**
      void comingUpViewAppeared();
      */
    void comingUpViewAppeared();
    /**
      void monthViewAppeared();
      */
    void monthViewAppeared();
    /**
      void threeDayViewAppeared();
      */
    void threeDayViewAppeared();

private:
    QList<MApplicationPage *> pageList;
    int currentViewIndex;

    QDate* selectedDate;

    CalEngine*              calendarEngine;
    QList<CalendarEvent*>*  events;
    QList<QString *>*        calendarFilters;
    QList<QString *>*        calendarNames;
    QList<CalendarData*>*   calendars;
    QString*                calendarFilterAll;
    MCreateNewdialog*        editDlg;
};
#endif // MVIEWMANAGER_H
