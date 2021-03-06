/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#ifndef QMLPROFILEREVENTSVIEW_H
#define QMLPROFILEREVENTSVIEW_H

#include "qmlprofiler_global.h"
#include "qmlprofilermodelmanager.h"

#include <QAbstractItemModel>
#include <QWidget>

namespace QmlProfiler {

class QMLPROFILER_EXPORT QmlProfilerEventsView : public QWidget
{
    Q_OBJECT
public:
    QmlProfilerEventsView(QWidget *parent = 0) : QWidget(parent) {}

    virtual void clear() = 0;
    virtual void restrictToRange(qint64 rangeStart, qint64 rangeEnd) = 0;
    virtual bool isRestrictedToRange() const = 0;

signals:
    void gotoSourceLocation(const QString &fileName, int lineNumber, int columnNumber);
    void typeSelected(int typeIndex);
    void showFullRange();

public slots:
    virtual void selectByTypeId(int typeIndex) = 0;
    virtual void onVisibleFeaturesChanged(quint64 features) = 0;
};

class QMLPROFILER_EXPORT QmlProfilerEventsViewFactory : public QObject
{
    Q_OBJECT
public:
    virtual QList<QmlProfilerEventsView *> create(QWidget *parent,
                                                  QmlProfilerModelManager *manager) = 0;
};

}

#endif // QMLPROFILEREVENTSVIEW_H
