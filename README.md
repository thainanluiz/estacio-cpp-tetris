# estacio-cpp-tetris

gcc src/main.c -o bin/tetris.exe -Ilibs/include -Llibs/lib \
  -lallegro -lallegro_image -lallegro_font \
  -lallegro_ttf -lallegro_primitives
