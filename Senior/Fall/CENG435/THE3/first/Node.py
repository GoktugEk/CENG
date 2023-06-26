import sys
import socket
import time
import threading
from queue import Queue

HOST = "127.0.0.1"

class Node:
    def __init__(self,PORT : int, distances : dict):
        # Create the socket.
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.bind((HOST,PORT))        
        self.s.listen()
        self.s.settimeout(5) 
        
        self.port = PORT
        

        # Bind to the local net to listen.
        
        self.distances = distances


    def parse_message(self,data :str):
        
        n1,n2,dis = data.split(" ")
        
        return int(n1),int(n2),int(dis)
    
    def process_info(self,info):
        n1,n2,dis = self.parse_message(info)

        
        
        info = None
        
                
        totaldist = dis + self.distances[n1]
        if totaldist < self.distances[n2]:
            self.distances[n2] = totaldist
            info = f"{self.port} {n2} {totaldist}"
        
        if info == None:
            n1,n2 = n2,n1
            
            totaldist = dis + self.distances[n1]
            if totaldist < self.distances[n2]:
                self.distances[n2] = totaldist
                info = f"{self.port} {n2} {totaldist}"
                
    

        return info

    def __str__(self):
        neighbors = list(distances.keys())
        res = ""
        for i in neighbors:
            res += f"{self.port} - {i} | {self.distances[i]}\n"
        
        return res[:-1]
    
to_inform = Queue()
kill = False

def listener(node : Node):
    
    while(True):

        while not to_inform.empty():
            information = to_inform.get()
            send(node,information)
            
        if kill:
            break
    
    
            
            
def send(node : Node, data : str):
    # Connect to the destination host
    data = bytes(data, encoding='utf8')
    for i in node.distances.keys():
        if i == node.port:
            continue
        else:    
            dest = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            dest.connect((HOST, i))
            
            dest.sendall(data)
            dest.close()
            


if __name__ == "__main__":
    
    start = time.time() 
    
    node_num = int(sys.argv[1])
    
    lines = None
    with open(f"{node_num}.costs") as f:
        lines = f.readlines()           
        
    num_nodes = int(lines[0])
    del lines[0]
    
    distances = {}
    
    for i in range(num_nodes):
        if 3000+i == node_num:
            distances[3000 + i] = 0
        else:
            distances[3000 + i] = float('inf') 
        

    for line in lines:
        n, dis = line.split(" ")
        
        n   = int(n)
        dis = int(dis)
        
        to_inform.put(f"{node_num} {n} {dis}")
        
        distances[n] = dis
        
    node = Node(node_num,distances)
    
    time.sleep(0.1)
    
    talk = threading.Thread(target=listener, args=(node,))
    
    talk.start()

    while True:
        try:
            client,addr = node.s.accept()
                
            info = client.recv(1024).decode()
            
            response = node.process_info(info)
            
            if response != None:
                to_inform.put(response)
        except TimeoutError:
            kill = True
            print(node)
            node.s.close()
            exit()
        

        

    
    