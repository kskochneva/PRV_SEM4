int main() {
    // Логгер для строк
    Logger<std::string> string_logger("string_log.txt");

    // Логгер для чисел
    Logger<int> int_logger("int_log.txt");

    // Логгер для пользовательского класса
    Logger<User> user_logger("user_log.txt");

    std::cout << "=== Запуск потоков логирования ===" << std::endl;

    // Создание потоков для строкового логирования
    std::vector<std::thread> string_threads;
    for (int i = 0; i < 3; ++i) {
        string_threads.push_back(std::thread(worker_thread, std::ref(string_logger), i + 1, 5));
    }

    // Создание потоков для числового логирования
    std::vector<std::thread> int_threads;
    for (int i = 0; i < 2; ++i) {
        int_threads.push_back(std::thread(number_thread, std::ref(int_logger), i + 10, 8));
    }

    // Запуск с detach
    for (auto& t : string_threads) {
        t.detach();
    }
    for (auto& t : int_threads) {
        t.detach();
    }

    // Логирование пользовательского объекта
    User user1("Alice", 30);
    User user2("Bob", 25);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    user_logger.log(user1);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    user_logger.log(user2);

    // Ожидание завершения
    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "\n=== Логирование завершено ===" << std::endl;
    std::cout << "Проверьте файлы: string_log.txt, int_log.txt, user_log.txt" << std::endl;

    return 0;
}
