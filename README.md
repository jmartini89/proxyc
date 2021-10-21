# TCP Proxy C

### Simple TCP proxy written in C
Handles multiple simultaneous connections towards a specified `address:port`
#
### Compile instructions
```
make
```
Simple as that. The binary file is compiled inside `/bin` folder created by `make`
#
### Usage instructions
```
proxyc [destination address] [destination port] [proxy listening port]
```

Example: `./bin/proxyc 127.0.0.1 22 6969`
#
Use it at your own risk or don't use it at all.