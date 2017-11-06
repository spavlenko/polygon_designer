#include "polygon.h"
#include <cassert>


namespace
{
	long long crossProduction(const QPoint& lh, const QPoint& rh)
	{
		return static_cast<long long>(lh.x()) * rh.y() - static_cast<long long>(lh.y()) * rh.x();
	}
}


Polygon::Polygon(const VertexList& vertexes)
	: m_vertexes(vertexes)
{
}

const VertexList& Polygon::getVertexes() const
{
	return m_vertexes;
}

double calculateArea(const Polygon& polygon)
{
	if (polygon.getVertexes().size() < 3)
		return -1;

	double area = .0;

	const auto vertexesCount = polygon.getVertexes().size();
	
	size_t i = vertexesCount - 1;

	for(std::size_t j = 0; j < vertexesCount; ++j)
	{
		const auto pi = polygon.getVertexes()[i];
		const auto pj = polygon.getVertexes()[j];

		area += (pi.x() + pj.x()) * (pi.y() - pj.y());

		i = j;
	}

	return area / 2;

}

bool isConvex(const Polygon& polygon)
{
	const auto& vertexes = polygon.getVertexes();
	
	assert(vertexes.size() > 2);
	
	const auto size = vertexes.size();

	if (size == 3)
		return true;

	bool sign = false;
	
	for(size_t i = 0; i < size; ++i)
	{
		const auto& v1Start = vertexes[(i + 2) % size];
		const auto& v1End = vertexes[(i + 1) % size];

		const QPoint v1 = v1End - v1Start;

		const auto& v2Start = vertexes[(i + 1) % size];
		const auto& v2End = vertexes[(i + 0) % size];

		const QPoint v2 = v2End - v2Start;
		
		const auto product = crossProduction(v1, v2);

		if (0 == i)
			sign = product > 0;
		else if( sign != product > 0)
			return false;
	}

	return true;
}
