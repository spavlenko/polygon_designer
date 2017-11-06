#pragma once
#include <QPoint>
#include <vector>

using Vertex = QPoint;
using VertexList = std::vector<Vertex>;

class Polygon
{
public:
	explicit Polygon(const VertexList& vertexes);

	const VertexList& getVertexes() const;

private:
	const VertexList m_vertexes;
};


double calculateArea(const Polygon& polygon);
bool isConvex(const Polygon& polygon);

