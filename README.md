# ParallelPiTest
Based on "Can My Water Cooled Raspberry Pi Cluster Beat My MacBook?" (https://youtu.be/hGyJTcdfR1E) 

I wanted to test this on my new M1 Mac mini. Then I started to look into Python parallelization and native arm M1 support (there is none for python3 yet). 
So I wrote it in C++. Also implemented a (dumb) prime number checker to test. 

My Mac mini M1 does 100'000 terms for Pi in **850 microseconds** when in parallel mode. For all prime numbers *up to* 1'000'000 it uses **21574 milliseconds**.
