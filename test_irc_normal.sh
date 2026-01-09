#!/bin/bash

SERVER=127.0.0.1
PORT=6667
PASS=irc2026

tmux new-session -d -s irc_test

# Alice
tmux new-window -t irc_test -n Alice
tmux send-keys -t irc_test:Alice "irssi" C-m
sleep 3
tmux send-keys -t irc_test:Alice "/connect $SERVER $PORT $PASS" C-m
sleep 3

tmux send-keys -t irc_test:Alice "/nick Alice" C-m
sleep 3

tmux send-keys -t irc_test:Alice "/quote USER alice 0 * :Alice User" C-m
sleep 3

tmux send-keys -t irc_test:Alice "/join #room1" C-m
sleep 3


# Bob
tmux new-window -t irc_test -n Bob
tmux send-keys -t irc_test:Bob "irssi" C-m
sleep 3
tmux send-keys -t irc_test:Bob "/connect $SERVER $PORT $PASS" C-m
sleep 3

tmux send-keys -t irc_test:Bob "/nick Bob" C-m
sleep 3

tmux send-keys -t irc_test:Bob "/quote USER bob 0 * :Bob User" C-m
sleep 3

tmux send-keys -t irc_test:Bob "/join #room1" C-m
sleep 3


# Carol
tmux new-window -t irc_test -n Carol
tmux send-keys -t irc_test:Carol "irssi" C-m
sleep 3
tmux send-keys -t irc_test:Carol "/connect $SERVER $PORT $PASS" C-m
sleep 3

tmux send-keys -t irc_test:Carol "/nick Carol" C-m
sleep 3

tmux send-keys -t irc_test:Carol "/quote USER carol 0 * :Carol User" C-m
sleep 3

tmux send-keys -t irc_test:Carol "/join #room2" C-m
sleep 3


# Dave
tmux new-window -t irc_test -n Dave
tmux send-keys -t irc_test:Dave "irssi" C-m
sleep 3
tmux send-keys -t irc_test:Dave "/connect $SERVER $PORT $PASS" C-m
sleep 3

tmux send-keys -t irc_test:Dave "/nick Dave" C-m
sleep 3

tmux send-keys -t irc_test:Dave "/quote USER dave 0 * :Dave User" C-m
sleep 3

tmux send-keys -t irc_test:Dave "/join #room1" C-m


sleep 5

# === OPERATIONS ===

# Alice sets topic
tmux send-keys -t irc_test:Alice "/topic #room1 :Welcome to Room 1" C-m
sleep 3

# Bob sends message
tmux send-keys -t irc_test:Bob "/msg #room1 Hello everyone!" C-m
sleep 3

# Dave sends private message to Alice
tmux send-keys -t irc_test:Dave "/msg Alice Hi Alice!" C-m
sleep 3

# Alice gives op to Bob
tmux send-keys -t irc_test:Alice "/quote MODE #room1 +o Bob" C-m
sleep 3

# Bob sets channel limit
tmux send-keys -t irc_test:Bob "/quote MODE #room1 +l 5" C-m
sleep 3

# Carol tries to join full channel
tmux send-keys -t irc_test:Carol "/join #room1" C-m
sleep 3

# Alice removes limit
tmux send-keys -t irc_test:Alice "/quote MODE #room1 -l" C-m
sleep 3

# Carol joins successfully
tmux send-keys -t irc_test:Carol "/join #room1" C-m
sleep 3

# NOTICE test
tmux send-keys -t irc_test:Bob "/notice #room1 This is a NOTICE" C-m
sleep 3

# Private NOTICE
tmux send-keys -t irc_test:Carol "/notice Alice Hi Alice (notice)" C-m
sleep 3

# Dave parts
tmux send-keys -t irc_test:Dave "/part #room1 :Goodbye" C-m
sleep 3

# Alice quits
tmux send-keys -t irc_test:Alice "/quit :Server test done" C-m
sleep 3

tmux attach -t irc_test

sleep 10
# Kill all tmux windows
tmux kill-session -t irc_test