#!/bin/sh

while :; do ./bash_test.sh; [ ! $? -eq 0 ] && break; done
