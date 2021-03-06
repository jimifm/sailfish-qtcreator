/****************************************************************************
**
** Copyright (C) 2016 Jochen Becher
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

#ifndef QMT_EDITABLETEXTITEM_H
#define QMT_EDITABLETEXTITEM_H

#include <QGraphicsTextItem>

namespace qmt {

class EditableTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit EditableTextItem(QGraphicsItem *parent);
    ~EditableTextItem();

signals:
    void returnKeyPressed();

public:
    void setShowFocus(bool showFocus);
    void setFilterReturnKey(bool filterReturnKey);
    void setFilterTabKey(bool filterTabKey);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void selectAll();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    bool m_showFocus = false;
    bool m_filterReturnKey = false;
    bool m_filterTabKey = false;
};

} // namespace qmt

#endif // QMT_EDITABLETEXTITEM_H
