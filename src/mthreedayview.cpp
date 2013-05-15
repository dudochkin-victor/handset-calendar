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

#include "mthreedayview.h"
#include <MLayout>
#include <MGridLayoutPolicy>
#include <MButton>
#include "mviewmanager.h"
#include <MAction>
#include <MWidgetAction>
#include <MButton>
#include <MLabel>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MComboBox>

#include "threedayviewitemcreator.h"
#include "threedayviewitemmodel.h"
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <QSwipeGesture>
#include <MDialog>
#include <QGraphicsColorizeEffect>

MThreeDayView::MThreeDayView(MViewManager* manager) : MApplicationPage(),
           viewManager(manager)
{
    setAcceptTouchEvents(true);
    grabGesture(Qt::SwipeGesture);
    //% "3 day"
    setTitle(qtTrId("title_3_day"));

    QGraphicsWidget *panel = centralWidget();
    MLayout *layout = new MLayout(panel);
    layout->setAnimation(NULL);
    panel->setLayout(layout);

    MLinearLayoutPolicy *mainPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);

    QGraphicsWidget *labelWidget = new QGraphicsWidget;
    QGraphicsGridLayout *labelLayout = new QGraphicsGridLayout(labelWidget);

    leftLabel = new MLabel(panel);
    middleLabel = new MLabel(panel);
    rightLabel = new MLabel(panel);

    //% "day 1"
    leftLabel->setText(qtTrId("lbl_day1"));
    leftLabel->setAlignment(Qt::AlignCenter);
    //% "day 2"
    middleLabel->setText(qtTrId("lbl_day2"));
    middleLabel->setAlignment(Qt::AlignCenter);
    //% "day 3"
    rightLabel->setText(qtTrId("lbl_day3"));
    rightLabel->setAlignment(Qt::AlignCenter);

    labelLayout->addItem(leftLabel, 0, 0);
    labelLayout->addItem(middleLabel, 0, 1);
    labelLayout->addItem(rightLabel, 0, 2);

    leftLabel->setPreferredWidth(1);
    middleLabel->setPreferredWidth(1);
    rightLabel->setPreferredWidth(1);

    mainPolicy->addItem(labelWidget);


    QGraphicsWidget *listWidget = new QGraphicsWidget;
    QGraphicsGridLayout *listLayout = new QGraphicsGridLayout(listWidget);


    dayOneList = new MList(panel);
    dayTwoList = new MList(panel);
    dayThreeList = new MList(panel);

    // Content item creator and item model for the list
    ThreeDayViewItemCreator *cellCreatorOne = new ThreeDayViewItemCreator();
    ThreeDayViewItemCreator *cellCreatorTwo = new ThreeDayViewItemCreator();
    ThreeDayViewItemCreator *cellCreatorThree = new ThreeDayViewItemCreator();

    dayOneList->setCellCreator(cellCreatorOne);
    dayTwoList->setCellCreator(cellCreatorTwo);
    dayThreeList->setCellCreator(cellCreatorThree);

    modelOne = new ThreeDayViewItemModel(*viewManager);
    modelTwo = new ThreeDayViewItemModel(*viewManager);
    modelThree = new ThreeDayViewItemModel(*viewManager);

    dayOneList->setItemModel(modelOne);
    dayTwoList->setItemModel(modelTwo);
    dayThreeList->setItemModel(modelThree);

    listLayout->addItem(dayOneList, 0, 0);
    listLayout->addItem(dayTwoList, 0, 1);
    listLayout->addItem(dayThreeList, 0, 2);

    connect(dayOneList, SIGNAL(itemClicked(QModelIndex)), this , SLOT(openDayOneListItem(QModelIndex)));
    connect(dayTwoList, SIGNAL(itemClicked(QModelIndex)), this , SLOT(openDayTwoListItem(QModelIndex)));
    connect(dayThreeList, SIGNAL(itemClicked(QModelIndex)), this , SLOT(openDayThreeListItem(QModelIndex)));

    mainPolicy->addItem(listWidget);

    setStartDateFortLists( QDate::currentDate() );

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

    viewComboBox->setCurrentIndex(2);
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

void MThreeDayView::updateViewComboBox(int index)
{
    viewComboBox->setCurrentIndex(index);
}

MThreeDayView::~MThreeDayView()
{

}

void MThreeDayView::exitEvent()
{
    viewManager->writeSettings();
    exit(0);
}

void MThreeDayView::viewChanged(int index)
{
    viewManager->changeView(index);
}

void MThreeDayView::openDayOneListItem(const QModelIndex &index)
{
    CalendarEvent* event = modelOne->selectedEvent( index.row() );
    viewManager->showEventDetails(event);
}

void MThreeDayView::openDayTwoListItem(const QModelIndex &index)
{
    CalendarEvent* event = modelTwo->selectedEvent( index.row() );
    viewManager->showEventDetails(event);
}

void MThreeDayView::openDayThreeListItem(const QModelIndex &index)
{
    CalendarEvent* event = modelThree->selectedEvent( index.row() );
    viewManager->showEventDetails(event);
}

void MThreeDayView::createNewEvent()
{
    viewManager->handleEditCalendarEvent();
}

void MThreeDayView::searchEvent()
{
    MDialog* dlg = new MDialog();
    //% "search"
    dlg->setTitle(qtTrId("dlg_title_search"));
    dlg->exec();
    delete dlg;
    dlg=NULL;
}

void MThreeDayView::updateEvents()
{
    dayOneList->setItemModel(0);
    dayTwoList->setItemModel(0);
    dayThreeList->setItemModel(0);

    modelOne->updateEvents();
    modelTwo->updateEvents();
    modelThree->updateEvents();

    setAllDayIndicator();

    dayOneList->setItemModel(modelOne);
    dayTwoList->setItemModel(modelTwo);
    dayThreeList->setItemModel(modelThree); 
}

void MThreeDayView::setAllDayIndicator()
{
    if ( modelOne->dayHasAllDayEvent() ) {
        QFont font =leftLabel->font();
        font.setUnderline(true);
        leftLabel->setFont(font);
    }
    if ( modelTwo->dayHasAllDayEvent() ) {
        QFont font =middleLabel->font();
        font.setUnderline(true);
        middleLabel->setFont(font);
    }
    if ( modelThree->dayHasAllDayEvent() ) {
        QFont font =rightLabel->font();
        font.setUnderline(true);
        rightLabel->setFont(font);
    }
}

void MThreeDayView::setStartDateFortLists( const QDate& startDate )
{
    QDate today = QDate::currentDate();
    QDate date_1 = startDate;
    QDate date_2 = date_1.addDays(1);
    QDate date_3 = date_1.addDays(2);

    modelOne->setDate( date_1 );
    modelTwo->setDate( date_2 );
    modelThree->setDate( date_3 );

    if ( today == date_1 ) {
        //% "Today "
        QString txt(qtTrId("str_today"));
        txt.append( date_1.toString( "dddd dd" ) );
        leftLabel->setText( txt );
        middleLabel->setText( date_2.toString( "dddd dd" ) );
        rightLabel->setText( date_3.toString( "dddd dd" ) );

        leftLabel->setColor(Qt::red);
        middleLabel->setColor(Qt::black);
        rightLabel->setColor(Qt::black);
    }
    else if ( today == date_2 ) {
        //% "Today "
        QString txt(qtTrId("str_today"));
        txt.append( date_2.toString( "dddd dd" ) );
        leftLabel->setText( date_1.toString( "dddd dd" ) );
        middleLabel->setText( txt );
        rightLabel->setText( date_3.toString( "dddd dd" ) );

        leftLabel->setColor(Qt::black);
        middleLabel->setColor(Qt::red);
        rightLabel->setColor(Qt::black);
    }
    else if ( today == date_3 ) {
        //% "Today "
        QString txt(qtTrId("str_today"));
        txt.append( date_3.toString( "dddd dd" ) );
        leftLabel->setText( date_1.toString( "dddd dd" ) );
        middleLabel->setText( date_2.toString( "dddd dd" ) );
        rightLabel->setText( txt );

        leftLabel->setColor(Qt::black);
        middleLabel->setColor(Qt::black);
        rightLabel->setColor(Qt::red);
    }
    else {
        leftLabel->setText( date_1.toString( "dddd dd" ) );
        middleLabel->setText( date_2.toString( "dddd dd" ) );
        rightLabel->setText( date_3.toString( "dddd dd" ) );

        leftLabel->setColor(Qt::black);
        middleLabel->setColor(Qt::black);
        rightLabel->setColor(Qt::black);
    }

    QFont font =middleLabel->font();
    font.setUnderline(false);
    leftLabel->setFont(font);
    middleLabel->setFont(font);
    rightLabel->setFont(font);

    updateEvents();
}

void MThreeDayView::swipeGestureEvent(QGestureEvent *event, QSwipeGesture* gesture)
{
    if (gesture->verticalDirection() != QSwipeGesture::NoDirection) {
         event->ignore(gesture);
         return;
     }

    bool performScroll = false;
    switch( gesture->state() )
    {
    case Qt::GestureStarted:
    case Qt::GestureFinished:
        {
        performScroll = true;
        break;
        }
    case Qt::NoGesture:
    case Qt::GestureUpdated:
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
            setStartDateFortLists( modelOne->modelDate().addDays(1) );
        }
        if (gesture->horizontalDirection() == QSwipeGesture::Right)
        {
            event->accept(gesture);
            setStartDateFortLists( modelOne->modelDate().addDays(-1) );
        }
    }
}
