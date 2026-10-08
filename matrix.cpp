#include <iostream>

int** alloc_matrix(size_t rows, size_t cols)
{
  int** matrix = nullptr;
  size_t allocated_rows = 0;

  try {
    matrix = new int*[rows];

    for(; allocated_rows < rows; allocated_rows++) {
      matrix[allocated_rows] = new int[cols];
    }
  } catch (...) {
    while(allocated_rows > 0) {
      delete[] matrix[allocated_rows];
    }
    delete[] matrix;
    return nullptr;
  }
  return matrix;
}

void print_matrix(int** matrix, size_t rows, size_t cols) {
  for(size_t i = 0; i < rows; i++) {
    for(size_t j = 0; j < cols; j++) {
      std::cout<<matrix[i][j]<<" ";
    }
    std::cout<<"\n";
  }
}

bool input_matrix(int** matrix, size_t rows, size_t cols) {
  int n = 0;
  for(size_t i = 0; i < rows; i++) {
    for(size_t j = 0; j < cols; j++) {
      if(std::cin>>n) {
        matrix[i][j] = n;
      } else return false;
    }
  }
  return true;
}

void delete_matrix(int** matrix, size_t rows) {
  for(size_t i = 0; i < rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int** transpose(int** t_matrix, int** matrix, size_t rows, size_t cols) {
  for(size_t i = 0; i < rows; i++) {
    for(size_t j = 0; j < cols; j++) {
      t_matrix[j][i] = matrix[i][j];
    }
  }
  return t_matrix;
}

int main()
{
  size_t rows = 0, cols = 0;
  
  if(!(std::cin>>rows >> cols)) {
    return 1;
  }
  if (rows == 0 || cols == 0) {
    return 1;
  }

  int** matrix = alloc_matrix(rows, cols);

  if(matrix == nullptr) {
    return 2;
  }

  if(!(input_matrix(matrix, rows, cols))) {
    delete_matrix(matrix, rows);  
    return 1;
  }

  int** t_matrix = alloc_matrix(cols, rows);

  if(t_matrix == nullptr) {
    return 2;
  }
  
  t_matrix = transpose(t_matrix, matrix, rows, cols);
  
  print_matrix(t_matrix, cols, rows);

  delete_matrix(matrix, rows);
  delete_matrix(t_matrix, cols);
  
  return 0;
}

