#!/usr/bin/env python
""" star.py:

    This mininet script creates a simple star topology with a switch
    in the center:

      h1               h3
         \           /
        10 \       /10 mbps
             \   /
               s1
             /   \
        10 /       \10 mbps
         /           \
      h2              h4
"""

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.topo import Topo
from mininet.log import setLogLevel

class Star(Topo):
    def __init__(self, **opts):
        Topo.__init__(self, **opts)
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        h3 = self.addHost('h3')
        h4 = self.addHost('h4')
        s1 = self.addSwitch('s1')
        self.addLink(h1, s1, bw=10)
        self.addLink(h2, s1, bw=10)
        self.addLink(h3, s1, bw=10)
        self.addLink(h4, s1, bw=10)

if __name__ == '__main__':
    setLogLevel('info')

    topo = Star()
    net = Mininet(topo=topo, link=TCLink,
                  autoSetMacs=True, autoStaticArp=True)

    net.start()
    CLI(net)
    net.stop()
