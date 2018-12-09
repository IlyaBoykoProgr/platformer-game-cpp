#include<cstdlib>
#include<fstream>

int main(){
setlocale(LC_ALL, "rus");

 ofstream fout.open(/home/pi/.config/lxpanel/LXDE-pi/panels/panel);

 fout<<"
Global {\n
  edge=bottom\n
  allign=left\n
  margin=0\n
  widthtype=percent\n
  width=100\n
  height=62\n
  transparent=1\n
  tintcolor=#ffffff\n
  alpha=0\n
  autohide=0\n
  heightwhenhidden=10\n
  setdocktype=1\n
  setpartialstrut=1\n
  usefontcolor=1\n
  fontsize=20\n
  fontcolor=#ffffff\n
  usefontsize=1\n
  background=0\n
  backgroundfile=/usr/share/lxpanel/images/xkb-flags/ru.png\n
  iconsize=62\n
  align=left\n
  monitor=-1\n
}\n
Plugin {\n
  type=menu\n
  Config {\n
    image=/usr/share/raspberrypi-artwork/launch.png\n
    system {\n
    }\n
    separator {\n
    }\n
    item {\n
      name=Выполнить\n
      image=system-run\n
      command=run\n
    }\n
    separator {\n
    }\n
    item {\n
      name=Завершение работы\n
      image=system-shutdown\n
      command=logout\n
    }\n
  }\n
}\n
Plugin {\n
  type=launchbar\n
  Config {\n
    Button {\n
      id=chromium-browser.desktop\n
    }\n
    Button {\n
      id=pcmanfm.desktop\n
    }\n
    Button {\n
      id=lxterminal.desktop\n
    }\n
  }\n
}\n
Plugin {\n
  type=taskbar\n
  expand=1\n
  Config {\n
    tooltips=1\n
    IconsOnly=0\n
    ShowAllDesks=-1\n
    UseMouseWheel=-1\n
    UseUrgencyHint=-1\n
    FlatButton=0\n
    MaxTaskWidth=1000\n
    spacing=1\n
    GroupedTasks=0\n
    UseSmallerIcons=-1\n
    DisableUpscale=0\n
    SameMonitorOnly=0\n
  }\n
}\n
Plugin {\n
  type=bluetooth\n
  Config {\n
  }\n
}\n
Plugin {\n
  type=dhcpcdui\n
  Config {\n
  }\n
}\n
Plugin {\n
  type=volumealsa\n
  Config {\n
  }\n
}\n
Plugin {\n
  type=dclock\n
  Config {\n
    ClockFmt=%R\n
    TooltipFmt=%A %x\n
    BoldFont=0\n
    IconOnly=0\n
    CenterText=1\n
  }\n
}\n
Plugin {\n
  type=xkb\n
  Config {\n
    Model=pc105\n
    LayoutsList=us,ru\n
    VariantsList=,\n
    ToggleOpt=grp:alt_shift_toggle\n
    KeepSysLayouts=0\n
    NoResetOpt=1\n
    PerWinLayout=1\n
    DisplayType=0\n
    FlagSize=2\n
  }\n
}\n
Plugin {\n
  type=thermal\n
  Config {\n
    NormalColor=#00ff01\n
    Warning1Color=#fff000\n
    Warning2Color=#ff0000\n
    AutomaticLevels=0\n
    Warning1Temp=55\n
    Warning2Temp=60\n
    AutomaticSensor=1\n
  }\n
}\n
Plugin {\n
  type=cpu\n
  Config {\n
    ShowPercent=1\n
    Foreground=#5f64ffff0000\n
    Background=#ffffffffffff\n
  }\n
}\n
Plugin {\n
  type=ejecter\n
  Config {\n
  }\n
}\n

}";
fout.close();
system("sudo reboot");
}
