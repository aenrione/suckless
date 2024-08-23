#!/usr/bin/env bash

# colors
bg=#2d3139
fg=#D9E0EE
cyan=#89DCEB
green=#ABE9B3
red=#F28FAD
yellow=#FAE3B0
blue=#96CDFB
magenta=#F5C2E7

# Path to custom statusbar snippets
bar_path="$HOME/.local/bin/statusbar/"

## SEP '|'
SEP(){
    sep=$(echo '|')
    echo "^c#6E6C7E^$sep"
}

# Modules

TEMP(){
    temp=$(sensors | grep temp1 | awk 'NR==1 {print $2}' | sed 's/+//g')
    echo -e "^c$red^ ^c$fg^$temp"
}

BAT(){
    bat=$(upower -i `upower -e | grep 'BAT'` | grep 'percentage' | awk 'NR==1 {print $2}' | sed 's/+//g')
    echo -e "^c$green^⚡ ^c$fg^$bat"
}
BAT2(){
  echo -e "$($bar_path/sb-battery)"
}

 UPTIME(){
     uptime=$(uptime --pretty | sed -e 's/up //g' -e 's/ days/d/g' -e 's/ day/d/g' -e 's/ hours/h/g' -e 's/ hour/h/g' -e 's/ minutes/m/g' -e 's/, / /g')
     echo -e "^c$green^ ^c$fg^$uptime"
 }

VOL(){
    vol=$(amixer sget Master | grep 'Right:' | awk -F'[][]' '{print $2}')
    echo -e "^c$yellow^ ^c$fg^ $vol"
}

CPU(){
    cpu=$(top -b -n1 | grep "Cpu(s)" | awk '{print $2 + $4}')
    echo -e "^c$blue^ ^c$fg^$cpu"
}

MEM(){
    mem=$(free -h | awk '/^Mem:/ {print $3 "/" $2}' | sed 's/i//g')
    echo -e "^c$magenta^  ^c$fg^$mem"
}

TIME(){
    time=$(date '+%b %d - %I:%M%p')
    echo -e "^c$cyan^  ^c$fg^$time"
}

TRAFFIC(){
  echo -e "$($bar_path/sb-nettraf)"
}

KB(){
  echo -e " ^c$fg^$($bar_path/sb-kbselect)"
}

ASUSPROFILE(){
  profile=$(asusctl profile -p | grep "Active profile" | awk '{print $4}')
  echo -e "  ^c$fg^$profile"
}

WIFI(){
    ethernet_ip=$(ip a | grep 'inet ' | grep ' enx00e04c6824f6' | awk '{print $2}' | sed 's/\/24//g')
    ip=$(ip a | grep 'inet ' | grep -v ' lo' | awk '{print $2}' | sed 's/\/24//g')
    # limit ip to 1 line
    ip=$(echo $ip | awk '{print $1}')
    wifi=$(iwgetid -r)
    # if ethernet is connected, show ethernet ip
    if [ -n "$ethernet_ip" ]; then
        ip=$ethernet_ip
        wifi="ETH"
    fi
    echo -e "^c$blue^ ^c$fg^ $wifi ($ip)"
}

GPU(){
  gpu=$(supergfxctl -g)
  echo -e " ^c$fg^$gpu"
}

while true; do
    sleep 1 && xsetroot -name " $(SEP) $(WIFI) $(SEP) $(ASUSPROFILE) $(SEP) $(GPU) $(SEP) $(KB) $(SEP) $(VOL) $(SEP) $(CPU)% $(SEP) $(MEM) $(SEP) $(BAT2) $(SEP) $(TIME)"
done
