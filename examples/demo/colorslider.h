/****************************************************************************
** Copyright (C) 2001-2021 Klaralvdalens Datakonsult AB.  All rights reserved.
**
** This file is part of the KD Chart library.
**
** Licensees holding valid commercial KD Chart licenses may use this file in
** accordance with the KD Chart Commercial License Agreement provided with
** the Software.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 and version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE.GPL.txt included.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Contact info@kdab.com if any conditions of this licensing are not
** clear to you.
**
**********************************************************************/

#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QAbstractSlider>

class ColorSlider : public QAbstractSlider
{
    Q_OBJECT
    Q_PROPERTY(QColor startColor READ startColor WRITE setStartColor NOTIFY startColorChanged)
    Q_PROPERTY(QColor endColor READ endColor WRITE setStartColor NOTIFY endColorChanged)
public:
    explicit ColorSlider(QWidget *parent = nullptr);
    ~ColorSlider() override;
    [[nodiscard]] QColor startColor() const;
    void setStartColor(const QColor &color);
    [[nodiscard]] QColor endColor() const;
    void setEndColor(const QColor &color);
    [[nodiscard]] QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void startColorChanged();
    void endColorChanged();

public Q_SLOTS:
private:
    class Private;
    Private *d;
};

#endif // COLORSLIDER_H
