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

#ifndef MMONTHWIDDET_H
#define MMONTHWIDGET_H

#include <MWidget>
#include <QCalendarWidget>

class MMonthWidget : public MWidget
{
public:
    MMonthWidget( MWidget* parent );

private:
    QCalendarWidget* calendar;
};

#endif // MMONTHWIGDET_H
