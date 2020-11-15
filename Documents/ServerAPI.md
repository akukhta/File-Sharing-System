# Server API description
<h2>1. Connect</h2>
Input parameters: none <br>
Output parameters: connecting status <br>
Connecting to server. Method returns <i>true</i> if connected, otherwise returns <i>false</i> <br>

<h2>2. Account registration </h2>
Input parameters: email, password <br>
Output parameters: session token <br>
A new account registration. Method creates a new user on server and returns session tokken (using for any server operations). <br>

<h2>3. Authorization </h2>
Input parameters: email, password <br>
Output parameters: session token <br>
Method creates a new seans for user on server and returns session tokken (using for any server operations). <br>

<h2>4. Logout </h2>
Input parameters: session's tokken <br>
Output parameters: none <br>
Closes a user's session. <br>

<h2>5. Get list of nodes </h2>
Input parameters: session tokken <br>
Output parameters: list of nodes <br>
Method returns a current user's list of nodes.<br>

<h2>6. Get list of files (doesn't require authorization) </h2>
Input parameters: node ID <br>
Output parameters: list of files <br>
Method returns an inputed node's list of files <br> 

<h2>7. Upload files </h2>
Input parameters: node ID, list of files paths <br>
Output parameters: none <br>
Uploads choose files to the selected node by current node ID <br> 

<h2>8. Delete file from node </h2>
Input parameters: node ID, filename <br>
Output parameters: none <br>
Method deletes a file from node<br> 

<h2>9. Get file info (doesn't require authorization) </h2>
Input parameters: node ID, filename <br>
Output parameters: information about file <br>
Returns information about choosed file <br> 

<h2>10. Create a new node</h2>
Input parameters: session tokken<br>
Output parameters: node ID <br>
Creates a new node on the server. Returns a created node id.<br> 

<h2>11. Download files (doesn't require authorization)</h2>
Input parameters: node ID, list of choosed files<br>
Output parameters: none <br>
Downloads choose files to the user's PC.<br> 

<h2>12. Reset password </h2>
Input parameters: session tokken<br>
Output parameters: temporary password <br>
Resets current user's passoword and returns a new temporary password back to the user<br> 

<h2>13. Disconnect</h2>
Input parameters: none<br>
Output parameters: none <br>
Disconnects from server with/without session closing<br> 


