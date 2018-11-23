# meta-zgemma
BSP layer for Zgemma Star models

*** Setup your build system *** <br />
Install ubuntu/kubuntu 16.04 64bit <br />
To build an AOSP or E2 images you'll need to install the follow packages: <br />
sudo apt install openjdk-8-jdk m4 lib32stdc++6 curl git subversion chrpath gawk g++ texinfo repo android-tools-fsutils python-lunch u-boot-tools <br />

*** How to build E2 image *** <br />
example: Openpli image for model H9 <br />

Build option 1: <br />
cd /opt <br />
git clone https://github.com/OpenPLi/openpli-oe-core.git <br />
cd openpli-oe-core <br />
MACHINE=h9 make <br />
MACHINE=h9 make image <br />

Build option 2: <br />
cd /opt <br />
git clone https://github.com/OpenPLi/openpli-oe-core.git <br />
cd openpli-oe-core <br />
make -f Makefile <br />
cd build <br />
MACHINE=h9 <br />
bitbake -k openpli-enigma2-image <br />

*** How to build AOSP image *** (OFFLINE) <br />
cd /opt <br />
mkdir aosp-build <br />
cd aosp-build <br />
git config --global user.mail "you@example.com" <br />
git config --global user.name "Your Name" <br />
repo init -u https://android.googlesource.com/platform/manifest.git -b android-8.0.0_r4 <br />
repo sync -j8 <br />

git clone https://github.com/zgemma-star/aosp/h9-device device/hisilicon/h9 <br />
git clone https://github.com/zgemma-star/aosp/kernel device/hisilicon/kernel <br />
git clone https://github.com/zgemma-star/aosp/h9-vendor vendor/hisilicon/h9 <br />

source build/envsetup.sh <br />
lunch h9<br />
Choose your build (Venus-eng)<br />
make -j32 bigfish <br />

*** Easy to know *** <br />
Download all the packages before build: bitbake "image" -c fetchall <br />
Build packages without brakedown on an error: bitbake -k "image" <br />
Speed up image build: Use a PC with more Threads, Solid state disk, DDR Memory <br />
Set read/write access for map /opt : sudo chmod 755 -R /opt <br /> <br />
Download direct the branch: -b "branch_name" <br />
example: git clone -b release-6.2 https://github.com/OpenPLi/openpli-oe-core.git <br />
Build image from local enigma2 git<br />
example: git clone https://github.com/OpenPLi/enigma2.git <br />
Adjust enigma2.bb SRC_URI = "git:///opt/enigma2/;branch=${ENIGMA2_BRANCH};protocol=file" <br>