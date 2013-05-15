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

#ifndef MCALENDARLAYOUT_H
#define MCALENDARLAYOUT_H

#include <QGraphicsGridLayout>

enum EWeekDays
{
    EMonday = 0,
    ETuesday,
    EWednesday,
    EThursday,
    EFriday,
    ESaturday,
    ESunday
};

enum ECellType
{
    EWeekLabel = 1,
    EMonthsDay = 2,
    ENotMonthsDay = 3
};

class MViewManager;

class MCalendarLayout : public QGraphicsGridLayout
{
public:
    /**
      MCalendarLayout( QGraphicsWidget* widget, MViewManager* manager);
      */
    MCalendarLayout( QGraphicsWidget* widget, MViewManager* manager);

    ~MCalendarLayout();
    /**
      void daySelected( const QDate& date );
      */
    void daySelected( const QDate& date );
    /**
      void setNextMonth():
      */
    void setNextMonth();
    /**
      void setPreviousMonth():
      */
    void setPreviousMonth();
    /**
      void populateCalendar();
      */
    void populateCalendar();
    /**
      void setWeekdayOffset(int offset);
      */
    void setWeekdayOffset(int offset);
    /**
      QDate currentDate();
      */
    QDate currentDate();

private:
    /**
      void writeSettings();
      */
    void writeSettings();
    /**
      vvoid readSettings();
      */
    void readSettings();

private:
    MViewManager* viewManager;
    QDate* currDate;
    int visibleRows;
    int visibleColumns;
    int weekDayOffset;
};
#endif // MCALENDARLAYOUT_H
