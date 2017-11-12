#pragma once

#include <QObject>

class Figure : public QObject
{
    Q_OBJECT;
protected:
    Figure() = default;

public:
    virtual ~Figure() = default;

signals:
    void changed() const;

};


