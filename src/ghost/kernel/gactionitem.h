#ifndef GACTIONITEM_H
#define GACTIONITEM_H

#include "gghostitem.h"

class GActionItemPrivate;
class GActionItem : public GGhostItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(GActionItem)

public:
    explicit GActionItem(QObject *parent = 0);

Q_SIGNALS:
    void reset();
    void execute();
    void terminate();

public Q_SLOTS:
    void setSuccessStatus();
    void setFailureStatus();
    void setStoppedStatus();
};

#endif // GACTIONITEM_H