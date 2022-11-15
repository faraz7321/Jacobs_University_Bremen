#! /usr/bin/gst -f

"Comments are enclosed in double quotes. May feel a bit unusual."

| aMsg n |
aMsg := 'Hello World'.
n := 1.
[ n-1 ~= aMsg size ] whileTrue: [
        Transcript show: (aMsg copyFrom: 1 to: n); cr.
        n := n + 1.
]