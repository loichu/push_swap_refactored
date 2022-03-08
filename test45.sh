#!/usr/bin/env bash

ARGS=$(ruby -e "puts (-25..20).to_a.shuffle.join(' ')")
echo $ARGS
./push_swap $ARGS
