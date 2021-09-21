# v8dmoj [![Build Status](https://ci.dmoj.ca/job/v8dmoj-linux-amd64/badge/icon)](https://ci.dmoj.ca/job/v8dmoj-linux-amd64/)
V8-based JavaScript interpreter for online judging

## Prebuilt Packages

The DMOJ offers prebuilt packages for Debian-based amd64 systems, although the binaries are statically linked.

We offer this as a Debian repository. First, choose the line suited to your distro. (For non-Debian distros, select the closest Debian release):

```
deb [arch=amd64] https://apt.dmoj.ca/ jessie main non-free
deb [arch=amd64] https://apt.dmoj.ca/ stretch main non-free
deb [arch=amd64] https://apt.dmoj.ca/ buster main non-free
```

Then run:

```sh
curl https://dmoj.ca/dmoj-apt.key | sudo apt-key add -
sudo apt update
sudo apt install v8dmoj
```

## Building on Linux

You must have `git`, `gcc`, and GNU `make` installed.

1. Build a v8 monolith by running `./build-monolith`.
2. `mkdir monolith`
3. `tar -C monolith --strip-components=1 -xf <path to monolith built>`
4. `make`
