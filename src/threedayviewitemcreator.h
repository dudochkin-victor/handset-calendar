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

#ifndef THREEDAYVIEWITEMCREATOR_H
#define THREEDAYVIEWITEMCREATOR_H

#include <MList>
#include <MContentItem>

class ThreeDayViewItemCreator : public MAbstractCellCreator<MContentItem>
{
public:
    /**
      ThreeDayViewItemCreator();
      */
    ThreeDayViewItemCreator();

public:
    /**
      void updateCell(const QModelIndex &index, MWidget *cell) const;
      */
    void updateCell(const QModelIndex &index, MWidget *cell) const;
};

#endif // THREEDAYVIEWITEMCREATOR_H
