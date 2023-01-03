/* mp3 player on linux */
#include <fmt123.h>
#include <mpg123.h>
#include <pulse/def.h>
#include <pulse/simple.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BUFSIZE 1024000
/* #define BUFSIZE 409600 */

int main(int argc, char *argv[]) {
  mpg123_handle *handle;
  /* uint8_t buf[BUFSIZE]; // */
  char buf[BUFSIZE]; //
  if (argc <= 1) {
    fprintf(stderr, "Error!\nThis program requires the path of the mp3 files "
                    "as an argument!\n");
  } else {
    printf("%s\n", argv[1]);
  }

  handle = mpg123_new(NULL, NULL);
  mpg123_open_fixed(handle, argv[1], 2, MPG123_ENC_SIGNED_16);

  size_t decoded = 1;
  /* 从 handle 里读取 bufsize 大小的数据到 buf 中 */
  mpg123_read(handle, buf, BUFSIZE, &decoded);

  pa_simple *s;
  pa_sample_spec ss;

  ss.format = PA_SAMPLE_S16NE;
  ss.channels = 2;
  ss.rate = 44100;

  s = pa_simple_new(NULL, "mp3-player", PA_STREAM_PLAYBACK, NULL, "Audio", &ss,
                    NULL, NULL, NULL);

  while (decoded > 0) {
    mpg123_read(handle, buf, BUFSIZE, &decoded);
    pa_simple_write(s, buf, decoded, NULL);
  }
  /* 播放完毕释放资源 */
  pa_simple_free(s);
  return 0;
}
