# Server communication protocol desctiption

Server based on sockets.<br>For multiplexing "poll" is using. <br><h5> Communications algorithm: <br>
1. Receive packet size (this size garanted will be 4 bytes). <br>
2. Receive packet <br>
3. Use first byte for command recognition(0- Account registration, 1 - authorization ... (see ServerAPI.md)) <br>
4. Run handler function <br>
5. Send answer if needed <br>
<h6>Example:</h6>
Account registration: <br>
Data size: 29<br>
Data packet (converted to string):<br>
<i>017example@gmail.com8password</i><br>
0 - function descriptor <br>
17 - length of first string parameter <br>
example@gmail.com - user's email <br>
password - user's password <br>
Answer to client:<br>
Data size: 33 <br>
Data packet (converted to string):<br>
<i>1477df96bf4a8dc6c4ffe52f6a5f93860</i><br>
1 - result of operation (if operation failed, after result goes error message with message length) <br>
477df96bf4a8dc6c4ffe52f6a5f93860 - session token <br>
</h5>

