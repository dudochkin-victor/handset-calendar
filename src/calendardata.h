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

#ifndef CALENDARDATA_H
#define CALENDARDATA_H

#include <QString>
#include <QColor>

class CalendarData
{
public:
    /**
      CalendarData::CalendarData()
    */
    CalendarData(const QString& newUri, const QString& newName, const QColor& newColor );
    /**
      CalendarData::~CalendarData()
    */
    ~CalendarData();

public:
    //Getters
    /**
      QString& Uri();
      @return cal uri as string
    */
    QString& Uri();
    /**
      QString& Name();
      @return cal name
    */
    QString& Name();
    /**
      QColor& Color();
      @return cal color
    */
    QColor& Color();

public:
    //Setters
    /**
      void SetUri( const QString& newUri );
      @param cal uri as string
    */
    void SetUri( const QString& newUri );
    /**
      void SetName( const QString& newUri );
      @param cal name as string
    */
    void SetName( const QString& newUri );
    /**
      void SetColor( const QColor& newUri );
      @param cal color
    */
    void SetColor( const QColor& newUri );

private:
    QString* uri;
    QString* name;
    QColor* color;

};

#endif // CALENDARDATA_H
