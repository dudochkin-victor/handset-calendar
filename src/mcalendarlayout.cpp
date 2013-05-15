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

#include "mcalendarlayout.h"

#include <MCalendar>

#include <QtDebug>
#include <QObject>
#include <QSettings>
#include "mviewmanager.h"
#include "mcalendaritem.h"
#include <iostream>

#define DAYS_IN_WEEK        7
#define LANDSCAPE_ROWS      7
#define LANDSCAPE_COLUMNS   7
#define CELL_SPACING        0

MCalendarLayout::MCalendarLayout( QGraphicsWidget* widget, MViewManager* manager )
    : QGraphicsGridLayout(widget), viewManager(manager), weekDayOffset(EMonday)
{
    readSettings();
    currDate = new QDate( QDate::currentDate().addMonths(0) );
    populateCalendar();
    //connect(this,SIGNAL(),this,)
}

MCalendarLayout::~MCalendarLayout()
{
    writeSettings();
}

void MCalendarLayout::populateCalendar()
{
    //title( currDate->longMonthName(currDate->month())  + " " + QString("%1").arg(currDate->year()) );
    qDebug() << "################## count: " << this->count() <<"\n";

    for( int itemCount = 0; itemCount < this->count(); itemCount++ )
    {
        MCalendarItem* item = (MCalendarItem*)itemAt(0);
        this->removeAt(0);
        delete item;
    }
    qDebug() << "count: " << this->count() <<"\n";

    MCalendar* calendar = new MCalendar();

    calendar->setDate( *currDate );

    visibleRows     = LANDSCAPE_ROWS;
    visibleColumns  = LANDSCAPE_COLUMNS;

    setSpacing(CELL_SPACING);
    setContentsMargins(0,0,0,0);
    setVerticalSpacing(0);
    //0-6
    int firstWeekday = (((currDate->dayOfWeek()+DAYS_IN_WEEK) - currDate->day() % DAYS_IN_WEEK) % DAYS_IN_WEEK);

    int magicNumber = DAYS_IN_WEEK - 1;

    bool extraRow=false;

    if((weekDayOffset-firstWeekday)>0)
    {
        extraRow=true;
        visibleRows=LANDSCAPE_ROWS+1;
    }
    else
    {
        visibleRows=LANDSCAPE_ROWS;
    }


    for (int i = 0; i < visibleRows*visibleColumns; ++i)
    {
        QString text;
        QDate* date = 0;

        int start = magicNumber+firstWeekday-weekDayOffset;

        if( extraRow )
        {
            start+=DAYS_IN_WEEK;
        }

        MCalendarItem* item = 0;

        if( i>start && i<calendar->lastDayOfMonth()+1+start )
        {
            int daysToAdd = -currDate->day()+i-magicNumber-firstWeekday+weekDayOffset;
            if(extraRow)
            {
                daysToAdd-=DAYS_IN_WEEK;
            }
            date = new QDate(currDate->addDays(daysToAdd));
            text = QString("%1").arg(date->day());
            qDebug() << date;
            item = new MCalendarItem( this, date, text );
            item->setCellType(EMonthsDay);

        }
        else if(i>magicNumber)
        {
            int daysToAdd = -currDate->day()+i-magicNumber-firstWeekday+weekDayOffset;
            if(extraRow)
            {
                daysToAdd-=DAYS_IN_WEEK;
            }

            date = new QDate(currDate->addDays(daysToAdd));
            text = QString("%1").arg(date->day());
            qDebug() << date;
            item = new MCalendarItem( this, date, text );
            // Bug#7321  Author: Sirisha Muppavarapu
            // Added this code to make UI look more like in Wireframes.
            item->setVisible(false);
            item->setCellType(ENotMonthsDay);

        }
        else
        {
            //Adding row corresponding to Week Days M-S
            text = QDate::shortDayName(((weekDayOffset+i)%7)+1).left(1).toUpper();
            item = new MCalendarItem( this, date, text );
            item->setData( 0, (weekDayOffset+i)%7 );
            item->setCellType(EWeekLabel);
        }


        addItem( item, i / visibleColumns, i % visibleColumns );

        if(date)
        {
            QColor* eventColor = new QColor();
\
            item->setAllDayEvent( viewManager->isAlldayEvent(*date, *eventColor) );
            item->setEventHours( viewManager->getDateEventHours(*date) );
            item->setMultipleDaysEvent( viewManager->isMultipledaysEvent( *date) );
            item->setColor( eventColor );
        }

        int rowHeight=47;//this->geometry().height()/8;
        item->setObjectName("item");
        item->setMaximumHeight(rowHeight);
    }
    qDebug() << "count: " << this->count() <<"\n";
}

void MCalendarLayout::setNextMonth()
{
    currDate->setDate(currDate->year(), currDate->month(), 1);
    currDate->addMonths(1);
}

void MCalendarLayout::setPreviousMonth()
{
    currDate->setDate(currDate->year(), currDate->month(), 1 );
    currDate->addMonths(-1);
}

void MCalendarLayout::setWeekdayOffset(int offset)
{
    weekDayOffset = offset;
    populateCalendar();
}

void MCalendarLayout::daySelected( const QDate& date )
{
    if( &date )
    {
        if(date.month()!=currDate->month() || date.year()!=currDate->year() )
        {
            currDate->setDate(date.year(), date.month(), date.day() );
            viewManager->setSelectedDate(*currDate);
            populateCalendar();
        }
        else
        {
            viewManager->setSelectedDate(date);
            viewManager->changeView( EThreeDayView );
        }
    }
}

void MCalendarLayout::writeSettings()
{
    QSettings settings("Company", "MeegoCalendar");

    settings.beginGroup("WeekdayOffset");
    settings.setValue("offset", weekDayOffset);
    settings.endGroup();
}

void MCalendarLayout::readSettings()
{
    QSettings settings("Company", "MeegoCalendar");
    settings.beginGroup("WeekdayOffset");
    weekDayOffset = settings.value("offset", int(0)).toInt();
    settings.endGroup();
    if(weekDayOffset<0 || weekDayOffset>6)
    {
        weekDayOffset=0;
    }
}

QDate MCalendarLayout::currentDate()
{
    if ( currDate )
    {
        return *currDate;
    }
    else {
        return QDate::currentDate();
    }
}
