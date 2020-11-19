# Server communication protocol desctiption

Server based on sockets.<br>For multiplexing "poll" is using. <br><h5> Communications algorithm: <br>
1. Receive packet size (this size garanted will be 4 bytes). <br>
2. Receive packet <br>
3. Use first byte for command recognition(0- Account registration, 1 - authorization ... (see ServerAPI.md)) <br>
4. Run handler function <br>
5. Send answer if needed <br>
</h5>
