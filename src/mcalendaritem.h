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

#ifndef MCALENDARITEM_H
#define MCALENDARITEM_H

#include <MButton>

class QDate;
class MCalendarLayout;

class MCalendarItem : public MButton
{
    Q_OBJECT

public:
    /**
      MCalendarItem( MCalendarLayout* layout, const QDate* date, const QString &text );
      */
    MCalendarItem( MCalendarLayout* layout, const QDate* date, const QString &text );
    /**
      ~MCalendarItem();
      */
    ~MCalendarItem();
public:
    /**
      void setAllDayEvent(bool isAllDay);
      */
    void setAllDayEvent(bool isAllDay);
    /**
      void setEventHours(float hours);
      */
    void setEventHours(float hours);
    /**
      void setMultipleDaysEvent(bool isMultipleDays);
      */
    void setMultipleDaysEvent(bool isMultipleDays);
    /**
      void setColor(QColor* color);
      */
    void setColor(QColor* color);

    void setCellType(int cellType);

private:
    /**
      void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
      */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

public Q_SLOTS:
    /**
      void itemSelected();
      */
    void itemSelected();

private:
    /**
      QColor* eventColor;
      */
    QColor* eventColor;
    /**
      MCalendarLayout* layout;
      */
    MCalendarLayout* layout;
    /**
      const QDate* date;
      */
    const QDate* date;
    /**
      bool isAllDayEvent;
      */
    bool isAllDayEvent;
    /**
      float eventHours;
      */
    float eventHours;
    /**
      bool isMultipleDaysEvent;
      */
    bool isMultipleDaysEvent;

    int cellType;
};

#endif // MCALENDARITEM_H
