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

#ifndef MMONTHVIEW_H
#define MMONTHVIEW_H

#include <MApplicationPage>
#include <MButton>

class MViewManager;

class MCalendarLayout;
class MComboBox;

class QGestureEvent;

class QGraphicsLinearLayout;

class MMonthView : public MApplicationPage
{
    Q_OBJECT

public:
    /**
      MMonthView(MViewManager* manager);
      */
    MMonthView(MViewManager* manager);
    /**
      ~MMonthView();
      */
    ~MMonthView();
    /**
      void updateEvents();
      */
    void updateEvents();


public Q_SLOTS:
    /**
      void viewChanged(int);
      */
    void viewChanged(int);
    /**
      void createNewEvent();
      */
    void createNewEvent();
    /**
      void searchEvent();
      */
    void searchEvent();
    /**
      void exitEvent();
      */
    void exitEvent();
    /**
      void monthClicked();
      */
    void monthClicked(int value=0);

public:
    /**
      void setDate( const QDate & date );
      */
    void setDate( const QDate & date );
    /**
      void updateViewComboBox();
      */
    void updateViewComboBox(int index);

protected:
    /**
      void swipeGestureEvent(QGestureEvent *event, QSwipeGesture* gesture)
     */
    virtual void swipeGestureEvent(QGestureEvent *event, QSwipeGesture* gesture);

private:
    void setHighlights(int value);
private:
    MViewManager* viewManager;

    QGraphicsLinearLayout *monthSelectLayout;
    MCalendarLayout* calendarLayout;

    QDate* currDate;

    MComboBox* viewComboBox;
};

class MMonthSelectItem : public MButton
{
    Q_OBJECT

public:
    /**
      MMonthSelectItem();
      */
    MMonthSelectItem(const QString& text);
    /**
      ~MMonthSelectItem();
      */
    ~MMonthSelectItem();

public:
    void setHighlighted(bool isHighlighted);

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public Q_SLOTS:
    void sendValue();

Q_SIGNALS:
    void monthClicked( int value );

private:
    bool isHighlighted;

};
#endif // MMONTHVIEW_H
