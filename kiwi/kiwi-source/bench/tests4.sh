cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1500000 n 67 33 2 > Tests/moremult/2_threads/1_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1500000 n 67 33 2 > Tests/moremult/2_threads/2_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1500000 n 67 33 2 > Tests/moremult/2_threads/3_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1500000 n 67 33 2 > Tests/moremult/2_threads/4_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1500000 n 67 33 2 > Tests/moremult/2_threads/5_1000000_raw_perc.txt  2> /dev/null
echo ~~~ 1 ~~~
cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1333333 n 75 25 3 > Tests/moremult/3_threads/1_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1333333 n 75 25 3 > Tests/moremult/3_threads/2_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1333333 n 75 25 3 > Tests/moremult/3_threads/3_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1333333 n 75 25 3 > Tests/moremult/3_threads/4_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1333333 n 75 25 3 > Tests/moremult/3_threads/5_1000000_raw_perc.txt  2> /dev/null
echo ~~~ 2 ~~~
cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1200000 n 83 17 5 > Tests/moremult/5_threads/1_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1200000 n 83 17 5 > Tests/moremult/5_threads/2_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1200000 n 83 17 5 > Tests/moremult/5_threads/3_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1200000 n 83 17 5 > Tests/moremult/5_threads/4_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1200000 n 83 17 5 > Tests/moremult/5_threads/5_1000000_raw_perc.txt  2> /dev/null
echo ~~~ 3 ~~~
cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1100000 n 91 9 10 > Tests/moremult/10_threads/1_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1100000 n 91 9 10 > Tests/moremult/10_threads/2_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1100000 n 91 9 10 > Tests/moremult/10_threads/3_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1100000 n 91 9 10 > Tests/moremult/10_threads/4_1000000_raw_perc.txt  2> /dev/null
./kiwi-bench raw 1100000 n 91 9 10 > Tests/moremult/10_threads/5_1000000_raw_perc.txt  2> /dev/null
echo ~~~ 4 ~~~
