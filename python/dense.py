import networkx as nx
import pudb

def augment(vertex, flow, flows, pred):
  edge = pred[vertex]

  while edge is not None:
    flows[(edge,vertex)] += flow

    vertex = pred[edge]
    if vertex == None:
      return
    else:
      flows[(edge,vertex)] -= flow
      edge = pred[vertex]

def scan_edges(edges, graph, label, scan, pred, pathcap):
  for e in (label & edges) - scan:
    for v in set(graph.succ[e]) - label:
      label.add(v)
      pred[v] = e
      pathcap[v] = pathcap[e]
    scan.add(e)

def scan_nodes(nodes, graph, label, scan, pred, pathcap, flows, edge):
  for v in (label & nodes) - scan:
    flow = sum([flows[ed] for ed in graph.in_edges(v)])
    node_flow = min(graph.node[v]['weight'] - flow, pathcap[v])
    if flow < graph.node[v]['weight']:
      augment(v, node_flow, flows, pred)
      pathcap[edge] -= node_flow
      label.clear()
      label.add(edge)
      scan.clear()
      return
    else:
      for e in set(graph.pred[v]) - label:
        if flows[(e,v)] > 0:
          label.add(e)
          pred[e] = v
          pathcap[e] = min(pathcap[v], flows[(e,v)])
    scan.add(v)

def initialize(edge):
  return {edge}, set()

def distribute(graph_star, flows, edge):
  graph = graph_star[0]
  nodes = set(graph_star[1])
  edges = set(graph_star[2])
  pathcap = {node: None for node in graph.nodes()}
  pred = {node: None for node in graph.nodes()}
  pathcap[edge] = graph.node[edge]['weight']
  label,scan = initialize(edge)

  while pathcap[edge] > 0 and label != scan:
    print('cap:\t' + str(pathcap[edge]))
    print('label:\t' + str(list(label)))
    print('scan:\t' + str(list(scan)))
    printflows(flows)
    scan_edges(edges, graph, label, scan, pred, pathcap)
    scan_nodes(nodes, graph, label, scan, pred, pathcap, flows, edge)

  return label & nodes, pathcap[edge] <= 0

def dense(graph):
  graph_ = set()
  graph_star = get_bipartite(graph)
  flows = {edge: 0 for edge in graph_star[3]}
  for v in graph.nodes_iter():
    print(str(v))
    print(str(graph[v]))
    print(str(graph_))
    for e in [(u,v) for u in set(graph[v]) & graph_]:
      print('edge:\t' + str(e))
      label,success = distribute(graph_star, flows, e)
      printflows(flows)
      print('\n')
      if not success:
        return label
    graph_.add(v)
  return label

def get_bipartite(graph):
  graph_bi = nx.DiGraph()
  node_nodes = graph.nodes()
  edge_nodes = graph.edges()
  graph_bi.add_nodes_from(graph.nodes(data=True))
  graph_bi.add_nodes_from([((e[0],e[1]),e[2]) for e in graph.edges(data=True)])
  for u,v in graph.edges_iter():
    graph_bi.add_edge((u,v), u)
    graph_bi.add_edge((u,v), v)
  edges = graph_bi.edges()
  return graph_bi, node_nodes, edge_nodes, edges

def printflows(flows):
  print('flows:')
  for key, val in flows.iteritems():
    print('\t' + str(key) + '\t' + str(val))

def density(graph):
  edge_weights = sum([e[2]['weight'] for e in graph.edges(data=True)])
  vertex_weights = sum([v[1]['weight'] for v in graph.nodes(data=True)])
  return edge_weights - vertex_weights

G1 = nx.Graph()
G1.add_node(1, weight=2)
G1.add_node(2, weight=3)
G1.add_node(3, weight=4)
G1.add_edge(1, 2, weight=3)
G1.add_edge(1, 3, weight=3)
G1.add_edge(2, 3, weight=3)

G2 = nx.Graph()
G2.add_node(1, weight=3)
G2.add_node(2, weight=3)
G2.add_node(3, weight=3)
G2.add_node(4, weight=3)
G2.add_node(5, weight=3)
G2.add_edge(1, 2, weight=2)
G2.add_edge(1, 3, weight=2)
G2.add_edge(2, 3, weight=2)
G2.add_edge(1, 5, weight=2)
G2.add_edge(4, 5, weight=2)
G2.add_edge(3, 4, weight=2)

G3 = nx.Graph()
G3.add_node(1, weight=2)
G3.add_node(2, weight=2)
G3.add_node(3, weight=2)
G3.add_node(4, weight=2)
G3.add_node(5, weight=2)
G3.add_edge(1, 2, weight=3)
G3.add_edge(1, 3, weight=3)
G3.add_edge(2, 3, weight=3)
G3.add_edge(1, 5, weight=3)
G3.add_edge(4, 5, weight=3)
G3.add_edge(3, 4, weight=3)

G4 = nx.Graph()
G4.add_node(1, weight=2)
G4.add_node(2, weight=2)
G4.add_node(3, weight=2)
G4.add_edge(1, 2, weight=3)
G4.add_edge(1, 3, weight=3)
G4.add_edge(2, 3, weight=3)


S1 = dense(G1)
S2 = dense(G2)
S3 = dense(G3)
#S4 = dense(G4)

#d1 = density(G1)
#d2 = density(G2)
