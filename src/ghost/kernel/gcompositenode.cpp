#include "gcompositenode_p.h"
#include "gcompositenode_p_p.h"

// class GCompositeNode

GCompositeNode::GCompositeNode(GCompositeNodePrivate &dd, QObject *parent)
    : GGhostNode(dd, parent)
{
}

void GCompositeNode::setBrokenStatus(Ghost::Status value)
{
    Q_D(GCompositeNode);

    if ((Ghost::Success != value)
            && (Ghost::Failure != value)) {
        qWarning("GtGhost : Invalid broken status: '%s'",
                 Ghost::toString(value));
        return;
    }

    if (value != d->brokenStatus) {
        d->brokenStatus = value;
        emit brokenStatusChanged(value);
    }
}

void GCompositeNode::setUnmatchCount(int value)
{
    Q_D(GCompositeNode);

    if (value < 1) {
        qWarning("GtGhost : Value is too small, reset to 1.");
        value = 1;
    }

    if (value != d->unmatchCount) {
        d->unmatchCount = value;
        emit unmatchCountChanged(value);
    }
}

Ghost::Status GCompositeNode::brokenStatus() const
{
    Q_D(const GCompositeNode);
    return d->brokenStatus;
}

int GCompositeNode::unmatchCount() const
{
    Q_D(const GCompositeNode);
    return d->unmatchCount;
}

// class GCompositeNodePrivate

GCompositeNodePrivate::GCompositeNodePrivate(Ghost::NodeType nodeType)
    : GGhostNodePrivate(Ghost::CompositeNode, nodeType)
    , brokenStatus(Ghost::Failure)
    , unmatchCount(1)
    , unmatchCounter(-1)
    , executeIndex(0)
    , executeCounter(-1)
{
}

GCompositeNodePrivate::~GCompositeNodePrivate()
{
}
