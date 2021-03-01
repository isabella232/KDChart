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

#ifndef KDCHARTABSTRACTCARTESIANDIAGRAM_H
#define KDCHARTABSTRACTCARTESIANDIAGRAM_H

#include "KDChartAbstractDiagram.h"
#include "KDChartCartesianAxis.h"
#include "KDChartCartesianCoordinatePlane.h"

namespace KDChart
{
class GridAttributes;

/**
 * @brief Base class for diagrams based on a cartesian coordianate system.
 *
 * The AbstractCartesianDiagram interface adds those elements that are
 * specific to diagrams based on a cartesian coordinate system to the
 * basic AbstractDiagram interface.
 */
class KDCHART_EXPORT AbstractCartesianDiagram : public AbstractDiagram
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractCartesianDiagram)
    KDCHART_DECLARE_DERIVED_DIAGRAM(AbstractCartesianDiagram, CartesianCoordinatePlane)

public:
    explicit AbstractCartesianDiagram(QWidget *parent = nullptr, CartesianCoordinatePlane *plane = nullptr);
    ~AbstractCartesianDiagram() override;

    /**
     * Returns true if both diagrams have the same settings.
     */
    bool compare(const AbstractCartesianDiagram *other) const;

    [[nodiscard]] virtual int numberOfAbscissaSegments() const = 0;
    [[nodiscard]] virtual int numberOfOrdinateSegments() const = 0;

    /**
     * Add the axis to the diagram. The diagram takes ownership of the axis
     * and will delete it.
     *
     * To gain back ownership (e.g. for assigning the axis to another diagram)
     * use the takeAxis method, before calling addAxis on the other diagram.
     *
     * \sa takeAxis
     */
    virtual void addAxis(CartesianAxis *axis);
    /**
     * Removes the axis from the diagram, without deleting it.
     *
     * The diagram no longer owns the axis, so it is
     * the caller's responsibility to delete the axis.
     *
     * \sa addAxis
     */
    virtual void takeAxis(CartesianAxis *axis);
    /**
     * @return a list of all axes added to the diagram
     */
    [[nodiscard]] virtual KDChart::CartesianAxisList axes() const;

    /**
     * Triggers layouting of all coordinate planes on the current chart.
     * Normally you don't need to call this method. It's handled automatically
     * for you.
     */
    virtual void layoutPlanes();
    /** \reimpl */
    void setCoordinatePlane(AbstractCoordinatePlane *plane) override;

    /**
     * Makes this diagram use another diagram \a diagram as reference diagram
     * with relative offset \a offset. To share cartesian axes between different
     * diagrams there might be cases when you need that. Normally you don't. \sa
     * examples/SharedAbscissa
     */
    virtual void setReferenceDiagram(AbstractCartesianDiagram *diagram, const QPointF &offset = QPointF());
    /**
     * @return this diagram's reference diagram
     *  \sa setReferenceDiagram
     */
    [[nodiscard]] virtual AbstractCartesianDiagram *referenceDiagram() const;
    /**
     * @return the relative offset of this diagram's reference diagram
     * \sa setReferenceDiagram
     */
    [[nodiscard]] virtual QPointF referenceDiagramOffset() const;

    /* reimpl */
    void setModel(QAbstractItemModel *model) override;
    /* reimpl */
    void setRootIndex(const QModelIndex &index) override;
    /* reimpl */
    void setAttributesModel(AttributesModel *model) override;

protected Q_SLOTS:
    void connectAttributesModel(AttributesModel *);

protected:
    /** @return the 3D item depth of the model index \a index */
    [[nodiscard]] virtual qreal threeDItemDepth(const QModelIndex &index) const = 0;
    /** @return the 3D item depth of the data set \a column */
    [[nodiscard]] virtual qreal threeDItemDepth(int column) const = 0;
};
}

#endif
