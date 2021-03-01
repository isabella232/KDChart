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

#ifndef KDGANTTCONSTRAINTMODEL_H
#define KDGANTTCONSTRAINTMODEL_H

#include <QDebug>
#include <QModelIndex>

#include "kdganttconstraint.h"
#include "kdganttglobal.h"

namespace KDGantt
{
class KDGANTT_EXPORT ConstraintModel : public QObject
{
    Q_OBJECT
    KDGANTT_DECLARE_PRIVATE_DERIVED_PARENT(ConstraintModel, QObject *)
public:
    explicit ConstraintModel(QObject *parent = nullptr);
    ~ConstraintModel() override;

    /**
     * Subclassing ConstraintModel and overriding addConstraint() and
     * removeConstraint() can provide re-entrancy issues in the
     * ConstraintModel<->ConstraintProxy interaction. Therefore it is recommed
     * to better subclass GraphicsView and override addConstraint() there.
     */
    virtual void addConstraint(const Constraint &c);
    virtual bool removeConstraint(const Constraint &c);

    void clear();
    void cleanup();

    [[nodiscard]] QList<Constraint> constraints() const;

    [[nodiscard]] bool hasConstraint(const Constraint &c) const;
    [[nodiscard]] inline bool hasConstraint(const QModelIndex &s, const QModelIndex &e) const;

    [[nodiscard]] QList<Constraint> constraintsForIndex(const QModelIndex &) const;

Q_SIGNALS:
    void constraintAdded(const KDGantt::Constraint &);
    void constraintRemoved(const KDGantt::Constraint &);

private:
    Private *_d;
};

inline const ConstraintModel::Private *ConstraintModel::d_func() const
{
    return _d;
}
inline ConstraintModel::Private *ConstraintModel::d_func()
{
    return _d;
}
inline bool ConstraintModel::hasConstraint(const QModelIndex &s, const QModelIndex &e) const
{
    return hasConstraint(Constraint(s, e));
}
}

#ifndef QT_NO_DEBUG_STREAM
#include <QDebug>

QDebug KDGANTT_EXPORT operator<<(QDebug dbg, const KDGantt::ConstraintModel &model);
inline QDebug operator<<(QDebug dbg, KDGantt::ConstraintModel *model)
{
    return operator<<(dbg, *model);
}

#endif /* QT_NO_DEBUG_STREAM */

#endif /* KDGANTTCONSTRAINTMODEL_H */
