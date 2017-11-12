#pragma once

#include "figure.h"

#include <QPoint>
#include <QLine>

#include <vector>
#include <memory>


namespace Error
{
    class Base : public std::exception
    {
    public:
        Base(char const* const message);
        virtual ~Base() override = default;
    };

    class InvalidVertexIndex : public Base
    {
    public:
        InvalidVertexIndex();
        virtual ~InvalidVertexIndex() override = default;
    };
}


using Edge       = std::pair<std::size_t, std::size_t>;
using EdgesList  = std::vector<Edge>;

using Vertex     = QPoint;
using VertexList = std::vector<Vertex>;

class Polygon final: public Figure
{
public:
    explicit Polygon(const VertexList& vertexes = {});

    Polygon(const Polygon& p);
    Polygon& operator =(const Polygon& p) = default;

    std::size_t getVertexCount() const;
    const Vertex& getVertex(const std::size_t id) const;

    EdgesList getEdgesList() const;

    void setVertexPosition(const std::size_t id, const Vertex& newPosition);

    void pushVertex(const Vertex& newVertex);
    void popVertex();

    bool doEdgesIntersects(const Edge& rhs, const Edge& lhs) const;

private:
    VertexList m_vertexes;
};


double calculateArea(const Polygon& polygon);
bool   isConvex(const Polygon& polygon);

