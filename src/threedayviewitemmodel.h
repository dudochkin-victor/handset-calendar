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

#ifndef THREEDAYVIEWITEMMODEL_H
#define THREEDAYVIEWITEMMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>
class CalendarEvent;
class MViewManager;

class ThreeDayViewItemModel : public QAbstractTableModel
{
public:
    /**
      ThreeDayViewItemModel();
      */
    ThreeDayViewItemModel(MViewManager& manager);
    /**
      virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
      */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
      virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
      */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    /**
      virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
      */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    /**
      updateEvents();
      */
    void updateEvents();
    /**
      updateEvents();
      */
    CalendarEvent* selectedEvent(int index);
    /**
      void setDate(const QDate& newDate)
      */
    void setDate(const QDate& newDate);
    /**
      const QDate& modelDate();
      */
    const QDate& modelDate();
    /**
      bool dayHasAllDayEvent();
      */
    bool dayHasAllDayEvent();

private:
    MViewManager& viewManager;
    QList<CalendarEvent*>* modelEventList;
    QVector<QStringList> theData;
    QStringList theHeaderData;
    QDate* date;
};

#endif // THREEDAYVIEWITEMMODEL_H
