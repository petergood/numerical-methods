#set terminal png eps color enhanced size 10,5
set terminal png
set output 'plt.png'

set multiplot layout 1, 2 title "N = 20";
set title "Węzły równoodległe";
plot  "data1" with line title "interpolated", [-10:5] sin(5 * x / pi) * exp(-1 * x / pi) title "f(x)"
set title "Węzły Czebyszewa";
plot  "data2" with line title "interpolated", [-10:5] sin(5 * x / pi) * exp(-1 * x / pi) title "f(x)"
unset multiplot

