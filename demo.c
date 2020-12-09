#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <svm.h>
#include <time.h>

struct svm_problem gen_data(int num) {
  double *Y = (double *)malloc(sizeof(double) * num);
  struct svm_node **X = (struct svm_node **)malloc(sizeof(struct svm_node *));
  struct svm_problem p;
  for (int i = 0; i < num; i++) {
    double x = rand() % 10;
    double y = rand() % 10;
    struct svm_node *nodes =
        (struct svm_node *)malloc(sizeof(struct svm_node) * 3);
    nodes[0].index = 1;
    nodes[0].value = x;
    nodes[1].index = 2;
    nodes[1].value = y;
    nodes[2].index = -1;
    X[i] = nodes;
    Y[i] = y > x ? 1 : -1;
  }
  p.l = num;
  p.x = X;
  p.y = Y;
  return p;
}

void plot(const struct svm_problem *prob) {
  int fig[10][10] = {0};

  for (int i = 0; i < prob->l; i++) {
    int x1 = prob->x[i][0].value;
    int x2 = prob->x[i][1].value;
    int y = prob->y[i];
    fig[x1][x2] = y == 1 ? '+' : '-';
  }

  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {
      if (fig[x][y]) {
        putchar(fig[x][y]);
      } else {
        putchar(' ');
      }
    }
    putchar('\n');
  }
}

int main(void) {
  srand(time(0));
  struct svm_problem prob = gen_data(100);
  struct svm_parameter param;

  // default values
  param.svm_type = C_SVC;
  param.kernel_type = RBF;
  param.degree = 3;
  param.gamma = 2;
  param.coef0 = 0;
  param.nu = 0.5;
  param.cache_size = 100;
  param.C = 1;
  param.eps = 1e-3;
  param.p = 0.1;
  param.shrinking = 1;
  param.probability = 0;
  param.nr_weight = 0;
  param.weight_label = NULL;
  param.weight = NULL;

  const char *error_msg = svm_check_parameter(&prob, &param);

  if (error_msg) {
    fprintf(stderr, "ERROR: %s\n", error_msg);
    exit(1);
  }

  plot(&prob);

  struct svm_model *model = svm_train(&prob, &param);

  // plot the model

  struct svm_node test_nodes[3];
  double result;
  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {
      test_nodes[0].index = 1;
      test_nodes[0].value = x;
      test_nodes[1].index = 2;
      test_nodes[1].value = y;
      test_nodes[2].index = -1;
      result = svm_predict(model, test_nodes);
      printf("%c", result == 1 ? '+' : '-');
    }
    printf("\n");
  }

  return 0;
}
