#include <stdio.h>
#include <unistd.h>

void drawWithDocker(const char *dotFile, const char *graphType)
{
  char cmd[400];
  sprintf(cmd, "cat %s | docker run --rm -i nshine/dot dot -T%s > graph.%s", dotFile, graphType, graphType);

  FILE *fp = popen(cmd, "r");
  if (fp == NULL)
  {
    return;
  }

  char output[1024];

  fread(output, 1024, 1, fp);

  pclose(fp);

  return;
}
