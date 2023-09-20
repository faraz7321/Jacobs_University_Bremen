#
# This shell script creates the following IP network topology using
# Linux network namespaces.
#
#           10.0.0.1/30                   10.0.0.5/30 
# .--------.h1-e0               .--------.r1-e1               .--------.
# |   h1   |--------------------|   r1   |--------------------|   h2   |
# '--------'               r1-e0'--------'               h2-e0'--------'
#                    10.0.0.2/30                   10.0.0.6/30
#
# To create more advanced topologies, consider using the mininet
# Python API (which is hiding some of the verbosity).
#

NSH1="ns-h1"
NSH2="ns-h2"
NSR1="ns-r1"

H1E0="h1-e0"
R1E0="r1-e0"
R1E1="r2-e1"
H2E0="h2-e0"

# Remove existing namespace
sudo ip netns del $NSH1 2> /dev/null
sudo ip netns del $NSH2 2> /dev/null
sudo ip netns del $NSR1 2> /dev/null

# Remove existing veth pairs (this is likely not needed / useful)
sudo ip link del $H1E0 2> /dev/null
sudo ip link del $H2E0 2> /dev/null
sudo ip link del $R1E0 2> /dev/null
sudo ip link del $R1E1 2> /dev/null

# Create veth pairs as links
sudo ip link add $H1E0 type veth peer name $R1E0
sudo ip link add $R1E1 type veth peer name $H2E0

# Bring up the links
sudo ip link set dev $H1E0 up
sudo ip link set dev $R1E0 up
sudo ip link set dev $R1E1 up
sudo ip link set dev $H2E0 up

# Create the specific namespaces
sudo ip netns add $NSH1
sudo ip netns add $NSH2
sudo ip netns add $NSR1

# Move the interfaces to the namespace
sudo ip link set $H1E0 netns $NSH1
sudo ip link set $R1E0 netns $NSR1
sudo ip link set $R1E1 netns $NSR1
sudo ip link set $H2E0 netns $NSH2

# Configure the loopback interface in namespace
sudo ip netns exec $NSH1 ip address add 127.0.0.1/8 dev lo
sudo ip netns exec $NSH1 ip link set dev lo up
sudo ip netns exec $NSH2 ip address add 127.0.0.1/8 dev lo
sudo ip netns exec $NSH2 ip link set dev lo up
sudo ip netns exec $NSR1 ip address add 127.0.0.1/8 dev lo
sudo ip netns exec $NSR1 ip link set dev lo up

# Bridge configuration (not used - we do routing)
#sudo ip netns exec $R1 brctl addbr br549
#sudo ip netns exec $R1 brctl addif br549 $R1E0
#sudo ip netns exec $R1 brctl addif br549 $R1E1
#sudo ip netns exec $H2 ip route add 10.0.0.0/30 via 10.0.0.5

# Bring up interfaces in namespace
sudo ip netns exec $NSH1 ip link set dev $H1E0 up
sudo ip netns exec $NSH1 ip address add 10.0.0.1/30 dev $H1E0
sudo ip netns exec $NSR1 ip link set dev $R1E0 up
sudo ip netns exec $NSR1 ip address add 10.0.0.2/30 dev $R1E0
sudo ip netns exec $NSR1 ip link set dev $R1E1 up
sudo ip netns exec $NSR1 ip address add 10.0.0.5/30 dev $R1E1
sudo ip netns exec $NSH2 ip link set dev $H2E0 up
sudo ip netns exec $NSH2 ip address add 10.0.0.6/30 dev $H2E0

# Add ip routes
sudo ip netns exec $NSH1 ip route add 10.0.0.4/30 via 10.0.0.2
sudo ip netns exec $NSH2 ip route add 10.0.0.0/30 via 10.0.0.5

# Enable forwarding
sudo ip netns exec $NSR1 sysctl -w net.ipv4.ip_forward=1

# Connectivity testing...
# sudo ip netns exec $NSH1 ping 10.0.0.6
# sudo ip netns exec $NSH2 ping 10.0.0.5

# emulating link delays and packet loss

# delay packets with value from uniform [90ms-110ms] distribution
# sudo ip netns exec $NSH1 tc qdisc replace dev $H1E0 root netem delay 100ms 10ms

# drop packets randomly with probability of 10%
# sudo ip netns exec $NSH1 tc qdisc replace dev $H1E0 root netem loss 10%

# duplicate packets with probability 5%
# sudo ip netns exec $NSH1 tc qdisc replace dev $H1E0 root netem duplicate 5%

# corrupt packets with probability 5%
# sudo ip netns exec $NSH1 tc qdisc replace dev $H1E0 root netem corrupt 5%

# combination of impairments
# sudo ip netns exec $NSH1 tc qdisc replace dev $H1E0 root netem \
#     delay 10ms reorder 25% loss 0.2