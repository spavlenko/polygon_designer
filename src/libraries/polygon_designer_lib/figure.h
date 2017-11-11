#pragma once

#include <QObject>

class Figure : public QObject
{
    Q_OBJECT;
public:
    Figure() = default;
    virtual ~Figure() = default;

signals:
    void changed() const;

};


