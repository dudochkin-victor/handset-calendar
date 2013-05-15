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

#include "mcomingupview.h"
#include <MLayout>
#include <MGridLayoutPolicy>
#include <MWidgetAction>
#include "mviewmanager.h"
#include <MAction>
#include <MButton>
#include <MLabel>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MComboBox>
#include <MList>

#include "comingupviewitemcreator.h"
#include "comingupviewitemmodel.h"

#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <MNavigationBar>
#include <MApplicationMenu>
#include <MToolBar>
#include <MAction>
#include <MDialog>

MComingUpView::MComingUpView(MViewManager* manager) : MApplicationPage(),
   viewManager(manager)
{
    //% "Coming up"
    setTitle(qtTrId("title_coming_up"));

    QGraphicsWidget *panel = centralWidget();
    MLayout* layout = new MLayout(panel);
    layout->setAnimation(NULL);
    panel->setLayout(layout);

    MLinearLayoutPolicy *mainPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);

    QGraphicsWidget *labelWidget = new QGraphicsWidget;
    QGraphicsGridLayout *labelLayout = new QGraphicsGridLayout(labelWidget);

    MLabel* leftLabel = new MLabel();
    MLabel* rightLabel = new MLabel();

    //% "Coming up"
    leftLabel->setText(qtTrId("lbl_coming_up"));
    leftLabel->setAlignment(Qt::AlignLeft);
    //% "Later"
    rightLabel->setText(qtTrId("lbl_later"));
    rightLabel->setAlignment(Qt::AlignLeft);
    labelLayout->addItem(leftLabel, 0, 0);
    labelLayout->addItem(rightLabel, 0, 1);

    leftLabel->setPreferredWidth(1);
    rightLabel->setPreferredWidth(1);

    mainPolicy->addItem(labelWidget);

    QGraphicsWidget *listWidget = new QGraphicsWidget;
    //QGraphicsGridLayout *listLayout = new QGraphicsGridLayout(listWidget);
    listLayout = new QGraphicsGridLayout(listWidget);

    comingUpList = new MList(panel);

    // Content item creator and item model for the list
    ComingUpViewItemCreator *cellCreator = new ComingUpViewItemCreator(true);
    comingUpList->setCellCreator(cellCreator);
    comingUpModel = new ComingUpViewItemModel(*viewManager, true);
    comingUpList->setItemModel(comingUpModel);

    laterList = new MList(panel);
    // Content item creator and item model for the list
    ComingUpViewItemCreator *cellCreatorLater = new ComingUpViewItemCreator();
    laterList->setCellCreator(cellCreatorLater);
    laterModel = new ComingUpViewItemModel(*viewManager, false);
    laterList->setItemModel(laterModel);

    connect(comingUpList, SIGNAL(itemClicked(QModelIndex)), this , SLOT(openComingUpListItem(QModelIndex)));
    connect(laterList, SIGNAL(itemClicked(QModelIndex)), this , SLOT(openLaterListItem(QModelIndex)));

    listLayout->addItem(comingUpList, 0, 0);
    listLayout->addItem(laterList, 0, 1);
    mainPolicy->addItem(listWidget);

    //Create view change combo box
    MWidgetAction* viewChangeAction = new MWidgetAction(panel);
    viewChangeAction->setLocation(MAction::ApplicationMenuLocation);

    viewComboBox = new MComboBox(panel);
    //% "Coming Up"
    viewComboBox->addItem(qtTrId("cmb_val_coming_up"));
    //% "Month"
    viewComboBox->addItem(qtTrId("cmb_val_month"));
    //% "3 Day"
    viewComboBox->addItem(qtTrId("cmb_val_3_day"));

    viewComboBox->setCurrentIndex(0);
    viewChangeAction->setWidget(viewComboBox);
    connect( viewComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(viewChanged(int)) );

    //Create filter change combo box
    MWidgetAction* filterChangeAction = new MWidgetAction(panel);
    filterChangeAction->setLocation(MAction::ApplicationMenuLocation);

    MComboBox* filterComboBox = new MComboBox;
    //% "All"
    filterComboBox->addItem(qtTrId("cmb_val_all"));

    QList<QString*>& list = viewManager->getCalendarNames();
    for ( int i=0; i<list.count();i++ ) {
        filterComboBox->addItem( *list.at(i) );
    }
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

    updateEvents();
}

void MComingUpView::updateViewComboBox(int index)
{
    viewComboBox->setCurrentIndex(index);
}

MComingUpView::~MComingUpView()
{

}

void MComingUpView::exitEvent()
{
    viewManager->writeSettings();
    exit(0);
}

void MComingUpView::viewChanged(int index)
{
    viewManager->changeView(index);
}

void MComingUpView::openComingUpListItem(const QModelIndex &index)
{
    CalendarEvent* event = comingUpModel->selectedEvent( index.row() );
    if ( event ) {
        viewManager->showEventDetails(event);
    }
}

void MComingUpView::openLaterListItem(const QModelIndex &index)
{
    CalendarEvent* event = laterModel->selectedEvent( index.row() );
    if ( event ) {
        viewManager->showEventDetails( event );
    }
}

void MComingUpView::createNewEvent()
{
    viewManager->handleEditCalendarEvent();
}

void MComingUpView::searchEvent()
{
    MDialog* dlg = new MDialog();
    //% "search"
    dlg->setTitle(qtTrId("title_search"));
    dlg->exec();
    delete dlg;
    dlg=NULL;
}

void MComingUpView::updateEvents()
{
    comingUpList->setItemModel(0);
    laterList->setItemModel(0);

    comingUpModel->updateEvents();
    laterModel->updateEvents();

    comingUpList->setItemModel(comingUpModel);
    laterList->setItemModel(laterModel);
}

