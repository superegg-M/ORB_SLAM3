echo "Configuring and building my code ..."

cd /home/superegg/slam/ORB_SLAM3/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4 -o mono_euroc
