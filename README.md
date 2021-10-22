# TCP Proxy C

### Simple TCP proxy & process daemonizer written in C
Handles multiple simultaneous connections towards a specified `address:port`<br />
Optionally executes a system service when activity is detected on the listening port

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
Example `./bin/proxyc 127.0.0.1 22 6969`

#
### Special features
That's not all!<br />
There's a few more optional accepted arguments
```
[inactivity timeout] [systemd service name]
```
Example `./bin/proxyc 127.0.0.1 22 6969 15 magic_server.service`<br />
* `inactivity timeout` is a timer in **minutes**<br />
starts at last client disconnection, at goal closes `systemd service name` (if it was started)<br />
* `systemd service name` is a systemd service name<br />
it's executed through `systemctl` when activity is detected on `proxy listening port` and no client is connected at the moment

#
### Compatibility
* Written and tested on Linux using the GNU C Library
* Behaviour with BSD Library is undefined

#
### Why?
Why not! Fun little project to learn a lot about TCP and sockets.<br />
I was searching for something like this. A friend suggested to write it myself and here we are.<br />
It's intended to be used as a daemonized process on a headless server: no more wasted power, run those processes only when *actually* needed! Very eco-friendly if you ask me!<br />
It patiently waits for a user to show up, then gently executes the process the client was asking for, forwarding the connection<br />
*MAGIC*

#
### Disclaimer
Use it at your own risk or don't use it at all