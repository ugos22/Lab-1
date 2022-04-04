cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1250000 n 80 20 4 > Tests/multithread/1_1m_raw_perc.txt  2> /dev/null
echo ~~~ 1 ~~~ 
./kiwi-bench raw 1250000 n 80 20 4 > Tests/multithread/2_1m_raw_perc.txt  2> /dev/null
echo ~~~ 2 ~~~
./kiwi-bench raw 1250000 n 80 20 4 > Tests/multithread/3_1m_raw_perc.txt  2> /dev/null
echo ~~~ 3 ~~~
./kiwi-bench raw 1250000 n 80 20 4 > Tests/multithread/4_1m_raw_perc.txt  2> /dev/null
echo ~~~ 4 ~~~
./kiwi-bench raw 1250000 n 80 20 4 > Tests/multithread/5_1m_raw_perc.txt  2> /dev/null
echo ~~~ 5 ~~~
cd ..
make clean
make all
cd bench/
echo ~~~ 6 ~~~
./kiwi-bench raw 1000000 n > Tests/multithread/1_raw_1m.txt  2> /dev/null
echo ~~~ 7 ~~~
./kiwi-bench raw 1000000 n > Tests/multithread/2_raw_1m.txt  2> /dev/null
echo ~~~ 8 ~~~
./kiwi-bench raw 1000000 n > Tests/multithread/3_raw_1m.txt  2> /dev/null
echo ~~~ 9 ~~~
./kiwi-bench raw 1000000 n > Tests/multithread/4_raw_1m.txt  2> /dev/null
echo ~~~ 10 ~~~
./kiwi-bench raw 1000000 n > Tests/multithread/5_raw_1m.txt  2> /dev/null
echo ~~~ 11 ~~~
cd ..
make clean
make all
cd bench/
