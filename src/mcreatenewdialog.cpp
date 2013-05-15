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

#include "mcreatenewdialog.h"

#include <MLayout>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <MLinearLayoutPolicy>
#include <MLabel>
#include <MButton>
#include <MTextEdit>
#include <MComboBox>
#include <QGraphicsLinearLayout>

#include <MMessageBox>

MAmPmButton::MAmPmButton() : MButton(),
state(EPm)
{
    setText("PM");
    connect( this, SIGNAL(clicked()), this, SLOT(changeState()) );
}

MAmPmButton::~MAmPmButton()
{
}

void MAmPmButton::changeState()
{
    if (state == EAm )
    {
        state = EPm;
        setText("PM");
        return;
    }
    if (state == EPm )
    {
        state = EAm;
        setText("AM");
    }
}

QString MAmPmButton::getState()
{
    QString ret;
    if (state == EAm )
    {
        ret = QString("AM");
    }
    if (state == EPm )
    {
        ret = QString("PM");
    }
    return ret;
}

void MAmPmButton::setState( buttonState btState )
{
    if (btState == EAm )
    {
        state = EAm;
        setText("AM");
    }
    else //if (btState == EPm )
    {
        state = EPm;
        setText("PM");
    }
}

void MAmPmButton::setState( const QString &ampm )
{
    if (ampm == "AM" )
    {
        state = EAm;
        setText("AM");
    }
    else if (ampm == "PM" )
    {
        state = EPm;
        setText("PM");
    }
    else
    {

    }
}




MCreateNewdialog::MCreateNewdialog( MViewManager* manager, CalendarEvent* eventToEdit ) : MDialog(),
viewManager(manager),
editEvent(eventToEdit)
{  
    if ( eventToEdit ) {
        //% "Edit event"
        setTitle( qtTrId("title_edit_event") );
    } else {
        //% "Create new event"
        setTitle( qtTrId("title_create_new_event") );
    }

    QGraphicsWidget *panel = centralWidget();
    MLayout *layout = new MLayout(panel);
    mainPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);

    //EDescription
    QGraphicsWidget *descriptionWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* descLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, descriptionWidget);
    MLabel* descriptionNameLabel = new MLabel();
    eventTitleEdit = new MTextEdit(MTextEditModel::MultiLine);
    //% "Description"
    descriptionNameLabel->setText( qtTrId("lbl_description") );
    if ( editEvent ) {
        eventTitleEdit->setText( editEvent->Description() );
    } else {
        //% "Event title"
        eventTitleEdit->setText( qtTrId("title_event_title") );
    }
    descriptionNameLabel->setAlignment(Qt::AlignLeft);
    descLinLayout->addItem(descriptionNameLabel);
    descLinLayout->addItem(eventTitleEdit);
    mainPolicy->addItem(descriptionWidget);

    //ECalendarType
    QGraphicsWidget *calTypeWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* caltypeLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, calTypeWidget);
    MLabel* calendarTypeNameLabel = new MLabel();
    calendarComboBox = new MComboBox();
    //% "Calendar"
    calendarTypeNameLabel->setText( qtTrId("lbl_calendar") );
    QList<QString*>& list = viewManager->getCalendarNames();
    for ( int i = 0; i < list.count(); i++ )
    {
        calendarComboBox->addItem(*list.at(i));
    }
    if ( editEvent && editEvent->Calendar() ) {
        QString calName = editEvent->Calendar()->Name();
        int calIndex = -1;
        for (int i=0;i<list.count();i++)
        {
            if ( !list.at(i)->compare(calName) )
            {
                calIndex = i;
                break;
            }
        }
        calendarComboBox->setCurrentIndex( calIndex );
    } else  {
        if ( list.count() > 0 ) {
            calendarComboBox->setCurrentIndex( 0 );
        }
    }
    calendarTypeNameLabel->setAlignment(Qt::AlignLeft);
    caltypeLinLayout->addItem(calendarTypeNameLabel);
    caltypeLinLayout->addItem(calendarComboBox);
    mainPolicy->addItem(calTypeWidget);

    //EAllDay
    allDayWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* allDayLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, allDayWidget);
    MLabel* allDayNameLabel = new MLabel();
    alldaySwitch = new MButton();
    alldaySwitch->setViewType(MButton::switchType);
    alldaySwitch->setCheckable(true);
    connect( alldaySwitch, SIGNAL(clicked()), this, SLOT(allDaySwitchStateChanged()) );

    //% "All day"
    allDayNameLabel->setText(qtTrId("lbl_all_day"));
    allDayNameLabel->setAlignment(Qt::AlignLeft);
    allDayLinLayout->addItem(allDayNameLabel);
    allDayLinLayout->addItem(alldaySwitch);
    mainPolicy->addItem(allDayWidget);

    //EStartDate
    startDtWidget = new QGraphicsWidget;
    startDtLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, startDtWidget);
    MLabel* startDateNameLabel = new MLabel();
    //% "Start date"
    startDateNameLabel->setText(qtTrId("lbl_start_date"));
    stDtDayEdit = new MTextEdit();
    stDtMonthEdit = new MTextEdit();
    stDtYearEdit = new MTextEdit();
    stDtDayEdit->setContentType(M::CustomContentType );
    stDtMonthEdit->setContentType(M::CustomContentType);
    stDtYearEdit->setContentType(M::CustomContentType);
    if ( editEvent ) {
        QDate date = editEvent->StartDate().date();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        stDtDayEdit->setText( day );
        stDtMonthEdit->setText( month );
        stDtYearEdit->setText( year );
    } else {
        QDate date = QDate::currentDate();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        stDtDayEdit->setText( day );
        stDtMonthEdit->setText( month );
        stDtYearEdit->setText( year );
    }
    startDtLinLayout->addItem(startDateNameLabel);
    startDtLinLayout->addItem(stDtDayEdit);
    startDtLinLayout->addItem(stDtMonthEdit);
    startDtLinLayout->addItem(stDtYearEdit);

    //EStartTime
    MLabel* startTimeNameLabel = new MLabel();
    //% "Time"
    startTimeNameLabel->setText(qtTrId("lbl_time"));
    stTimeHourEdit = new MTextEdit();
    stTimeMinEdit = new MTextEdit();
    startAmPm = new MAmPmButton();
    stTimeHourEdit->setContentType(M::NumberContentType);
    stTimeMinEdit->setContentType(M::NumberContentType);   
    if ( editEvent ) {
        QDateTime datetime = editEvent->StartDate();
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        stTimeHourEdit->setText( hour );
        stTimeMinEdit->setText( minute );
        startAmPm->setState( ampm );
    } else {
        QDateTime datetime = QDateTime::currentDateTime();
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        stTimeHourEdit->setText( hour );
        stTimeMinEdit->setText( minute );
        startAmPm->setState( ampm );
    }
    startDtLinLayout->addItem(startTimeNameLabel);
    startDtLinLayout->addItem(stTimeHourEdit);
    startDtLinLayout->addItem(stTimeMinEdit);
    startDtLinLayout->addItem(startAmPm);
    mainPolicy->addItem(startDtWidget);

    //EEndDate
    endDtWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* endDtLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, endDtWidget);
    endDateNameLabel = new MLabel();
    //% "End date"
    endDateNameLabel->setText(qtTrId("lbl_end_date"));
    endDateNameLabel->setAlignment(Qt::AlignLeft);
    endDtDayEdit = new MTextEdit();
    endDtMonthEdit = new MTextEdit();
    endDtYearEdit = new MTextEdit();
    endDtDayEdit->setContentType(M::NumberContentType);
    endDtMonthEdit->setContentType(M::NumberContentType);
    endDtYearEdit->setContentType(M::NumberContentType);
    if ( editEvent ) {
        QDate date = editEvent->EndDate().date();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        endDtDayEdit->setText( day );
        endDtMonthEdit->setText( month );
        endDtYearEdit->setText( year );
    } else {
        QDate date = QDate::currentDate();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        endDtDayEdit->setText( day );
        endDtMonthEdit->setText( month );
        endDtYearEdit->setText( year );
    }
    endDtLinLayout->addItem(endDateNameLabel);
    endDtLinLayout->addItem(endDtDayEdit);
    endDtLinLayout->addItem(endDtMonthEdit);
    endDtLinLayout->addItem(endDtYearEdit);

    //EEndTime
    endTimeNameLabel = new MLabel();
    //% "Time"
    endTimeNameLabel->setText(qtTrId("lbl_time"));
    endTimeNameLabel->setAlignment(Qt::AlignLeft);
    endTimeHourEdit = new MTextEdit();
    endTimeMinEdit = new MTextEdit();
    endAmPm = new MAmPmButton();
    endTimeHourEdit->setContentType(M::NumberContentType);
    endTimeMinEdit->setContentType(M::NumberContentType);
    if ( editEvent ) {
        QDateTime datetime = editEvent->EndDate();
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        endTimeHourEdit->setText( hour );
        endTimeMinEdit->setText( minute );
        endAmPm->setState( ampm );
    } else {
        QDateTime datetime = QDateTime::currentDateTime().addSecs(60*60);
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        endTimeHourEdit->setText( hour );
        endTimeMinEdit->setText( minute );
        endAmPm->setState( ampm );
    }
    endDtLinLayout->addItem(endTimeNameLabel);
    endDtLinLayout->addItem(endTimeHourEdit);
    endDtLinLayout->addItem(endTimeMinEdit);
    endDtLinLayout->addItem(endAmPm);
    mainPolicy->addItem(endDtWidget);

    //ERepeat
    repeatWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* repeatLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, repeatWidget);
    MLabel* repeatNameLabel = new MLabel();
    repeatSwitch = new MButton();
    repeatSwitch->setViewType(MButton::switchType);
    repeatSwitch->setCheckable(true);
    connect( repeatSwitch, SIGNAL(clicked()), this, SLOT(repeatSwitchStateChanged()) );

    //% "Repeat"
    repeatNameLabel->setText(qtTrId("lbl_repeat"));
    repeatNameLabel->setAlignment(Qt::AlignLeft);
    repeatLinLayout->addItem(repeatNameLabel);
    repeatLinLayout->addItem(repeatSwitch);
    mainPolicy->addItem(repeatWidget);

    //ERepeatType
    repeatTypeWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* repeatTypeLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, repeatTypeWidget);
    repeatTypeNameLabel = new MLabel();
    repeatComboBox = new MComboBox();
    //% "Repeat type"
    repeatTypeNameLabel->setText(qtTrId("lbl_repeat_type"));
    repeatTypeNameLabel->setAlignment(Qt::AlignLeft);
    //% "Not used"
    repeatComboBox->addItem(qtTrId("cmb_val_not_used"));
    //% "Once"
    repeatComboBox->addItem(qtTrId("cmb_val_Once"));
    //% "Everyday"
    repeatComboBox->addItem(qtTrId("cmb_val_everyday"));
    //% "Monday-Friday"
    repeatComboBox->addItem(qtTrId("cmb_val_monday_friday"));
    //% "Monday"
    repeatComboBox->addItem(qtTrId("cmb_val_monday"));
    //% "Tuesday"
    repeatComboBox->addItem(qtTrId("cmb_val_tuesday"));
    //% "Wednesday"
    repeatComboBox->addItem(qtTrId("cmb_val_wednesday"));
    //% "Thursday"
    repeatComboBox->addItem(qtTrId("cmb_val_thursday"));
    //% "Friday"
    repeatComboBox->addItem(qtTrId("cmb_val_friday"));
    //% "Saturday"
    repeatComboBox->addItem(qtTrId("cmb_val_saturday"));
    //% "Sunday"
    repeatComboBox->addItem(qtTrId("cmb_val_sunday"));

    repeatTypeLinLayout->addItem(repeatTypeNameLabel);
    repeatTypeLinLayout->addItem(repeatComboBox);

    if ( editEvent )
    {
        if ( editEvent->RepeatType() >= 0 && editEvent->RepeatType() < 11 ) {
            repeatComboBox->setCurrentIndex( editEvent->RepeatType() );
        }
    }

    mainPolicy->addItem(repeatTypeWidget);

    //ERepeatEndDate
    repeatEndDtWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* repeatEndDtLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, repeatEndDtWidget);
    repeatEndDateNameLabel = new MLabel();
    //% "Repeat until"
    repeatEndDateNameLabel->setText(qtTrId("lbl_repeat_until"));
    repeatEndDateNameLabel->setAlignment(Qt::AlignLeft);
    repeatEndDtDayEdit = new MTextEdit();
    repeatEndDtMonthEdit = new MTextEdit();
    repeatEndDtYearEdit = new MTextEdit();

    if ( editEvent ) {
        QDate date = editEvent->EndDate().date();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        repeatEndDtDayEdit->setText( day );
        repeatEndDtMonthEdit->setText( month );
        repeatEndDtYearEdit->setText( year );
    } else {
        QDate date = QDate::currentDate().addYears(50);
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        repeatEndDtDayEdit->setText( day );
        repeatEndDtMonthEdit->setText( month );
        repeatEndDtYearEdit->setText( year );
    }
    repeatEndDtLinLayout->addItem(repeatEndDateNameLabel);
    repeatEndDtLinLayout->addItem(repeatEndDtDayEdit);
    repeatEndDtLinLayout->addItem(repeatEndDtMonthEdit);
    repeatEndDtLinLayout->addItem(repeatEndDtYearEdit);
    mainPolicy->addItem(repeatEndDtWidget);

    //EAlarm
    alarmWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* alarmLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, alarmWidget);
    MLabel* alarmNameLabel = new MLabel();
    alarmSwitch = new MButton();
    alarmSwitch->setViewType(MButton::switchType);
    alarmSwitch->setCheckable(true);
    connect( alarmSwitch, SIGNAL(clicked()), this, SLOT(alarmSwitchStateChanged()) );

    //% "Alarm"
    alarmNameLabel->setText(qtTrId("lbl_alarm"));
    alarmNameLabel->setAlignment(Qt::AlignLeft);
    alarmLinLayout->addItem(alarmNameLabel);
    alarmLinLayout->addItem(alarmSwitch);
    mainPolicy->addItem(alarmWidget);

    //EAlarmDate
    alarmDtWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* alarmDtLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, alarmDtWidget);
    alarmDateNameLabel = new MLabel();
    //% "Alarm date:"
    alarmDateNameLabel->setText(qtTrId("lbl_alarm_date"));
    alarmDateNameLabel->setAlignment(Qt::AlignLeft);
    alarmDtDayEdit = new MTextEdit();
    alarmDtMonthEdit = new MTextEdit();
    alarmDtYearEdit = new MTextEdit();
    alarmDtDayEdit->setContentType(M::NumberContentType);
    alarmDtMonthEdit->setContentType(M::NumberContentType);
    alarmDtYearEdit->setContentType(M::NumberContentType);
    if ( editEvent ) {
        QDate date = editEvent->AlarmDate().date();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        alarmDtDayEdit->setText( day );
        alarmDtMonthEdit->setText( month );
        alarmDtYearEdit->setText( year );
    } else {
        QDate date = QDate::currentDate();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        alarmDtDayEdit->setText( day );
        alarmDtMonthEdit->setText( month );
        alarmDtYearEdit->setText( year );
    }
    alarmDtLinLayout->addItem(alarmDateNameLabel);
    alarmDtLinLayout->addItem(alarmDtDayEdit);
    alarmDtLinLayout->addItem(alarmDtMonthEdit);
    alarmDtLinLayout->addItem(alarmDtYearEdit);

    //EAlarmTime
    alarmTimeNameLabel = new MLabel();
    //% "Time"
    alarmTimeNameLabel->setText(qtTrId("lbl_time"));
    alarmTimeNameLabel->setAlignment(Qt::AlignLeft);
    alarmTimeHourEdit = new MTextEdit();
    alarmTimeMinEdit = new MTextEdit();
    alarmAmPm = new MAmPmButton();
    alarmTimeHourEdit->setContentType(M::NumberContentType);
    alarmTimeMinEdit->setContentType(M::NumberContentType);
    if ( editEvent ) {
        QDateTime datetime = editEvent->AlarmDate();
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        alarmTimeHourEdit->setText( hour );
        alarmTimeMinEdit->setText( minute );
        alarmAmPm->setState( ampm );
    } else {
        QDateTime datetime = QDateTime::currentDateTime().addSecs(-30*60);
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        alarmTimeHourEdit->setText( hour );
        alarmTimeMinEdit->setText( minute );
        alarmAmPm->setState( ampm );
    }
    alarmDtLinLayout->addItem(alarmTimeNameLabel);
    alarmDtLinLayout->addItem(alarmTimeHourEdit);
    alarmDtLinLayout->addItem(alarmTimeMinEdit);
    alarmDtLinLayout->addItem(alarmAmPm);
    mainPolicy->addItem(alarmDtWidget);

    //ENotes
    QGraphicsWidget *notesWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* notesLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, notesWidget);
    MLabel* notesNameLabel = new MLabel();
    notesEdit = new MTextEdit(MTextEditModel::MultiLine);
    //% "Notes"
    notesNameLabel->setText(qtTrId("lbl_notes"));
    if ( editEvent ) {
        notesEdit->setText( editEvent->Notes() );
    } else {
        //% "Add notes for this event"
        notesEdit->setText(qtTrId("lbl_add_notes_msg"));
    }
    notesNameLabel->setAlignment(Qt::AlignLeft);
    notesLinLayout->addItem(notesNameLabel);
    notesLinLayout->addItem(notesEdit);
    mainPolicy->addItem(notesWidget);

    // Save & Delete buttons
    QGraphicsWidget *buttonWidget = new QGraphicsWidget;
    QGraphicsLinearLayout* buttonLinLayout = new QGraphicsLinearLayout(Qt::Horizontal, buttonWidget);
    MButton *acceptButton = new MButton;
    //% "Save event"
    acceptButton->setText( qtTrId("button_txt_save_event") );
    connect( acceptButton, SIGNAL(clicked()), this, SLOT(dialogAccepted()) );
    MButton *rejectButton = new MButton;
    //% "Delete event"
    rejectButton->setText( qtTrId("button_txt_delete_event") );
    connect( rejectButton, SIGNAL(clicked()), this, SLOT(dialogRejected()) );
    buttonLinLayout->addItem(acceptButton);
    buttonLinLayout->addItem(rejectButton);
    mainPolicy->addItem(buttonWidget);

    panel->setLayout(layout);

    if ( editEvent ) {
        alldaySwitch->setChecked( editEvent->AllDay() );
        alarmSwitch->setChecked( editEvent->Alarm() );
        repeatSwitch->setChecked( editEvent->Repeat() );
    } else {
        alldaySwitch->setChecked( false );
        alarmSwitch->setChecked( false );
        repeatSwitch->setChecked( false );
    }

    allDaySwitchStateChanged();
    repeatSwitchStateChanged();
    alarmSwitchStateChanged();
}

void MCreateNewdialog::dialogAccepted()
{
    if ( !verifyDateTimes() )
    {
        //% "Check dates/times..."
        MMessageBox *msgBox = new MMessageBox(qtTrId("msgbox_date_time_check"));
        msgBox->exec();
        delete msgBox;
        return;
    }

    if ( editEvent )
    {
        QDate startDate( stDtYearEdit->text().toInt(), stDtMonthEdit->text().toInt(), stDtDayEdit->text().toInt() );
        int startHour = stTimeHourEdit->text().toInt();
        if ( startAmPm->getState() == "PM" )
        {
            //Bug#7327 Author Sirisha Muppavarapu
            //Fix 12 AM/PM issue
            if(startHour != 12) {
                startHour += 12;
            }
            if ( startHour == 24 )
            {
                startHour = 0;
            }
        }
        QTime startTime( startHour, stTimeMinEdit->text().toInt() );
        QDateTime startsDT( startDate, startTime );

        QDate endDate( endDtYearEdit->text().toInt(), endDtMonthEdit->text().toInt(), endDtDayEdit->text().toInt() );
        int endHour = endTimeHourEdit->text().toInt();
        if ( endAmPm->getState() == "PM" )
        {
            //Bug#7327 Author Sirisha Muppavarapu
            if(endHour!=12) {
                endHour += 12;
            }
            if ( endHour == 24 )
            {
                endHour = 0;
            }
        }
        QTime endTime( endHour, endTimeMinEdit->text().toInt() );
        QDateTime endsDT( endDate, endTime );

        QDate alarmDate( alarmDtYearEdit->text().toInt(), alarmDtMonthEdit->text().toInt(), alarmDtDayEdit->text().toInt() );
        int alarmHour = alarmTimeHourEdit->text().toInt();
        if ( alarmAmPm->getState() == "PM" )
        {
            //Bug#7327 Author: Sirisha Muppavarapu
            //Fix 12 AM/PM issue
            if(alarmHour != 12) {
                alarmHour += 12;
            }
            if ( alarmHour == 24 )
            {
                alarmHour = 0;
            }
        }
        QTime alarmTime( alarmHour, alarmTimeMinEdit->text().toInt() );
        QDateTime alarmDT( alarmDate, alarmTime );

        QDate repeatEndDate( repeatEndDtDayEdit->text().toInt(), repeatEndDtMonthEdit->text().toInt(), repeatEndDtYearEdit->text().toInt() );
        QDateTime repeatEndDT( repeatEndDate, QTime::currentTime() );

        editEvent->SetDescription( eventTitleEdit->text() );
        editEvent->SetCalendarType( calendarComboBox->currentIndex() );
        CalendarData* calendar = viewManager->GetCalendarByName( calendarComboBox->currentText() );
        if ( calendar ) {
            editEvent->SetCalendar(calendar);
        }
        editEvent->SetAllDay( alldaySwitch->isChecked() );
        editEvent->SetStartDate( startsDT );
        editEvent->SetEndDate( endsDT );
        editEvent->SetRepeat( repeatSwitch->isChecked() );
        editEvent->SetRepeatType( repeatComboBox->currentIndex() );
        editEvent->SetRepeatEndDate( repeatEndDT );
        editEvent->SetAlarm( alarmSwitch->isChecked() );
        editEvent->SetAlarmDate( alarmDT );
        editEvent->SetNotes( notesEdit->text() );

        viewManager->changeCalendarEvent(editEvent);
        close();
    }
    else {
        QDate startDate( stDtYearEdit->text().toInt(), stDtMonthEdit->text().toInt(), stDtDayEdit->text().toInt() );
        int startHour = stTimeHourEdit->text().toInt();
        if ( startAmPm->getState() == "PM" )
        {
            //Bug#7327 Author: Sirisha Muppavarapu
            //Fix 12 AM/PM issue
            if(startHour!=12) {
                startHour += 12;
            }
            if ( startHour == 24 )
            {
                startHour = 0;
            }
        }
        QTime startTime( startHour, stTimeMinEdit->text().toInt() );
        QDateTime startsDT( startDate, startTime );

        QDate endDate( endDtYearEdit->text().toInt(), endDtMonthEdit->text().toInt(), endDtDayEdit->text().toInt() );
        int endHour = endTimeHourEdit->text().toInt();
        if ( endAmPm->getState() == "PM" )
        {
            //Bug#7327 Author: Sirisha Muppavarapu
            //Fix 12 AM/PM issue
            if(endHour != 12) {
                endHour += 12;
            }
            if ( endHour == 24 )
            {
                endHour = 0;
            }
        }
        QTime endTime( endHour, endTimeMinEdit->text().toInt() );
        QDateTime endsDT( endDate, endTime );

        QDate alarmDate( alarmDtYearEdit->text().toInt(), alarmDtMonthEdit->text().toInt(), alarmDtDayEdit->text().toInt() );
        int alarmHour = alarmTimeHourEdit->text().toInt();
        if ( alarmAmPm->getState() == "PM" )
        {
            //Bug#7327 Author: Sirisha Muppavarapu
            //Fix 12 AM/PM issue
            if(alarmHour != 12) {
                alarmHour += 12;
            }
            if ( alarmHour == 24 )
            {
                alarmHour = 0;
            }
        }
        QTime alarmTime( alarmHour, alarmTimeMinEdit->text().toInt() );
        QDateTime alarmDT( alarmDate, alarmTime );

        QDate repeatEndDate( repeatEndDtYearEdit->text().toInt(), repeatEndDtMonthEdit->text().toInt(), repeatEndDtDayEdit->text().toInt() );
        QDateTime repeatEndDT( repeatEndDate, QTime::currentTime() );

        CalendarEvent* newEvent = new CalendarEvent(
                                  eventTitleEdit->text(),
                                  calendarComboBox->currentIndex(),
                                  alldaySwitch->isChecked(),
                                  startsDT,
                                  endsDT,
                                  repeatSwitch->isChecked(),
                                  repeatComboBox->currentIndex(),
                                  repeatEndDT,
                                  alarmSwitch->isChecked(),
                                  alarmDT,
                                  notesEdit->text(),
                                  NULL);
        CalendarData* calendar = viewManager->GetCalendarByName( calendarComboBox->currentText() );
        if ( calendar ) {
            newEvent->SetCalendar(calendar);
        }
        viewManager->addNewCalendarEvent(newEvent);
        close();
    }

    close();
}

void MCreateNewdialog::dialogRejected()
{
    if ( editEvent ) {
        viewManager->deleteEvent(editEvent);
    }
    close();
}

void MCreateNewdialog::allDaySwitchStateChanged()
{
    bool endDtwidgetFound = false;

    if ( !alldaySwitch->isChecked() ) {

        for ( int i=0;i<mainPolicy->count();i++ ) {
            QGraphicsLayoutItem* item = mainPolicy->itemAt(i);
            if ( item == endDtWidget ) {
                endDtwidgetFound = true;
            }
        }

        for ( int j=0;j<mainPolicy->count();j++ ) {
            QGraphicsLayoutItem* item = mainPolicy->itemAt(j);
            if ( item == startDtWidget ) {
                if ( endDtwidgetFound == false ) {
                    mainPolicy->insertItem( j+1, endDtWidget );
                    }
                }
            }
    } else {
        mainPolicy->removeItem( endDtWidget );
    }
}

void MCreateNewdialog::repeatSwitchStateChanged()
{
    bool repeatTypeWidgetFound = false;
    for ( int i=0;i<mainPolicy->count();i++ ) {
        QGraphicsLayoutItem* item = mainPolicy->itemAt(i);
        if ( item == repeatTypeWidget ) {
            repeatTypeWidgetFound = true;
        }
    }

    if ( repeatSwitch->isChecked() ) {

        for ( int i=0;i<mainPolicy->count();i++ ) {
            QGraphicsLayoutItem* item = mainPolicy->itemAt(i);
            if ( item == repeatWidget ) {
                if ( repeatTypeWidgetFound == false ) {
                    mainPolicy->insertItem( i+1, repeatEndDtWidget );
                    mainPolicy->insertItem( i+1, repeatTypeWidget );
                    }
                }
        }
    } else {
        mainPolicy->removeItem( repeatTypeWidget );
        mainPolicy->removeItem( repeatEndDtWidget );
    }
}

void MCreateNewdialog::alarmSwitchStateChanged()
{
    bool alarmDtWidgetFound = false;
    for ( int i=0;i<mainPolicy->count();i++ ) {
        QGraphicsLayoutItem* item = mainPolicy->itemAt(i);
        if ( item == alarmDtWidget ) {
            alarmDtWidgetFound = true;
        }
    }

    if ( alarmSwitch->isChecked() ) {

        for ( int i=0;i<mainPolicy->count();i++ ) {
            QGraphicsLayoutItem* item = mainPolicy->itemAt(i);
            if ( item == alarmWidget ) {
                if ( alarmDtWidgetFound == false ) {
                    mainPolicy->insertItem( i+1, alarmDtWidget );
                    }
                }
        }
    } else {
        mainPolicy->removeItem( alarmDtWidget );
    }
}

bool MCreateNewdialog::verifyDateTimes()
{
    bool retVal = true;
    QDate startDate( stDtYearEdit->text().toInt(), stDtMonthEdit->text().toInt(), stDtDayEdit->text().toInt() );
    int startHour = stTimeHourEdit->text().toInt();
    if ( startAmPm->getState() == "PM" )
    {
        //Bug#7327 Author: Sirisha Muppavarapu
        //Fix 12 AM/PM issue
        if(startHour!=12) {
            startHour += 12;
        }
        if ( startHour == 24 )
        {
            startHour = 0;
        }
    }
    QTime startTime( startHour, stTimeMinEdit->text().toInt() );
    QDateTime startsDT( startDate, startTime );

    QDate endDate( endDtYearEdit->text().toInt(), endDtMonthEdit->text().toInt(), endDtDayEdit->text().toInt() );
    int endHour = endTimeHourEdit->text().toInt();
    if ( endAmPm->getState() == "PM" )
    {
        //Bug#7327 Author: Sirisha Muppavarapu
        //Fix 12 AM/PM issue
        if(endHour != 12) {
            endHour += 12;
        }
        if ( endHour == 24 )
        {
            endHour = 0;
        }
    }
    QTime endTime( endHour, endTimeMinEdit->text().toInt() );
    QDateTime endsDT( endDate, endTime );

    QDate alarmDate( alarmDtYearEdit->text().toInt(), alarmDtMonthEdit->text().toInt(), alarmDtDayEdit->text().toInt() );
    int alarmHour = alarmTimeHourEdit->text().toInt();
    if ( alarmAmPm->getState() == "PM" )
    {
        //Bug#7327 Author: Sirisha Muppavarapu
        //Fix 12 AM/PM issue
        if(alarmHour != 12) {
            alarmHour += 12;
        }
        if ( alarmHour == 24 )
        {
            alarmHour = 0;
        }
    }
    QTime alarmTime( alarmHour, alarmTimeMinEdit->text().toInt() );
    QDateTime alarmDT( alarmDate, alarmTime );

    QDate repeatEndDate( repeatEndDtDayEdit->text().toInt(), repeatEndDtMonthEdit->text().toInt(), repeatEndDtYearEdit->text().toInt() );
    QDateTime repeatEndDT( repeatEndDate, QTime::currentTime() );

    if ( startsDT > endsDT )
    {
        //set endsDT = startsDT + 60 minutes
        QDate date = startsDT.date();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        endDtDayEdit->setText( day );
        endDtMonthEdit->setText( month );
        endDtYearEdit->setText( year );

        QDateTime datetime = startsDT.addSecs(60*60);
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        endTimeHourEdit->setText( hour );
        endTimeMinEdit->setText( minute );
        endAmPm->setState( ampm );
        retVal = false;
    }
    if ( alarmDT >= startsDT )
    {
        //set alarmDT = startsDT -15 minutes
        QDate date = startsDT.date();
        QString day;
        QString month;
        QString year;
        day.setNum( date.day() );
        month.setNum( date.month() );
        year.setNum( date.year() );
        alarmDtDayEdit->setText( day );
        alarmDtMonthEdit->setText( month );
        alarmDtYearEdit->setText( year );

        QDateTime datetime = startsDT.addSecs(-30*60);
        QString	hourStr = datetime.toString ( "hh" );
        QString	ampm = datetime.toString ( "AP" );
        int hourInt = hourStr.toInt() % 12;
        if ( hourInt == 0 )
        {
            hourInt = 12;
        }
        QTime time = datetime.time();
        QString hour;
        QString minute;
        hour.setNum( hourInt );
        minute.setNum( time.minute() );
        alarmTimeHourEdit->setText( hour );
        alarmTimeMinEdit->setText( minute );
        alarmAmPm->setState( ampm );
        retVal = false;
    }
    return retVal;
}


