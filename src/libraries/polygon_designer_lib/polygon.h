#pragma once

#include "figure.h"

#include <QPoint>
#include <vector>


using Vertex = QPoint;
using Edge = std::pair<Vertex, Vertex>;
using EdgesList = std::vector<Edge>;
using VertexList = std::vector<Vertex>;

namespace Error
{
    class Base : public std::exception
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

class Polygon : public Figure
{
public:
    explicit Polygon(const VertexList& vertexes = {});

    std::size_t getVertexCount() const;
    const Vertex& getVertex(const std::size_t id) const;

    EdgesList getEdgesList() const;

    void setVertexPosition(const std::size_t id, const Vertex& newPosition);

    void pushVertex(const Vertex& newVertex);
    void popVertex();

private:
    VertexList m_vertexes;
};


double calculateArea(const Polygon& polygon);
bool   isConvex(const Polygon& polygon);
bool   doEdgesIntersects(const Edge& rhs, const Edge& lhs);

