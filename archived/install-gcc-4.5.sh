cd /tmp
curl -O http://distfiles.macports.org/MacPorts/MacPorts-1.9.1-10.6-SnowLeopard.dmg
open MacPorts-1.9.1-10.6-SnowLeopard.dmg
read -p "Press any key when you have installed MacPorts"
/opt/local/bin/port install gcc_select
/opt/local/bin/port install gcc45

