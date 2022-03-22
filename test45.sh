#!/usr/bin/env bash

ARGS=$(ruby -e "puts (-25..20).to_a.shuffle.join(' ')")
#echo $ARGS
#echo -n "count: "
#echo $ARGS | wc -w
#echo -e "PROGRAM START\n=================================\n\n"
./push_swap $ARGS
