set files=src/main.cpp src/SpawnPlanets.cpp src/Game/Game.cpp src/Entity/Entity.cpp src/Player/Player.cpp

set preloaded_assets=--preload-file assets

em++ -o build/web/index.html %files% %preloaded_assets% -std=c++17 -Wno-c++11-narrowing -Os -Wall ./lib/libraylib.web.a -I. -I include/ -L. -L lib/ -s USE_GLFW=3 --shell-file build/web/shell.html -DPLATFORM_WEB