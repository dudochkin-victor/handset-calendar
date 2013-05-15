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

#ifndef MCREATENEWDIALOG_H
#define MCREATENEWDIALOG_H

#include <MDialog>
#include "calendarevent.h"
#include "mviewmanager.h"
#include <MButton>


class MTextEdit;
class MComboBox;
class MSlider;
class QGraphicsGridLayout;
class MLabel;
class MLinearLayoutPolicy;
class QGraphicsLinearLayout;



class MAmPmButton : public MButton
{
    Q_OBJECT

public:
    MAmPmButton();
    ~MAmPmButton();

public Q_SLOTS:
    /**
      void changeState();
      */
    void changeState();

public:
    enum buttonState
    {
       EAm = 0,
       EPm
    };

    /**
      void getState();
      return "AM" or "PM"
      */
    QString getState();

    /**
      void setState( buttonState btState );
      */
    void setState( buttonState btState );

    /**
      void setState( const QString &ampm );
      */
    void setState( const QString &ampm );

private:
    buttonState state;
};

class MCreateNewdialog : public MDialog
{
    Q_OBJECT

public:
    /**
      void updateEvents();
      */
    MCreateNewdialog(MViewManager* manager, CalendarEvent* eventToEdit=0);
    /**
      bool verifyDateTimes();
      */
    bool verifyDateTimes();

public Q_SLOTS:
    /**
      void dialogAccepted();
      */
    void dialogAccepted();
    /**
      void dialogRejected();
      */
    void dialogRejected();
    /**
      void allDaySwitchStateChanged();
      */
    void allDaySwitchStateChanged();
    /**
      void repeatSwitchStateChanged();
      */
    void repeatSwitchStateChanged();
    /**
      void alarmSwitchStateChanged();
      */
    void alarmSwitchStateChanged();

private:
    MViewManager* viewManager;
    CalendarEvent* editEvent;

    MTextEdit   *eventTitleEdit;
    MComboBox   *calendarComboBox;
    MButton     *alldaySwitch;
    MTextEdit   *stDtDayEdit;
    MTextEdit   *stDtMonthEdit;
    MTextEdit   *stDtYearEdit;
    MLabel      *startTimeNameLabel;
    MTextEdit   *stTimeHourEdit;
    MTextEdit   *stTimeMinEdit;
    MLabel      *endDateNameLabel;
    MTextEdit   *endDtDayEdit;
    MTextEdit   *endDtMonthEdit;
    MTextEdit   *endDtYearEdit;
    MLabel      *endTimeNameLabel;
    MTextEdit   *endTimeHourEdit;
    MTextEdit   *endTimeMinEdit;
    MTextEdit   *alarmDtDayEdit;
    MTextEdit   *alarmDtMonthEdit;
    MTextEdit   *alarmDtYearEdit;
    MTextEdit   *alarmTimeHourEdit;
    MTextEdit   *alarmTimeMinEdit;
    MButton     *repeatSwitch;
    MLabel      *repeatTypeNameLabel;
    MComboBox   *repeatComboBox;
    MLabel      *repeatEndDateNameLabel;
    MTextEdit   *repeatEndDtDayEdit;
    MTextEdit   *repeatEndDtMonthEdit;
    MTextEdit   *repeatEndDtYearEdit;
    MButton     *alarmSwitch;
    MTextEdit   *notesEdit;
    QGraphicsGridLayout *gridLayout;
    MLabel* alarmDateNameLabel;
    MLabel* alarmTimeNameLabel;
    QGraphicsLinearLayout* startDtLinLayout;
    MLinearLayoutPolicy *mainPolicy;
    QGraphicsWidget *allDayWidget;
    QGraphicsWidget *startDtWidget;
    QGraphicsWidget *endDtWidget;
    QGraphicsWidget *repeatWidget;
    QGraphicsWidget *repeatTypeWidget;
    QGraphicsWidget *repeatEndDtWidget;
    QGraphicsWidget *alarmWidget;
    QGraphicsWidget *alarmDtWidget;

    MAmPmButton *startAmPm;
    MAmPmButton *endAmPm;
    MAmPmButton *alarmAmPm;
};

#endif // MCREATENEWDIALOG_H
