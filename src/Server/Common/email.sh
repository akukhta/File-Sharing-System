#!/bin/bash
# Будет отображаться "От кого"
FROM=FileSharingSystem@gmail.com
# Кому
MAILTO=$1
# Тема письма
NAME=$2
# Тело письма
BODY=$3
echo $1
echo $2
echo $3
# В моем примере я отправляю письма через существующий почтовый ящик на gmail.com 
# Скрипт легко адаптируется для любых почтовых серверов
SMTPSERVER=smtp.gmail.com
# Логин и пароль от учетной записи gmail.com
SMTPLOGIN=example@gmail.com
SMTPPASS=password

# Отправляем письмо
/usr/bin/sendEmail -f $FROM -t $MAILTO -o message-charset=utf-8  -u $NAME -m $BODY -s $SMTPSERVER -o tls=yes -xu $SMTPLOGIN -xp $SMTPPASS
