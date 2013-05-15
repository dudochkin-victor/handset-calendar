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

#include "mdetaildialog.h"
#include <MLayout>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <MLinearLayoutPolicy>
#include <MLabel>
#include <MButton>

MDetailDialog::MDetailDialog( MViewManager* manager, CalendarEvent* eventToView ) : MDialog(),
viewManager(manager),
event(eventToView)
{
    QGraphicsWidget *panel = centralWidget();
    MLayout *layout = new MLayout(panel);

    MLinearLayoutPolicy *mainPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    QGraphicsWidget *labelWidget = new QGraphicsWidget;
    QGraphicsGridLayout *gridLayout = new QGraphicsGridLayout(labelWidget);

    int row = 0;

    //EDescription
    MLabel* descriptionNameLabel = new MLabel();
    MLabel* descriptionLabel = new MLabel();
    //% "Description:"
    descriptionNameLabel->setText(qtTrId("lbl_description"));
    descriptionNameLabel->setAlignment(Qt::AlignLeft);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setText( event->Description() );
    descriptionLabel->setAlignment(Qt::AlignLeft);
    descriptionNameLabel->setPreferredWidth(1);
    descriptionLabel->setPreferredWidth(1);
    gridLayout->addItem(descriptionNameLabel, row, 0);
    gridLayout->addItem(descriptionLabel, row, 1);
    row+=1;

    //ECalendarType
    MLabel* calendarTypeNameLabel = new MLabel();
    MLabel* calendarTypeLabel = new MLabel();
    //% "Calendar:"
    calendarTypeNameLabel->setText(qtTrId("lbl_calendar"));
    calendarTypeNameLabel->setAlignment(Qt::AlignLeft);
    if ( event->Calendar() ) {
        calendarTypeLabel->setText( event->Calendar()->Name() );
    } else {
        //% "Default"
        calendarTypeLabel->setText( qtTrId("lbl_default") );
    }
    calendarTypeLabel->setAlignment(Qt::AlignLeft);
    calendarTypeNameLabel->setPreferredWidth(1);
    calendarTypeLabel->setPreferredWidth(1);
    gridLayout->addItem(calendarTypeNameLabel, row, 0);
    gridLayout->addItem(calendarTypeLabel, row, 1);
    row+=1;

    //EAllDay
    if ( event->AllDay() ) {
        MLabel* allDayNameLabel = new MLabel();
        MLabel* allDayLabel = new MLabel();
        //% "All day:"
        allDayNameLabel->setText(qtTrId("lbl_all_day"));
        allDayNameLabel->setAlignment(Qt::AlignLeft);
        //% "Event lasts all day"
        allDayLabel->setText(qtTrId("lbl_event_lasts_all_day"));
        allDayLabel->setAlignment(Qt::AlignLeft);
        allDayNameLabel->setPreferredWidth(1);
        allDayLabel->setPreferredWidth(1);
        gridLayout->addItem(allDayNameLabel, row, 0);
        gridLayout->addItem(allDayLabel, row, 1);
        row+=1;

        //EStartDate
        MLabel* startDateNameLabel = new MLabel();
        MLabel* startDateLabel = new MLabel();
        //% "Start date:"
        startDateNameLabel->setText(qtTrId("lbl_start_date"));
        startDateNameLabel->setAlignment(Qt::AlignLeft);
        startDateLabel->setText( event->StartDate().toString("dd.MM.yyyy") );
        startDateLabel->setAlignment(Qt::AlignLeft);
        startDateNameLabel->setPreferredWidth(1);
        startDateLabel->setPreferredWidth(1);
        gridLayout->addItem(startDateNameLabel, row, 0);
        gridLayout->addItem(startDateLabel, row, 1);
        row+=1;
    } else {
        //EStartDate
        MLabel* startDateNameLabel = new MLabel();
        MLabel* startDateLabel = new MLabel();
        //% "Start date:"
        startDateNameLabel->setText(qtTrId("lbl_start_date"));
        startDateNameLabel->setAlignment(Qt::AlignLeft);
        startDateLabel->setText( event->StartDate().toString("dd.MM.yyyy") );
        startDateLabel->setAlignment(Qt::AlignLeft);
        startDateNameLabel->setPreferredWidth(1);
        startDateLabel->setPreferredWidth(1);
        gridLayout->addItem(startDateNameLabel, row, 0);
        gridLayout->addItem(startDateLabel, row, 1);
        row+=1;

        //EStartTime
        MLabel* startTimeNameLabel = new MLabel();
        MLabel* startTimeLabel = new MLabel();
        //% "Start time:"
        startTimeNameLabel->setText(qtTrId("lbl_start_time"));
        startTimeNameLabel->setAlignment(Qt::AlignLeft);
        startTimeLabel->setText( event->StartDate().toString("hh:mm AP") );
        startTimeLabel->setAlignment(Qt::AlignLeft);
        startTimeNameLabel->setPreferredWidth(1);
        startTimeLabel->setPreferredWidth(1);
        gridLayout->addItem(startTimeNameLabel, row, 0);
        gridLayout->addItem(startTimeLabel, row, 1);
        row+=1;

        //EEndDate
        MLabel* endDateNameLabel = new MLabel();
        MLabel* endDateLabel = new MLabel();
        //% "End date:"
        endDateNameLabel->setText(qtTrId("lbl_end_date"));
        endDateNameLabel->setAlignment(Qt::AlignLeft);
        endDateLabel->setText( event->EndDate().toString("dd.MM.yyyy") );
        endDateLabel->setAlignment(Qt::AlignLeft);
        endDateNameLabel->setPreferredWidth(1);
        endDateLabel->setPreferredWidth(1);
        gridLayout->addItem(endDateNameLabel, row, 0);
        gridLayout->addItem(endDateLabel, row, 1);
        row+=1;

        //EEndTime
        MLabel* endTimeNameLabel = new MLabel();
        MLabel* endTimeLabel = new MLabel();
        //% "End time:"
        endTimeNameLabel->setText(qtTrId("lbl_end_time:"));
        endTimeNameLabel->setAlignment(Qt::AlignLeft);
        endTimeLabel->setText( event->EndDate().toString("hh:mm AP") );
        endTimeLabel->setAlignment(Qt::AlignLeft);
        endTimeNameLabel->setPreferredWidth(1);
        endTimeLabel->setPreferredWidth(1);
        gridLayout->addItem(endTimeNameLabel, row, 0);
        gridLayout->addItem(endTimeLabel, row, 1);
        row+=1;
    }

    if ( event->Repeat() ) {
        //ERepeat
        MLabel* repeatNameLabel = new MLabel();
        MLabel* repeatLabel = new MLabel();
        //% "Repeat:"
        repeatNameLabel->setText(qtTrId("lbl_repeat:"));
        repeatNameLabel->setAlignment(Qt::AlignLeft);
        //% "Repeating event"
        repeatLabel->setText(qtTrId("lbl_repeating_event"));
        repeatLabel->setAlignment(Qt::AlignLeft);
        repeatNameLabel->setPreferredWidth(1);
        repeatLabel->setPreferredWidth(1);
        gridLayout->addItem(repeatNameLabel, row, 0);
        gridLayout->addItem(repeatLabel, row, 1);
        row+=1;

        //ERepeatType
        MLabel* repeatTypeNameLabel = new MLabel();
        MLabel* repeatTypeLabel = new MLabel();
        //% "Repeat type:"
        repeatTypeNameLabel->setText(qtTrId("lbl_repeat_type"));
        repeatTypeNameLabel->setAlignment(Qt::AlignLeft);
        repeatTypeLabel->setText( repeatTypetext() );
        repeatTypeLabel->setAlignment(Qt::AlignLeft);
        repeatTypeNameLabel->setPreferredWidth(1);
        repeatTypeLabel->setPreferredWidth(1);
        gridLayout->addItem(repeatTypeNameLabel, row, 0);
        gridLayout->addItem(repeatTypeLabel, row, 1);
        row+=1;
    }

    if ( event->Alarm() ) {
        //EAlarm
        MLabel* alarmNameLabel = new MLabel();
        MLabel* alarmLabel = new MLabel();
        //% "Alarm:"
        alarmNameLabel->setText(qtTrId("lbl_alarm"));
        alarmNameLabel->setAlignment(Qt::AlignLeft);
        //% "ON/OFF"
        alarmLabel->setText(qtTrId("lbl_on_off"));
        alarmLabel->setAlignment(Qt::AlignLeft);
        alarmNameLabel->setPreferredWidth(1);
        alarmLabel->setPreferredWidth(1);
        gridLayout->addItem(alarmNameLabel, row, 0);
        gridLayout->addItem(alarmLabel, row, 1);
        row+=1;

        //EAlarmDate
        MLabel* alarmDateNameLabel = new MLabel();
        MLabel* alarmDateLabel = new MLabel();
        //% "Alarm date:"
        alarmDateNameLabel->setText(qtTrId("lbl_alarm_date"));
        alarmDateNameLabel->setAlignment(Qt::AlignLeft);
        alarmDateLabel->setText( event->AlarmDate().toString("dd:MM:yyyy") );
        alarmDateLabel->setAlignment(Qt::AlignLeft);
        alarmDateNameLabel->setPreferredWidth(1);
        alarmDateLabel->setPreferredWidth(1);
        gridLayout->addItem(alarmDateNameLabel, row, 0);
        gridLayout->addItem(alarmDateLabel, row, 1);
        row+=1;

        //EAlarmTime
        MLabel* alarmTimeNameLabel = new MLabel();
        MLabel* alarmtimeLabel = new MLabel();
        //% "Alarm time:"
        alarmTimeNameLabel->setText(qtTrId("lbl_alarm_time"));
        alarmTimeNameLabel->setAlignment(Qt::AlignLeft);
        alarmtimeLabel->setText( event->AlarmDate().toString("hh:mm AP") );
        alarmtimeLabel->setAlignment(Qt::AlignLeft);
        alarmTimeNameLabel->setPreferredWidth(1);
        alarmtimeLabel->setPreferredWidth(1);
        gridLayout->addItem(alarmTimeNameLabel, row, 0);
        gridLayout->addItem(alarmtimeLabel, row, 1);
        row+=1;
    }

    //ENotes
    if ( event->Notes().length() > 0 ) {
        MLabel* notesNameLabel = new MLabel();
        MLabel* notesLabel = new MLabel();
        //% "Notes:"
        notesNameLabel->setText(qtTrId("lbl_notes:"));
        notesNameLabel->setAlignment(Qt::AlignLeft);
        notesLabel->setWordWrap(true);
        notesLabel->setText( event->Notes() );
        notesLabel->setAlignment(Qt::AlignLeft);
        notesNameLabel->setPreferredWidth(1);
        notesLabel->setPreferredWidth(1);
        gridLayout->addItem(notesNameLabel, row, 0);
        gridLayout->addItem(notesLabel, row, 1);
        row+=1;
    }

    mainPolicy->addItem(labelWidget);

    MButton *editButton = new MButton;
    //% "Edit"
    editButton->setText( qtTrId("button_txt_edit") );
    connect( editButton, SIGNAL(clicked()), this, SLOT(handleEditEvent()) );

    mainPolicy->addItem(editButton);
    panel->setLayout(layout);
}

void MDetailDialog::handleEditEvent()
{
    viewManager->handleEditCalendarEvent(event);
    close();
}

QString MDetailDialog::repeatTypetext()
{
    switch (event->RepeatType() )
    {
    case 0:
        //% "Not used"
        return QString(qtTrId("str_not_used"));
        break;
    case 1:
        //% "Once"
        return QString(qtTrId("str_once"));
        break;
    case 2:
        //% "Everyday"
        return QString(qtTrId("str_everyday"));
        break;
    case 3:
        //% "Monday-Friday"
        return QString(qtTrId("str_monday_friday"));
        break;
    case 4:
        //% "Monday"
        return QString(qtTrId("str_monday"));
        break;
    case 5:
        //% "Tuesday"
        return QString(qtTrId("str_tuesday"));
        break;
    case 6:
        //% "Wednesday"
        return QString(qtTrId("str_wednesday"));
        break;
    case 7:
        //% "Thursday"
        return QString(qtTrId("str_thursday"));
        break;
    case 8:
        //% "Friday"
        return QString(qtTrId("str_friday"));
        break;
    case 9:
        //% "Saturday"
        return QString(qtTrId("str_saturday"));
        break;
    case 10:
        //% "Sunday"
        return QString(qtTrId("str_sunday"));
        break;
    default:
        return QString(qtTrId("str_not_used"));
        break;
    }
}
