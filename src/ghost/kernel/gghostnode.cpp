#include "gghostnode.h"
#include "gghostnode_p.h"

#include <QtCore/QLoggingCategory>

Q_LOGGING_CATEGORY(qlcGhostNode, "GtGhost.GhostNode")

// class GGhostNode

GGhostNode::GGhostNode(GGhostNodePrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

GGhostItemList GGhostNode::childItems() const
{
    Q_D(const GGhostNode);
    return d->childItems;
}

Ghost::Status GGhostNode::status() const
{
    Q_D(const GGhostNode);
    return d->status;
}

void GGhostNode::setDescription(const QString &value)
{
    Q_D(GGhostNode);

    if (d->description != value) {
        d->description = value;
        emit descriptionChanged(value);
    }
}

QString GGhostNode::description() const
{
    Q_D(const GGhostNode);
    return d->description;
}

// class GGhostNodePrivate

GGhostNodePrivate::GGhostNodePrivate()
    : parentTree(nullptr)
    , parentNode(nullptr)
    , status(Ghost::Invalid)
{
}

GGhostNodePrivate::~GGhostNodePrivate()
{
}

QQmlListProperty<GGhostItem> GGhostNodePrivate::ghostItems()
{
    return QQmlListProperty<GGhostItem>(q_func(), childItems);
}

const char *GGhostNodePrivate::toString(Ghost::Status status)
{
    static const char s_invalid[] = "Invalid";
    static const char s_standBy[] = "StandBy";
    static const char s_running[] = "Running";
    static const char s_success[] = "Success";
    static const char s_failure[] = "Failure";
    static const char s_stopped[] = "Stopped";

    switch (status) {
    case Ghost::Invalid:
        return s_invalid;
        break;
    case Ghost::StandBy:
        return s_standBy;
        break;
    case Ghost::Running:
        return s_running;
        break;
    case Ghost::Success:
        return s_success;
        break;
    case Ghost::Failure:
        return s_failure;
        break;
    case Ghost::Stopped:
        return s_stopped;
        break;
    }

    Q_UNREACHABLE();
    return 0;
}

void GGhostNodePrivate::setStatus(Ghost::Status status)
{
    Q_Q(GGhostNode);

#if !defined(QT_NO_DEBUG)

    // 检查状态切换是否正确
    switch (this->status) {
    case Ghost::Invalid:
        switch (status) {
        case Ghost::StandBy:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::StandBy:
        switch (status) {
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Running:
        switch (status) {
        case Ghost::Success:
        case Ghost::Failure:
        case Ghost::Stopped:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Success:
        switch (status) {
        case Ghost::StandBy:
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Failure:
        switch (status) {
        case Ghost::StandBy:
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    case Ghost::Stopped:
        switch (status) {
        case Ghost::StandBy:
        case Ghost::Running:
            break;
        default:
            Q_UNREACHABLE();
        }
        break;
    }

    if (description.isEmpty()) {
        qCDebug(qlcGhostNode,
                "Status: '%s' ==> '%s' : %s(%p)",
                toString(this->status), toString(status),
                q->metaObject()->className(), q);
    } else {
        qCDebug(qlcGhostNode).nospace()
                << "Status: '" << toString(this->status)
                << "' ==> '" << toString(status)
                << "' : " << q->metaObject()->className()
                << "\n  " << description.toUtf8().constData();
    }

#endif // QT_NO_DEBUG

    if (status != this->status) {
        this->status = status;

        this->onStatusChanged(status);
        emit q->statusChanged(status);

        if (parentNode) {
            GGhostItem *item = reinterpret_cast<GGhostItem *>(q);
            dptr(parentNode)->onChildStatusChanged(item, status);
        }
    }
}

void GGhostNodePrivate::onStatusChanged(Ghost::Status status)
{
    Q_UNUSED(status);
}

void GGhostNodePrivate::onChildStatusChanged(GGhostItem *child, Ghost::Status status)
{
    Q_UNUSED(child);
    Q_UNUSED(status);
}

// moc_gghostnode.cpp
#include "moc_gghostnode.cpp"