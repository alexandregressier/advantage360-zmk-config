#!/usr/bin/env bash

set -eu

PWD=$(pwd)
TIMESTAMP="${TIMESTAMP:-$(date -u +"%Y%m%d%H%M")}"
COMMIT="${COMMIT:-$(echo xxxxxx)}"

# West Build (left)
west build \
  --source-dir app/ \
  --build-dir build/left/ \
  --board adv360_left \
  -- \
  -DZMK_CONFIG="${PWD}/config/"

# West Build (right)
west build \
  --source-dir app/ \
  --build-dir build/right/ \
  --board adv360_right \
  -- \
  -DZMK_CONFIG="${PWD}/config/"

# Delete previous firmware files
rm -f firmware/*-{left,right}.uf2

# Rename and copy firmware files
cp build/left/zephyr/zmk.uf2 "./firmware/${TIMESTAMP}-${COMMIT}-left.uf2"
cp build/right/zephyr/zmk.uf2 "./firmware/${TIMESTAMP}-${COMMIT}-right.uf2"
