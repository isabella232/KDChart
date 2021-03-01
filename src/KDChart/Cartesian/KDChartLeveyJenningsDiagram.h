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

#ifndef KDCHARTLEVEYJENNINGSDIAGRAM_H
#define KDCHARTLEVEYJENNINGSDIAGRAM_H

#include "KDChartLeveyJenningsCoordinatePlane.h"
#include "KDChartLineDiagram.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QPolygonF;
class QSvgRenderer;
QT_END_NAMESPACE

namespace KDChart
{
class ThreeDLineAttributes;

/**
 * @brief LeveyDiagram defines a Levey Jennings chart.
 *
 * It provides different subtypes which are set using \a setType.
 */
class KDCHART_EXPORT LeveyJenningsDiagram : public LineDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY(LeveyJenningsDiagram)
    //    KDCHART_DECLARE_PRIVATE_DERIVED_PARENT( LineDiagram,
    //    CartesianCoordinatePlane * )

    KDCHART_DECLARE_DERIVED_DIAGRAM(LeveyJenningsDiagram, LeveyJenningsCoordinatePlane)

public:
    explicit LeveyJenningsDiagram(QWidget *parent = nullptr, LeveyJenningsCoordinatePlane *plane = nullptr);
    ~LeveyJenningsDiagram() override;

    [[nodiscard]] LineDiagram *clone() const override;

    enum Symbol { OkDataPoint, NotOkDataPoint, LotChanged, SensorChanged, FluidicsPackChanged };

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare(const LeveyJenningsDiagram *other) const;

    void setLotChangedSymbolPosition(Qt::Alignment pos);
    [[nodiscard]] Qt::Alignment lotChangedSymbolPosition() const;

    void setFluidicsPackChangedSymbolPosition(Qt::Alignment pos);
    [[nodiscard]] Qt::Alignment fluidicsPackChangedSymbolPosition() const;

    void setSensorChangedSymbolPosition(Qt::Alignment pos);
    [[nodiscard]] Qt::Alignment sensorChangedSymbolPosition() const;

    void setExpectedMeanValue(float meanValue);
    [[nodiscard]] float expectedMeanValue() const;

    void setExpectedStandardDeviation(float sd);
    [[nodiscard]] float expectedStandardDeviation() const;

    [[nodiscard]] float calculatedMeanValue() const;
    [[nodiscard]] float calculatedStandardDeviation() const;

    void setFluidicsPackChanges(const QVector<QDateTime> &changes);
    [[nodiscard]] QVector<QDateTime> fluidicsPackChanges() const;

    void setSensorChanges(const QVector<QDateTime> &changes);
    [[nodiscard]] QVector<QDateTime> sensorChanges() const;

    void setScanLinePen(const QPen &pen);
    [[nodiscard]] QPen scanLinePen() const;

    void setSymbol(Symbol symbol, const QString &filename);
    [[nodiscard]] QString symbol(Symbol symbol) const;

    /* \reimpl */
    void setModel(QAbstractItemModel *model) override;

    [[nodiscard]] QPair<QDateTime, QDateTime> timeRange() const;
    void setTimeRange(const QPair<QDateTime, QDateTime> &timeRange);

protected:
    void paint(PaintContext *paintContext) override;
    void drawChanges(PaintContext *paintContext);

    virtual void drawDataPointSymbol(PaintContext *paintContext, const QPointF &pos, bool ok);
    virtual void drawLotChangeSymbol(PaintContext *paintContext, const QPointF &pos);
    virtual void drawSensorChangedSymbol(PaintContext *paintContext, const QPointF &pos);
    virtual void drawFluidicsPackChangedSymbol(PaintContext *paintContext, const QPointF &pos);

    [[nodiscard]] virtual QRectF iconRect() const;

    QSvgRenderer *iconRenderer(Symbol symbol);

    /** \reimpl */
    [[nodiscard]] const QPair<QPointF, QPointF> calculateDataBoundaries() const override;

protected Q_SLOTS:
    void calculateMeanAndStandardDeviation() const;
}; // End of class KDChartLineDiagram

}

#endif // KDCHARTLINEDIAGRAM_H
