cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1166666 n 86 14 6 > Tests/moremult/6_threads/1_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1166666 n 86 14 6 > Tests/moremult/6_threads/2_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1166666 n 86 14 6 > Tests/moremult/6_threads/3_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1166666 n 86 14 6 > Tests/moremult/6_threads/4_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1166666 n 86 14 6 > Tests/moremult/6_threads/5_1000000_raw_perc.txt  2> /dev/null
echo ~~~ 1 ~~~
