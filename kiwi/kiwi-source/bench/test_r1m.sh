cd ..
make clean
make all
cd bench/
./kiwi-bench raw 1000000 y > Tests/moremult/1_1mr_raw_perc.txt  2> /dev/null
sleep 2
echo ~~~ 1 ~~
./kiwi-bench raw 1000000 y > Tests/moremult/2_1mr_raw_perc.txt  2> /dev/null
sleep 2
echo ~~~ 2 ~~~
./kiwi-bench raw 1000000 y > Tests/moremult/3_1mr_raw_perc.txt  2> /dev/null
sleep 2
echo ~~~ 3 ~~~
./kiwi-bench raw 1000000 y > Tests/moremult/4_1mr_raw_perc.txt  2> /dev/null
sleep 2
echo ~~~ 4 ~~~
./kiwi-bench raw 1000000 y > Tests/moremult/5_1mr_raw_perc.txt  2> /dev/null
sleep 2
echo ~~~ 5 ~~~
