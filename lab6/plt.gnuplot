set terminal png size 580,800
set output "plot.png"

set multiplot layout 3, 2 title "SOR, w = 1.1";

set title "System 1"
plot [0:15] "data1" with line
unset label

set title "System 2"
plot [0:15] "data2" with line
unset label

set title "System 3"
plot [0:15] "data3" with line
unset label

set title "System 4"
plot "data4" with line
unset label

set title "System 5"
plot [0:15] "data5" with line
unset label

set title "System 6"
plot [0:15] "data6" with line
unset label