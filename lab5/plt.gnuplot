set terminal png size 580,800
set output "plot.png"

set multiplot layout 3, 2 title "f2";

set title "n = 3, L = 10"
set label "err: 18.82" at graph 0.05,0.1
plot "3_10" with line title "approx", [-5:5] sin(3 * x) * exp(cos(2 * x)) title "f(x)"  
unset label

set title "n = 5, L = 100"
set label "err: 33.51" at graph 0.05,0.1
plot "5_100" with line title "approx", [-5:5] sin(3 * x) * exp(cos(2 * x)) title "f(x)"
unset label

set title "n = 8, L = 100"
set label "err: 0.049" at graph 0.05,0.1
plot "8_100" with line title "approx", [-5:5] sin(3 * x) * exp(cos(2 * x)) title "f(x)"
unset label

set title "n = 10, L = 100"
set label "err: 7e-3" at graph 0.05,0.1
plot "10_100" with line title "approx", [-5:5] sin(3 * x) * exp(cos(2 * x)) title "f(x)"
unset label

set title "n = 50, L = 100"
set label "err: 8e-27" at graph 0.05,0.1
plot "50_100" with line title "approx", [-5:5] sin(3 * x) * exp(cos(2 * x)) title "f(x)"
unset label

set title "n = 60, L = 500"
set label "err:  3e-27" at graph 0.05,0.1
plot "60_500" with line title "approx", [-5:5] sin(3 * x) * exp(cos(2 * x)) title "f(x)"
unset label