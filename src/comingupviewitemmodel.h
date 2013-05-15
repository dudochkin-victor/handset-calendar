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

#ifndef COMINGUPVIEWITEMMODEL_H
#define COMINGUPVIEWITEMMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>

class MViewManager;
class CalendarEvent;

class ComingUpViewItemModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
      ComingUpViewItemModel( MViewManager& manager, bool showOnlyNextFewEvents);
      */
    ComingUpViewItemModel( MViewManager& manager, bool showOnlyNextFewEvents);
    /**
      ~ComingUpViewItemModel();
      */
    ~ComingUpViewItemModel();
    /**
      CalendarEvent* selectedEvent(int index);
      */
    CalendarEvent* selectedEvent(int index);
    /**
      void updateEvents();
      */
    void updateEvents();
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

private:
    /**
      MViewManager& viewManager;
      */
    MViewManager& viewManager;
    /**
      QList<CalendarEvent*>* modelEventList;
      */
    QList<CalendarEvent*>* modelEventList;
    /**
      QVector<QStringList> theData;
      */
    QVector<QStringList> theData;
    /**
      QStringList theHeaderData;
      */
    QStringList theHeaderData;
    /**
      bool restrictEventCount;
      */
    bool restrictEventCount;
};
#endif // COMINGUPVIEWITEMMODEL_H
