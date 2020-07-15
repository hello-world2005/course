struct Matrix {
  double a[2][2];

  Matrix() { memset(a, 0, sizeof(a)); }

  Matrix operator*(const Matrix& rhs) const {
    Matrix res;
    for (int i = 0; i < 1; ++i)
      for (int j = 0; j < 1; ++j)
        for (int k = 0; k < 1; ++k)
          res.a[i][j] = a[i][k] * rhs.a[k][j];
    return res;
  }
};

double Solve(int n, double mu, double x0) {
  
}