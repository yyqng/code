script -t 2> timing.log -a output.session
sleep 1
tclsh
puts [expr 2 + 2]
exit
sleep 1
exit

