#include "polygon.h"
#include <cassert>


namespace
{
	long long crossProduction(const QPoint& lh, const QPoint& rh)
	{
		return static_cast<long long>(lh.x()) * rh.y() - static_cast<long long>(lh.y()) * rh.x();
	}
}
namespace Error
{
	Base::Base(char const* const message)
		: std::exception(message)
	{
	}

	InvalidVertexIndex::InvalidVertexIndex()
		: Base("invalid vertex index")
	{
	}

}


Polygon::Polygon(const VertexList& vertexes)
	: m_vertexes(vertexes)
{
}

std::size_t Polygon::getVertextCount() const
{
	return m_vertexes.size();
}

const Vertex& Polygon::getVertex(const std::size_t id) const
{
	if (getVertextCount() <= id)
		throw Error::InvalidVertexIndex();
	
	return m_vertexes[id];
}

double calculateArea(const Polygon& polygon)
{
	const auto vertexesCount = polygon.getVertextCount();
	if (vertexesCount < 3)
		return -1;

	double area = .0;

	size_t i = vertexesCount - 1;

	for(std::size_t j = 0; j < vertexesCount; ++j)
	{
		const auto pi = polygon.getVertex(i);
		const auto pj = polygon.getVertex(j);

		area += (static_cast<long long>(pi.x()) + pj.x()) 
					* (static_cast<long long>(pi.y()) - pj.y());

		i = j;
	}

	return area / 2;
}

bool isConvex(const Polygon& polygon)
{	
	const auto vertexesCount = polygon.getVertextCount();
	
	assert(vertexesCount > 2);
	
	if (vertexesCount == 3)
		return true;

	bool sign = false;
	
	for(size_t i = 0; i < vertexesCount; ++i)
	{
		const auto& v1Start = polygon.getVertex((i + 2) % vertexesCount);
		const auto& v1End = polygon.getVertex((i + 1) % vertexesCount);

		const QPoint v1 = v1End - v1Start;

		const auto& v2Start = polygon.getVertex((i + 1) % vertexesCount);
		const auto& v2End = polygon.getVertex((i + 0) % vertexesCount);

		const QPoint v2 = v2End - v2Start;
		
		const auto product = crossProduction(v1, v2);

		if (0 == i)
			sign = product > 0;
		else if( sign != product > 0)
			return false;
	}

	return true;
}
