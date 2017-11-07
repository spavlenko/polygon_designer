#pragma once
#include <QPoint>

class Designer
{
public:
	Designer() = default;
		
	void setPendingPointPosition(const QPoint& pos);	
	void discardPendingPoint();
	void addPendingPoint();

	void finishCreation();

private:

};
