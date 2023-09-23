set term pdf
#set term dumb
set title "NewReno TCP Congestion Control Simulation"
set xlabel "Simulation time in [s]"
set xrange [0:10]
set x2range [0:10]
set ylabel "Congestion Window"
set y2label "Smoothed RTT"
set ytics nomirror
set y2tics
set autoscale y
set autoscale y2
set tics out

plot "ns-simple.data" using 1:2 axes x1y1 with lines title "cwnd", \
     "ns-simple.data" using 1:3 axes x2y2 with lines title "srtt"
