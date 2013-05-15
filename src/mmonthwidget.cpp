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

#include "mmonthwidget.h"

MMonthWidget::MMonthWidget( MWidget* parent ) : MWidget(parent)
{
    calendar = new QCalendarWidget();
}

