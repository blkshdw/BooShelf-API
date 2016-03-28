# BooShelf-API
HTTP Server for BooShelf project

# Build

## Requirements
```
RethinkDB
```

```
Boost
```

```
libssl
```

```
libcrypto
```

## Build on Ubuntu:

### Install RethinkDB

```
source /etc/lsb-release && echo "deb http://download.rethinkdb.com/apt $DISTRIB_CODENAME main" | sudo tee /etc/apt/sources.list.d/rethinkdb.list
wget -qO- https://download.rethinkdb.com/apt/pubkey.gpg | sudo apt-key add -
sudo apt-get update
sudo apt-get install rethinkdb
```

### Install Boost
```
sudo apt-get install libboost-all-dev
```

### Install libssl and libcrypto
```
sudo apt-get install libssl-dev libcrypto++-dev
```

## Build & run
```
make
```

## Contributions
```
crow https://github.com/ipkn/crow
```

```
RethinkDB C++ driver https://github.com/AtnNn/librethinkdbxx
```
