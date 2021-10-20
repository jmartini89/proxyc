# TCP Proxy C

### Simple TCP proxy written in C
Handles multiple simultaneous connections towards a specified `address:port`
#
### Compile instructions
```
make
```
simple as that. The binary file is compiled inside `/bin` folder created by `make`
#
### Usage instructions
```
proxyc [destination address] [destination port] [proxy port]
```
Proxy port is optional. Default port is `4242`

Example: `./bin/proxyc 8.8.8.8 22 6969`
#
Use it at your own risk or don't use it at all.