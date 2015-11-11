/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "backgroundaction.h"

#include <QComboBox>
#include <QPainter>

namespace QmlDesigner {

BackgroundAction::BackgroundAction(QObject *parent) :
    QWidgetAction(parent)
{
}

QIcon iconForColor(const QColor &color) {
    const int size = 16;
    QImage image(size, size, QImage::Format_ARGB32);
    image.fill(0);
    QPainter p(&image);

    p.fillRect(2, 2, size - 4, size - 4, Qt::black);

    if (color.alpha() == 0) {
        const int miniSize = (size - 8) / 2;
        p.fillRect(4, 4, miniSize, miniSize, Qt::white);
        p.fillRect(miniSize + 4, miniSize + 4, miniSize, miniSize, Qt::white);
    } else {
        p.fillRect(4, 4, size - 8, size - 8, color);
    }
    return QPixmap::fromImage(image);
}

QWidget *BackgroundAction::createWidget(QWidget *parent)
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->setFixedWidth(42);

    for (int i = 0; i < colors().count(); ++i) {
        comboBox->addItem(tr(""));
        comboBox->setItemIcon(i, iconForColor((colors().at(i))));
    }

    comboBox->setCurrentIndex(0);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), SLOT(emitBackgroundChanged(int)));

    comboBox->setProperty("hideborder", true);
    return comboBox;
}

void BackgroundAction::emitBackgroundChanged(int index)
{
    if (index < colors().count())
        emit backgroundChanged(colors().at(index));
}

QList<QColor> BackgroundAction::colors()
{
    static QColor alphaZero(Qt::transparent);
    static QList<QColor> colorList = QList<QColor>() << alphaZero
                                                  << QColor(Qt::black)
                                                  << QColor(Qt::darkGray)
                                                  << QColor(Qt::lightGray)
                                                  << QColor(Qt::white);


    return colorList;
}

} // namespace QmlDesigner
