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

#include "mviewmanager.h"
#include <QList>
#include <QDebug>
#include <QString>
#include "mdetaildialog.h"
#include "mthreedayview.h"
#include "mmonthview.h"
#include "mcomingupview.h"
#include "mdetaildialog.h"
#include <QSettings>
#include <MLabel>
#include <QGraphicsLinearLayout>
#include <MTextEdit>
#include "mcreatenewdialog.h"

MViewManager::MViewManager() : QObject()
{
    events=0;
    editDlg = NULL;
    selectedDate = new QDate(QDate::currentDate());

    events = new QList<CalendarEvent*>();
    setupCalendarEngine();

    MComingUpView* comingUpPage = new MComingUpView(this);
    MMonthView* monthPage = new MMonthView(this);
    MThreeDayView* threeDayPage = new MThreeDayView(this);

    connect(comingUpPage, SIGNAL(appeared()), this, SLOT(comingUpViewAppeared()));
    connect(monthPage, SIGNAL(appeared()), this, SLOT(monthViewAppeared()));
    connect(threeDayPage, SIGNAL(appeared()), this, SLOT(threeDayViewAppeared()));

    pageList.append(comingUpPage);
    pageList.append(monthPage);
    pageList.append(threeDayPage);

    //Activate coming up view first
    readSettings();

    pageList[currentViewIndex]->appear();
}

void MViewManager::comingUpViewAppeared()
{
    currentViewIndex = EComingUpView;
    MApplicationPage* page = pageList[EComingUpView];
    MComingUpView* thePage = (MComingUpView*)page;
    thePage->updateViewComboBox(currentViewIndex);
}

void MViewManager::monthViewAppeared()
{
    currentViewIndex = EMonthView;
    MApplicationPage* page = pageList[EMonthView];
    MMonthView* thePage = (MMonthView*)page;
    thePage->updateViewComboBox(currentViewIndex);
}

void MViewManager::threeDayViewAppeared()
{
    currentViewIndex = EThreeDayView;
    MApplicationPage* page = pageList[EThreeDayView];
    MThreeDayView* thePage = (MThreeDayView*)page;
    thePage->updateViewComboBox(currentViewIndex);
}

MViewManager::~MViewManager()
{
    writeSettings();
    delete calendarEngine;
    delete calendarFilterAll;
}

void MViewManager::setupCalendarEngine()
{
    calendarEngine = new CalEngine();

    calendars = &calendarEngine->getCalendars();

    calendarFilters = new QList<QString *>();
    calendarNames = new QList<QString *>();

    //% "All"
    calendarFilterAll = new QString( qtTrId("cal_fltr_all") );

    calendarFilters->append(calendarFilterAll);

    if( calendars->count() ) {
        for(int i=0; i<calendars->count(); i++) {
            calendarFilters->append( &calendars->at(i)->Name() );
            calendarNames->append( &calendars->at(i)->Name() );
        }

        //Set local calendar by default, assuming it is the first
        setCalendarByFilter( *calendarFilters->at(1), true );
    }  

    events = &calendarEngine->getCalendarEvents();
}

void MViewManager::changeView(int viewIndex)
{
    currentViewIndex = viewIndex;
    MApplicationPage* page = pageList[viewIndex];
    if (page) {
        page->appear();
    } else {

    }
}

QList<CalendarEvent*>& MViewManager::GetEvents()
    {
    events = &calendarEngine->getCalendarEvents();

    return *events;
    }


float MViewManager::getDateEventHours( const QDate & date ) const
{
    float retVal = 0.0;

    for( int i=0; i<events->count(); i++ )
    {
        if( isSameDate( date, events->at(i)->StartDate().date()) )
        {
            int secsTo = events->at(i)->StartDate().time().secsTo(events->at(i)->EndDate().time());
            retVal += float(secsTo) / float(3600);
        }
    }
    return retVal;
}

bool MViewManager::isSameDate(  const QDate & date1, const QDate & date2 ) const
{
    bool retVal = false;

    int year1   = 0;
    int month1  = 0;
    int day1    = 0;

    int year2   = 0;
    int month2 = 0;
    int day2   = 0;

    QDate* tdate1 = new QDate(date1);
    tdate1->getDate(&year1,&month1,&day1);
    QDate* tdate2 = new QDate(date2);
    tdate2->getDate(&year2,&month2,&day2);

    if( year1 == year2 && month1 == month2 && day1 == day2 )
    {
        retVal = true;
    }
    return retVal;
}

bool MViewManager::isAlldayEvent( const QDate & date, QColor& color ) const
{
    bool retVal = false;

    for( int i=0; i<events->count(); i++ )
    {
        if( isSameDate( date, events->at(i)->StartDate().date()) && events->at(i)->AllDay() )
        {
            color = events->at(i)->Calendar()->Color();
            retVal = true;
        }
    }
    return retVal;
}

bool MViewManager::isMultipledaysEvent( const QDate & date ) const
{
    bool retVal = false;

    for( int i=0; i<events->count(); i++ )
    {
        if( date>=events->at(i)->StartDate().date() && date <= events->at(i)->EndDate().date() )
        {
            return events->at(i)->GetCalCoreEvent()->isMultiDay();
        }
    }
    return retVal;
}

bool MViewManager::setCalendarByFilter( const QString& filter, bool disableUpdate )
{
   bool success = false;

   if (events)
   {
       events->clear();
   }

    for(int i=0;i<calendars->count();i++)
    {
        if(!calendars->at(i)->Name().compare(filter) )
        {
            events = &calendarEngine->getCalendarEvents( calendars->at(i) );
            success = true;
            break;
        }
    }

    if ( !disableUpdate ) {
        //updateView( *selectedDate );
    }

    return success;
}

const QDate& MViewManager::getSelectedDate()
{
    return *selectedDate;
}

void MViewManager::setSelectedDate(const QDate& date)
{
    if ( selectedDate )
    {
        delete selectedDate;
    }
    selectedDate = new QDate(date);

    MApplicationPage* page = pageList[EThreeDayView];
    MThreeDayView* threedayView = (MThreeDayView*)page;
    threedayView->setStartDateFortLists(date);

    MApplicationPage* monpage = pageList[EMonthView];
    MMonthView* monthView = (MMonthView*)monpage;
    monthView->setDate(*this->selectedDate);

    qDebug() << "\nViewManager date set to: " << selectedDate->currentDate() << "\n";
}

void MViewManager::addItemSorted(CalendarEvent* evt)
{
    QDateTime newDt = evt->StartDate();
    if ( events->count() == 0 ) {
        events->append(evt);
    } else if ( events->count() == 1 ) {
        QDateTime oldDt = events->at(0)->StartDate();
        if ( newDt > oldDt ) {
            events->append(evt);
        } else {
            events->insert(0, evt);
        }
    } else {
        //Bug7316 Author: Sirisha Muppavarapu
        //Events were not added in the sorted order
        //This is a linear sort. Very horrible, but a quick fix for now
        bool inserted = false;
        for ( int j=0; j<events->count(); j++ )
        {
            QDateTime oldDt1 = events->at(j)->StartDate();
            if ( newDt <= oldDt1 ) {
                events->insert(j, evt);
                inserted = true;
                break;
            }
        }
        if(!inserted) {
            events->append(evt);
        }
    }
}

void MViewManager::writeSettings()
{
    QSettings settings("Company", "MeegoCalendar");

    settings.beginGroup("ViewIndex");
    settings.setValue("index", currentViewIndex);
    settings.endGroup();
}

void MViewManager::readSettings()
{
    QSettings settings("Company", "MeegoCalendar");

    settings.beginGroup("ViewIndex");
    currentViewIndex = settings.value("index", int(0)).toInt();
    if ( currentViewIndex < 0 || currentViewIndex > 2 )
    {
       currentViewIndex = 0;
    }
    settings.endGroup();
}

void MViewManager::showEventDetails(CalendarEvent* event)
{
    MDetailDialog* dlg = new MDetailDialog(this, event);
    //% "Event details"
    dlg->setTitle(qtTrId("title_event_details") );
    dlg->exec();
}

void MViewManager::handleEditCalendarEvent( CalendarEvent* calendarEventToEdit )
{  
    if ( editDlg ) {
        delete editDlg;
        editDlg = NULL;
    }
    editDlg = new MCreateNewdialog(this, calendarEventToEdit);
    editDlg->exec();
}

QList<QString*>& MViewManager::getCalendarNames()
{
    return *calendarNames;
}

CalendarData* MViewManager::GetCalendarByName( const QString& name )
{
    CalendarData* calendar = 0;

    if( calendars && calendars->count() )
    {
        for( int i=0; i<calendars->count(); i++)
        {
            if ( !calendars->at(i)->Name().compare(name)  )
            {
                calendar = calendars->at(i);
                break;
            }
        }
    }
    return calendar;
}

void MViewManager::deleteEvent(CalendarEvent* calendarEventToRemove)
{
    calendarEngine->removeEvent( *calendarEventToRemove );
    if ( calendarEventToRemove->Repeat() )
    {
        for ( int i=0; i<events->count();i++ )
        {
            CalendarEvent* evt = events->at(i);
            if ( evt->GetCalCoreEvent() == calendarEventToRemove->GetCalCoreEvent() )
            {
                events->removeAt(i);
                delete evt;
                evt=NULL;
                i=-1;
            }
        }
        updateEvents();
    }
    else {
        for ( int i=0; i<events->count();i++ )
        {
            CalendarEvent* evt = events->at(i);
            if ( evt == calendarEventToRemove )
            {
                events->removeAt(i);
                delete evt;
                evt=NULL;
                updateEvents();
                break;
            }
        }
    }
}

void MViewManager::addNewCalendarEvent( CalendarEvent* newCalendarEvent )
{
    calendarEngine->createEvent( *newCalendarEvent );
    if ( newCalendarEvent->Repeat() ) {
        calendarEngine->reloadEvents();
    } else {
        addItemSorted(newCalendarEvent);

    }
updateEvents();
}

void MViewManager::changeCalendarEvent(CalendarEvent* editEvent)
{
    calendarEngine->modifyEvent( *editEvent );
    updateEvents();
}

void MViewManager::updateEvents()
{
    MApplicationPage* appPage1 = pageList[EComingUpView];
    MComingUpView* comingUpView = (MComingUpView*)appPage1;
    comingUpView->updateEvents();
    MApplicationPage* appPage2 = pageList[EThreeDayView];
    MThreeDayView* threedayView = (MThreeDayView*)appPage2;
    threedayView->updateEvents();
    MApplicationPage* appPage3 = pageList[EMonthView];
    MMonthView* monthView = (MMonthView*)appPage3;
    monthView->updateEvents();
}
