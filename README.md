# meta-zgemma
BSP layer for Zgemma Star models

*** Setup your build system ***
Install ubuntu/kubuntu 16.04 64bit
To build an AOSP or E2 images you'll need to install the follow packages:
sudo apt install openjdk-8-jdk m4 lib32stdc++6 curl git subversion chrpath gawk g++ texinfo repo


*** How to build E2 image ***
example: Openpli image for model H9

Build option 1:
cd /opt/
git clone https://github.com/OpenPLi/openpli-oe-core.git
cd openpli-oe-core
MACHINE=h9 make
MACHINE=h9 make image

Build option 2:
cd /opt/
git clone https://github.com/OpenPLi/openpli-oe-core.git
cd openpli-oe-core
make -f Makefile
cd build
MACHINE=h9
bitbake -k openpli-enigma2-image


*** How to build AOSP image *** (OFFLINE)
cd /opt/
mkdir aosp-build
cd aosp-build
git config --global user.mail "you@example.com"
git config --global user.name "Your Name"
repo init -u https://android.googlesource.com/platform/manifest.git -b android-8.1.0_r9
repo sync -j8

git clone https://github.com/zgemma-star/aosp/h9-device device/hisilicon/h9
git clone https://github.com/zgemma-star/aosp/kernel device/hisilicon/kernel
git clone https://github.com/zgemma-star/aosp/h9-vendor vendor/hisilicon/h9

source build/envsetup.sh
lunch h9-eng
make -j8
make bootimage -j8


*** Easy to know ***
Download all the packages before build: bitbake "image" -c fetchall
Build packages without brakedown on an error: bitbake -k "image"
Speed up image build: Use a PC with more Threads, Solid state disk, DDR Memory
Download direct the branch: -b "branch_name"
example: git clone -b release-6.1 https://github.com/OpenPLi/openpli-oe-core.git
Set read/write access for map /opt : sudo chmod 755 -R /opt
