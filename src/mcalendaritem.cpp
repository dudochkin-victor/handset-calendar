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

#include "mcalendaritem.h"

#include <QDate>
#include <QFont>
#include <QDateEdit>

#include "mcalendarlayout.h"

#define hourBarSteps 4

MCalendarItem::MCalendarItem(MCalendarLayout* layout, const QDate* dat, const QString &text )
    : MButton(text), layout(layout), date(dat), isAllDayEvent(0), eventHours(0), isMultipleDaysEvent(false)
{
    const QFont* font = new QFont("Helvetica [Cronyx]",28,4);//todo relative

    setFont(*font);

    QObject::connect(this,SIGNAL(clicked()),this,SLOT(itemSelected()));

    //QObject::connect(this,SIGNAL())
}

void MCalendarItem::itemSelected()
{
    if(date)
    {
        layout->daySelected(*date);
    }
    else
    {
        int weekday = this->data(0).toInt();
        layout->setWeekdayOffset(weekday);
      }
}

MCalendarItem::~MCalendarItem()
{
    if(date)
    {
        delete date;
        date = 0;
    }
}

void MCalendarItem::setAllDayEvent( bool allDayEvent )
{
    this->isAllDayEvent = allDayEvent;
}

void MCalendarItem::setEventHours( float hours )
{
    this->eventHours = hours;
}

void MCalendarItem::setMultipleDaysEvent(bool multipleDays)
{
    isMultipleDaysEvent=multipleDays;
}

void MCalendarItem::setColor( QColor* color )
{
    eventColor=color;
}

void MCalendarItem::setCellType(int cellType)
{
    this->cellType = cellType;
}

void MCalendarItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    MButton::paint(painter,option,widget);

    QDateTime today = QDateTime::currentDateTime();
    QBrush originalBrush = painter->brush();
    QPen originalPen = painter->pen();
    QColor monthsDayColor(153,204,102,255);
    QColor notMonthsDayColor(173,173,173,255);
    QColor weekLabelColor(112,112,112,255);

    //draw background
    QRect backgroundrect;
    backgroundrect.setLeft(rect().left());
    backgroundrect.setRight(rect().right());
    backgroundrect.setBottom(rect().bottom());
    backgroundrect.setTop(rect().top());

    backgroundrect.adjust(3,3,-5,-5);

    //Color the cell based on its type
    /*if(cellType == EWeekLabel) {
        this->setColor(&weekLabelColor);
    } else if(cellType == ENotMonthsDay) {
        this->setColor(&notMonthsDayColor);
    } else if(cellType == EMonthsDay) {
        this->setColor(&monthsDayColor);
    }*/

    //Paint multiple days
    if ( isMultipleDaysEvent)
    {
        QPen pen;
        pen.setWidth(5);
        pen.setColor(*eventColor);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        QRect r;
        r.setLeft(rect().left());
        r.setRight(rect().right());
        r.setBottom(rect().bottom());
        r.setTop(rect().top());
        r.adjust(-1,-1,-1,-1);
        painter->drawRect(r);
    }

    QRect lastRect;
    // if there is an event lasting whole day then indicate it

    int alldayWidth = backgroundrect.width()-10;
    int alldayHeight = backgroundrect.height()/8;
    QRect allDayEventrect( backgroundrect.topLeft().x()+5, backgroundrect.topLeft().y()+1, alldayWidth, alldayHeight );
    QBrush allDayBrush;

    //Paint all day event
    if( isAllDayEvent )
    {
        allDayBrush.setColor(*eventColor);
        allDayBrush.setStyle(Qt::SolidPattern);
        painter->setBrush(allDayBrush);
        painter->drawRect(allDayEventrect);
    }
    lastRect = allDayEventrect;

    painter->setPen(originalPen);
    painter->setBrush(originalBrush);

    //Empty - No appointments that day
    //Slightly full - One hour or under
    //Partly full - More than one but fewer than 6 hours of appointments
    //Totally full - more than 6 hours of appointments

    QRect busyIndicatorRect = backgroundrect;
    int height = busyIndicatorRect.height() - lastRect.height() - 7;
    if ( eventHours > 0 && eventHours <= 1 ) {
        busyIndicatorRect.setHeight( height*1/3 );
    } else if ( eventHours > 1 && eventHours < 6 ) {
        busyIndicatorRect.setHeight( height*2/3 );
    } else if ( eventHours >= 6) {
        busyIndicatorRect.setHeight( height );
    } else {
        busyIndicatorRect.setHeight( 0 );
    }

    busyIndicatorRect.setWidth(backgroundrect.width()/5);

    QPoint bR;
    bR.setX(backgroundrect.bottomRight().x() - 3 );
    bR.setY(backgroundrect.bottomRight().y() - 3 );
    QPoint tL;
    tL.setX( bR.x() - busyIndicatorRect.width() +1 );
    tL.setY( bR.y() - busyIndicatorRect.height() +1 );

    QRect indiRect = QRect( tL, bR );

    if ( indiRect.height() > 0 ) {
        QBrush originalBrush = painter->brush();
        QPen originalPen = painter->pen();

        QPen pen;
        pen.setColor(QColor(Qt::white));

        QBrush brush;
        QColor brushColor(Qt::white);
        brush.setColor(brushColor);
        brush.setStyle(Qt::SolidPattern);
        painter->setPen(pen);
        painter->setBrush(brush);

        painter->drawRect(indiRect);
        painter->setPen(originalPen);
        painter->setBrush(originalBrush);
    }
}
