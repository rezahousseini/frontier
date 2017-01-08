import graph_tool.all as gt
import pudb

def augment(graph, vertex, flow, flows, pred):
  edge = pred[vertex]
  while edge is not None:
    flows[graph.edge(edge,vertex)] += flow
    vertex = pred[edge]
    if vertex == None:
      return
    else:
      flows[graph.edge(edge,vertex)] -= flow
      edge = pred[vertex]

def scan_edges(graph, label, scan, pred, pathcap):
  for e in [ed for ed in graph.vertices() if graph.vp.isedge[ed]
            and label[ed] and not scan[ed]]:
    for v in [ve for ve in e.out_neighbours() if not label[ve]]:
      label[v] = True
      pred[v] = e
      pathcap[v] = pathcap[e]
    scan[e] = True

def scan_nodes(graph, label, scan, pred, pathcap, flows, edge):
  for v in [ve for ve in graph.vertices() if not graph.vp.isedge[ve]
            and label[ve] and not scan[ve]]:
    flow = sum([flows[ed] for ed in v.in_edges()])
    node_flow = min(graph.vp.weight[v] - flow, pathcap[v])
    if flow < graph.vp.weight[v]:
      augment(graph, v, node_flow, flows, pred)
      pathcap[edge] -= node_flow
      label.set_value(False)
      label[edge] = True
      scan.set_value(False)
      return
    else:
      for e in [ed for ed in v.in_neighbours() if not label[ed]]:
        if flows[graph.edge(e,v)] > 0:
          label[e] = True
          pred[e] = v
          pathcap[e] = min(pathcap[v], flows[graph.edge(e,v)])
    scan[v] = True

def distribute(graph, flows, edge):
  pathcap = {vertex: None for vertex in graph.vertices()}
  pred = {vertex: None for vertex in graph.vertices()}
  pathcap[edge] = graph.vp.weight[edge]
  label = graph.new_vertex_property("bool", val=False)
  scan = graph.new_vertex_property("bool", val=False)
  label[edge] = True

  while pathcap[edge] > 0 and any([label[v] and not scan[v] for v in
                                   graph.vertices()]):
    scan_edges(graph, label, scan, pred, pathcap)
    scan_nodes(graph, label, scan, pred, pathcap, flows, edge)
  return [v for v in graph.vertices() if not graph.vp.isedge[v] and
          label[v]], pathcap[edge] <= 0

def dense(graph):
  graph_ = set()
  graph_bi, edge_to_vertex = get_bipartite(graph)
  flows = {edge: 0 for edge in graph_bi.edges()}
  for v in graph.vertices():
    for e in [graph.edge(v, u) for u in set(v.out_neighbours()) & graph_]:
      label,success = distribute(graph_bi, flows, edge_to_vertex[e])
      printflows(flows)
      print('\n')
      if not success:
        issubgraph = graph.new_vertex_property("bool", val=False)
        for v in label:
          issubgraph[graph_bi.vp.origin[v]] = True
        return gt.GraphView(graph, vfilt=issubgraph)
    graph_.add(v)
  return gt.GraphView(graph, vfilt=label)

def get_bipartite(graph):
  graph_bi = gt.Graph()
  graph_bi.vp.weight = graph_bi.new_vertex_property("int")
  graph_bi.vp.origin = graph_bi.new_vertex_property("object")
  graph_bi.vp.isedge = graph_bi.new_vertex_property("bool", val=False)
  for v in graph.vertices():
    vc = graph_bi.add_vertex()
    graph_bi.vp.origin[vc] = v
  graph.copy_property(graph.vp.weight, graph_bi.vp.weight)
  edge_to_vertex = graph.new_edge_property("object")
  for e in graph.edges():
    vs = e.source()
    vt = e.target()
    v = graph_bi.add_vertex()
    graph_bi.vp.weight[v] = graph.ep.weight[e]
    graph_bi.vp.origin[v] = e
    graph_bi.vp.isedge[v] = True
    edge_to_vertex[e] = v
    et = graph_bi.add_edge(v, vt)
    es = graph_bi.add_edge(v, vs)
  return graph_bi, edge_to_vertex

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

gt.graph_draw(S2, vertex_text=S2.vertex_index, vertex_font_size=18,
              output_size=(200, 200), output="S2.pdf")
