#! /bin/bash 

function run {
 if ! pgrep $1 ;
  then
    $@&
  fi
}

run "pamac-tray"
run "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1"
run "synergy"

picom -b  --config ~/.config/arco-dwm/picom.conf &
nitrogen --restore &
dwmblocks &
