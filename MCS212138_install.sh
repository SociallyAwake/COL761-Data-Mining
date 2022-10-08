git clone https://github.com/SociallyAwake/COL761-Data-Mining
cd COL761-Data-Mining/
unzip *.zip
cd HW2_MCS212138
wget https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.zip
unzip boost_1_80_0.zip
cp -r boost_1_80_0/boost ./include/
rm -rf boost_1_80_0 boost_1_80_0.zip