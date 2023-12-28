#!/usr/bin/env bash

set -eu

start=$SECONDS

PWD=$(pwd)
TIMESTAMP="${TIMESTAMP:-$(date -u +"%Y%m%d%H%M")}"
COMMIT="${COMMIT:-$(echo xxxxxx)}"

parallel \
  --jobs 2 \
  --linebuffer \
  --tagstring '{= $_=$job->seq() == 1 ? "\033[34m[L]\033[0m" : "\033[35m[R]\033[0m" =}' \
  ::: \
  "west build \
    --source-dir app/ \
    --build-dir build/left/ \
    --board adv360_left \
    -- -DZMK_CONFIG=$PWD/config/ \
  " \
  "west build \
    --source-dir app/ \
    --build-dir build/right/ \
    --board adv360_right \
    -- -DZMK_CONFIG=$PWD/config/ \
  "

# Delete previous firmware files
rm -f firmware/*-{left,right}.uf2

# Rename and copy firmware files
cp build/left/zephyr/zmk.uf2 "./firmware/${TIMESTAMP}-${COMMIT}-left.uf2"
cp build/right/zephyr/zmk.uf2 "./firmware/${TIMESTAMP}-${COMMIT}-right.uf2"

# Print time taken
end=$SECONDS
printf "\nTook %d seconds\n" $((end - start))