#pragma once
#include <QPoint>
#include <vector>

using Vertex = QPoint;
using VertexList = std::vector<Vertex>;

namespace Error
{
	class Base : std::exception
	{
	public:
		Base(char const* const message);
		virtual ~Base() override = default;
	};

	class InvalidVertexIndex: public Base
	{
	public:
		InvalidVertexIndex();
		virtual ~InvalidVertexIndex() override = default ;
	};
}

class Polygon
{
public:
	explicit Polygon(const VertexList& vertexes);
	
	std::size_t getVertextCount() const;
	const Vertex& getVertex(const std::size_t id) const;	

private:
	VertexList m_vertexes;
};


double calculateArea(const Polygon& polygon);
bool   isConvex(const Polygon& polygon);

