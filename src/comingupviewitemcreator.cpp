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

#include "comingupviewitemcreator.h"
#include <MButton>
#include <QGraphicsColorizeEffect>

ComingUpViewItemCreator::ComingUpViewItemCreator( bool modifyFirstItem /*= false*/) :
modifyFirstListItem(modifyFirstItem)
{
}

void ComingUpViewItemCreator::updateCell(const QModelIndex &index, MWidget *cell) const
{
    MContentItem *contentItem = qobject_cast<MContentItem *>(cell);
    delete contentItem;

    QVariant data = index.data(Qt::DisplayRole);
    QStringList rowData = data.value<QStringList>();
    QString alarmString = rowData[2];

    if ( alarmString == "alarmON" ) {
        contentItem = new MContentItem(MContentItem::TwoIconsTwoWidgets );
    } else {
        contentItem = new MContentItem(MContentItem::TwoTextLabels );
    }

    if (modifyFirstListItem && index.row() == 0) {
        QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
        effect->setColor (Qt::red );
        contentItem->setGraphicsEffect( effect  );
    }

    cell = contentItem;

    contentItem->setTitle(rowData[0]);
    if (rowData.count() > 1)
        contentItem->setSubtitle(rowData[1]);

    if ( alarmString == "alarmON" ) {       
        contentItem->setOptionalImageID("icon-m-common-clock");
    }

    if (index.row() == 0)
        contentItem->setItemMode(MContentItem::SingleColumnTop);
    else if (index.sibling(index.row() + 1, 0).isValid())
        contentItem->setItemMode(MContentItem::SingleColumnCenter);
    else
        contentItem->setItemMode(MContentItem::SingleColumnBottom);
}
