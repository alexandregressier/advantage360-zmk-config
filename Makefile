DOCKER := $(shell { command -v podman || command -v docker; })
TIMESTAMP := $(shell date -u +"%Y%m%d%H%M")
COMMIT := $(shell git rev-parse --short HEAD 2>/dev/null)
detected_OS := $(shell uname)  # Classify UNIX OS
ifeq ($(strip $(detected_OS)),Darwin) #We only care if it's OS X
SELINUX1 :=
SELINUX2 :=
else
SELINUX1 := :z
SELINUX2 := ,z
endif

.PHONY: all clean

all:
	set -eu
	$(shell bin/get_version.sh >> /dev/null)
	$(DOCKER) build --tag adv360-zmk --file Dockerfile .
	$(DOCKER) run --rm -it --name zmk \
		--volume $(PWD)/firmware:/app/firmware$(SELINUX1) \
		--volume $(PWD)/config:/app/config:ro$(SELINUX2) \
		--volume $(PWD)/zmk/app:/app/app:ro$(SELINUX2) \
		--env TIMESTAMP=$(TIMESTAMP) \
		--env COMMIT=$(COMMIT) \
		adv360-zmk

clean:
	set -eu
	rm -f firmware/*.uf2
	$(DOCKER) image rm zmk docker.io/zmkfirmware/zmk-build-arm:stable
