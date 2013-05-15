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

#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QString>
#include <QDateTime>
#include <event.h>

class CalendarData;

class CalendarEvent
{
public:
    /**
      CalendarEvent::CalendarEvent()
    */
    CalendarEvent();
    /**
      CalendarEvent(const QString& newDescription,
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
                  KCalCore::Event* coreEvent);
    */
    CalendarEvent(const QString& newDescription,
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
                  KCalCore::Event* coreEvent);
    /**
      CalendarEvent::~CalendarEvent()
    */
    ~CalendarEvent();

public:
    //Getters
    /**
      CalendarData* Calendar();
    */
    CalendarData* Calendar();
    /**
      QString& Uid();
    */
    QString& Uid();
    /**
      QString& Description();
    */
    QString& Description();
    /**
      int CalendarType();
    */
    int CalendarType();
    /**
      bool AllDay();
    */
    bool AllDay();
    /**
      bool MultipleDays();
    */
    bool MultipleDays();
    /**
      QDateTime& StartDate();
    */
    QDateTime& StartDate();
    /**
      QDateTime& EndDate();
    */
    QDateTime& EndDate();
    /**
      bool Repeat();
    */
    bool Repeat();
    /**
      int RepeatType();
    */
    int RepeatType();
    /**
     QDateTime& RepeatId();
    */
    QDateTime& RepeatId();
    /**
      QDateTime& RepeatEndDate();
    */
    QDateTime& RepeatEndDate();
    /**
      bool Alarm();
    */
    bool Alarm();
    /**
     QDateTime& AlarmDate();
    */
    QDateTime& AlarmDate();
    /**
      QString& Notes();
    */
    QString& Notes();
    /**
      KCalCore::Event* GetCalCoreEvent();
    */
    KCalCore::Event* GetCalCoreEvent();

    //Setters
    /**
      void SetCalendar( CalendarData* calendar );
    */
    void SetCalendar( CalendarData* calendar );
    /**
      void SetUid( const QString& newUid );
    */
    void SetUid( const QString& newUid );
    /**
      void SetDescription( const QString& newDescription );
    */
    void SetDescription( const QString& newDescription );
    /**
      void SetCalendarType(int newType);
    */
    void SetCalendarType(int newType);
    /**
      void SetAllDay(bool newAllDay);
    */
    void SetAllDay(bool newAllDay);
    /**
      void SetMultipleDays(bool newMultipleDays);
    */
    void SetMultipleDays(bool newMultipleDays);
    /**
      void SetStartDate(const QDateTime& newStartDate);
    */
    void SetStartDate(const QDateTime& newStartDate);
    /**
      void SetEndDate(const QDateTime& newEndDate);
    */
    void SetEndDate(const QDateTime& newEndDate);
    /**
      void SetRepeat(bool newRepeat);
    */
    void SetRepeat(bool newRepeat);
    /**
      void SetRepeatType(int newRepeatType);
    */
    void SetRepeatType(int newRepeatType);
    /**
      void SetRepeatEndDate(const QDateTime& newRepeatEndDate);
    */
    void SetRepeatEndDate(const QDateTime& newRepeatEndDate);
    /**
      void SetAlarm(bool newAlarm);
    */
    void SetAlarm(bool newAlarm);
    /**
      void SetAlarmDate(const QDateTime& newAlarmDate);
    */
    void SetAlarmDate(const QDateTime& newAlarmDate);
    /**
      void SetNotes(const QString& newNotes);
    */
    void SetNotes(const QString& newNotes);
    /**
      void SetCalCoreEvent(KCalCore::Event* coreEvent);
    */
    void SetCalCoreEvent(KCalCore::Event* coreEvent);
    /**
      void SetRepeatId(const QDateTime& newRepeatId);
    */
    void SetRepeatId(const QDateTime& newRepeatId);

private:
    CalendarData* calendarData;
    QString*    uid;
    QString*    description;
    int         calendarType;
    bool        allDay;
    bool        multipleDays;
    QDateTime*  startDate;
    QDateTime*  endDate;
    bool        repeat;
    int         repeatType;
    QDateTime*  repeatEndDate;
    QDateTime*  repeatId;
    bool        alarm;
    QDateTime*  alarmDate;
    QString*    notes;
    KCalCore::Event* calCoreEvent;
};

#endif // CALENDAREVENT_H
