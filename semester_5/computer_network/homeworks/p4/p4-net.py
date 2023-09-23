#!/usr/bin/env python
"""p3-net.py: See the 4th homework assignment of the course
   Computer Networks 2019, Jacobs University Bremen.

   Work with the BIRD routing configuration, nothing needs to change
   in this mininet script.

   a) Create an OSPF network for ISP F and an OSPF network ISP E. Make
      sure all hosts Ai can reach each other and all host Bi can reach
      each other. [2pt]

   b) Test that the OSPF networks handle link failures. Take a link
      down and verify that OSPF calculates alternate paths. [2pt]

   c) ISP F and ISP E create two BGP peerings. Configure the two BGP
      peering sessions. [2pt]

   d) ISP F is interested to announce his customer networks to ISP E
      but he prefers to not announce his internal network to ISP E.
      Similarly, ISP F is interested to announce his customer networks
      to ISP F but he prefers to not announce his internal network to
      ISP F. Create filters implementing these policies. [2pt]

   e) ISP F prefers to use routes announced by E1 but he likes to be
      able to fallback to routes announced by E4 in case the link to
      E1 fails. Similarly, ISP E prefers to use routes announced by F3
      but he likes to be able to fallback to routes announced by F2 in
      case the link to F3 fails. Create filters implementing these
      policies. [2pt]
"""

from mininet.cli import CLI
from mininet.net import Mininet
from mininet.log import setLogLevel

if __name__ == '__main__':
    setLogLevel('info')

    net = Mininet(switch=None, controller=None)

    # Topology of ISP 'f':

    a1 = net.addHost('a1', ip=None)
    a2 = net.addHost('a2', ip=None)
    a3 = net.addHost('a3', ip=None)
    a4 = net.addHost('a4', ip=None)
    
    f1 = net.addHost('f1', ip=None)
    f1.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")
    f2 = net.addHost('f2', ip=None)
    f2.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")
    f3 = net.addHost('f3', ip=None)
    f3.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")
    f4 = net.addHost('f4', ip=None)
    f4.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")

    net.addLink(a1, f1)
    net.addLink(a2, f2)
    net.addLink(a3, f3)
    net.addLink(a4, f4)

    net.addLink(f1, f2)
    net.addLink(f2, f3)
    net.addLink(f3, f4)
    net.addLink(f4, f1)

    a1.cmd("ip addr add 2001:638:709:a1::1/64 dev a1-eth0")
    a1.cmd("ip route add default via 2001:638:709:a1::f1 dev a1-eth0")
    a2.cmd("ip addr add 2001:638:709:a2::1/64 dev a2-eth0")
    a2.cmd("ip route add default via 2001:638:709:a2::f2 dev a2-eth0")
    a3.cmd("ip addr add 2001:638:709:a3::1/64 dev a3-eth0")
    a3.cmd("ip route add default via 2001:638:709:a3::f3 dev a3-eth0")
    a4.cmd("ip addr add 2001:638:709:a4::1/64 dev a4-eth0")
    a4.cmd("ip route add default via 2001:638:709:a4::f4 dev a4-eth0")

    f1.cmd("ip addr add 2001:638:709:a1::f1/64 dev f1-eth0")
    f2.cmd("ip addr add 2001:638:709:a2::f2/64 dev f2-eth0")
    f3.cmd("ip addr add 2001:638:709:a3::f3/64 dev f3-eth0")
    f4.cmd("ip addr add 2001:638:709:a4::f4/64 dev f4-eth0")

    f1.cmd("ip addr add 2001:638:709:f::f2:f1/64 dev f1-eth1")
    f1.cmd("ip addr add 2001:638:709:f::f4:f1/64 dev f1-eth2")
    f2.cmd("ip addr add 2001:638:709:f::f1:f2/64 dev f2-eth1")
    f2.cmd("ip addr add 2001:638:709:f::f3:f2/64 dev f2-eth2")
    f3.cmd("ip addr add 2001:638:709:f::f2:f3/64 dev f3-eth1")
    f3.cmd("ip addr add 2001:638:709:f::f4:f3/64 dev f3-eth2")
    f4.cmd("ip addr add 2001:638:709:f::f3:f4/64 dev f4-eth1")
    f4.cmd("ip addr add 2001:638:709:f::f1:f4/64 dev f4-eth2")

    # Topology of ISP 'e':

    b1 = net.addHost('b1', ip=None)
    b2 = net.addHost('b2', ip=None)
    b3 = net.addHost('b3', ip=None)
    b4 = net.addHost('b4', ip=None)

    e1 = net.addHost('e1', ip=None)
    e1.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")
    e2 = net.addHost('e2', ip=None)
    e2.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")
    e3 = net.addHost('e3', ip=None)
    e3.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")
    e4 = net.addHost('e4', ip=None)
    e4.cmd("sysctl -w net.ipv6.conf.all.forwarding=1")

    net.addLink(b1, e1)
    net.addLink(b2, e2)
    net.addLink(b3, e3)
    net.addLink(b4, e4)

    net.addLink(e1, e2)
    net.addLink(e2, e3)
    net.addLink(e3, e4)
    net.addLink(e4, e1)

    b1.cmd("ip addr add 2001:638:709:b1::1/64 dev b1-eth0")
    b1.cmd("ip route add default via 2001:638:709:b1::e1 dev b1-eth0")
    b2.cmd("ip addr add 2001:638:709:b2::1/64 dev b2-eth0")
    b2.cmd("ip route add default via 2001:638:709:b2::e2 dev b2-eth0")
    b3.cmd("ip addr add 2001:638:709:b3::1/64 dev b3-eth0")
    b3.cmd("ip route add default via 2001:638:709:b3::e3 dev b3-eth0")
    b4.cmd("ip addr add 2001:638:709:b4::1/64 dev b4-eth0")
    b4.cmd("ip route add default via 2001:638:709:b4::e4 dev b4-eth0")

    e1.cmd("ip addr add 2001:638:709:b1::e1/64 dev e1-eth0")
    e2.cmd("ip addr add 2001:638:709:b2::e2/64 dev e2-eth0")
    e3.cmd("ip addr add 2001:638:709:b3::e3/64 dev e3-eth0")
    e4.cmd("ip addr add 2001:638:709:b4::e4/64 dev e4-eth0")
    
    e1.cmd("ip addr add 2001:638:709:e::e2:e1/64 dev e1-eth1")
    e1.cmd("ip addr add 2001:638:709:e::e4:e1/64 dev e1-eth2")
    e2.cmd("ip addr add 2001:638:709:e::e1:e2/64 dev e2-eth1")
    e2.cmd("ip addr add 2001:638:709:e::e3:e2/64 dev e2-eth2")
    e3.cmd("ip addr add 2001:638:709:e::e2:e3/64 dev e3-eth1")
    e3.cmd("ip addr add 2001:638:709:e::e4:e3/64 dev e3-eth2")
    e4.cmd("ip addr add 2001:638:709:e::e3:e4/64 dev e4-eth1")
    e4.cmd("ip addr add 2001:638:709:e::e1:e4/64 dev e4-eth2")

    # Create some peering links...

    net.addLink(f2, e1)
    net.addLink(f3, e4)

    f2.cmd("ip addr add 2001:638:709:f::f2 dev f2-eth3")
    e1.cmd("ip addr add 2001:638:709:e::e1 dev e1-eth3")
    f3.cmd("ip addr add 2001:638:709:f::f3 dev f3-eth3")
    e4.cmd("ip addr add 2001:638:709:e::e4 dev e4-eth3")

    # Kick off the bird routing daemons...
    
    f1.cmd("bird6 -c ./f1-bird.conf -s /var/run/f1-bird.ctl")
    f2.cmd("bird6 -c ./f2-bird.conf -s /var/run/f2-bird.ctl")
    f3.cmd("bird6 -c ./f3-bird.conf -s /var/run/f3-bird.ctl")
    f4.cmd("bird6 -c ./f4-bird.conf -s /var/run/f4-bird.ctl")

    e1.cmd("bird6 -c ./e1-bird.conf -s /var/run/e1-bird.ctl")
    e2.cmd("bird6 -c ./e2-bird.conf -s /var/run/e2-bird.ctl")
    e3.cmd("bird6 -c ./e3-bird.conf -s /var/run/e3-bird.ctl")
    e4.cmd("bird6 -c ./e4-bird.conf -s /var/run/e4-bird.ctl")

    net.start()
    CLI(net)
    
    # Shutdown the bird routing daemons...
    
    f1.cmd("birdc6 -s /var/run/f1-bird.ctl down")
    f2.cmd("birdc6 -s /var/run/f2-bird.ctl down")
    f3.cmd("birdc6 -s /var/run/f3-bird.ctl down")
    f4.cmd("birdc6 -s /var/run/f4-bird.ctl down")

    e1.cmd("birdc6 -s /var/run/e1-bird.ctl down")
    e2.cmd("birdc6 -s /var/run/e2-bird.ctl down")
    e3.cmd("birdc6 -s /var/run/e3-bird.ctl down")
    e4.cmd("birdc6 -s /var/run/e4-bird.ctl down")

    net.stop()
