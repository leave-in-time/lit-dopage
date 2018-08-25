## Install openframeworks

In the pi home : `cd ~`

[https://openframeworks.cc/setup/raspberrypi/](https://openframeworks.cc/setup/raspberrypi/)

## Install ofxOMXPlayer

```
cd ~/of_v0.10.0_linuxarmv6l_release/addons/
git clone https://github.com/jvcleave/ofxOMXPlayer.git
```

## `/etc/fstab` for USB stick

USB stick must be FAT32 and add this at the end of the file.
Should work with any USB stick, if not use `sudo blkid` to get the UUID and use it instead of `/dev/sda1` (e.g. `UUID=E3AB-886E`).

```
/dev/sda1 /media/data       vfat    defaults          0       2
```

## Clone the project

```
cd ~
git clone https://github.com/leave-in-time/lit-dopage.git
```

## Compile and run it

Add the env variables to the `/etc/environment` file (once)

```
MAKEFLAGS=-j4
```

Compile and run (for developement)

```
make
make run
```

## `init.d` script

Copy the following:

```
sudo cp misc/lit-dopage /etc/init.d/
sudo chmod +x /etc/init.d/lit-dopage
sudo update-rc.d lit-dopage defaults
```

This will make the app run at startup
