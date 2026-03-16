std::cout << "=== Многопоточная обработка матрицы ===" << std::endl;

    MatrixProcessor<int> processor(test_matrix, 3);

    std::cout << "Исходная матрица:" << std::endl;
    processor.print_matrix();

    // Применение функции square
    std::cout << "\n--- Применение функции square ---" << std::endl;
    processor.apply(MatrixProcessor<int>::square);
    processor.print_matrix();

    // Создание новой матрицы для следующей операции
    std::vector<std::vector<int>> another_matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    MatrixProcessor<int> processor2(another_matrix, 2);

    std::cout << "\n--- Применение функции double_value ---" << std::endl;
    std::cout << "Исходная матрица:" << std::endl;
    processor2.print_matrix();

    processor2.apply(MatrixProcessor<int>::double_value);
    processor2.print_matrix();

    return 0;
}
