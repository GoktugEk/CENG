import pandas as pd
import json

 
def init_graph():
    """
    Returns an empty dictionary
    """
    return {}

def add_node(graph,node):
    """
    INPUTS: 
    Graph: type=dict base dictionary for the graph
    Node : type=str target widget to add
    METHOD:
    Adds target widget to graph and add edges to all other nodes of target node
    """
    if not(node in graph):          
        for key in graph:
            graph[key][node] = 0
        graph[node] = {}

def init_edges(graph,node):
    """
    INPUTS:
    graph: type=dict base dictionary for the graph
    node : type=str target node whose edges to be added
    METHOD:
    Adds all of the other nodes as edges to target node
    """
    for key in graph:
        if key != node:
            graph[node][key] = 0

def parse_cols(string,sep=','):
    """
    INPUTS:
    string = str to be parsed
    sep    = target seperator for string
    RETURNS:
    Splitted version of string
    """
    return string.split(sep)

def edge_up(graph,node,target):
    """
    INPUTS:
    graph: type=dict base dictionary for the graph
    node : type=str base node edges will be added
    target: type=str target node will be added to base node as edge
    """
    if node != target:
        graph[node][target] += 1

def base_integrate(base,target):
    """
    INPUTS:
    base  : type=dict edges of a node
    target: type=dict edges of the target node
    METHOD:
    Integrates the edge values of two node
    """
    if base == {}:
        return target
    else:
        for key in target:
            if key in base:
                base[key] += target[key]
            else:
                base[key] = target[key]
    return base

def recommend(graph,widgets):
    """
    INPUTS: 
    graph  : type=dict base dictionary for the graph
    widgets: type=list widgets that user has used
    METHOD:
    Integrates the edges of all widgets and recommend 5 widgets which have the most powerful edges
    """
    base = {}

    for widget in widgets:
        if not(widget in graph):
            continue
        base = base_integrate(base,graph[widget])

    sorted_widgets =  sorted(base.items(), key=lambda x: x[1], reverse=True) 
    recommended_widgets = [x for x,y in sorted_widgets[:5:]]

    return recommended_widgets

def init_save_graph(filename):
    """
    METHOD:
    Inits the graph,nodes,edges according to the data. Prints it as json string 
    """
    graph = init_graph()

    df = pd.read_csv("dataset_for_widgets_rec.csv")

    for row in df["used widgets"]:
        nodes = parse_cols(row)

        for node in nodes:
            add_node(graph,node)
            init_edges(graph,node)

            
    for row in df["used widgets"]:
        nodes = parse_cols(row)
        
        for node in nodes:
            for target in nodes:
                edge_up(graph,node,target)


    graph = json.dumps(graph,indent=4)

    with open(filename,'w') as file:
        json.dump(graph,file)

def load_graph(filename):
    """
    Returns saved graph
    """
    with open(filename) as file:
        graph = json.load(file)
        graph = json.loads(graph)
    
    return graph

