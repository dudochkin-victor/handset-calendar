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

#ifndef MCOMINGUPVIEW_H
#define MCOMINGUPVIEW_H

#include <MApplicationPage>

class MViewManager;
class MList;
class ComingUpViewItemModel;
class QModelIndex;
class QGraphicsGridLayout;
class MComboBox;

class MComingUpView : public MApplicationPage
{
    Q_OBJECT

public:
    /**
      MComingUpView(MViewManager* manager);
      */
    MComingUpView(MViewManager* manager);
    /**
      ~MComingUpView();
      */
    ~MComingUpView();
    /**
      void updateEvents();
      */
    void updateEvents();
    /**
      void updateViewComboBox();
      */
    void updateViewComboBox(int index);

public Q_SLOTS:
    /**
      void viewChanged(int);
      */
    void viewChanged(int);
    /**
      void openComingUpListItem(const QModelIndex &index);
      */
    void openComingUpListItem(const QModelIndex &index);
    /**
      void openLaterListItem(const QModelIndex &index);
      */
    void openLaterListItem(const QModelIndex &index);
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

private:
    MViewManager *viewManager;
    MList *comingUpList;
    MList *laterList;
    ComingUpViewItemModel *comingUpModel;
    ComingUpViewItemModel *laterModel;

    QGraphicsGridLayout *listLayout;

    MComboBox* viewComboBox;
};
#endif // MCOMINGUPVIEW_H
