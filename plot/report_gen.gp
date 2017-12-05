reset
set ylabel 'ratio'
set style fill solid
set title 'Report Generator'
set term png size 1600,900 enhanced font 'Verdana,12'
set output 'plot/report.png'

plot [:][0:1]'plot/report.txt' using 2:xtic(1) with histogram title 'frame loss rate', \
'' using ($0-0.06):($2+0.001):2 with labels title ' ', \
'' using 3:xtic(1) with histogram title 'server utilization'  , \
'' using ($0+0.3):($3+0.0015):3 with labels title ' ' , \

#plot [:][0:1]'plot/report.txt' using 2:xtic(1) with histogram title 'arrival time', \
#'' using ($0-0.06):($2+0.001):2 with labels title ' ', \
#'' using 3:xtic(1) with histogram title 'field complexity'  , \
#'' using ($0+0.3):($3+0.0015):3 with labels title ' ' , \
#'' using 4:xtic(1) with histogram title 'buffer size'  , \
#'' using ($0+0.4):($4+0.0015):4 with labels title ' ' , \
#'' using 5:xtic(1) with histogram title 'frame loss rate'  , \
#'' using ($0+0.5):($5+0.0015):5 with labels title ' ' , \
#'' using 6:xtic(1) with histogram title 'server utilization'  , \
#'' using ($0+0.6):($6+0.0015):6 with labels title ' '