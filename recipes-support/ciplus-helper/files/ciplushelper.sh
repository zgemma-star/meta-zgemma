#!/bin/sh
### BEGIN INIT INFO
# Provides:          ciplushelper
# Required-Start:
# Required-Stop:
# Default-Start:     2 3 4 5
# Default-Stop:
# Short-Description: ciplushelper
# Description:
### END INIT INFO

PATH=/sbin:/bin:/usr/sbin:/usr/bin

if [[ -x /usr/bin/ciplushelper && -r /etc/cicert.bin ]]
then
    echo "CiPlus Certificate found "
else
    echo "CiPlus Certificate not installed "
    exit 0
fi

case "$1" in
start)
        echo -n "Running ciplushelper..."
        /usr/bin/ciplushelper
        echo "done."
        ;;
*)
        ;;
esac

exit 0

