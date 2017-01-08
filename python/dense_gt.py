import graph_tool.all as gt
from itertools import chain
import pudb

def augment(graph, vertex, flow, flows, pred):
  edge = pred[vertex]
  while edge is not None:
    flows[(edge,vertex)] += flow
    vertex = pred[edge]
    if vertex == None:
      return
    else:
      flows[(edge,vertex)] -= flow
      edge = pred[vertex]

def scan_edges(graph, label, scan, pred, pathcap):
  for e in [ed for ed in graph.edges() if label[ed] and not scan[ed]]:
    for v in [ve for ve in [e.source(), e.target()] if not label[ve]]:
      label[v] = True
      pred[v] = e
      pathcap[v] = pathcap[e]
    scan[e] = True

def scan_nodes(graph, label, scan, pred, pathcap, flows, edge):
  for v in [ve for ve in graph.vertices() if label[ve] and not scan[ve]]:
    flow = sum([flows[(ed,v)] for ed in v.all_edges()])
    node_flow = min(graph.vp.weight[v] - flow, pathcap[v])
    if flow < graph.vp.weight[v]:
      augment(graph, v, node_flow, flows, pred)
      pathcap[edge] -= node_flow
      label = {v: False for v in label}
      label[edge] = True
      scan = {v: False for v in scan}
      return
    else:
      for e in [ed for ed in v.all_edges() if not label[ed]]:
        if flows[(e,v)] > 0:
          label[e] = True
          pred[e] = v
          pathcap[e] = min(pathcap[v], flows[(e,v)])
    scan[v] = True

def distribute(graph, flows, edge):
  vertices = list(chain(graph.vertices(), graph.edges()))
  pathcap = {vertex: None for vertex in vertices}
  pred = {vertex: None for vertex in vertices}
  label = {vertex: False for vertex in vertices}
  scan = {vertex: False for vertex in vertices}
  pathcap[edge] = graph.ep.weight[edge]
  label[edge] = True

  while pathcap[edge] > 0 and any([label[v] and not scan[v] for v in vertices]):
    scan_edges(graph, label, scan, pred, pathcap)
    scan_nodes(graph, label, scan, pred, pathcap, flows, edge)
  return [v for v in graph.vertices() if label[v]], pathcap[edge] <= 0

def dense(graph):
  graph_ = set()
  f1 = lambda e: (e,e.source())
  f2 = lambda e: (e,e.target())
  flows = {f(e): 0 for e in graph.edges() for f in (f1,f2)}
  for v in graph.vertices():
    for e in [graph.edge(v, u) for u in set(v.out_neighbours()) & graph_]:
      label,success = distribute(graph, flows, e)
      #printflows(flows)
      #print('\n')
      if not success:
        return label
    graph_.add(v)
  return label

def printflows(flows):
  print('flows:')
  for key, val in flows.iteritems():
    print('\t' + str(key) + '\t' + str(val))

#def minimal(A, flows, edge):
#  B = {edge}
#  while density(B) <= 0 and density(A) > 1:
#    vk = A - B


#def density(graph):
#  edge_weights = sum([e[2]['weight'] for e in graph.edges(data=True)])
#  vertex_weights = sum([v[1]['weight'] for v in graph.nodes(data=True)])
#  return edge_weights - vertex_weights

G1 = gt.Graph(directed=False)
G1.vp.weight = G1.new_vertex_property("int")
G1.ep.weight = G1.new_edge_property("int")

v0 = G1.add_vertex()
v1 = G1.add_vertex()
v2 = G1.add_vertex()
e0 = G1.add_edge(v0, v1)
e1 = G1.add_edge(v0, v2)
e2 = G1.add_edge(v1, v2)


G1.vp.weight[v0] = 2
G1.vp.weight[v1] = 3
G1.vp.weight[v2] = 4


G1.ep.weight[e0] = 3
G1.ep.weight[e1] = 3
G1.ep.weight[e2] = 3

#gt.graph_draw(G1, vertex_text=G1.vertex_index, vertex_font_size=18,
#              output_size=(200, 200), output="G1.pdf")

G2 = gt.Graph(directed=False)
G2.vp.weight = G2.new_vertex_property("int")
G2.ep.weight = G2.new_edge_property("int")

v0 = G2.add_vertex()
v1 = G2.add_vertex()
v2 = G2.add_vertex()
v3 = G2.add_vertex()
v4 = G2.add_vertex()
e0 = G2.add_edge(v0, v1)
e1 = G2.add_edge(v0, v2)
e2 = G2.add_edge(v1, v2)
e3 = G2.add_edge(v0, v4)
e4 = G2.add_edge(v2, v3)
e5 = G2.add_edge(v3, v4)

G2.vp.weight[v0] =2
G2.vp.weight[v1] =2
G2.vp.weight[v2] =2
G2.vp.weight[v3] =2
G2.vp.weight[v4] =2

G2.ep.weight[e0] =3
G2.ep.weight[e1] =3
G2.ep.weight[e2] =3
G2.ep.weight[e3] =3
G2.ep.weight[e4] =3
G2.ep.weight[e5] =3

#G3 = nx.Graph()
#G3.add_node(1, weight=2)
#G3.add_node(2, weight=2)
#G3.add_node(3, weight=2)
#G3.add_node(4, weight=2)
#G3.add_node(5, weight=2)
#G3.add_edge(1, 2, weight=3)
#G3.add_edge(1, 3, weight=3)
#G3.add_edge(2, 3, weight=3)
#G3.add_edge(1, 5, weight=3)
#G3.add_edge(4, 5, weight=3)
#G3.add_edge(3, 4, weight=3)
#
#G4 = nx.Graph()
#G4.add_node(1, weight=2)
#G4.add_node(2, weight=2)
#G4.add_node(3, weight=2)
#G4.add_edge(1, 2, weight=3)
#G4.add_edge(1, 3, weight=3)
#G4.add_edge(2, 3, weight=3)

G3 = gt.Graph(directed=False)
G3.vp.weight = G3.new_vertex_property("int")
G3.ep.weight = G3.new_edge_property("int")

v0 = G3.add_vertex()
v1 = G3.add_vertex()
v2 = G3.add_vertex()
e0 = G3.add_edge(v0, v1)
e1 = G3.add_edge(v0, v2)
e2 = G3.add_edge(v1, v2)

G3.vp.weight[v0] = 2
G3.vp.weight[v1] = 2
G3.vp.weight[v2] = 2

G3.ep.weight[e0] = 3
G3.ep.weight[e1] = 3
G3.ep.weight[e2] = 3


#S1 = dense(G1)
S2 = dense(G2)
#S3 = dense(G3)
#S4 = dense(G4)

#d1 = density(G1)
#d2 = density(G2)

#gt.graph_draw(S2, vertex_text=S2.vertex_index, vertex_font_size=18,
#              output_size=(200, 200), output="S2.pdf")
