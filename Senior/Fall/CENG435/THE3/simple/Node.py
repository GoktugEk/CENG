import sys
import socket
import time
import threading
from queue import Queue

# Host IP
HOST = "127.0.0.1"

class Node:
    """ Node class for general use.
    """
    def __init__(self,PORT : int, distances : dict) -> None:
        # Create the socket.
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        # Bind to the local net to listen.
        self.s.bind((HOST,PORT))        
        
        # Start listening
        self.s.listen()
        
        # Timeout of 5 seconds
        self.s.settimeout(5) 
        
        # Save the port or id
        self.port = PORT
        
        # Save the graph for this node
        self.distances = distances


    def parse_message(self,data :str) -> tuple:
        # {} {} {} : data format parsing.
        n1,n2,dis = data.split(" ")
        
        return int(n1),int(n2),int(dis)
    
    def process_info(self,info : str) -> str:
        """ It parses the info message and processes it. Changes any edges if needed.

        Args:
            info (str): Information string in form "node1 node2 distance"

        Returns:
            str: It returns a string of new edge information if an update is done, returns none otherwise.
        """
        n1,n2,dis = self.parse_message(info)
        
        info = None
        
        # Calculate the total distance to the target.
        totaldist = dis + self.distances[n1]
        if totaldist < self.distances[n2]:
            
            # If it is less, update it and save the info of it.
            self.distances[n2] = totaldist
            info = f"{self.port} {n2} {totaldist}"
        
        
       
                
    
        return info
    
    def send(self, data : str) -> None:
        
        # String to bytes
        data = bytes(data, encoding='utf8')
        
        for i in node.distances.keys():
            # Itself
            if i == node.port: continue
            else:    
                
                # Connect to the destination host
                dest = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                dest.connect((HOST, i))
                
                # Send the data and close the connection
                dest.sendall(data)
                dest.close()

    def __str__(self):
        """String method for printing.

        Returns:
            str: Resulting string of the edges for the node
        """
        neighbors = list(distances.keys())
        res = ""
        for i in neighbors:
            res += f"{self.port} - {i} | {self.distances[i]}\n"
        
        return res[:-1]

# Information queue, queue is used to eliminate race conditions.
to_inform = Queue()

# Flag to shut the child thread down
kill = False

# Threading function
def talker(node : Node) -> None:
    """Threading function for sending new informations to the other nodes.

    Args:
        node (Node): Current node
    """
    while(True):
        # Check the information queue
        while not to_inform.empty():
            information = to_inform.get()
            
            # Broadcast the data 
            node.send(information)
            
        # If flag is set by the main thread
        if kill:
            break
    

# Main
if __name__ == "__main__":
    
    # Main node ID    
    node_num = int(sys.argv[1])
    
    # Node creation, early for early connection establishment
    node = Node(node_num,{})
    
    # Read the regarding file
    lines = None
    with open(f"{node_num}.costs") as f:
        lines = f.readlines()           
        
    # First line
    num_nodes = int(lines[0])
    del lines[0]

    # The graph.    
    distances = {}
    
    # Set the edges, 0 for itself
    for i in range(num_nodes):
        if 3000+i == node_num:
            distances[3000 + i] = 0
        else:
            distances[3000 + i] = float('inf') 
    
    # Line parsing and edge assignments    
    for line in lines:
        n, dis = line.split(" ")
        
        n   = int(n)
        dis = int(dis)
        
        to_inform.put(f"{node_num} {n} {dis}")
        
        distances[n] = dis
    
    # Set the node objects distances
    node.distances = distances
    
    # This sleep is to wait for connections to be established
    time.sleep(0.1)
    
    # Initialize the thread
    talk = threading.Thread(target=talker, args=(node,))
    
    # Run the thread
    talk.start()

    # Listening loop
    while True:
        try:
            # Listen for any messages
            client,addr = node.s.accept()
            
            # Receive the information
            info = client.recv(1024).decode()
            
            # Take the response of the info processing, if it is not none, something is updated.
            response = node.process_info(info)
            
            # Add the new info to the info queue.
            if response != None:
                to_inform.put(response)
        
        # Timeout, we should leave the threads.
        except TimeoutError:
            # Kill the child thread.
            kill = True
            
            # Print the resulting graph for regarding node.
            print(node)
            
            # Close the connection.
            node.s.close()
            
            # Thanks for reading, this is the end of the code
            exit()
        

        

    
    