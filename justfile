#!/usr/bin/env just --justfile

default:
    @just --choose

bootstrap:
    #!/usr/bin/env bash
    set -euxo pipefail
    python3 -m venv .venv/
    source .venv/bin/activate
    pip install west
    west init -l config/
    west update
    west zephyr-export
    pip install -r zephyr/scripts/requirements-base.txt

update:
    .venv/bin/west update

build: build-left build-right

build-parallel:
    parallel \
      --jobs 2 \
      --linebuffer \
      --tagstring '{= $_=$job->seq() == 1 ? "\033[34m[L]\033[0m" : "\033[35m[R]\033[0m" =}' \
      ::: \
      'just build-left' \
      'just build-right'

clean:
	rm -r build/

build-left:
	.venv/bin/west build \
	    --pristine \
	    --build-dir=build/left \
	    --board=adv360_left \
	    ../zmk/app \
	    -- \
	    -DZMK_CONFIG="{{justfile_directory()}}/config/"

build-right:
	.venv/bin/west build \
	    --pristine \
	    --build-dir=build/right \
	    --board=adv360_right \
	    ../zmk/app \
	    -- \
	    -DZMK_CONFIG="{{justfile_directory()}}/config/"