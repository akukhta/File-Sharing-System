# Server API description

<h2>1. Account registration </h2>
Input parameters: email, password <br>
Output parameters: session token <br>
Probably errors: incorrect email, incorrect password, email is using<br>
A new account registration. Method creates a new user on server and returns session tokken (using for any server operations). <br>

<h2>2. Authorization </h2>
Input parameters: email, password <br>
Output parameters: session token <br>
Probably errors: wrong email, wrong password <br>
Method creates a new seans for user on server and returns session tokken (using for any server operations). <br>

<h2>3. Logout </h2>
Input parameters: session's token <br>
Output parameters: none <br>
Probably errors: incorrect session token<br>
Closes a user's session. <br>

<h2>4. Get list of nodes </h2>
Input parameters: session token <br>
Output parameters: list of nodes <br>
Probably errors: incorrect session token<br>
Method returns a current user's list of nodes.<br>

<h2>5. Get list of files (doesn't require authorization) </h2>
Input parameters: node ID <br>
Output parameters: list of files <br>
Probably errors: incorrect node ID <br>
Method returns an inputed node's list of files <br> 

<h2>6. Upload files </h2>
Input parameters: node ID, list of files paths, files <br>
Output parameters: none <br>
Probably errors: incorrect node ID, non-existent filename<br>
Uploads choose files to the selected node by current node ID <br> 

<h2>7. Delete file from node </h2>
Input parameters: node ID, filename, sessiong token <br>
Output parameters: none <br>
Probably errors: incorrect node ID, non-existent filename, incorrect session token<br>
Method deletes a file from node<br> 

<h2>8. Get file info (doesn't require authorization) </h2>
Input parameters: node ID, filename <br>
Output parameters: information about file <br>
Probably errors: incorrect node ID, non-existent filename<br>
Returns information about choosed file <br> 

<h2>9. Create a new node</h2>
Input parameters: session token<br>
Output parameters: node ID <br>
Probably errors: incorrect session token<br>
Creates a new node on the server. Returns a created node id.<br> 

<h2>10. Download files (doesn't require authorization)</h2>
Input parameters: node ID, list of choosed files, choosed files<br>
Output parameters: none <br>
Probably errors: incorrect node ID, non-existent filename<br>
Downloads choose files to the user's PC.<br> 

<h2>11. Reset password </h2>
Input parameters: session token<br>
Output parameters: temporary password <br>
Probably errors: incorrect session token<br>
Resets current user's passoword and returns a new temporary password back to the user's email<br> 

<h2>12. Rename file</h2>
Input parameters: session token, node ID, old filename, new filename <br>
Output parameters: none <br>
Probably errors: incorrect session token, incorrect node ID, non-existent filename, existent filename<br>
Renames file<br> 

<h2>13. Change password</h2>
Input parameters: session token, node ID, old filename, new filename <br>
Output parameters: none <br>
Probably errors: incorrect session token, wrong password<br>
Changes user's current pasword<br> 

<h1>Probably errors:</h1>
<h2>1.Incorrect email</h2><br>
The user entered an incorrect email when registering an account. <br>

<h2>2.Incorrect password</h2><br>
Password doesn't meet requirements. <br>

<h2>3.Email is using</h2><br>
The user entered an email address when registering, which is already in use. <br>


<h2>4.Wrong email</h2><br>
The user registered under this mail does not exist <br>

<h2>5.Wrong password</h2><br>
The user entered an invalid password<br>

<h2>6.Incorrect session token</h2><br>
There is no session with such a token or token doesn't match tokens of the node owner<br>

<h2>7.Incorrect node ID</h2><br>
No node with this identifier exists<br>

<h2>8.Non-existent filename</h2><br>
File with this name does not exist<br>

<h2>9.Existent filename</h2><br>
The current node already contains a file with the same filename<br>


