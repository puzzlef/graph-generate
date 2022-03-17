#pragma once
#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "_main.hxx"
#include "DiGraph.hxx"

using std::string;
using std::istream;
using std::stringstream;
using std::ofstream;
using std::getline;
using std::max;




// PROCESS-MTX
// -----------

template <class FV, class FE, class FC>
void processMtx(istream& s, FV fv, FE fe, FC fc) {
  string ln, h0, h1, h2, h3, h4;

  // read header
  while (1) {
    getline(s, ln);
    if (ln.find('%')!=0) break;
    if (ln.find("%%")!=0) continue;
    stringstream ls(ln);
    ls >> h0 >> h1 >> h2 >> h3 >> h4;
  }
  if (h1!="matrix" || h2!="coordinate") return;
  bool sym = h4=="symmetric" || h4=="skew-symmetric";

  // read rows, cols, size
  int r, c, sz;
  stringstream ls(ln);
  ls >> r >> c >> sz;
  int n = max(r, c);
  for (int u=1; u<=n; u++)
    fv(u);

  // read edges (from, to)
  while (getline(s, ln)) {
    int u, v;
    ls = stringstream(ln);
    if (!(ls >> u >> v)) break;
    fe(u, v);
    if (sym) fe(v, u);
  }
  fc();
}

template <class FV, class FE, class FC>
void processMtx(const char *pth, FV fv, FE fe, FC fc) {
  string buf = readFile(pth);
  stringstream s(buf);
  processMtx(s, fv, fe, fc);
}




// READ-MTX
// --------

template <class G>
void readMtx(G& a, istream& s) {
  auto fv = [&](int u) { a.addVertex(u); };
  auto fe = [&](int u, int v) { a.addEdge(u, v); };
  auto fc = [&]() { a.correct(); };
  processMtx(s, fv, fe, fc);
}

auto readMtx(istream& s) {
  DiGraph<> a; readMtx(a, s);
  return a;
}


template <class G>
void readMtx(G& a, const char *pth) {
  string buf = readFile(pth);
  stringstream s(buf);
  return readMtx(a, s);
}

auto readMtx(const char *pth) {
  DiGraph<> a; readMtx(a, pth);
  return a;
}




// WRITE-MTX
// ---------

template <class G>
void writeMtx(ostream& a, const G& x) {
  a << "%%MatrixMarket matrix coordinate real asymmetric\n";
  a << x.order() << " " << x.order() << " " << x.size() << "\n";
  for (int u : x.vertices()) {
    for (int v : x.edges(u))
      a << u << " " << v << " " << x.edgeData(u) << "\n";
  }
}

template <class G>
void writeMtx(string pth, const G& x) {
  string s0; stringstream s(s0);
  writeMtx(s, x);
  ofstream f(pth);
  f << s.rdbuf();
  f.close();
}
