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

#ifndef MDETAILDIALOG_H
#define MDETAILDIALOG_H

#include <MDialog>
#include "calendarevent.h"
#include "mviewmanager.h"

class MDetailDialog : public MDialog
{
    Q_OBJECT

public:
    /**
      MDetailDialog( MViewManager* manager, CalendarEvent* eventToView);
      */
    MDetailDialog( MViewManager* manager, CalendarEvent* eventToView);

public Q_SLOTS:
    /**
      void handleEditEvent();
      */
    void handleEditEvent();

private:
    /**
      QString repeatTypetext();
      */
    QString repeatTypetext();

private:
    MViewManager* viewManager;
    CalendarEvent* event;
};

#endif // MDETAILDIALOG_H
