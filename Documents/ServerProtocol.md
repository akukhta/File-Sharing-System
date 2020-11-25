# Server communication protocol desctiption

Server based on TCP sockets.<br>For multiplexing "poll" is using. <br><h5> Communications algorithm: <br>
1. Receive packet size (this size garanted will be 4 bytes). <br>
2. Receive packet <br>
3. Use first byte for command recognition(0- Account registration, 1 - authorization ... (see ServerAPI.md)) <br>
4. Run handler function <br>
5. Send answer if needed <br>
The function arguments are taken from the received data packet. <br>
Data packet template: <br>
<i>function descriptor (first byte), argument 1 length, argument 1, ... . </i> <br>
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

<h3>Functions parameters</h3><br>
<h4>Account registration/Authorization:</h4><br>
<img src="AccReg.png" width="600" height = "150" title="Account registration">
<h5>Answer to client:</h5><br>
<img src="AccAnswer1.png" width="600" height = "150" title="Account answer">
<h6>First byte - function ID(0 - registration, 1 - log in). Second byte - an email length. After second byte goes an user's email. After the user's email goes a password's size and after it goes password.If authorization function on server's side returns with some errors: first byte - 0; second byte - error's ID (client's side has a table with errors' description).Otherwise: first byte - 1; byte from 2 to 33 - session token.</h6><br>

<h4>Logout:</h4>
<h6>First byte - 2;<br> 
Bytes from 2 to 33 - session token.<br></h6>
<h5>Answer to client:</h5>
<h6>On success: single byte - 1. <br>
Otherwise: first byte - 0, second byte - error's ID. <br></h6>

<h4>Get list of nodes:</h4>
<h6>First byte - 3;<br>
Bytes from 2 to 33 - session token;<br></h6>
<h5>Answer to client:</h5>
<h6>On success:<br> first byte - 1;<br>second byte - nodes count;<br>After them: (byte of nodes length)(nodes ID).<br>Otherwise:<br> Fist byte - 0;<br>Second byte - error's ID<br></h5>

<h4>Get list of files:</h4>
<h6>First byte - 4;<br>
Bytes from 2 to 33 - node id;<br></h6>
<h5>Answer to client:</h5>
<h6>On success:<br> first byte - 1;<br>second byte - filenames count;<br>After them: (byte of filenames length)(filename).<br>Otherwise:<br> Fist byte - 0;<br>Second byte - error's ID<br></h5>

<h4>Upload files:</h4>
<h6>First byte - 5;<br>
Bytes from 2 to 33 - node id;<br> Byte 34 - files' count;<br>After them: (filename length)(filename)(filesize)(file's buffer) </h6>
<h5>Answer to client:</h5>
<h6>On success: single byte - 1;<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Delete file from node:</h4>
<h6>First byte - 6;<br>
Bytes from 2 to 33 - node id;<br>After it: (filename length)(filename)(32 bytes of session token)</h6>
<h5>Answer to client:</h5>
<h6>On success: single byte - 1;<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Get file info:</h4>
<h6>First byte - 7;<br>
Bytes from 2 to 33 - node id;<br>After it: (filename length)(filename)</h6>
<h5>Answer to client:</h5>
<h6>On success: first byte - 1, after it: (text length)(text)<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Create a new node:</h4>
<h6>First byte - 8;<br>
Bytes from 2 to 33 - session token.<br></h6>
<h5>Answer to client:</h5>
<h6>On success: first byte - 1, bytes from 2 to 33: node ID.<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Download files:</h4>
<h6>First byte - 9;<br>
Bytes from 2 to 33 - session token.(files list size)(files list)(files' buffers)<br></h6>
<h5>Answer to client:</h5>
<h6>On success: single byte - 1.<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Reset password:</h4>
<h6>First byte - 10;<br>
Bytes from 2 to 33 - session token.<br></h6>
<h5>Answer to client:</h5>
<h6>On success: first byte - 1, bytes from 2 to 66: temporary password.<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Rename file:</h4>
<h6>First byte - 11;<br>
(session token)(node ID)(old filename size)(filename)(new filename size)(new filename)<br></h6>
<h5>Answer to client:</h5>
<h6>On success: single byte - 1.<br>Otherwise: first byte - 0, second byte - error's ID.</h5>

<h4>Change password:</h4>
<h6>First byte - 12;<br>
(session token)(old password size1)(old password 1)(old password size 2)(old password 2)(new password size)(new password)<br></h6>
<h5>Answer to client:</h5>
<h6>On success: single byte - 1.<br>Otherwise: first byte - 0, second byte - error's ID.</h5>


