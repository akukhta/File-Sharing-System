#!/bin/bash
FROM=FileSharingSystem@gmail.com
MAILTO=$1
NAME=$2
BODY=$3
SMTPSERVER=smtp.gmail.com
SMTPLOGIN=example@gmail.com
SMTPPASS=password

/usr/bin/sendEmail -f $FROM -t $MAILTO -o message-charset=utf-8  -u $NAME -m $BODY -s $SMTPSERVER -o tls=yes -xu $SMTPLOGIN -xp $SMTPPASS
