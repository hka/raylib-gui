https://emscripten.org/docs/getting_started/downloads.html
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh

cd to the project root:
emcmake cmake -DPLATFORM=Web -S . -B build_html
cmake --build build_html
