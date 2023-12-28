FROM docker.io/zmkfirmware/zmk-build-arm:stable

WORKDIR /app

COPY zmk/app/west.yml app/west.yml

# West Init
RUN west init --local app/
# West Update
RUN west update
# West Zephyr export
RUN west zephyr-export

COPY bin/build.sh ./

RUN apt update \
    && apt install -y parallel \
    && rm -rf /var/lib/apt/lists/*

CMD ["./build.sh"]
