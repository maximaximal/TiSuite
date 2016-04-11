#!/bin/bash

/opt/chroots/ubuntu_trusty_x64/mount_jenkins.sh

# TiC
# ======

sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "mkdir -p /root/jenkins/workspace/TiSuite/build/tic"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "rm -f /root/jenkins/workspace/TiSuite/build/tic/tic-*"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "cd /root/jenkins/workspace/TiSuite/build/tic/ && cmake ../../TiC -DCPACK_GENERATOR=DEB"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "cd /root/jenkins/workspace/TiSuite/build/tic/ && make"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "cd /root/jenkins/workspace/TiSuite/build/tic/ && make install"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "cd /root/jenkins/workspace/TiSuite/build/tic/ && make package"

echo "Add the package to the repository"
DEB="$(ls /var/lib/jenkins/workspace/TiSuite/build/tic/*deb)"
echo "DEBFILE: $DEB"

while read -r line; do
    cd /media/maximaximal.com/www/repos/apt/ubuntu && sudo reprepro includedeb trusty "$line"
done <<< "$DEB"

# TiEdit
# =======

sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "mkdir -p /root/jenkins/workspace/TiSuite/build/tiedit"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "rm -f /root/jenkins/workspace/TiSuite/build/tiedit/tiedit-*"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "QT_SELECT=qt5 cd /root/jenkins/workspace/TiSuite/build/tiedit/ && cmake ../../TiEditor -DCPACK_GENERATOR=DEB"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "cd /root/jenkins/workspace/TiSuite/build/tiedit/ && make"
sudo chroot /opt/chroots/ubuntu_trusty_x64 /bin/bash -c "cd /root/jenkins/workspace/TiSuite/build/tiedit/ && make package"

echo "Add the package to the repository"
DEB="$(ls /var/lib/jenkins/workspace/TiSuite/build/tiedit/*deb)"
echo "DEBFILE: $DEB"
cd /media/maximaximal.com/www/repos/apt/ubuntu && sudo reprepro includedeb trusty "$DEB"

/opt/chroots/ubuntu_trusty_x64/umount_jenkins.sh
