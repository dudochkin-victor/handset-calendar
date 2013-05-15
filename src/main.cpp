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

#include <MApplication>
#include <MApplicationWindow>
#include <MApplicationPage>

#include "mviewmanager.h"

int main(int argc, char **argv)
{
    /* The base class of all DirectUI applications */
    MApplication app(argc, argv);

    /* The application window is a top-level window that contains
       the Home and Back/Close framework controls, Navigation bar,
       View menu and Toolbar components */
    MApplicationWindow w;
    w.show();

    MViewManager viewManager;

    return app.exec();
}
