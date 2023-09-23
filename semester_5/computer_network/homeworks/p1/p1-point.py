#!/usr/bin/env python
""" point.py:

    This mininet script creates a simple point-to-point topology:

             10 mbps
      h1 ------------- h2
"""

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.link import TCLink
from mininet.topo import Topo
from mininet.log import setLogLevel

class PointToPoint(Topo):
    def __init__(self, **opts):
        Topo.__init__(self, **opts)
        h1 = self.addHost('h1')
        h2 = self.addHost('h2')
        self.addLink(h1, h2, bw=10)

if __name__ == '__main__':
    setLogLevel('info')

    topo = PointToPoint()
    net = Mininet(topo=topo, link=TCLink,
                  autoSetMacs=True, autoStaticArp=True)

    net.start()
    CLI(net)
    net.stop()
