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

#include "mmonthview.h"
#include <MScene>
#include <MLayout>
#include <MGridLayoutPolicy>
#include <MButton>
#include "mviewmanager.h"
#include <MAction>
#include <MWidgetAction>
#include <MLabel>
#include <MLinearLayoutPolicy>
#include <MComboBox>
#include "mcalendarlayout.h"
#include <QGraphicsWidget>
#include <QGridLayout>
#include <QSwipeGesture>
#include <QGraphicsLinearLayout>
#include <MDialog>

MMonthView::MMonthView(MViewManager* manager) : MApplicationPage(),
   viewManager(manager)
{
    currDate=0;
    setAcceptTouchEvents(true);
    grabGesture(Qt::SwipeGesture);

    //% "Month"
    setTitle(qtTrId("title_month"));

    MLayout *layout = new MLayout(this->centralWidget());

    //QGraphicsWidget* widget = new QGraphicsWidget;

    MLinearLayoutPolicy *mainPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);


    QGraphicsWidget* monthSelectWidget = new QGraphicsWidget();

    monthSelectLayout = new QGraphicsLinearLayout(Qt::Horizontal, monthSelectWidget);

    for(int i=0;i<12;i++)
    {
        MMonthSelectItem *button = new MMonthSelectItem( QDate::shortMonthName(i+1).left(1).toUpper() );
        button->setMaximumWidth( 70 );
        button->setMaximumHeight( 48 );
        button->setData( 0, i );

        if( i == QDate::currentDate().month()-1 )
        {
            button->setHighlighted(true);
        }

        monthSelectLayout->addItem(button);
        QObject::connect( button, SIGNAL(monthClicked(int)), this, SLOT(monthClicked(int)) );
        monthSelectLayout->setItemSpacing(i,0);
        monthSelectLayout->setContentsMargins(0,0,0,0);
    }

    mainPolicy->addItem(monthSelectWidget);


    QGraphicsWidget* gridWidget = new QGraphicsWidget();

    calendarLayout = new MCalendarLayout(gridWidget, viewManager);

    mainPolicy->addItem(gridWidget);

    QGraphicsWidget *panel = this->centralWidget();

    //Create view change combo box
    MWidgetAction* viewChangeAction = new MWidgetAction(panel);
    viewChangeAction->setLocation(MAction::ApplicationMenuLocation);

    viewComboBox = new MComboBox(panel);
    //% "Coming up"
    viewComboBox->addItem(qtTrId("cmb_val_coming_up"));
    //% "Month"
    viewComboBox->addItem(qtTrId("cmb_val_month"));
    //% "3 day"
    viewComboBox->addItem(qtTrId("cmb_val_3_day"));

    viewComboBox->setCurrentIndex(1);
    viewChangeAction->setWidget(viewComboBox);
    connect( viewComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(viewChanged(int)) );

    //Create filter change combo box
    MWidgetAction* filterChangeAction = new MWidgetAction(panel);
    filterChangeAction->setLocation(MAction::ApplicationMenuLocation);

    MComboBox* filterComboBox = new MComboBox;
    //% "All"
    filterComboBox->addItem(qtTrId("cmb_fltr_all"));

    filterComboBox->setCurrentIndex(0);
    filterChangeAction->setWidget(filterComboBox);

    //Create new action
    MAction *newAction = new MAction(this->centralWidget());
    newAction->setLocation(MAction::ToolBarLocation);
    //% "new"
    newAction->setText(qtTrId("action_new"));
    connect(newAction, SIGNAL(triggered()), this , SLOT(createNewEvent()));

    //Create search action
    MAction *searchAction = new MAction(this->centralWidget());
    searchAction->setLocation(MAction::ToolBarLocation);
    //% "search"
    searchAction->setText(qtTrId("action_search"));
    connect(searchAction, SIGNAL(triggered()), this , SLOT(searchEvent()));

    //Create exit action
    MAction *exitAction = new MAction(this->centralWidget());
    exitAction->setLocation(MAction::ApplicationMenuLocation);
    //% "exit"
    exitAction->setText(qtTrId("action_exit"));
    connect(exitAction, SIGNAL(triggered()), this , SLOT(exitEvent()));

    //Add the actions for all pages
    this->addAction(viewChangeAction);
    this->addAction(filterChangeAction);
    this->addAction(newAction);
    this->addAction(searchAction);
    this->addAction(exitAction);
}

void MMonthView::monthClicked(int value)
{
    QDate* date = new QDate( QDate::currentDate() );
    date->setDate(date->year(),value+1,1);
    calendarLayout->daySelected(*date);
    calendarLayout->populateCalendar();

    if ( value >= 12 )
    {
        value -= 12;
    }
    else if ( value < 0 )
    {
        value += 12;
    }
    setHighlights(value);
}

void MMonthView::setHighlights(int value)
{
    for(int i=0; i<monthSelectLayout->count();i++)
    {
        bool isHighlighted = false;

        if(i==value)
        {
            isHighlighted = true;
        }
        MMonthSelectItem* item = (MMonthSelectItem*)monthSelectLayout->itemAt(i);
        item->setHighlighted(isHighlighted);
    }
}

void MMonthView::updateViewComboBox(int index)
{
    viewComboBox->setCurrentIndex(index);
}

void MMonthView::swipeGestureEvent(QGestureEvent *event, QSwipeGesture* gesture)
{
    if (gesture->verticalDirection() != QSwipeGesture::NoDirection) {
         event->ignore(gesture);
         return;
     }

    bool performScroll = false;
    switch( gesture->state() )
    {
    case Qt::GestureStarted:
        {
        performScroll = true;
        break;
        }
    case Qt::NoGesture:
    case Qt::GestureUpdated:
    case Qt::GestureFinished:
    case Qt::GestureCanceled:
        {
        performScroll = false;
        break;
        }
    }

    if ( performScroll )
    {
        if (gesture->horizontalDirection() == QSwipeGesture::Left)
        {
            event->accept(gesture);
            monthClicked( calendarLayout->currentDate().month() );
        }
        if (gesture->horizontalDirection() == QSwipeGesture::Right)
        {
            event->accept(gesture);
            monthClicked( calendarLayout->currentDate().month()-2 );
        }
    }
}


MMonthView::~MMonthView()
{
}

void MMonthView::exitEvent()
{
    viewManager->writeSettings();
    exit(0);
}

void MMonthView::viewChanged(int index)
{
    viewManager->changeView(index);
}

void MMonthView::setDate( const QDate & date )
{
    if(currDate)
    {
        delete currDate;
    }
    currDate = new QDate(date);

    //viewManager->setSelectedDate(date);
    //setSelectedDate(date);
    //populateLists();
    if(currDate)
      {
          setHighlights(currDate->month()-1);
      }
}

void MMonthView::createNewEvent()
{
    viewManager->handleEditCalendarEvent();
    updateEvents();
}

void MMonthView::searchEvent()
{
    MDialog* dlg = new MDialog();
    //% "search"
    dlg->setTitle(qtTrId("title_search"));
    dlg->exec();
    delete dlg;
    dlg=NULL;
}

void MMonthView::updateEvents()
{
    calendarLayout->populateCalendar();
}

MMonthSelectItem::MMonthSelectItem(const QString& text) : MButton(text), isHighlighted(false)
{
    QObject::connect( this, SIGNAL(clicked()) ,this, SLOT(sendValue()) );
}

void MMonthSelectItem::sendValue()
{
    emit monthClicked( this->data(0).toInt() );
}

MMonthSelectItem::~MMonthSelectItem()
{
}

void MMonthSelectItem::setHighlighted(bool highlighted)
{
    isHighlighted = highlighted;
}

void MMonthSelectItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    if(isHighlighted)
    {
        QRect backgroundrect;
        backgroundrect.setLeft(rect().left());
        backgroundrect.setRight(rect().right());
        backgroundrect.setBottom(rect().bottom());
        backgroundrect.setTop(rect().top());

        backgroundrect.adjust( -2,-2,2,2 );

        QBrush brush;
        brush.setColor( Qt::white );
        brush.setStyle( Qt::SolidPattern );
        painter->setBrush( brush );
        painter->drawRoundRect(backgroundrect, 20, 20);
    }
    MButton::paint(painter,option,widget);
}
