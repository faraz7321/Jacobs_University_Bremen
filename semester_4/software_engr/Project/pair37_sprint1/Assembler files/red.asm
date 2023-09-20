;
; stupid.buggy
;
search:
sense ahead food else walk
move else search
pickup else search
goto home
walk:
flip 3 else searchright
turn left
goto search
searchright:
flip 2 else searchstraightturn right
goto search
searchstraight:
move else walk
goto search
home:
sense ahead home else walkhome
move else home
drop
goto search
walkhome:
flip 3 else walkhomeright
turn left
goto home
walkhomeright:
flip 2 else walkhomestraight
turn right
goto home
walkhomestraight:
move else walkhome
goto home