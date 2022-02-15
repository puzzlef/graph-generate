#pragma once
#include "Graph.hxx"




// TRANSPOSE
// ---------

template <class H, class G>
void transposeTo(H& a, const G& x, bool unq=false) {
  x.forEachVertex([&](auto u, auto d) { a.addVertex(u, d); });
  x.forEachVertexKey([&](auto u) {
    x.forEachEdge(u, [&](auto v, auto w) { a.addEdge(v, u, w); });
  });
  a.correct(unq);
}

template <class G>
auto transpose(const G& x) {
  G a; transposeTo(a, x, true);
  return a;
}




// TRANSPOSE-WITH-DEGREE
// ---------------------

template <class H, class G>
void transposeWithDegreeTo(H& a, const G& x, bool unq=false) {
  x.forEachVertexKey([&](auto u) { a.addVertex(u, x.degree(u)); });
  x.forEachVertexKey([&](auto u) {
    x.forEachEdge(u, [&](auto v, auto w) { a.addEdge(v, u, w); });
  });
  a.correct(unq);
}

template <class G>
auto transposeWithDegree(const G& x) {
  using K = typename G::key_type;
  using H = decltype(retype(x, K(), K()));
  H a; transposeWithDegreeTo(a, x, true);
  return a;
}
