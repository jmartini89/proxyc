#!/bin/bash

echo $(pgrep -f ./bin/proxy)

lsof -p $(pgrep -f ./bin/proxy)