#ifndef Graph_H
#define Graph_H

#include <list>
#include <vector>
#include <unordered_map>

template<typename TV, typename TE>
struct Edge;

template<typename TI, typename TV, typename TE>
struct Vertex;

template<typename TI, typename TV, typename TE>
class Graph;

template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];
    TE weight;
};

template<typename TI, typename TV, typename TE>
struct Vertex {
    TI id;
    TV data;
    std::list<Edge<TV, TE>*> edges;
};

template<typename TI, typename TV, typename TE>
class Graph{
private:
    std::unordered_map<TI, Vertex<TI, TV, TE>*>  vertexes;
    
public:
    virtual bool insertVertex(const TI& id, const TV& vertex) = 0;
    virtual bool createEdge(const TI& id1, const TI& id2, const TE& weight) = 0;
    virtual bool deleteVertex(const TI& id) = 0;
    virtual bool deleteEdge(const TI& id1, const TI& id2) = 0;
    [[nodiscard]] virtual TE &operator()(const TI& id1, const TI& id2) = 0;
    [[nodiscard]] virtual float density() const = 0;
    [[nodiscard]] virtual bool isDense(float threshold = 0.5) const = 0;
    [[nodiscard]] virtual bool isConnected() const = 0; //or StronglyConnected
    [[nodiscard]] virtual bool empty() const = 0;
    virtual void clear() = 0;
      
    virtual void display() const = 0;
    virtual void displayVertex(const TI& id) const = 0;
    [[nodiscard]] virtual TV findById(const TI& id) = 0;
};

#endif
