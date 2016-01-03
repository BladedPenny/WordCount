#!/bin/bash
wc test1.txt test2.txt test3.txt > real-wc.txt
wc209 test1.txt test2.txt test3.txt > wc_209.txt
diff -u -w real-wc.txt wc_209.txt
