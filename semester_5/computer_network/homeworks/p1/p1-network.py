#!/usr/bin/env python
""" network.py:

    This mininet script creates a switched multi-hop topology:

      h1               h3               h5               h7
       |                |                |                |
     10|              10|              10|              10|
       |     10 mbps    |     15 mbs     |     20 mbps    |
      s1 ------------- s2 ------------- s3 ------------- s4
       |                |     5% loss    |                |
     10|              10|              10|              10|
       |                |                |                |
      h2               h4               h6               h8
"""

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.topo import Topo
from mininet.log import setLogLevel

class Network(Topo):
    def __init__(self, **opts):
        Topo.__init__(self, **opts)
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        h3 = self.addHost('h3')
        h4 = self.addHost('h4')
        h5 = self.addHost('h5')
        h6 = self.addHost('h6')
        h7 = self.addHost('h7')
        h8 = self.addHost('h8')
        s1 = self.addSwitch('s1')
        s2 = self.addSwitch('s2')
        s3 = self.addSwitch('s3')
        s4 = self.addSwitch('s4')
        self.addLink(h1, s1, bw=10)
        self.addLink(h2, s1, bw=10)
        self.addLink(h3, s2, bw=10)
        self.addLink(h4, s2, bw=10)
        self.addLink(h5, s3, bw=10)
        self.addLink(h6, s3, bw=10)
        self.addLink(h7, s4, bw=10)
        self.addLink(h8, s4, bw=10)
        self.addLink(s1, s2, bw=10)
        self.addLink(s2, s3, bw=15, loss=5)
        self.addLink(s3, s4, bw=20)

if __name__ == '__main__':
    setLogLevel('info')

    topo = Network()
    net = Mininet(topo=topo, link=TCLink,
                  autoSetMacs=True, autoStaticArp=True)

    net.start()
    CLI(net)
    net.stop()
