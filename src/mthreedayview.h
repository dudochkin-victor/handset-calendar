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

#ifndef MTHREEDAYVIEW_H
#define MTHREEDAYVIEW_H

#include <MApplicationPage>

class MViewManager;
class ThreeDayViewItemModel;
class MList;
class QModelIndex;
class MLabel;
class MComboBox;

class MThreeDayView : public MApplicationPage
{
    Q_OBJECT

public:
    /**
      MThreeDayView(MViewManager* manager);
      */
    MThreeDayView(MViewManager* manager);
    /**
      ~MThreeDayView();
      */
    ~MThreeDayView();
    /**
      void updateEvents();
      */
    void updateEvents();

    /**
      void searchEvent();
      */
    void searchEvent();
    /**
      void updateViewComboBox();
      */
    void updateViewComboBox(int index);

protected:
    /**
      void swipeGestureEvent(QGestureEvent *event, QSwipeGesture* gesture)
     */
    virtual void swipeGestureEvent(QGestureEvent *event, QSwipeGesture* gesture);

public Q_SLOTS:
    /**
      void viewChanged(int);
      */
    void viewChanged(int);
    /**
      void openDayOneListItem(const QModelIndex &index);
      */
    void openDayOneListItem(const QModelIndex &index);
    /**
      void openDayTwoListItem(const QModelIndex &index);
      */
    void openDayTwoListItem(const QModelIndex &index);
    /**
      void openDayThreeListItem(const QModelIndex &index);
      */
    void openDayThreeListItem(const QModelIndex &index);
    /**
      void createNewEvent();
      */
    void createNewEvent();
    /**
      void exitEvent();
      */
    void exitEvent();

public:
    /**
      void setStartDateFortLists( const QDate& startDate );
      */
    void setStartDateFortLists( const QDate& startDate );

private:
    void setAllDayIndicator();

private:
    MViewManager* viewManager;
    MList* dayOneList;
    MList* dayTwoList;
    MList* dayThreeList;

    ThreeDayViewItemModel* modelOne;
    ThreeDayViewItemModel* modelTwo;
    ThreeDayViewItemModel* modelThree;

    MLabel  *leftLabel;
    MLabel  *middleLabel;
    MLabel  *rightLabel;

    MComboBox* viewComboBox;
};

#endif // MTHREEDAYVIEW_H
